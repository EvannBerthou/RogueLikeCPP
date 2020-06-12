#include <iostream>
#include "inventory.h"

static SDL_Color color_from_rarity(int rarity) {
    switch(rarity) {
    case 0: return {255,255,255,255};
    case 1: return {0,255,255,255};
    }
    return {255,255,255,255};
}

void render_tooltip(camera_t &camera, texture_dict &textures,
                                 item_t *item, TTF_Font *font, vec2i mp) {
    SDL_Rect rect = { mp.x, mp.y, 225, 125 };
    camera.render_texture_static(textures.get_texture_by_name("bg"), &rect);
    render_text(camera.renderer, font, item->name.c_str(),{mp.x+20,mp.y+10},
                color_from_rarity(item->rarity));
    render_text(camera.renderer, font, item->description.c_str(), {mp.x+20,mp.y+30}, {255,255,255,255});
}

void inventory_t::init_inventory() {
    for (size_t i = 0; i < INVENTORY_SIZE; i++)
    {
        slots[i].item.id = -1;
        slots[i].item_count = 0;
        slots[i].item.texture = NULL;
        slots[i].item.description = "";
    }
}

void inventory_t::add_item(item_t item) {
    for (size_t i = 0; i < INVENTORY_SIZE; i++)
    {
        slot_t* slot = &slots[i];
        if (slot->item.id == item.id && slot->item_count < 3) {
            slot->item_count++;
            return;
        }

        if (slot->item.id == -1) {
            slot->item = item;
            slot->item_count++;
            return;
        }
    }
}

void inventory_t::render(camera_t &camera, texture_dict &textures) {
    if (!active) return;
    float scale = (camera.w < 800 || camera.h < 600)? 0.5 : 1;
    int w = (int)((SLOT_SIZE * 4 + 50) * scale);
    int h = (int)((SLOT_SIZE * 2 + 50) * scale);
    int offset_x = camera.w / 2 - w / 2;
    int offset_y = camera.h / 2 - h / 2;

    if (in_chest)
        offset_y -= (SLOT_SIZE + SPACING) * scale;

    if (is_chest)
        offset_y += ((SLOT_SIZE + SPACING) * 2) * scale;

    SDL_Rect bg_rect = { offset_x, offset_y, w, h };
    camera.scale_rect_with_offset(bg_rect, {-10,-10}, {15,15});
    camera.render_texture_static(textures.get_texture_by_name("bg"), &bg_rect);

    for (int i = 0; i < INVENTORY_SIZE; i++)
    {
        SDL_Rect rect = { i % (INVENTORY_SIZE / 2) * (int)(SLOT_SIZE * scale) + offset_x,
                          i / (INVENTORY_SIZE / 2) * (int)(SLOT_SIZE * scale) + offset_y,
                          0,0 };
        camera.scale_rect_with_offset(rect, { 20, 20 }, { SLOT_SIZE, SLOT_SIZE});
        camera.render_texture_static(textures.get_texture_by_name("slot"), &rect);

        if (slots[i].item_count > 0) {
            rect = { i % (INVENTORY_SIZE / 2) * (int)(SLOT_SIZE * scale) + offset_x,
                     i / (INVENTORY_SIZE / 2) * (int)(SLOT_SIZE * scale) + offset_y,
                     0,0 };
            camera.scale_rect_with_offset(rect, { 35, 35 }, { SLOT_SIZE - 30, SLOT_SIZE - 30});
            if (slots[i].item.texture == NULL)
                std::cout << "no texture for this slot " << i  << std::endl;
            camera.render_texture_static(slots[i].item.texture, &rect);
        }
    }
}

slot_t *get_hovered_slot(int x, int y, float scale, camera_t &camera, vec2i mp, slot_t slots[]) {
    for (int i = 0; i < INVENTORY_SIZE; i++)
    {
        SDL_Rect rect = { i % (INVENTORY_SIZE / 2) * (int)(SLOT_SIZE * scale) + x,
                          i / (INVENTORY_SIZE / 2) * (int)(SLOT_SIZE * scale) + y,
                          0,0 };
        camera.scale_rect_with_offset(rect, { 20, 20 }, { SLOT_SIZE, SLOT_SIZE});
        if (mp.x > rect.x && mp.x < rect.x + rect.w && mp.y > rect.y && mp.y < rect.y + rect.h) {
            return &slots[i];
        }
    }
    return NULL;
}

item_t *inventory_t::slot_hovered(camera_t &camera, vec2i mp) {
    if (!active) return NULL;
    float scale = (camera.w < 800 || camera.h < 600) ? 0.5 : 1;
    int w = (int)((SLOT_SIZE * 4 + 50) * scale);
    int h = (int)((SLOT_SIZE * 2 + 50) * scale);
    int offset_x = camera.w / 2 - w / 2;
    int offset_y = camera.h / 2 - h / 2;

    if (in_chest)
        offset_y -= (SLOT_SIZE + SPACING) * scale;

    if (is_chest)
        offset_y += ((SLOT_SIZE + SPACING) * 2) * scale;

    slot_t *slot = get_hovered_slot(offset_x, offset_y, scale, camera, mp, slots);
    if (slot != NULL && slot->item.id != -1)
        return &slot->item;
    return NULL;
}

void inventory_t::remove_item(item_t *item) {
    for (int i = 0; i < INVENTORY_SIZE; ++i) {
        if (&slots[i].item == item) {
            slots[i].item.id = -1;
            slots[i].item_count = 0;
            return;
        }
    }
}

void inventory_t::open(bool in_chest, bool is_chest) {
    active = true;
    this->in_chest = in_chest;
    this->is_chest = is_chest;
}

void inventory_t::toggle_inventory() {
    if (active) close_inventory();
    else open(false, false);
}

void inventory_t::close_inventory() {
    active = false;
    in_chest = false;
    is_chest = false;
}
