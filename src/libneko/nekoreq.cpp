#include "nekoreq.hpp"

#include <cstdlib>
#include <curl/curl.h>
#include <curl/easy.h>
#include <dpp/nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include <string>

#include "mettaton/libneko.h"

namespace nekolib
{
    using json = nlohmann::json;

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

        json serialized;
        // serialized << *store;
        nlohmann::to_json(serialized, static_cast<NekoStore&>(*store));

        ostr << serialized;
        return 0;
    }

    // std::ofstream ostr(filename);
    // fetch_nekos(ostr, url.c_str());
    // ostr.close();

    // std::ifstream istr(filename);

    // json json = store;
    // json["id_next"] = 0UL;
    // try
    // {
    //     json["nekos"] = json::parse(istr);
    // }
    // catch (const json::parse_error& e)
    // {
    //     std::cerr << e.what() << std::endl;
    //     return 1;
    // }
    // istr.close();

    // ostr = std::ofstream(filename);
    // ostr << json;
    // ostr.close();

    // return 0;

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
