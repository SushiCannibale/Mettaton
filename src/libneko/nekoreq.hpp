#pragma once

#include <json/json.hpp>
#include <mettaton/libneko.h>

namespace nekolib
{
    struct NekoImpl : public Neko
    {
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(NekoImpl, id, url, width, height)
    };

    struct NekoStoreImpl : public NekoStore
    {
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(NekoStoreImpl, id_next, nekos)
    };

    int save_nekos_impl(NekoStoreImpl* store, std::string filename);
    int load_nekos_impl(NekoStoreImpl* store, std::string filename);
    Neko& get_neko_impl(NekoStoreImpl* store);

} // namespace nekolib
