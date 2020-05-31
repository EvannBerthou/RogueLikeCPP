#include "enemy.h"

void enemy_t::render(camera_t &camera) {
    if (!alive) return;
    camera.render_texture_to_room(texture, {x,y});
}

void enemy_t::take_damage(int amount) {
    stats.health -= amount;
    if (stats.health <= 0) alive = false;
}
