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

typedef struct {
    void init_inventory();
    void add_item(item_t *item);
    void render(camera_t &camera, texture_dict &textures);
    item_t *slot_hovered(camera_t &camera, vec2i mp);
    void render_tooltip(camera_t &camera, texture_dict &textures,
                        item_t *item, TTF_Font *font, vec2i mouse_position);
    void remove_item(item_t *item);

    slot_t m_slots[INVENTORY_SIZE] = {};
    bool active = false;
} inventory_t;

#endif
