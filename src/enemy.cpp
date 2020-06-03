#include "enemy.h"

void enemy_t::take_damage(int amount) {
    stats.health -= amount;
    if (stats.health <= 0) stats.alive = false;
}
