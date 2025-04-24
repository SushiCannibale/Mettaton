#pragma once

// #include <vector>

// #include "nekoreq.hpp"
// #include "nlhomann/json.hpp"

// NLOHMANN_JSON_NAMESPACE_BEGIN
// template <>
// struct adl_serializer<nekolib::NekoStoreImpl>
// {
//     static void to_json(json& json, const nekolib::NekoStoreImpl& store)
//     {
//         // (void)json;
//         // (void)store;
//         json["id_next"] = store.id_next;
//         std::vector<nekolib::NekoImpl> nekos;
//         for (const auto& neko : store.nekos)
//         {
//             nekos.push_back(dynamic_cast<const nekolib::NekoImpl&>(neko));
//         }
//         json["nekos"] = nekos;
//     }

//     static void from_json(const json& json, nekolib::NekoStoreImpl& store)
//     {
//         (void)json;
//         (void)store;
//         // store.id_next = json.at("id_next").get<int>();
//         // store.nekos =
//         json.at("nekos").get<std::vector<nekolib::NekoImpl>>();
//     }
// };
// NLOHMANN_JSON_NAMESPACE_END
