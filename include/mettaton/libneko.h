#pragma once

#include <json/json.hpp>
#include <ostream>
#include <string>

namespace nekolib
{
    struct Neko
    {
        std::string id;
        std::string url;
        int width;
        int height;

        virtual ~Neko() = default;

        friend std::ostream& operator<<(std::ostream& ostr, const Neko& neko);
    };

    struct NekoStore
    {
        size_t id_next;
        std::vector<Neko> nekos;

        virtual ~NekoStore() = default;

        friend std::ostream& operator<<(std::ostream& ostr,
                                        const NekoStore& store);
    };

    /**
     * @brief Creates a new store. The store is internally bound to a file on
     * the disk. I/O operations are done at runtime. Caller is responsible of
     * freeing the store object.
     */
    NekoStore* make_store();

    /**
     * @brief Saves the state of the store on the disk
     *
     * @param filename: where to store the nekos
     * @param url: where to fetch the nekos from
     * @return either success or failure
     */
    int save_nekos(NekoStore* store, std::string filename);

    /**
     * @brief Fills the store with some nekos patiently waiting to be picked up
     * on the disk
     */
    int load_nekos(NekoStore* store, std::string filename);

    /**
     * @brief Get a new neko. Fills the store if necessary
     */
    Neko& get_neko(NekoStore* store);

} // namespace nekolib