#include "nekoreq.hh"

#include <curl/curl.h>
#include <curl/easy.h>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

const char* NEKO_SOURCE = std::getenv("NEKOS_SOURCE");
const char* NEKO_STORE = std::getenv("NEKO_STORE");

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

int fetch_nekos(std::istream& istr)
{
    CURL* curl = curl_easy_init();
    if (curl != nullptr)
    {
        curl_easy_setopt(curl, CURLOPT_URL, NEKO_SOURCE);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_nekos);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &istr);

        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    return 0;
}

nlohmann::json load_nekos(std::string filename)
{
    std::ifstream istr(NEKO_STORE);
    if (!istr.is_open())
    {
        std::cerr << "Could not open neko store '" << NEKO_STORE << "'.\n";
    }
    istr.close();
    return 0;
}
