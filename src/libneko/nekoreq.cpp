#include "nekoreq.hh"

#include <curl/curl.h>
#include <curl/easy.h>
#include <fstream>
#include <iostream>
#include <nlohmann/detail/exceptions.hpp>
#include <nlohmann/json.hpp>
#include <string>

namespace nekolib
{
    using json = nlohmann::json;

    /**
     * @brief Callback function for curl GET at neko source.
     *
     * @param data The data to be written
     * @param ostr The stream in which data will be written
     */
    static void write_nekos(char* data, size_t size, size_t nmemb,
                            std::ofstream* ostr)
    {
        ostr->write(data, size * nmemb);
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

            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_nekos);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &ostr);

            curl_easy_perform(curl);
            curl_easy_cleanup(curl);
        }
        return 0;
    }

    int save_nekos(std::string filename, std::string url)
    {
        std::ofstream ostr(filename);
        fetch_nekos(ostr, url.c_str());
        ostr.close();

        std::ifstream istr(filename);

        json json;
        json["id_next"] = 0;
        try
        {
            json["nekos"] = json::parse(istr);
        }
        catch (const json::parse_error& e)
        {
            std::cerr << e.what() << std::endl;
            return 1;
        }
        istr.close();

        ostr = std::ofstream(filename);
        ostr << json;
        ostr.close();

        return 0;
    }
} // namespace nekolib
