#include <curl/curl.h>
#include <dpp/appcommand.h>
#include <dpp/dpp.h>
#include <dpp/message.h>
#include <mettaton/libneko.h>
#include <ostream>

static bool read_token(std::ostream& ostr)
{
    /// TOOD: char* tokenfile = std::getenv("TOKEN_LOC");
    const char* tokenfile = "secret";
    if (tokenfile == nullptr)
    {
        return false;
    }

    std::string buf;
    std::ifstream ifs(tokenfile);
    if (!ifs.is_open())
    {
        return false;
    }
    while (!ifs.eof())
    {
        std::getline(ifs, buf);
        ostr << buf;
    }
    ifs.close();
    return true;
}

int main()
{
    (void)read_token;
    nekolib::NekoStore* store = nekolib::make_store();

    nekolib::Neko& neko = nekolib::get_neko(store);
    std::cout << "Neko: " << neko << std::endl;
    std::cout << "Store: " << *store << std::endl;

    neko = nekolib::get_neko(store);
    std::cout << "Neko: " << neko << std::endl;
    std::cout << "Store: " << *store << std::endl;

    neko = nekolib::get_neko(store);
    std::cout << "Neko: " << neko << std::endl;
    std::cout << "Store: " << *store << std::endl;

    nekolib::save_nekos(store, "saved-store.json");
    delete store;

    // std::stringstream sstr;
    // read_token(sstr);
    // dpp::cluster bot(sstr.str());
    // nekolib::NekoStore* store = nekolib::make_store();

    // /// Register handlers
    // bot.on_ready([&bot](const dpp::ready_t& event) {
    //     (void)event;
    //     if (dpp::run_once<struct uwuland_registry>())
    //     {
    //         std::cout << bot.me.username << " ready!\n";
    //         bot.global_command_create(
    //             dpp::slashcommand("ping", "Dare u ping me", bot.me.id));
    //         bot.global_command_create(
    //             dpp::slashcommand("neko", "Some cute neko", bot.me.id));
    //     }
    // });

    // bot.on_slashcommand([&store](const dpp::slashcommand_t& event) {
    //     if (event.command.get_command_name() == "ping")
    //     {
    //         event.reply("Pong!");
    //     }
    //     else if (event.command.get_command_name() == "neko")
    //     {
    //         const std::string url = nekolib::get_neko(store);
    //         event.reply(url);
    //     }
    // });

    // bot.start(dpp::st_wait);

    // delete store;
    // return 0;
}