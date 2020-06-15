#ifndef INVENTORY_H
#define INVENTORY_H

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include "camera.h"
#include "textures.h"
#include "item.h"
#include "fonts.h"
#include "vec2.h"

int constexpr INVENTORY_SIZE = 8;
int constexpr SLOT_SIZE = 75;
int constexpr SPACING = 25;

typedef struct {
    SDL_Rect inv_rect = {};
    int slot_size = 0;
    SDL_Rect slot_base_rect = {};

    void init_inventory();
    void add_item(item_t item);
    void render(camera_t &camera, texture_dict &textures);
    void update(camera_t &camera);

    item_t *slot_hovered(vec2i mp);

    void remove_item(item_t *item);

    void open(bool in_chest, bool is_chest);
    void toggle_inventory();
    void close_inventory();

    item_t slots[INVENTORY_SIZE] = {};
    bool active = false;

    bool in_chest = false;
    bool is_chest = false;
} inventory_t;


void render_tooltip(camera_t &camera, texture_dict &textures,
                    item_t *item, TTF_Font *font, vec2i mouse_position);

#endif
