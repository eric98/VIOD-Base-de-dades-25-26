#include "opcions_menu.hpp"

// Opció (1) del menú: crear un nou rècord
void opcioCreate(pqxx::connection &conn)
{
    // 1. Formulari de creació d'un nou rècord
    int rondaMaxima;
    std::string mapa;

    char charPersonatgeRecord;
    record_cod_zombies::tipus_personatge personatge_record;

    char charJugatAPC;
    bool jugatAPC;

    std::cout << "\n>> Menú per a inserir un nou rècord" << std::endl;

    std::cout << "- Màxima ronda: ";
    std::cin >> rondaMaxima;

    std::cout << "- Nom del mapa: ";
    std::cin.ignore();
    std::cin.clear();
    std::getline(std::cin, mapa);

    std::cout << "- Personatge jugat (Nikolai = n, Richtofen = r, Takeo = t, Dempsey = d) [n/r/t/d]: ";
    std::cin >> charPersonatgeRecord;
    personatge_record = (record_cod_zombies::tipus_personatge)charPersonatgeRecord;

    std::cout << "- Jugat a ordinador [s/n]: ";
    std::cin >> charJugatAPC;
    jugatAPC = charJugatAPC == 's';

    record_cod_zombies nouRecord{
        rondaMaxima,
        mapa,
        personatge_record,
        jugatAPC};

    // 2. Es pregunta a l'usuari si les dades són correctes
    char confirm;
    std::cout << "\n... creant cub: " << recordToString(nouRecord) << std::endl;
    std::cout << "Les dades són correctes? [s/n]: " << std::flush;
    std::cin >> confirm;

    if (confirm == 's')
    {
        // 3. Inserció del nou rècord a la base de dades
        std::cout << "\n... executant consulta ..." << std::endl;
        createRecord(conn, nouRecord);
        std::cout << "--> Operació INSERT executada amb èxit" << std::endl;
    }
    else
    {
        std::cout << "--> Operació INSERT cancel·lada" << std::endl;
    }
}

// Opció (2) del menú: consultar els rècords existents
void opcioRead(pqxx::connection &conn)
{
    std::cout << "\n... executant consulta ..." << std::endl;
    readRecords(conn);
    std::cout << "\n--> Operació SELECT executada amb èxit" << std::endl;
}

// Opció (3) del menú: actualitzar un rècord existent
void opcioUpdate(pqxx::connection &conn)
{
    // TODO update

    // 1. Mostrem els records existents (SELECT)
    // 2. Preguntem per l'id del record que es vol modificar
    // 3. Creem un record amb les noves dades però amb el mateix id
    // 4. Executem la funció updateRecord(id, nouRecord)
}

// Opció (4) del menú: esborrar un rècord existent
void opcioDelete(pqxx::connection &conn)
{
    // TODO delete

    // 1. Mostrem els records existents (SELECT)
    // 2. Preguntem per l'id del record que es vol esborrar
    // 3. Executem la funció deleteRecord(id)
}