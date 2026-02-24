#include "orm.hpp"

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