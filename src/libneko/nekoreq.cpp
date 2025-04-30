#include "nekoreq.hpp"

#include <cstdlib>
#include <curl/curl.h>
#include <curl/easy.h>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

#include "mettaton/libneko.h"

namespace nekolib
{
    using json = nlohmann::json;

    void to_json(json& j, const NekoStoreImpl& p)
    {
        std::vector<NekoImpl> v;
        for (auto ptr = p.nekos.begin(); ptr != p.nekos.end(); ptr++)
        {
            v.push_back(dynamic_cast<const NekoImpl&>(*ptr));
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

    int save_nekos(NekoStore* store, std::string filename)
    {
        NekoStoreImpl* impl = dynamic_cast<NekoStoreImpl*>(store);
        return save_nekos_impl(impl, filename);
    }

    int load_nekos(NekoStore* store, std::string filename)
    {
        NekoStoreImpl* impl = dynamic_cast<NekoStoreImpl*>(store);
        return save_nekos_impl(impl, filename);
    }

    std::string get_neko(NekoStore* store)
    {
        NekoStoreImpl* impl = dynamic_cast<NekoStoreImpl*>(store);
        return get_neko_impl(impl);
    }

    /**
     * @brief Fetch nekos from the source
     *
     * @param istr
     * @return int
     */
    static int fetch_nekos(std::ostream& ostr, const char* url)
    {
        CURL* curl = curl_easy_init();
        if (curl != nullptr)
        {
            curl_easy_setopt(curl, CURLOPT_URL, url);

            curl_easy_setopt(
                curl, CURLOPT_WRITEFUNCTION,
                [](char* data, size_t size, size_t nmemb, std::ofstream* ostr) {
                    ostr->write(data, size * nmemb);
                });
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &ostr);

            curl_easy_perform(curl);
            curl_easy_cleanup(curl);
        }
        return 0;
    }

    NekoStore* make_store()
    {
        NekoStoreImpl* store = new NekoStoreImpl;
        const char* store_loc = std::getenv("NEKO_STORE_LOC");
        const char* neko_source = std::getenv("NEKOS_SOURCE");
        if (store_loc == nullptr || neko_source == nullptr)
        {
            return nullptr;
        }
        std::ofstream ostr(store_loc);
        fetch_nekos(ostr, neko_source);
        save_nekos_impl(store, store_loc);
        return dynamic_cast<NekoStore*>(store);
    }

    int save_nekos_impl(NekoStoreImpl* store, std::string filename)
    {
        std::ofstream ostr(filename);
        if (!ostr.is_open())
        {
            return 1;
        }

        json serialized = *store;
        ostr << serialized;
        return 0;
    }

    int load_nekos_impl(NekoStoreImpl* store, std::string filename)
    {
        std::ifstream istr(filename);
        json json;
        int status = 0;
        try
        {
            json = json::parse(istr);
        }
        catch (const json::parse_error& e)
        {
            std::cerr << e.what() << std::endl;
            status = 1;
        }
        istr.close();
        json.get_to<NekoStoreImpl&>(*store);
        // json.get_to<NekoStore>(static_cast<NekoStore>(*store));
        return status;
    }

    std::string get_neko_impl(NekoStoreImpl* store)
    {
        if (store->id_next >= store->nekos.size())
        {
            /// TODO: reached the end of the buffer, refill the store in nekos
        }
        else
        {
            return store->nekos[store->id_next++].url;
        }
        return 0;
    }
} // namespace nekolib
