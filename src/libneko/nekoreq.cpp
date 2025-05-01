#include "nekoreq.hpp"

#include <algorithm>
#include <curl/curl.h>
#include <curl/easy.h>
#include <exception>
#include <format>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <json/json.hpp>
#include <mettaton/libneko.h>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace nekolib
{
    using json = nlohmann::json;

    void to_json(json& j, const NekoStoreImpl& p)
    {
        std::vector<NekoImpl> v;
        for (auto ptr = p.nekos.begin(); ptr != p.nekos.end(); ptr++)
        {
            const NekoImpl& cast = static_cast<const NekoImpl&>(*ptr);
            v.push_back(cast);
        }
        j = json{ { "id_next", p.id_next }, { "nekos", v } };
    }

    void from_json(const json& j, NekoStoreImpl& p)
    {
        j.at("id_next").get_to<size_t>(p.id_next);

        std::vector<NekoImpl> v;
        j.at("nekos").get_to<std::vector<NekoImpl>>(v);
        for (auto ptr = v.begin(); ptr != v.end(); ptr++)
        {
            p.nekos.push_back(dynamic_cast<Neko&>(*ptr));
        }
    }

    std::ostream& operator<<(std::ostream& ostr, const Neko& neko)
    {
        const NekoImpl& impl = static_cast<const NekoImpl&>(neko);
        json json = impl;
        ostr << std::setw(4) << json;

        return ostr;
    }
    std::ostream& operator<<(std::ostream& ostr, const NekoStore& store)
    {
        const NekoStoreImpl& impl = static_cast<const NekoStoreImpl&>(store);
        json json = impl;
        ostr << std::setw(4) << json;

        return ostr;
    }

    void save_nekos(NekoStore* store, std::string filename)
    {
        NekoStoreImpl* impl = dynamic_cast<NekoStoreImpl*>(store);
        save_nekos_impl(impl, filename);
    }

    void load_nekos(NekoStore* store, std::string filename)
    {
        NekoStoreImpl* impl = dynamic_cast<NekoStoreImpl*>(store);
        load_nekos_impl(impl, filename);
    }

    Neko& get_neko(NekoStore* store)
    {
        NekoStoreImpl* impl = dynamic_cast<NekoStoreImpl*>(store);
        return get_neko_impl(impl);
    }

    NekoStore* make_store()
    {
        NekoStoreImpl* store = new NekoStoreImpl;
        return dynamic_cast<NekoStore*>(store);
    }

    void save_nekos_impl(NekoStoreImpl* store, std::string filename)
    {
        std::ofstream ostr(filename);
        json serialized = *store;
        ostr << std::setw(4) << serialized;
        ostr.close();
    }

    void load_nekos_impl(NekoStoreImpl* store, std::string filename)
    {
        std::ifstream istr(filename);
        json json;
        try
        {
            json = json::parse(istr);
            istr.close();
            json.get_to<NekoStoreImpl&>(*store);
        }
        catch (const json::parse_error& e)
        {
            throw e;
        }
    }

    static size_t write_callback(char* data, size_t size, size_t nmemb,
                                 std::ostream* ostr)
    {
        ostr->write(data, size * nmemb);
        return size * nmemb;
    }

    /**
     * @brief Constructs a cURL-able url from environment variables
     */
    static std::string format_url()
    {
        const char* neko_source = std::getenv("NEKOS_SOURCE");
        const char* neko_batch = std::getenv("NEKO_BATCH");

        std::string url = std::format("{}?limit={}", std::string(neko_source),
                                      std::string(neko_batch));
        return url;
    }
    /**
     * @brief Fetch nekos from the source and fills the store. Synchronized
     */
    static void fetch_nekos(NekoStoreImpl* store)
    {
        std::string url = format_url();
        CURL* curl = curl_easy_init();
        std::stringstream sstr;
        if (curl != nullptr)
        {
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &sstr);

            curl_easy_perform(curl);
            curl_easy_cleanup(curl);

            json j = json::parse(sstr);
            std::vector<NekoImpl> v;
            j.get_to<std::vector<NekoImpl>>(v);

            store->nekos.clear();
            store->id_next = 0;

            for (auto ptr = v.begin(); ptr != v.end(); ptr++)
            {
                store->nekos.push_back(static_cast<Neko>(*ptr));
            }
        }
    }

    Neko& get_neko_impl(NekoStoreImpl* store)
    {
        const char* neko_store = std::getenv("NEKO_STORE_LOC");

        if (store->id_next < store->nekos.size())
        {
            return store->nekos[store->id_next++];
        }

        std::ifstream istr(neko_store);
        try
        {
            load_nekos_impl(store, neko_store);
            istr.close();

            if (store->id_next >= store->nekos.size())
            {
                /// ADD LOGGING
                istr.close();
                fetch_nekos(store);
                save_nekos_impl(store, neko_store);
            }
        }
        catch (const json::parse_error& e)
        {
            /// ADD LOGGING
            istr.close();
            fetch_nekos(store);
            save_nekos_impl(store, neko_store);
        }
        return store->nekos[store->id_next++];
    }
} // namespace nekolib
