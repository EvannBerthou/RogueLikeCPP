#ifndef ITEM_H
#define ITEM_H

#include <SDL2/SDL.h>
#include <string>

enum class ItemType { Undefined, Weapon, Armor, Effect};
enum class ItemEffect { None, Heal, Damage};

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
