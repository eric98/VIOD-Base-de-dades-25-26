#include <iostream>
#include <string>
#include <pqxx/pqxx>

/*

Implementació d'un CRUD utilitzant C++ i PostgreSQL.
El CRUD són les operacions bàsiques per a gestionar una base de dades.
Utilització de la llibreria pqxx que connecta C++ amb PostgreSQL
basat en el tutorial https://www.tutorialspoint.com/postgresql/postgresql_c_cpp.htm.

*/

struct record_cod_zombies
{
    enum tipus_personatge
    {
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

    std::cout << "- Personatge jugat (Nikolai = n, Richtofen = r, Takeo = t, Dempsey = d) [n/r/t/d]" << std::endl;
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

int main(int argc, char *argv[])
{
    try
    {
        pqxx::connection conn("dbname = codzombies user = postgres password = Alumne.123");
        if (conn.is_open())
        {
            std::cout << "S'ha obert la base de dades: " << conn.dbname() << std::endl;

            // TODO: parametritzar 'jugador' a INSERT, sempre és 1
            // TODO: poder actualitzar 'jugador' a UPDATE, sempre és 1
            conn.prepare("insert","INSERT INTO records (record, jugador) VALUES (ROW($1,$2,$3,$4), 1)");
            conn.prepare("select", "SELECT id, (record).*, jugador FROM records");
            conn.prepare("update", "UPDATE records SET record = ROW($2,$3,$4,$5) WHERE id = $1");
            // TODO: prepare delete
            
            int opcio_menu = 0;
            do
            {
                std::cout << "\n<<< Rècords COD Zombies >>>" << std::endl;
                std::cout << "\nIndica quina opció vols fer: " << std::endl;
                std::cout << "\t (1) Inserir rècord" << std::endl;
                std::cout << "\t (2) Consultar records" << std::endl;
                std::cout << "\t (3) Actualtitzar rècord" << std::endl;
                std::cout << "\t (4) Esborrar rècord" << std::endl;
                std::cout << "\t (5) Sortir" << std::endl;
                std::cin >> opcio_menu;

                switch (opcio_menu)
                {
                case 1:
                    opcioCreate(conn);
                    break;
                case 2:
                    opcioRead(conn);
                    break;
                case 3:
                    opcioUpdate(conn);
                    break;
                case 4:
                    opcioDelete(conn);
                    break;
                case 5:
                    // TODO sortida del programa
                    break;

                // Si la opció no existeix
                default:
                    std::cout << "La opció " << opcio_menu << " no existeix." << std::endl;
                    break;
                }

            } while (opcio_menu != 5);
        }
        else
        {
            std::cout << "No s'ha pogut obrir la base de dades." << std::endl;
            return 1;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
}
