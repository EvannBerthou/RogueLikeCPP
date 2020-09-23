#include <iostream>
#include <sqlite3.h>
#include "load_database_items.h"

static void replace_description(item_t &item) {
    std::string replaced_description = "";
    bool replacing = false;
    std::string key = "";
    for (const char &c : item.description) {
        if (c != '[' && c != ']') {
            if (!replacing) replaced_description += c;
            else key += c;
        }
        if (c == '[') {
            if (replacing) {
                std::cerr << "[ERROR] Nested '[' for " << item.name << "'s description" << std::endl;
                exit(1);
            }
            replacing = true;
        }
        if (c == ']') {
            if (!replacing) {
                std::cerr << "[ERROR] Dectected ']' without opening '[' for " << item.name
                          << "'s description" << std::endl;
                exit(1);
            }
            if (key == "amount") {
                replaced_description += std::to_string(item.amount);
            }
            replacing = false;
        }
    }
    item.description = replaced_description;
}

static std::string parse_text(sqlite3_stmt *stmt, int i) {
    const char *text = (const char *)sqlite3_column_text(stmt, i);
    if (text != NULL) {
        return std::string(text);
    }
    return "";
}

static int parse_int(sqlite3_stmt *stmt, int i) {
    return sqlite3_column_int(stmt, i);
}

static std::pair<std::string, item_t> parse_item(sqlite3_stmt *stmt) {
    std::string item_name;
    item_t item = {};
    for (int i = 0; i < sqlite3_column_count(stmt); i++) {
        std::string column_name = std::string(sqlite3_column_name(stmt, i));
        if (column_name == "id")          item.id          = parse_int(stmt,  i);
        if (column_name == "code_name")   item_name        = parse_text(stmt, i);
        if (column_name == "name")        item.name        = parse_text(stmt, i);
        if (column_name == "description") item.description = parse_text(stmt, i);
        if (column_name == "texture_name")item.texture_name= parse_text(stmt, i);
        if (column_name == "rarity")      item.rarity      = parse_int(stmt,  i);
        if (column_name == "type")        item.type        = (ItemType)parse_int(stmt,  i);
        if (column_name == "effect")      item.effect      = (ItemEffect)parse_int(stmt,  i);
        if (column_name == "amount")      item.amount      = parse_int(stmt,  i);
        if (column_name == "range")       item.range       = parse_int(stmt,  i);
    }
    replace_description(item);
    return std::make_pair(item_name, item);
}

std::unordered_map<std::string, item_t> load_database_items() {
    std::unordered_map<std::string, item_t> items = {};

    sqlite3 *db;

    if (sqlite3_open("items.db", &db)) {
        std::cerr << "Error while opening items database" << std::endl;
        exit(1);
    }

    sqlite3_stmt *stmt;
    const char *get_items_querry = "SELECT * FROM items;";
    if (sqlite3_prepare_v2(db, get_items_querry, -1, &stmt, 0)) {
        std::cerr << "Error while preparing request" << std::endl;
        exit(1);
    }

    while (sqlite3_step(stmt) != SQLITE_DONE) {
        std::pair<std::string, item_t> parsed_item = parse_item(stmt);
        items[parsed_item.first] = parsed_item.second;
    }
    return items;
}
