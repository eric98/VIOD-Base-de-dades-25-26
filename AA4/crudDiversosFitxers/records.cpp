#include "records.hpp"

std::string getStringFromTipusPersonatge(record_cod_zombies::tipus_personatge p) {

    switch (p)
    {
        case record_cod_zombies::tipus_personatge::NIKOLAI:
            return "NIKOLAI";
        case record_cod_zombies::tipus_personatge::RICHTOFEN:
            return "RICHTOFEN";
        case record_cod_zombies::tipus_personatge::TAKEO:
            return "TAKEO";
        case record_cod_zombies::tipus_personatge::DEMPSEY:
            return "DEMPSEY";
        default:
            return "";
    }

}