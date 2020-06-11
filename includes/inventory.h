#ifndef INVENTORY_H
#define INVENTORY_H

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include "slot.h"
#include "camera.h"
#include "textures.h"
#include "item.h"
#include "fonts.h"
#include "vec2.h"

int constexpr INVENTORY_SIZE = 8;
int constexpr SLOT_SIZE = 100;
int constexpr SPACING = 30;

typedef struct {
    void init_inventory();
    void add_item(item_t *item);
    void render(camera_t &camera, texture_dict &textures);

    item_t *slot_hovered(camera_t &camera, vec2i mp);

    void remove_item(item_t *item);

    void open(bool in_chest, bool is_chest);
    void toggle_inventory();
    void close_inventory();

    slot_t slots[INVENTORY_SIZE] = {};
    bool active = false;

    bool in_chest = false;
    bool is_chest = false;
} inventory_t;


void render_tooltip(camera_t &camera, texture_dict &textures,
                    item_t *item, TTF_Font *font, vec2i mouse_position);

#endif
