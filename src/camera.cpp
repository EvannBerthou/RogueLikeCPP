#include <iostream>
#include "camera.h"
#include "vec2.h"

camera_t::camera_t(SDL_Renderer *r){
    renderer = r;
}

void camera_t::update(double dt){
    if (in_transisition){
        if (transition_time < transition_distance){
            transition_time += dt;
            x += dir.x * dt;
            y += dir.y * dt;
        }
        else{
            x = to_x;
            y = to_y;
            in_transisition = false;
        }
    }
}

void camera_t::render_fill_rect_static(SDL_Color color, SDL_Rect *rect){
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, rect);
}

void camera_t::render_fill_rect(SDL_Color color, SDL_Rect *rect){
    rect->x -= x;
    rect->y -= y;
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, rect);
}

void camera_t::render_texture(SDL_Texture *texture, SDL_Rect *rect, bool flip){
    rect->x -= x;
    rect->y -= y;
    SDL_RenderCopyEx(renderer, texture, NULL, rect, 0, NULL, flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}
void camera_t::render_texture_static(SDL_Texture *texture, SDL_Rect *rect, bool flip) {
    SDL_RenderCopyEx(renderer, texture, NULL, rect, 0, NULL, flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}

void camera_t::begin_transistion(float from_x, float from_y, float to_x, float to_y){
    dir = vec2((to_x - from_x), (to_y - from_y)).normalized();
    if (dir.x != 0) transition_distance = 15.0f * tile_size + tile_size * 2;
    if (dir.y != 0) transition_distance = 11.0f * tile_size + tile_size * 2;

    transition_time = 0;
    in_transisition = true;

    this->to_x = to_x;
    this->to_y = to_y;
}
