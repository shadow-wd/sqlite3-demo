#ifndef OPERA_DB_H
#define OPERA_DB_H
#include "sqlite3.h"

int opera_create(sqlite3 **db);

int opera_add(sqlite3 **db);

int opera_show(sqlite3 **db );
#endif