#ifndef CHEST_H
#define CHEST_H

#include <SDL2/SDL.h>
#include "camera.h"
#include "vec2.h"

typedef struct {
    vec2i pos;
    SDL_Texture *texture;

    void render(camera_t &camera);
} chest_t;

#endif
