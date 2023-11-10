#include "stdio.h"
#include "sqlite3.h"
#include "opera_db.h"
/*
    database name my.db
    
*/
int main(){
    sqlite3 *db;
    if( sqlite3_open("my.db",&db) != 0){
        fprintf(stdout,"open database fail!\n");
        return -1;
    }

    opera_create(&db);
    opera_add(&db);
    opera_show(&db);






    if(sqlite3_close(db) != 0){
        fprintf(stdout,"close database fail!\n");
    }
    return 0;
}