#ifndef WORLD_ITEM_H
#define WORLD_ITEM_H

#include <cmath>
#include "item.h"

typedef struct {
    int x,y;
    item_t item;
    double angle = 0;

    void update(double dt) {
        angle = fmod(angle + dt / 200, 2 * 3.14);
    }

} world_item_t;

#endif
