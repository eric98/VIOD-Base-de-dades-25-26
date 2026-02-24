#include <iostream>
#include <string>
#include <pqxx/pqxx>
#include "opcions_menu.hpp"

/*

Implementació d'un CRUD utilitzant C++ i PostgreSQL.
El CRUD són les operacions bàsiques per a gestionar una base de dades.
Utilització de la llibreria pqxx que connecta C++ amb PostgreSQL
basat en el tutorial https://www.tutorialspoint.com/postgresql/postgresql_c_cpp.htm.

# 1. Compilació (Afegir els cpp i la llibreria pqxx):
$ g++ -o crud main.cpp opcions_menu.cpp orm.cpp records.cpp -lpqxx

# 2. Execució:
$ ./crud

*/


int main(int argc, char* argv[]) {
   try {
      pqxx::connection conn("dbname = codzombies user = postgres password = Alumne.123");
      if (conn.is_open()) {
         std::cout << "S'ha obert la base de dades: " << conn.dbname() << std::endl;

         std::cout << "<<< Rècords COD Zombies >>>" << std::endl;
         
         int opcio_menu = 0;
         while (opcio_menu < 1 || opcio_menu > 5)
         {
            std::cout << "Indica quina opció vols fer: " << std::endl;
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
                std::cout << "Fins aviat" << std::endl;
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
