#pragma once

#include <mettaton/libneko.h>

#include "nlhomann/json.hpp"

namespace nekolib
{
    struct NekoImpl : public Neko
    {
        // NLOHMANN_DEFINE_DERIVED_TYPE_INTRUSIVE(NekoImpl, Neko, id, url,
        // width,
        //                                        height)
    };

    struct NekoStoreImpl : public NekoStore
    {
        // NLOHMANN_DEFINE_DERIVED_TYPE_INTRUSIVE(NekoStoreImpl, NekoStore,
        //                                        id_next, nekos)
    };

    int save_nekos_impl(NekoStoreImpl* store, std::string filename);
    int load_nekos_impl(NekoStoreImpl* store, std::string filename);
    std::string get_neko_impl(NekoStoreImpl* store);

} // namespace nekolib

#include "nekoreq.hxx"