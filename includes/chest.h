#ifndef CHEST_H
#define CHEST_H

#include <SDL2/SDL.h>
#include "textures.h"
#include "camera.h"
#include "vec2.h"
#include "slot.h"
#include "item.h"
#include "inventory.h"

typedef struct {
    vec2i pos;
    inventory_t inventory = {};
} chest_t;

#endif
