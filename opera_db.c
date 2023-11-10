#include "stdio.h"
#include "opera_db.h"


static int callback(void *NotUsed, int argc, char **argv, char **azColName){
    int i;
   for(i=0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}


/*
    create table
*/
int opera_create(sqlite3 **db){
    const char * sql;
    char *errmsg;
    sql = "CREATE TABLE IF NOT EXISTS COMPANY(" \
    "ID     INT PRIMARY KEY NOT NULL," \
    "NAME   TEXT            NOT NULL," \
    "AGE    INT             NOT NULL);";

    if( sqlite3_exec(*db,sql,callback,0,errmsg) != SQLITE_OK){
        fprintf(stderr, "SQL error: %s\n", errmsg);
        sqlite3_free(errmsg);
        return -1;
    }else{
        fprintf(stdout,"Table create Successfully!\n");
    }
    return 0;
}


/*
  init data to table  
*/
int opera_add(sqlite3 **db){
    const char * sql;
    char *errmsg;
    sql = "INSERT OR IGNORE INTO COMPANY (ID,NAME,AGE) "  \
         "VALUES (1, 'Paul', 32 ); " \
         "INSERT OR IGNORE INTO COMPANY (ID,NAME,AGE) "  \
         "VALUES (2, 'Allen', 25 ); "     \
         "INSERT OR IGNORE INTO COMPANY (ID,NAME,AGE)" \
         "VALUES (3, 'Teddy', 23);" \
         "INSERT OR IGNORE INTO COMPANY (ID,NAME,AGE)" \
         "VALUES (4, 'Mark', 25 );";

    if( sqlite3_exec(*db,sql,callback,0,errmsg) != SQLITE_OK){
        fprintf(stderr, "SQL add error: %s\n", errmsg);
        sqlite3_free(errmsg);
        return -1;
    }else{
        fprintf(stdout,"Records create Successfully!\n");
    }
    return 0;
}


/* 
    Print the contents of the table
*/
int opera_show(sqlite3 **db ){
    const char * sql;
    char *errmsg;
    sql = "select * from company";
    
    if( sqlite3_exec(*db,sql,callback,0,errmsg) != SQLITE_OK){
        fprintf(stderr, "SQL show fail %s\n", errmsg);
        sqlite3_free(errmsg);
        return -1;
    }else{
        fprintf(stdout,"SQL show Successfully!\n");
    }
    return 0;
}

