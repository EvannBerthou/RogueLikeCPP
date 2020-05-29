#include <cmath>
#include "room.h"

void room_t::render (camera_t &camera, int offset){
    SDL_Rect rect = {this->x * (15 * camera.tile_size + offset),
                     this->y * (11 * camera.tile_size + offset),
                     15*camera.tile_size,11*camera.tile_size};
    camera.render_texture(this->static_texture, &rect);

    for (auto &item: this->items) {
        SDL_Rect rect = {this->x * (15 * camera.tile_size + offset) + item.x * camera.tile_size,
                         this->y * (11 * camera.tile_size + offset) + item.y * camera.tile_size
                         + (int)(sin(item.angle) * 8),
                         camera.tile_size, camera.tile_size};
        camera.render_texture(item.item.texture, &rect);
    }

    for (auto &chest: this->chests) {
        SDL_Rect rect = {this->x * (15 * camera.tile_size + offset) + chest.x * camera.tile_size,
                         this->y * (11 * camera.tile_size + offset) + chest.y * camera.tile_size,
                         camera.tile_size, camera.tile_size};
        camera.render_texture(chest.texture, &rect);
    }
}
