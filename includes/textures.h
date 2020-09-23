#ifndef TEXTURES_H
#define TEXTURES_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <unordered_map>
#include "item.h"

typedef struct {
    std::unordered_map<std::string, SDL_Texture*> textures = {};
    SDL_Texture * get_texture_by_name(std::string name);
    SDL_Texture * load_texture(SDL_Renderer *renderer, std::string name, const char *path);
    void free();

} texture_dict;

texture_dict load_textures(SDL_Renderer *renderer);
void load_items_textures(std::unordered_map<std::string, item_t> &items, texture_dict &textures);

#endif
