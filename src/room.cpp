#include <cmath>
#include "room.h"

void room_t::render (camera_t &camera, int offset){
    int offset_x = this->x * (15 * camera.tile_size + offset);
    int offset_y = this->y * (11 * camera.tile_size + offset);
    int center_x = (camera.w / 2) - ((15 * camera.tile_size + 50) / 2);
    int center_y = (camera.h / 2) - ((11 * camera.tile_size + 50) / 2);

    SDL_Rect rect = {offset_x + center_x, offset_y + center_y,
                     15*camera.tile_size,11*camera.tile_size};
    camera.render_texture(this->static_texture, &rect);

    for (auto &item: this->items) {
        SDL_Rect rect = {offset_x + center_x + item.x * camera.tile_size,
                         offset_y + center_y + item.y * camera.tile_size + (int)(sin(item.angle) * 8),
                         camera.tile_size, camera.tile_size};
        camera.render_texture(item.item.texture, &rect);
    }

    for (auto &chest: this->chests) {
        SDL_Rect rect = {offset_x + center_x + chest.x * camera.tile_size,
                         offset_y + center_y + chest.y * camera.tile_size,
                         camera.tile_size, camera.tile_size};
        camera.render_texture(chest.texture, &rect);
    }

    for (auto &enemy: this->enemies) enemy.render(camera);
}

void room_t::update(float dt) {
    for (auto &item: items)
        item.update(dt);
}
