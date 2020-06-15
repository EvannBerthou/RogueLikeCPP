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

typedef struct {
    int id;
    SDL_Texture *texture;
    std::string name;
    std::string description;
    int rarity;
    ItemType type;
    ItemEffect effect;
    int amount;
} item_t;

#endif
