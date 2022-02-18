#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include "cJSON.h"
static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    int i;
    for (i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

int main(int argc, char *argv[]) {
    sqlite3 *db;
    char *ErrMsg = 0;
    int status;
    char *sql;

    /* Open database */
    status = sqlite3_open("test.db", &db);

    if (status) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return (0);
    }
    else {
        fprintf(stdout, "Opened database successfully\n");
    }

    /* Create SQL statement */
    sql = "CREATE TABLE messages("
          "ID INT NOT NULL,"
          "NAME TEXT NOT NULL,"
          "MESSAGE TEXT NOT NULL,"
          "TIME TEXT)";

    /* Execute SQL statement */
    status = sqlite3_exec(db, sql, callback, 0, &ErrMsg);

    if (status != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", ErrMsg);
        sqlite3_free(ErrMsg);
    }
    else {
        fprintf(stdout, "Table created successfully\n");
    }
    sqlite3_close(db);
    return 0;
}
