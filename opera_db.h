#ifndef OPERA_DB_H
#define OPERA_DB_H
#include "sqlite3.h"
#include <stdbool.h>
#include <stdio.h>
/*
company
Table
---------------------------------
ID          NAME            AGE
---------------------------------
1           Paul            32
2           Allen            25
3           Teddy            23
4           Mark             25
*/

#define LOG_ENABLED

#ifdef LOG_ENABLED
#define LOGI(...) fprintf(stderr, "I: " __VA_ARGS__)
#else
#define LOGI(...) do {} while (0) // 空操作，即忽略日志输出
#endif

int opera_create(sqlite3 **db);

int opera_init_table(sqlite3 **db);

bool isIdExists(sqlite3 **db);


int opera_show(sqlite3 **db );

int opera_update(sqlite3 **db );

int opera_delete(sqlite3 **db );

int opera_add(sqlite3 **db );

int opera_close(sqlite3 **db );

#endif