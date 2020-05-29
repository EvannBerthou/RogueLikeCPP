#include <iostream>
#include "inventory.h"

void inventory_t::init_inventory() {
    for (size_t i = 0; i < INVENTORY_SIZE; i++)
    {
        m_slots[i].item.id = -1;
        m_slots[i].item_count = 0;
        m_slots[i].item.texture = NULL;
        m_slots[i].item.description = "";
    }
}

void inventory_t::add_item(item_t *item) {
    for (size_t i = 0; i < INVENTORY_SIZE; i++)
    {
        slot_t* slot = &m_slots[i];
        if (slot->item.id == item->id && slot->item_count < 3) {
            slot->item_count++;
            return;
        }

        if (slot->item.id == -1) {
            slot->item = *item;
            slot->item_count++;
            return;
        }
    }
}

void inventory_t::render(camera_t &camera, texture_dict &textures) {
    if (!active) return;
    int constexpr inv_width  = INVENTORY_SIZE / 2 * SLOT_SIZE;
    int constexpr inv_height = SLOT_SIZE * 2;
    int offset_x = 400 - inv_width / 2;
    int offset_y = 300 - inv_height / 2;

    SDL_Rect bg_rect = { offset_x - 15, offset_x - 15, SLOT_SIZE * 4 + 50, SLOT_SIZE * 2 + 50};
    camera.render_texture_static(textures.get_texture_by_name("bg"), &bg_rect);

    for (int i = 0; i < INVENTORY_SIZE; i++)
    {
        SDL_Rect rect = { i % (INVENTORY_SIZE / 2) * SLOT_SIZE + offset_x + 15,
                          i / (INVENTORY_SIZE / 2) * SLOT_SIZE + offset_y + 15,
                          SLOT_SIZE, SLOT_SIZE };
        camera.render_texture_static(textures.get_texture_by_name("slot"), &rect);

        if (m_slots[i].item_count > 0) {
            SDL_Rect item_rect = {i % (INVENTORY_SIZE / 2) * SLOT_SIZE + offset_x + 30,
                                  i / (INVENTORY_SIZE / 2) * SLOT_SIZE + offset_y + 30,
                                  SLOT_SIZE - 30, SLOT_SIZE - 30 };
            camera.render_texture_static(m_slots[i].item.texture, &item_rect);
        }
    }
}

static SDL_Color color_from_rarity(int rarity) {
    switch(rarity) {
    case 0: return {255,255,255,255};
    case 1: return {0,255,255,255};
    }
    return {255,255,255,255};
}

void inventory_t::render_tooltip(camera_t &camera, texture_dict &textures,
                                 item_t *item, TTF_Font *font, int m_x,int m_y) {
    SDL_Rect rect = { m_x, m_y, 225, 125 };
    camera.render_texture_static(textures.get_texture_by_name("bg"), &rect);
    render_text(camera.renderer, font, item->name.c_str(),{m_x+20,m_y+10},color_from_rarity(item->rarity));
    render_text(camera.renderer, font, item->description.c_str(), {m_x+20,m_y+30}, {255,255,255,255});
}

item_t *inventory_t::slot_hovered(int m_x, int m_y) {
    if (!active) return NULL;
    int constexpr inv_width  = INVENTORY_SIZE / 2 * SLOT_SIZE;
    int constexpr inv_height = SLOT_SIZE * 2;
    int offset_x = 400 - inv_width / 2;
    int offset_y = 300 - inv_height / 2;

    for (int i = 0; i < INVENTORY_SIZE; i++)
    {
        SDL_Rect rect = { i % (INVENTORY_SIZE / 2) * SLOT_SIZE + offset_x + 15,
                          i / (INVENTORY_SIZE / 2) * SLOT_SIZE + offset_y + 15,
                          SLOT_SIZE, SLOT_SIZE };
        if (m_x > rect.x && m_x < rect.x + rect.w && m_y > rect.y && m_y < rect.y + rect.h) {
            if (m_slots[i].item.id > -1)
                return &m_slots[i].item;
            return NULL;
        }
    }
    return NULL;
}
