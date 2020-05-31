#include "textures.h"

void load_room_textures(texture_dict &textures, SDL_Renderer *renderer) {
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
}

void load_item_textures(texture_dict &textures, SDL_Renderer *renderer) {
    textures.load_texture(renderer,  "healing_potion",  "assets/images/healing_potion.png");
    textures.load_texture(renderer,  "slot",            "assets/images/slot.png");
    textures.load_texture(renderer,  "bg",              "assets/images/inventory_background.png");
    textures.load_texture(renderer,  "sword",           "assets/images/sword.png");
    textures.load_texture(renderer,  "wand",            "assets/images/wand.png");
    textures.load_texture(renderer,  "ds",              "assets/images/ds.png");
    textures.load_texture(renderer,  "chest",           "assets/images/chest.png");
    textures.load_texture(renderer,  "hovered",         "assets/images/hovered.png");
    textures.load_texture(renderer,  "selected",        "assets/images/selected.png");
    textures.load_texture(renderer,  "error",           "assets/images/error_texture.png");
}

void load_characters_textures(texture_dict &textures, SDL_Renderer *renderer) {
    textures.load_texture(renderer,  "player0",   "assets/images/player0.png");
    textures.load_texture(renderer,  "player1",   "assets/images/player1.png");
    textures.load_texture(renderer,  "player2",   "assets/images/player2.png");
    textures.load_texture(renderer,  "player3",   "assets/images/player3.png");
    textures.load_texture(renderer,  "ennemy",    "assets/images/ennemy.png");
}
