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
     * @brief Creates a new empty store.
     */
    NekoStore* make_store();

    /**
     * @brief Saves the state of the store on the disk
     */
    void save_nekos(NekoStore* store, std::string filename);

    /**
     * @brief Fills the store with some nekos patiently waiting to be picked up
     * on the disk.
     *
     * @throws json::parse_error The file cannot be parsed correctly
     */
    void load_nekos(NekoStore* store, std::string filename);

    /**
     * @brief Tries to get the next neko from the store. Eventually pulling from
     * the file located at 'NEKO_STORE'.
     * If the file cannot be loaded or parsed, then writes data into both the
     * store structure and the file.
     */
    Neko& get_neko(NekoStore* store);

} // namespace nekolib