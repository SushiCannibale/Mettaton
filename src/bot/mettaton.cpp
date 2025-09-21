#include <cstdlib>
#include <curl/curl.h>
#include <dpp/appcommand.h>
#include <dpp/dpp.h>
#include <dpp/message.h>
#include <fstream>
#include <mettaton/libneko.h>
#include <ostream>
#include <signal.h>

static nekolib::NekoStore* store = nullptr;

static void save_exit(int sig)
{
    if (store != nullptr)
    {
        nekolib::save_nekos(store);
    }

    exit(0);
}

static bool read_token(std::ostream& ostr)
{
    char* tokenfile = std::getenv("TOKEN_LOC");
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
    std::stringstream sstr;
    read_token(sstr);
    dpp::cluster bot(sstr.str());
    store = nekolib::make_store();

    signal(SIGINT, save_exit);

    /// Register handlers
    bot.on_ready([&bot](const dpp::ready_t& event) {
        (void)event;
        if (dpp::run_once<struct uwuland_registry>())
        {
            std::cout << bot.me.username << " ready!\n";
            bot.global_command_create(
                dpp::slashcommand("ping", "Dare u ping me", bot.me.id));
            bot.global_command_create(
                dpp::slashcommand("neko", "Some cute neko", bot.me.id));
        }
    });

    bot.on_slashcommand([](const dpp::slashcommand_t& event) {
        if (event.command.get_command_name() == "ping")
        {
            event.reply("Pong!");
        }
        else if (event.command.get_command_name() == "neko")
        {
            nekolib::Neko& neko = nekolib::get_neko(store);
            event.reply(neko.url);
        }
    });

    bot.start(dpp::st_wait);

    delete store;
    return 0;
}