#include "nekoreq.hh"

#include <curl/curl.h>
#include <curl/easy.h>

void load_nekos(std::string filename, int* json_out)
{
    CURL* curl = curl_easy_init();
}
void write_nekos(int* json, std::string filename)
{}