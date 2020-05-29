#ifndef SLOT_H
#define SLOT_H

#include <SDL2/SDL.h>
#include <cstddef>
#include "item.h"

typedef struct {
    item_t item;
    size_t item_count;
} slot_t;

#endif
