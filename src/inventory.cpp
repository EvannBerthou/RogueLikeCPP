#include <iostream>
#include "inventory.h"

static SDL_Color color_from_rarity(int rarity) {
    switch(rarity) {
    case 0: return {255,255,255,255};
    case 1: return {0,255,255,255};
    case 2: return {255,0,255,255};
    }
    return {255,255,255,255};
}

void render_tooltip(camera_t &camera, texture_dict &textures,
                    item_t *item, TTF_Font *font, vec2i mp) {
    SDL_Rect rect = { mp.x, mp.y, (int)(225 * camera.scale), (int)(125 * camera.scale) };
    camera.render_texture_static(textures.get_texture_by_name("ui_bg"), &rect);
    render_text(camera.renderer, font, item->name.c_str(), mp + vec2i(20,10) * camera.scale,
                color_from_rarity(item->rarity));
    render_text(camera.renderer, font, item->description.c_str(), mp + vec2i(20,30) * camera.scale,
                {255,255,255,255});

    if (item->type == ItemType::Sword) {
        std::string stat = "Strength : " + std::to_string(item->amount);
        render_text(camera.renderer, font, stat.c_str(), mp + vec2i(20,50) * camera.scale,{255,0,255,255});
    }
    if (item->type == ItemType::Wand) {
        std::string stat = "Magic : " + std::to_string(item->amount);
        render_text(camera.renderer, font, stat.c_str(), mp + vec2i(20,50) * camera.scale,{255,0,255,255});
    }
}

void inventory_t::init_inventory() {
    for (size_t i = 0; i < INVENTORY_SIZE; i++)
    {
        slots[i].id = -1;
    }
}

void inventory_t::add_item(item_t item) {
    for (size_t i = 0; i < INVENTORY_SIZE; i++)
    {
        item_t *slot_item = &slots[i];
        if (slot_item->id == -1) {
            slots[i] = item;
            return;
        }
    }
}

void inventory_t::update(camera_t &camera) {
    int w = (int)((SLOT_SIZE * 4 + 50) * camera.scale);
    int h = (int)((SLOT_SIZE * 2 + 50) * camera.scale);
    int offset_x = camera.w / 2 - w / 2;
    int offset_y = camera.h / 2 - h / 2;

    if (is_chest)
        offset_y += (SLOT_SIZE + SPACING + 5) * camera.scale;
    else if (in_chest)
        offset_y -= (SLOT_SIZE + SPACING + 5) * camera.scale;

    inv_rect = { offset_x, offset_y, w, h };

    slot_size = (int)(SLOT_SIZE * camera.scale);
    slot_base_rect = {(int)(inv_rect.x + SPACING * camera.scale),
                      (int)(inv_rect.y + SPACING * camera.scale),
                      slot_size, slot_size };
}

void inventory_t::render(camera_t &camera, texture_dict &textures) {
    if (!active)
        return;

    camera.render_texture_static(textures.get_texture_by_name("ui_bg"), &inv_rect);

    for (int i = 0; i < INVENTORY_SIZE; i++)
    {
        SDL_Rect slot_rect = { i % (INVENTORY_SIZE / 2) * slot_size + slot_base_rect.x,
                               i / (INVENTORY_SIZE / 2) * slot_size + slot_base_rect.y,
                               slot_size, slot_size};
        camera.render_texture_static(textures.get_texture_by_name("slot"), &slot_rect);

        if (slots[i].id > 0) {
            scale_rect(slot_rect, 0.75);
            if (slots[i].texture == NULL)
                std::cout << "no texture for this slot " << i  << std::endl;
            camera.render_texture_static(slots[i].texture, &slot_rect);
        }
    }
}

item_t *inventory_t::slot_hovered(vec2i mp) {
    if (!active)
        return NULL;

    for (int i = 0; i < INVENTORY_SIZE; i++)
    {
        SDL_Rect rect = { i % (INVENTORY_SIZE / 2) * slot_size + slot_base_rect.x,
                          i / (INVENTORY_SIZE / 2) * slot_size + slot_base_rect.y,
                          slot_size, slot_size};
        if (mp.x > rect.x && mp.x < rect.x + rect.w && mp.y > rect.y && mp.y < rect.y + rect.h) {
            item_t *slot = &slots[i];
            if (slot->id > 0)
                return slot;
        }
    }
    return NULL;
}

void inventory_t::remove_item(item_t *item) {
    for (int i = 0; i < INVENTORY_SIZE; ++i) {
        if (&slots[i] == item) {
            slots[i].id = -1;
            slots[i].texture = NULL;
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
