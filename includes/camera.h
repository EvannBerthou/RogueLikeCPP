#ifndef CAMERA_H
#define CAMERA_H

#include <SDL2/SDL.h>
#include "vec2.h"
struct room_t;
typedef struct room_t room_t;
#include "room.h"

typedef struct camera_t {
    float x = -5;
    float y = -5;
    int w = 0, h = 0;
    int tile_size = 50;
    SDL_Renderer *renderer;

    camera_t(SDL_Renderer *r);
    void render_fill_rect_static(SDL_Color color, SDL_Rect *rect);
    void render_fill_rect(SDL_Color color, SDL_Rect *rect);
    void render_texture(SDL_Texture *texture, SDL_Rect *rect, bool flip = false);
    void render_texture_static(SDL_Texture *texture, SDL_Rect *rect, bool flip = false);

    void update(double dt);
    void begin_transistion(room_t *from, room_t *to);
    room_t *prev_room = NULL;

    float to_x = 0;
    float to_y = 0;
    vec2 dir = vec2(0,0);
    bool in_transisition = false;
    float transition_distance = 0;
    float transition_time = 0;

} camera_t;

#endif
