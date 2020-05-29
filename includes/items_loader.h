#ifndef ITEM_LOADER_H
#define ITEM_LOADER_H

#include <unordered_map>
#include <string>
#include "textures.h"
#include "item.h"

std::unordered_map<std::string, item_t> load_items(texture_dict &textures);

#endif
