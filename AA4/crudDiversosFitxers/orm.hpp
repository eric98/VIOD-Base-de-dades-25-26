#pragma once

#include <pqxx/pqxx>
#include <iostream>
#include "records.hpp"

// Gestió INSERT a PostgreSQL (sense consultes preparades)
void readRecord(pqxx::connection &conn, record_cod_zombies &r);

// Gestió SELECT a PostgreSQL (sense consultes preparades)
void readRecords(pqxx::connection &conn);