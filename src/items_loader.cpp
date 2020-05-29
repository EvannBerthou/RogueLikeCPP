#include <iostream>
#include <fstream>
#include <vector>
#include <cctype>
#include <algorithm>
#include "items_loader.h"

const std::string WHITESPACE = " \n\r\t\f\v";

static std::string ltrim(const std::string &s) {
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == std::string::npos) ? "" : s.substr(start);
}

static std::string rtrim(const std::string &s) {
    size_t end = s.find_last_not_of(WHITESPACE);
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}

static std::string remove_trailing_whitespaces(const std::string &s) {
    return rtrim(ltrim(s));
}

std::unordered_map<std::string, item_t> load_items(texture_dict &textures) {
    std::unordered_map<std::string, item_t> items =  {};

    std::ifstream file ("assets/items/weapons");
    if (file.is_open()) {

        bool in_item = false;
        item_t current_item = {};
        std::string item_name;

        std::string line;
        while (getline(file, line)) {
            std::string read;
            for (char &c : line) {
                if (c == '#') break;
                if (c == '}') {
                    in_item = false;
                    if (current_item.texture == NULL) {
                        std::cout << "no texture provided" << std::endl;
                        current_item.texture = textures.get_texture_by_name("error");
                    }
                    current_item.id = items.size();
                    items[item_name] = current_item;
                    current_item = {};
                }
                else if (c == '{') {
                    in_item = true;
                    read.erase(std::remove_if(read.begin(), read.end(), ::isspace), read.end());
                    item_name = read;
                }
                else {
                    read += c;
                }
            }

            read = remove_trailing_whitespaces(read);

            if (in_item) {
                if (read.rfind("name:", 0) == 0) {
                    std::string name = read.substr(strlen("name:"));
                    current_item.name = name;
                }
                if (read.rfind("description:", 0) == 0) {
                    std::string description = read.substr(strlen("description:"));
                    current_item.description = description;
                }
                if (read.rfind("texture:", 0) == 0) {
                    std::string texture_name = read.substr(strlen("texture:"));
                    current_item.texture = textures.get_texture_by_name(texture_name);
                }
                if (read.rfind("rarity:", 0) == 0) {
                    std::string rarity_str  = read.substr(strlen("rarity:"));
                    int rarity = 0;
                    if (!rarity_str.empty() && std::all_of(rarity_str.begin(),rarity_str.end(),::isdigit)){
                        rarity = std::atoi(rarity_str.c_str());
                    }
                    else {
                        std::cout << "the given rarity is not an int for : " << item_name << std::endl;
                    }
                    current_item.rarity = rarity;
                }
            }
        }
    }
    else {
        std::cout << "error while opening file" << std::endl;
        exit(1);
    }
    return items;
}
