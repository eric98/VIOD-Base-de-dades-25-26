#pragma once

#include <pqxx/pqxx>
#include <iostream>
#include "records.hpp"

// CREATE: Gestió INSERT a PostgreSQL (sense consultes preparades)
void createRecord(pqxx::connection &conn, record_cod_zombies &r);

// READ: Gestió SELECT a PostgreSQL (sense consultes preparades)
void readRecords(pqxx::connection &conn);

// UPDATE: Gestió UPDATE a PostgreSQL
void updateRecord(pqxx::connection &conn, int id, record_cod_zombies &r);

// DELETE: Gestió DELETE a PostgreSQL
void deleteRecord(pqxx::connection &conn, int id);