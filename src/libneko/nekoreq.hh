#pragma once

#include <string>

/**
 * @brief Fetch nekos from the API and puts the raw result into the stream
 */
int fetch_nekos(std::istream& istr);

/**
 * @brief Loads nekos from disk. Fills it if necessary
 */

int load_nekos(std::string filename, int* json);