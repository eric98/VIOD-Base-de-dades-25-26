#include "orm.hpp"

// CREATE: Gestió INSERT a PostgreSQL (sense consultes preparades)
void createRecord(pqxx::connection &conn, record_cod_zombies &r)
{
    // Iniciem la transacció work
    pqxx::work w(conn);

    // Executem la consulta preparada
    w.exec_prepared("insert", r.rondaMaxima, r.mapa, getStringFromTipusPersonatge(r.personatge), r.jugatAPC ? "TRUE" : "FALSE");

    // Finalitzem la transacció
    w.commit();
}

// READ: Gestió SELECT a PostgreSQL (sense consultes preparades)
void readRecords(pqxx::connection &conn)
{
    // Iniciem la transacció nontransaction
    pqxx::nontransaction nt(conn);

    // Executem la consulta SQL amb totes les columnes de l'objecte record
    //   SELECT (record).* retorna totes les columnes de l'objecte record,
    //   és a dir, la consulta següent retornaria:

    //     codzombies=# SELECT id,(record).*,jugador FROM records;
    //  id | ronda_maxima |      mapa      | personatge | jugat_pc | jugador
    // ----+--------------+----------------+------------+----------+---------
    //   1 |           56 | Kino der toten | NIKOLAI    | t        |       1
    //   2 |           32 | Estación       | DEMPSEY    | f        |       2
    //   3 |          123 | Der riese      | TAKEO      | f        |       1
    //   4 |           56 | Ascension      | DEMPSEY    | f        |       1

    // Executem la consulta preparada
    pqxx::result r(nt.exec_prepared("select"));

    // Llistem tots els resultats
    for (pqxx::result::const_iterator c = r.begin(); c != r.end(); ++c)
    {

        // Extraiem les dades segons cada columna de la consulta SQL
        int id = c[0].as<int>();
        record_cod_zombies recordLlegit{
            c[1].as<int>(),
            c[2].as<std::string>(),
            getTipusPersonatgeFromString(c[3].as<std::string>()),
            c[4].as<bool>()};
        int jugadorID = c[5].as<int>();

        // Mostrem les dades per pantalla
        std::cout << "\n--- Rècord amb ID " << id << " ---" << std::endl;
        std::cout << "Ronda màxima: " << recordLlegit.rondaMaxima << std::endl;
        std::cout << "Mapa: " << recordLlegit.mapa << std::endl;
        std::cout << "Personatge: " << getStringFromTipusPersonatge(recordLlegit.personatge) << std::endl;
        std::cout << "Jugat a ordinador? " << (recordLlegit.jugatAPC ? "Sí" : "No") << std::endl;
        std::cout << "Jugador ID: " << jugadorID << std::endl;
    }
}

// UPDATE: Gestió UPDATE a PostgreSQL
void updateRecord(pqxx::connection &conn, int id, record_cod_zombies &r)
{
    // TODO update
}

// DELETE: Gestió DELETE a PostgreSQL
void deleteRecord(pqxx::connection &conn, int id)
{
    // TODO delete
}