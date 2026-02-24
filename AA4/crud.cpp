#include <iostream>
#include <pqxx/pqxx>

struct records_cod_zombies {

    enum tipus {
        SOLO,
        COOP
    };

    int record;
    std::string mapa;
    enum tipus;
    // TODO: afegir bool

};

void create_record() {
    // TODO insert
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
                create_record();
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
