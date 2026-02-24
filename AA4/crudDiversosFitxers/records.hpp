#pragma once

#include <iostream>

struct record_cod_zombies {

    enum tipus_personatge {
        NIKOLAI = 'n',
        RICHTOFEN = 'r',
        TAKEO = 't',
        DEMPSEY = 'd'     
    };

    int rondaMaxima;
    std::string mapa;
    tipus_personatge personatge;
    bool jugatAPC;

};

std::string getStringFromTipusPersonatge(record_cod_zombies::tipus_personatge p);