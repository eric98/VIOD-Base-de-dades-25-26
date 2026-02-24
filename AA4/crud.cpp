#include <iostream>
#include <string>
#include <pqxx/pqxx>

/*

Implementació d'un CRUD utilitzant C++ i PostgreSQL.
El CRUD són les operacions bàsiques per a gestionar una base de dades.
Utilització de la llibreria pqxx que connecta C++ amb PostgreSQL
basat en el tutorial https://www.tutorialspoint.com/postgresql/postgresql_c_cpp.htm.

*/

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

// Gestió INSERT a PostgreSQL (sense consultes preparades)
void inserirRecord(pqxx::connection &conn, record_cod_zombies &r){
    
    // Iniciem la transacció
    pqxx::work w(conn);

    // Executem la consulta SQL amb els atributs del record r
    w.exec(
        "INSERT INTO records (record, jugador) VALUES (ROW("+
        std::to_string(r.rondaMaxima)+",'"+
        r.mapa+"','"+
        getStringFromTipusPersonatge(r.personatge)+"',"+
        (r.jugatAPC? "TRUE":"FALSE")+"), 1)" 
    );

    // Finalitzem la transacció
    w.commit();
}

// Gestió SELECT a PostgreSQL (sense consultes preparades)
void readRecords(pqxx::connection &conn) {
    
    // Iniciem la transacció
    pqxx::nontransaction nt(conn);

    // Executem la consulta SQL amb els atributs del record r
    pqxx::result r( nt.exec(
        "SELECT * FROM records"
    ));
      

    for (pqxx::result::const_iterator c = r.begin(); c != r.end(); ++c) {
        std::cout << "ID = " << c[0].as<int>() << std::endl;
        std::cout << "Rècord = " << c[1].as<std::string>() << std::endl;
        std::cout << "Jugador = " << c[2].as<int>() << std::endl;
    }
}

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

int main(int argc, char* argv[]) {
   try {
      pqxx::connection conn("dbname = codzombies user = postgres password = Alumne.123");
      if (conn.is_open()) {
         std::cout << "S'ha obert la base de dades: " << conn.dbname() << std::endl;

         std::cout << "<<< Rècords COD Zombies >>>" << std::endl;
         
         int opcio_menu = 0;
         while (opcio_menu < 1 || opcio_menu > 3)
         {
            std::cout << "Indica quina opció vols fer: " << std::endl;
            std::cout << "\t (1) Inserir rècord" << std::endl;
            std::cout << "\t (2) Consultar records" << std::endl;
            std::cout << "\t (3) Actualtitzar rècord" << std::endl;
            std::cout << "\t (4) Esborrar rècord" << std::endl;

            
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

            // Si la opció no existeix
            default:
                std::cout << "La opció " << opcio_menu << " no existeix." << std::endl;
                break;
            }

         }
         

      } else {
         std::cout << "No s'ha pogut obrir la base de dades." << std::endl;
         return 1;
      }
   } catch (const std::exception &e) {
      std::cerr << e.what() << std::endl;
      return 1;
   }

}
