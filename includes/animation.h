#ifndef ANIMATION_H
#define ANIMATION_H

#include <SDL2/SDL.h>
#include "textures.h"
#include "camera.h"

typedef struct {
    SDL_Texture **sprites;
    int frame;
    int frame_count;
    double frame_time;
    double animation_speed;

    void render(camera_t &camera, SDL_Rect *rect, bool flip = false);
    void update(double dt);
} animation_t;

animation_t load_animation(texture_dict &textures, std::string sprite_name);

#endif

