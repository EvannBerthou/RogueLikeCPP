#ifndef ITEM_H
#define ITEM_H

#include <SDL2/SDL.h>
#include <string>

// Order based on indexes for equipment_item
enum ItemType {
    Sword = 0,
    Helmet,
    Wand,
    Chestplate,
    Ring,
    Pants,
    Effect,
    Undefined
};

enum ItemEffect { Heal = 0, Damage, None};

typedef struct item_t {
    int id;
    SDL_Texture *texture;
    std::string name;
    std::string description;
    int rarity;
    ItemType type;
    ItemEffect effect;
    int amount;
    int range;

    item_t random_stats() {
        item_t new_item = *this;
        int min = amount - range;
        int max = amount + range;
        new_item.amount = (rand() % (max - min + 1) + min);
        return new_item;
    }
} item_t;

#endif
