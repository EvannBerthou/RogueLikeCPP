#include <iostream>
#include "camera.h"
#include "vec2.h"

void camera_t::update(double dt){
    if (in_transisition){
        if (transition_time < transition_distance){
            transition_time += dt;
            x += dir.x * dt;
            y += dir.y * dt;
        }
        else{
            x = moving_to.x;
            y = moving_to.y;
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
    if (texture == NULL) {
        std::cout << "no texture" << std::endl;
        exit(1);
    }
    rect->x -= x;
    rect->y -= y;
    SDL_RenderCopyEx(renderer, texture, NULL, rect, 0, NULL, flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}
void camera_t::render_texture_static(SDL_Texture *texture, SDL_Rect *rect, bool flip) {
    if (texture == NULL) {
        std::cout << "no texture" << std::endl;
        exit(1);
    }
    SDL_RenderCopyEx(renderer, texture, NULL, rect, 0, NULL, flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}

void camera_t::begin_transistion(vec2i from, vec2i to) {
    dir = vec2((to.x - from.x), (to.y - from.y)).normalized();
    if (dir.x != 0) transition_distance = 15.0f * tile_size + tile_size * 2;
    if (dir.y != 0) transition_distance = 11.0f * tile_size + tile_size * 2;

    transition_time = 0;
    in_transisition = true;
    moving_to = to;
}

void camera_t::rect_room_to_screen(SDL_Rect &rect) {
    int center_x = w / 2 - (15*tile_size) / 2;
    int center_y = h / 2 - (11*tile_size) / 2;
    rect.x = rect.x * tile_size + center_x;
    rect.y = rect.y * tile_size + center_y;
}

vec2i camera_t::vec2_screen_to_room(vec2i vec) {
    vec2i result(0,0);
    result.x = (vec.x - (w / 2 - (15*tile_size) / 2)) / tile_size;
    result.y = (vec.y - (h / 2 - (11*tile_size) / 2)) / tile_size;
    return result;
}

void camera_t::render_texture_to_room(SDL_Texture *texture, vec2i position, bool flip) {
    if (texture == NULL) {
        std::cout << "no texture" << std::endl;
        exit(1);
    }
    SDL_Rect rect = {position.x, position.y, tile_size, tile_size};
    rect_room_to_screen(rect);
    render_texture_static(texture, &rect, flip);
}
