#include "stdio.h"
#include "sqlite3.h"
#include "opera_db.h"
#include "stdlib.h"
/*
    database name my.db
    
*/
int main(){
    sqlite3 *db;
    int choice;
    if( sqlite3_open("my.db",&db) != 0){
        fprintf(stdout,"open database fail!\n");
        return -1;
    }
    printf("database open Successfully!\n");
    opera_create(&db);
    opera_init_table(&db);


    while(1){
        printf("Enter your choice (1, 2, 3, 4, or 5): \n");
        printf(" 1. add data to table. \n 2. delete data from table. \n 3. show the table. \n 4. updata data from table. \n 5. query id\n 6. quit\n");
        printf("please select : "); 
        // Ensure the input is an integer
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter an integer.\n");
            // return 1; // Exit with an error code
        }
        switch(choice){
            case 1:
                opera_add(&db);
                break;
            case 2:
                opera_delete(&db);
                break;
            case 3:
                opera_show(&db);
                break;
            case 4:
                opera_update(&db);
                break;
            case 5:    
                isIdExists(&db);
                break;
            case 6:
                opera_close(&db);
                exit(0);
                break;
        }
    }
    return 0;
}