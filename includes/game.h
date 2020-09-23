#ifndef GAME_H
#define GAME_H

#include <chrono>
#include "camera.h"
#include "dungeon.h"
#include "player.h"
#include "dungeon.h"
#include "camera.h"
#include "fonts.h"
#include "textures.h"

typedef struct {
    using clock = std::chrono::time_point<std::chrono::steady_clock>;
    clock LAST = std::chrono::steady_clock::now();
    clock NOW  = std::chrono::steady_clock::now();
    double dt = 0;

    void tick() {
        NOW = std::chrono::steady_clock::now();
        std::chrono::duration<double, std::milli> diff = (NOW - LAST);
        dt = diff.count();
        //std::cout << 1 / dt * 1000 << std::endl;
        LAST = NOW;
    }
} fps_clock_t;

typedef struct game_t {
    dungeon_t    dungeon;
    player_t     player;
    camera_t     camera;
    fps_clock_t  fps_clock;
    TTF_Font     *full_font;
    TTF_Font     *half_font;

    std::unordered_map<std::string, item_t> items;
    texture_dict textures;

    SDL_Window *window;
    int offset;
    vec2i mouse_position;
    int turn_count;

    TTF_Font * get_font();
    void key_press(SDL_Event &event);
    void update();
    void render();
    void new_turn();

    int init();
    void run();
    void exit();
} game_t;

#endif
