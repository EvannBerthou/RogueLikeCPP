#ifndef CAMERA_H
#define CAMERA_H

#include <SDL2/SDL.h>
#include "vec2.h"

typedef struct camera_t {
    SDL_Renderer *renderer;
    float x = -5;
    float y = -5;
    int w = 0, h = 0;
    int tile_size = 50;

    void render_fill_rect_static(SDL_Color color, SDL_Rect *rect);
    void render_fill_rect(SDL_Color color, SDL_Rect *rect);
    void render_texture(SDL_Texture *texture, SDL_Rect *rect, bool flip = false);
    void render_texture_static(SDL_Texture *texture, SDL_Rect *rect, bool flip = false);
    void render_texture_to_room(SDL_Texture *texture, vec2i position, bool flip = false);

    void rect_room_to_screen(SDL_Rect &rect);
    vec2i vec2_screen_to_room(vec2i vec);

    void update(double dt);
    void begin_transistion(vec2i from, vec2i to);
    void begin_shake();

    void scale_rect_with_offset(SDL_Rect &rect, vec2i offset, vec2i size_offset);

    vec2i moving_to = vec2i(0,0);
    vec2 dir = vec2(0,0);
    bool in_transisition = false;
    float transition_distance = 0;
    float transition_time = 0;

    bool shaking = false;
    vec2i original = vec2i(0,0);
    float elapsed = 0.0f;

} camera_t;

#endif
