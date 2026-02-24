#include <iostream>
#include <pqxx/pqxx>

/*

Implementació d'un CRUD utilitzant C++ i PostgreSQL.
El CRUD són les operacions bàsiques per a gestionar una base de dades.
Utilització de la llibreria pqxx que connecta C++ amb PostgreSQL
basat en el tutorial https://www.tutorialspoint.com/postgresql/postgresql_c_cpp.htm.

*/

struct records_cod_zombies {

    enum tipus {
        SOLO = 's',
        COOP = 'c'
    };

    int record;
    std::string mapa;
    enum tipus;
    // TODO: afegir bool

};

void create_record(pqxx::connection &conn) {

    // Menú de creació d'un nou rècord
    int ronda_maxima;
    std::string mapa;
    char char_tipus_record;

    std::cout << "Menú per a inserir un nou rècord" << std::endl;
    
    std::cout << "- màxima ronda: ";
    std::cin >> ronda_maxima;

    std::cout << "- nom del mapa: ";
    std::cin >> mapa;

    std::cout << "- SOLO o COOP? (s/c): ";
    std::cin >> char_tipus_record;

    // Gestió a la psql
    std::string sql(
        "INSERT INTO records (record, jugador) VALUES (ROW("+std::to_string(ronda_maxima)+",'"+mapa+"','"+
        (char_tipus_record == 's'? "SOLO":"COOP")
        +"'), 1)"
    );

    pqxx::work w(conn);

    /* Execute SQL query */
    w.exec( sql );
    w.commit();
    std::cout << "Rècord inserit amb èxit" << std::endl;

}

void read_records() {
    // TODO select * from 
}

int main(int argc, char* argv[]) {
   try {
      pqxx::connection conn("dbname = codzombies user = postgres password = Alumne.123");
      if (conn.is_open()) {
         std::cout << "S'ha obert la base de dades: " << conn.dbname() << std::endl;

         std::cout << "<<< Records COD Zombies >>>" << std::endl;
         
         int opcio_menu = 0;
         while (opcio_menu < 1 || opcio_menu > 3)
         {
            std::cout << "Indica quina opció vols fer: " << std::endl;
            std::cout << "\t (1) Inserir rècord" << std::endl;
            std::cout << "\t (2) Consultar records" << std::endl;
            std::cout << "\t (3) Actualtitzar rècord" << std::endl;
            
            std::cin >> opcio_menu;

            switch (opcio_menu)
            {
            case 1:
                create_record(conn);
                break;

            case 2:
                read_records();
                break;

            case 3:
                // TODO
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
