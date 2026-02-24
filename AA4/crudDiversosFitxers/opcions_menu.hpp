#pragma once

#include <pqxx/pqxx>
#include <iostream>
#include "orm.hpp"

void opcioCreate(pqxx::connection &conn);

// Opció (2) del menú: consultar els rècords existents
void opcioRead(pqxx::connection &conn);

// Opció (3) del menú: actualitzar un rècord existent
void opcioUpdate(pqxx::connection &conn);

// Opció (4) del menú: esborrar un rècord existent
void opcioDelete(pqxx::connection &conn);