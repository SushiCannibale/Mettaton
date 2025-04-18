#include <mettaton/mettaton.h>
// #include <dpp/cluster.h>
// #include <dpp/dispatcher.h>
// #include <dpp/once.h>
#include <fstream>
#include <sstream>

bool load_token(std::ostream& ostr)
{
    char* tokenfile = std::getenv("TOKEN");
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
    while (!ifs.is_open())
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
    load_token(sstr);
    // dpp::cluster bot(sstr.str());

    /// Register handlers
    // bot.on_ready([&bot](const dpp::ready_t& event) {
    //     (void)event;
    //     if (dpp::run_once<struct uwuland_registry>())
    //     {
    //         bot.global_command_create(
    //             dpp::slashcommand("ping", "Dare u ping me", bot.me.id));
    //     }
    // });

    // bot.start(dpp::st_wait);
    return 0;
}