#pragma once

#include <curl/curl.h>
#include <json/json.h>
#include <string>

/**
 * @brief Load nekos URL from disk
 */
void load_nekos(std::string filename, int* json_out);

/**
 * @brief Write nekos from json to ostr
 */
void write_nekos(int* json, std::string filename);