#include "opera_db.h"



static int callback(void *NotUsed, int argc, char **argv, char **azColName){
    int i;
    // is ID exist
   if(NotUsed != NULL){
        *((int*)NotUsed) = 1;
   }

   for(i=0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}



/*
    return 0  id nonexistent
            1 id exist
            -1 query fail
*/
static int isIdExists_rb(sqlite3 **db,int id) {
    char sql[100];
    char *errmsg = NULL;
    int idExist = 0;
    
    sprintf(sql, "SELECT * FROM COMPANY WHERE ID=%d;", id);
    LOGI("cmd:%s\n",sql);
    if (sqlite3_exec(*db, sql, callback, &idExist, &errmsg) != SQLITE_OK) {
        fprintf(stderr, "SQL check ID fail %s\n", errmsg);
        sqlite3_free(errmsg);
        return -1;
    }
    // 0 nonexistent
    // 1 exist
    if(idExist){
        printf("id = %d exist\n",id);
        return 1;
    }
    printf("id = %d nonexistent\n",id);
    return 0;
}


/*
    return 0  id nonexistent
            1 id exist
*/
bool isIdExists(sqlite3 **db) {
    int id;
    int j;

    printf("Enter the ID of the data you want to found:  ");
    scanf("%d", &id);
    j =  isIdExists_rb(db,id);
    return j;
}

/*
    create table
*/
int opera_create(sqlite3 **db){
    const char * sql;
    char *errmsg= NULL;
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
int opera_init_table(sqlite3 **db){
    const char * sql;
    char *errmsg= NULL;
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
    char *errmsg= NULL;
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

/*
    delete the data in the table
*/
int opera_delete(sqlite3 **db ){
    // const char * sql;
    char sql[100];
    char *errmsg= NULL;
    int id;

    printf("Enter the ID of the data you want to delete:");
    scanf("%d", &id);
    
    // id nonexist or query fail
    if(isIdExists_rb(db,id) != 1){
        printf("id nonexist\n");
        return 0;
    }

    sprintf(sql,"DELETE from COMPANY where ID=%d;", id);
    LOGI("cmd:%s\n",sql);
    if( sqlite3_exec(*db,sql,callback,0,errmsg) != SQLITE_OK){
        fprintf(stderr, "SQL delete fail %s\n", errmsg);
        sqlite3_free(errmsg);
        return -1;
    }else{
        fprintf(stdout,"SQL delete Successfully!\n");
    }

    return 0;
}

/*
    update the data in the table
*/
int opera_update(sqlite3 **db ){
    char sql[100];
    char *errmsg= NULL;
    int id;
    char name[50];
    int age;
    printf("Enter the ID of the data you want to update:  ");
    scanf("%d", &id);

    // id exist or query fail
    if(isIdExists_rb(db,id) != 1){
        printf("id nonexist\n");
        return 0;
    }
    printf("Enter the name of the data you want to add:   ");
    scanf("%s", name);
    printf("Enter the age of the data you want to add:   ");
    scanf("%d", &age);


    sprintf(sql,"UPDATE COMPANY set NAME = '%s' ,AGE= %d where ID=%d;",name, age, id);

    LOGI("cmd:%s\n",sql);
    if( sqlite3_exec(*db,sql,callback,0,errmsg) != SQLITE_OK){
        fprintf(stderr, "SQL update fail %s\n", errmsg);
        sqlite3_free(errmsg);
        return -1;
    }else{
        fprintf(stdout,"SQL update Successfully!\n");
    }
    return 0;
}


/*
    add the data to the table
*/
int opera_add(sqlite3 **db ){
    // const char * sql;
    char sql[100];
    char *errmsg= NULL;
    int id;
    char name[50];
    int age;
    printf("Enter the ID of the data you want to add:  ");
    scanf("%d", &id);
    
    // id exist or query fail
    if(isIdExists_rb(db,id) != 0){
        printf("id exist\n");
        return 0;
    }
    printf("Enter the name of the data you want to add:   ");
    scanf("%s", name);
    printf("Enter the age of the data you want to add:   ");
    scanf("%d", &age);


    sprintf(sql, "INSERT INTO COMPANY (ID, NAME, AGE) VALUES (%d, '%s', %d);", id, name, age);

    LOGI("cmd:%s\n",sql);
    
    if( sqlite3_exec(*db,sql,callback,0,errmsg) != SQLITE_OK){
        fprintf(stderr, "SQL show fail %s\n", errmsg);
        sqlite3_free(errmsg);
        return -1;
    }else{
        fprintf(stdout,"SQL show Successfully!\n");
    }
    return 0;
}


int opera_close(sqlite3 **db ){
    if(sqlite3_close(*db) != SQLITE_OK){
        fprintf(stderr,"close database fail!\n");   
    }else{
        printf("close database Successfully!\n");
    };
}