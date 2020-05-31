#ifndef CHEST_H
#define CHEST_H

#include <SDL2/SDL.h>
#include "camera.h"

typedef struct {
    int x,y;
    SDL_Texture *texture;

    void render(camera_t &camera);
} chest_t;

#endif
