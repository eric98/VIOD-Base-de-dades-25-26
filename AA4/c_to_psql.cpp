#include <iostream>
#include <pqxx/pqxx>


int main(int argc, char* argv[]) {
   try {
      pqxx::connection conn("dbname = poblacions user = postgres password = Alumne.123");
      if (conn.is_open()) {
         std::cout << "S'ha obert la base de dades: " << conn.dbname() << std::endl;
      } else {
         std::cout << "No s'ha pogut obrir la base de dades." << std::endl;
         return 1;
      }
   } catch (const std::exception &e) {
      std::cerr << e.what() << std::endl;
      return 1;
   }

}
