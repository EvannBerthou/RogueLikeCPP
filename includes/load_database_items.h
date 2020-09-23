#ifndef LOAD_DATABASE_ITEMS
#define LOAD_DATABASE_ITEMS

#include <unordered_map>
#include <string>
#include "item.h"

std::unordered_map<std::string, item_t> load_database_items();

#endif
