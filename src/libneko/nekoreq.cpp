#include "nekoreq.hpp"

#include <curl/curl.h>
#include <curl/easy.h>
#include <format>
#include <fstream>
#include <iostream>
#include <json/json.hpp>
#include <mettaton/libneko.h>
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

    int save_nekos(NekoStore* store, std::string filename)
    {
        NekoStoreImpl* impl = dynamic_cast<NekoStoreImpl*>(store);
        return save_nekos_impl(impl, filename);
    }

    int load_nekos(NekoStore* store, std::string filename)
    {
        NekoStoreImpl* impl = dynamic_cast<NekoStoreImpl*>(store);
        return load_nekos_impl(impl, filename);
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

    NekoStoreImpl::~NekoStoreImpl()
    {}

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
        return status;
    }

    static size_t write_callback(char* data, size_t size, size_t nmemb,
                                 std::ostream* ostr)
    {
        ostr->write(data, size * nmemb);
        return size * nmemb;
    }
    /**
     * @brief Fetch nekos from the source
     *
     * @param istr
     * @return int
     */
    static int fetch_nekos(std::ostream& ostr, std::string url)
    {
        CURL* curl = curl_easy_init();
        if (curl != nullptr)
        {
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &ostr);

            curl_easy_perform(curl);
            curl_easy_cleanup(curl);
        }
        return 0;
    }

    /**
     * @brief Constructs a cURL-able url from envvars
     */
    static std::string format_url()
    {
        const char* neko_source = std::getenv("NEKOS_SOURCE");
        const char* neko_batch = std::getenv("NEKO_BATCH");

        std::string url = std::format("{}?limit={}", std::string(neko_source),
                                      std::string(neko_batch));
        return url;
    }

    Neko& get_neko_impl(NekoStoreImpl* store)
    {
        if (store->id_next >= store->nekos.size())
        {
            const char* neko_store = std::getenv("NEKO_STORE_LOC");

            std::ofstream ostr(neko_store);
            ostr << "{ \"id_next\": 0, \"nekos\": ";
            std::string url = format_url();
            fetch_nekos(ostr, url);
            ostr << " }";
            ostr.close();

            load_nekos_impl(store, neko_store);
        }
        return store->nekos[store->id_next++];
    }
} // namespace nekolib
