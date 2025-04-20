#pragma once

#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>
#include <string>
#include <vector>

namespace nekolib
{
    struct NekoStore
    {
        int id_next;
        std::vector<struct Neko> nekos;

        NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(NekoStore, id_next, nekos)
    };

    struct Neko
    {
        std::string id;
        std::string url;
        int width;
        int height;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(Neko, id, url, width, height)
    };

    int save_nekos(std::string filename, std::string url);
} // namespace nekolib
