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

static ItemType get_type_from_str(const std::string &s) {
    if (s == "weapon") return ItemType::Weapon;
    if (s == "armor")  return ItemType::Armor;
    if (s == "effect") return ItemType::Effect;
    return ItemType::Undefined;
}

static ItemEffect get_effect_from_str(const std::string &s) {
    if (s == "heal") return ItemEffect::Heal;
    if (s == "damage") return ItemEffect::Damage;
    return ItemEffect::None;
}

static bool is_key(std::string &str, std::string key) {
    return str.rfind(key, 0) == 0;
}

static std::string extract_value_from_key(std::string line) {
    size_t separator_index = line.find_first_of(":") + 1;
    std::string value = line.substr(separator_index);
    return value;
}

static int convert_to_int(std::string string) {
    string.erase(std::remove_if(string.begin(), string.end(), ::isspace), string.end());
    if (!string.empty() && std::all_of(string.begin(),string.end(), ::isdigit))
        return std::atoi(string.c_str());
    return -1;
}

static void parse_line(std::string &line, size_t line_index, item_t &item, texture_dict &textures) {
    if (is_key(line, "name")) {
        item.name = extract_value_from_key(line);
    }
    if (is_key(line, "description")) {
        item.description = extract_value_from_key(line);
    }
    if (is_key(line, "texture")) {
        std::string value = extract_value_from_key(line);
        value.erase(std::remove_if(value.begin(), value.end(), ::isspace), value.end());
        item.texture = textures.get_texture_by_name(value);
    }
    if (is_key(line, "rarity")) {
        std::string rarity_str = extract_value_from_key(line);
        int rarity = convert_to_int(rarity_str);
        if (rarity == -1) {
            std::cout << "[WARNING] The given rarity for " << item.name << " is not an int "
                      << "(line " << line_index << ")" << std::endl;
            rarity = 0;
        }
        if (rarity < 0 || rarity > 2) {
            std::cout << "[WARNING] The given rarity for " << item.name << " is not valid"
                      << "it needs to be over 0 " << "(line " << line_index << ")" << std::endl;
            rarity = 0;
        }
        item.rarity = rarity;
    }
    if (is_key(line, "type")) {
        std::string type_str = extract_value_from_key(line);
        item.type = get_type_from_str(type_str);
    }
    if (is_key(line, "effect")) {
        std::string effect_str = extract_value_from_key(line);
        item.effect = get_effect_from_str(effect_str);
    }
    if (is_key(line, "amount")) {
        std::string amount_str = extract_value_from_key(line);
        int amount = convert_to_int(amount_str);
        if (amount == -1) {
            std::cout << "[WARNING] The given amount for " << item.name << " is not an int "
                      << "(line " << line_index << ")" << std::endl;
            amount = 0;
        }
        if (amount < 0) {
            std::cout << "[WARNING] The given amount for " << item.name << " is not valid"
                      << "it needs to be over 0 " << "(line " << line_index << ")" << std::endl;
            amount = 0;
        }

        item.amount = amount;
    }
}

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
                std::cout << "[ERROR] Nested '[' for " << item.name << "'s description" << std::endl;
                exit(1);
            }
            replacing = true;
        }
        if (c == ']') {
            if (!replacing) {
                std::cout << "[ERROR] Dectected ']' without opening '[' for " << item.name
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

std::unordered_map<std::string, item_t> load_items(texture_dict &textures) {
    std::unordered_map<std::string, item_t> items =  {};

    std::ifstream file ("assets/items/weapons");
    if (!file.is_open()) {
        exit(1);
    }

    bool in_item = false;
    item_t current_item = {};
    std::string item_name;

    std::string line;
    size_t line_index = 0;
    while (getline(file, line)) {
        line_index++;
        std::string read;
        for (const char &c : line) {
            if (c == '#') break;
            if (c == '}') {
                if (!in_item) {
                    std::cout << "[ERROR] Unexpected '}' on line " << line_index << std::endl;
                    exit(1);
                }
                in_item = false;
                if (current_item.texture == NULL) {
                    std::cout << "[WARNING] No texture provided for " << item_name << std::endl;
                    current_item.texture = textures.get_texture_by_name("error");
                }
                current_item.id = items.size() + 1;
                replace_description(current_item);
                items[item_name] = current_item;
                current_item = {};
            }
            else if (c == '{') {
                if (in_item) {
                    std::cout << "[ERROR] Unexpected '{' on line " << line_index << std::endl;
                    exit(1);
                }
                in_item = true;
                read.erase(std::remove_if(read.begin(), read.end(), ::isspace), read.end());
                item_name = read;
            }
            else {
                read += c;
            }
        }
        read = remove_trailing_whitespaces(read);
        parse_line(read, line_index, current_item, textures);
    }
    return items;
}
