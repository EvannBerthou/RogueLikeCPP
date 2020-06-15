#ifndef ITEM_H
#define ITEM_H

#include <SDL2/SDL.h>
#include <string>

enum ItemType { Sword = 0, Wand, Armor, Effect, Undefined};
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
