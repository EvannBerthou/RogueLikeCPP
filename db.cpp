#include <iostream>
#include <sqlite3.h>

int main(void) {
    sqlite3 *DB;
    if (sqlite3_open("items.db", &DB)) {
        std::cerr << "Error while opening DB" << sqlite3_errmsg(DB) << std::endl;
        exit(1);
    }

    const char *delete_querry = "DROP TABLE IF EXISTS items;";
    sqlite3_exec(DB, delete_querry, NULL, 0, NULL);

    const char *create_table = "CREATE TABLE items ("
                               "id INT PRIMARY KEY NOT NULL,"
                               "code_name TEXT NOT NULL,"
                               "name TEXT NOT NULL,"
                               "description TEXT,"
                               "texture_name TEXT NOT NULL,"
                               "rarity INT NOT NULL,"
                               "type INT NOT NULL,"
                               "effect INT NOT NULL,"
                               "amount INT NOT NULL,"
                               "range INT NOT NULL);";
    if (sqlite3_exec(DB, create_table, NULL, 0, NULL)) {
        std::cerr << "Error while creating table" << std::endl;
    }
}
