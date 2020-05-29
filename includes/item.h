#ifndef ITEM_H
#define ITEM_H

#include <SDL2/SDL.h>
#include <string>

typedef struct {
    int id;
    SDL_Texture *texture;
    std::string name;
    std::string description;
    int rarity;
} item_t;

#endif
