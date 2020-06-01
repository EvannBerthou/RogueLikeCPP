#ifndef WORLD_ITEM_H
#define WORLD_ITEM_H

#include <cmath>
#include "item.h"
#include "vec2.h"

typedef struct {
    vec2i pos;
    item_t item;
    double angle = 0;

    void update(double dt) {
        angle = fmod(angle + dt / 200, 2 * 3.14);
    }

} world_item_t;

#endif
