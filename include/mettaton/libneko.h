#pragma once

#include <string>
namespace nekolib
{
    struct NekoStore;
    struct Neko;
    /**
     * @brief Writes nekos in the given file.
     *
     * @param filename: where to store the nekos
     * @param url: where to fetch the nekos from
     * @return either success or failure
     */
    int save_nekos(std::string filename, std::string url);
} // namespace nekolib