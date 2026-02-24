#include "opcions_menu.hpp"

// Opció (1) del menú: crear un nou rècord
void opcioCreate(pqxx::connection &conn) {

    // Menú de creació d'un nou rècord
    int rondaMaxima;
    std::string mapa;

    char charPersonatgeRecord;
    record_cod_zombies::tipus_personatge personatge_record;

    char charJugatAPC;
    bool jugatAPC;

    std::cout << "Menú per a inserir un nou rècord" << std::endl;
    
    std::cout << "- màxima ronda: ";
    std::cin >> rondaMaxima;
    std::cout << std::endl;

    std::cout << "- nom del mapa: ";
    std::cin.ignore();
    std::cin.clear();
    std::getline(std::cin, mapa);
    std::cout << std::endl;

    std::cout << "Personatges disponibles" << std::endl;
    std::cout << "> (n) Nikolai" << std::endl;
    std::cout << "> (r) Richtofen" << std::endl;
    std::cout << "> (t) Takeo" << std::endl;
    std::cout << "> (d) Dempsey" << std::endl;

    std::cout << "- personatge jugat amb el rècord (n/r/t/d): ";
    std::cin >> charPersonatgeRecord;
    personatge_record = (record_cod_zombies::tipus_personatge)charPersonatgeRecord;
    std::cout << std::endl;

    std::cout << "- s'ha jugat a ordinador (s/n): ";
    std::cin >> charJugatAPC;
    jugatAPC = charJugatAPC == 's';
    std::cout << std::endl;

    record_cod_zombies nouRecord{
        rondaMaxima,
        mapa,
        personatge_record,
        jugatAPC
    };

    inserirRecord(conn, nouRecord);

    std::cout << "Rècord inserit amb èxit" << std::endl;
}

// Opció (2) del menú: consultar els rècords existents
void opcioRead(pqxx::connection &conn) {
    readRecords(conn); 
}

// Opció (3) del menú: actualitzar un rècord existent
void opcioUpdate(pqxx::connection &conn) {
    // TODO update
}

// Opció (4) del menú: esborrar un rècord existent
void opcioDelete(pqxx::connection &conn) {
    // TODO delete
}