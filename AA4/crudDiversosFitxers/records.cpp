#include "records.hpp"

std::string getStringFromTipusPersonatge(record_cod_zombies::tipus_personatge p)
{

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

record_cod_zombies::tipus_personatge getTipusPersonatgeFromString(const std::string &p)
{
    if (p == "NIKOLAI")
        return record_cod_zombies::NIKOLAI;
    if (p == "RICHTOFEN")
        return record_cod_zombies::RICHTOFEN;
    if (p == "TAKEO")
        return record_cod_zombies::TAKEO;
    if (p == "DEMPSEY")
        return record_cod_zombies::DEMPSEY;

    // Valor per defecte (en cas de string no reconegut)
    return record_cod_zombies::NIKOLAI;
}

std::string recordToString(record_cod_zombies &r)
{
    return "{ rondaMaxima: " + std::to_string(r.rondaMaxima) +
           ", mapa: '" + r.mapa +
           "', personatge: '" + getStringFromTipusPersonatge(r.personatge) +
           "', jugatAPC: " + (r.jugatAPC ? "TRUE" : "FALSE") + " }";
}