#include <stdio.h>
#include <dirent.h>
#include "textures.h"

SDL_Texture * texture_dict::get_texture_by_name(std::string name) {
    if (textures.find(name) == textures.end()) {
        std::cout << "texture \"" << name << "\" not found" << std::endl;
        return textures["error"];
    }
    return textures[name];
}

SDL_Texture *texture_dict::load_texture(SDL_Renderer *renderer, std::string name, const char *path) {
    SDL_Texture *text = IMG_LoadTexture(renderer, path);
    if (text == NULL) {
        std::cout << "error while loading " << path << std::endl;
        return NULL;
    }
    textures[name] = text;
    return text;
}

void texture_dict::free() {
    for (auto t : textures)
        SDL_DestroyTexture(t.second);
    textures.clear();
}

// TODO: Rewrite to load all sprites in a folder
texture_dict load_textures(SDL_Renderer *renderer) {
    texture_dict textures;

    DIR *d;
    struct dirent *dir;
    std::string folderpath = "assets/images";
    d = opendir(folderpath.c_str());
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            std::string filename = std::string(dir->d_name);
            // filename ends with .png
            std::string ext = ".png";
            if (std::equal(ext.rbegin(), ext.rend(), filename.rbegin())) {
                filename.erase(filename.rfind('.'));
                std::string full_path = folderpath + "/" + filename + ext;
                textures.load_texture(renderer, filename, full_path.c_str());
            }
        }
        closedir(d);
    }
    return textures;
}

void load_items_textures(std::unordered_map<std::string, item_t> &items, texture_dict &textures) {
    for (auto& item : items) {
        item.second.texture = textures.get_texture_by_name(item.second.texture_name);
    }
}

