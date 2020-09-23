#include "textures.h"

SDL_Texture * texture_dict::get_texture_by_name(std::string name) {
    if (textures.find(name) == textures.end()) {
        std::cout << "texture \"" << name << "\" not found" << std::endl;
        return textures["error"];
    }
    return textures[name];
}

SDL_Texture *texture_dict::load_texture(SDL_Renderer *renderer, std::string name, const char *path){
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
    textures.load_texture(renderer,  "error", "assets/images/error_texture.png");
    // TILES
    textures.load_texture(renderer,  "wall_top",           "assets/images/wall_top.png");
    textures.load_texture(renderer,  "wall_bottom",        "assets/images/wall_bottom.png");
    textures.load_texture(renderer,  "wall_left",          "assets/images/wall_left.png");
    textures.load_texture(renderer,  "wall_right",         "assets/images/wall_right.png");
    textures.load_texture(renderer,  "wall_bottom_left",   "assets/images/wall_bottom_left.png");
    textures.load_texture(renderer,  "wall_bottom_right",  "assets/images/wall_bottom_right.png");
    textures.load_texture(renderer,  "ground",             "assets/images/ground.png");
    textures.load_texture(renderer,  "door_front",         "assets/images/door_front.png");
    textures.load_texture(renderer,  "door_back",          "assets/images/door_back.png");
    textures.load_texture(renderer,  "door_side_left",     "assets/images/door_side_left.png");
    textures.load_texture(renderer,  "door_side_right",    "assets/images/door_side_right.png");
    textures.load_texture(renderer,  "chest",              "assets/images/chest.png");


    //ITEMS
    textures.load_texture(renderer,  "healing_potion",  "assets/images/healing_potion.png");
    textures.load_texture(renderer,  "sword",           "assets/images/sword.png");
    textures.load_texture(renderer,  "wand",            "assets/images/wand.png");
    textures.load_texture(renderer,  "ds",              "assets/images/ds.png");


    //UI
    textures.load_texture(renderer,  "bg",       "assets/images/inventory_background.png");
    textures.load_texture(renderer,  "hovered",  "assets/images/hovered.png");
    textures.load_texture(renderer,  "selected", "assets/images/selected.png");
    textures.load_texture(renderer,  "slot",     "assets/images/slot.png");


    // CHARACTERS
    textures.load_texture(renderer,  "player0",   "assets/images/player0.png");
    textures.load_texture(renderer,  "player1",   "assets/images/player1.png");
    textures.load_texture(renderer,  "player2",   "assets/images/player2.png");
    textures.load_texture(renderer,  "player3",   "assets/images/player3.png");
    textures.load_texture(renderer,  "ennemy",    "assets/images/ennemy.png");
    return textures;
}

void load_items_textures(std::unordered_map<std::string, item_t> &items, texture_dict &textures) {
    for (auto& item : items) {
        item.second.texture = textures.get_texture_by_name(item.second.texture_name);
    }
}
