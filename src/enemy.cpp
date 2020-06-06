#include "enemy.h"

void enemy_t::take_damage(int amount) {
    stats.health -= amount;
    if (stats.health <= 0) stats.alive = false;
}

void enemy_t::render(camera_t &camera, vec2i offset) {
    SDL_Rect rect = {offset.x + pos.x * camera.tile_size,
                     offset.y + pos.y * camera.tile_size,
                     camera.tile_size, camera.tile_size};
    camera.render_texture(texture, &rect);

    if (!camera.in_transisition) {
        SDL_Rect health_rect = {pos.x, pos.y, (int)(stats.health) / 2, 10};
        camera.rect_room_to_screen(health_rect);
        health_rect.y -= 10;
        camera.render_fill_rect_static({222,23,56,255}, &health_rect);
    }
}
