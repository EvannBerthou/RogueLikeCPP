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

    SDL_Texture * get_texture_by_name(std::string name) {
        if (textures.find(name) == textures.end()) {
            std::cout << "texture \"" << name << "\" not found" << std::endl;
            return NULL;
        }
        return textures[name];
    }

    SDL_Texture *load_texture(SDL_Renderer *renderer, std::string name, const char *path){
        SDL_Texture *text = IMG_LoadTexture(renderer, path);
        if (text == NULL) {
            std::cout << "error while loading " << path << std::endl;
            return NULL;
        }
        textures[name] = text;
        return text;
    }

    void free() {
        for (auto t : textures)
            SDL_DestroyTexture(t.second);
        textures.clear();
    }

} texture_dict;

texture_dict load_textures(SDL_Renderer *renderer);
void load_items_textures(std::unordered_map<std::string, item_t> &items, texture_dict &textures);

#endif
