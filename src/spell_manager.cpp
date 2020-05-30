#include "spell_manager.h"

static bool is_hovered(SDL_Rect &rect, int m_x, int m_y) {
    return (m_x > rect.x && m_x < rect.x + rect.w && m_y > rect.y && m_y < rect.y + rect.h);
}

void spells_t::select_spell(camera_t &camera, int p_x, int p_y, int m_x, int m_y) {
    int bar_width  = spells.size() * 50;
    int offset_x = 400 - bar_width / 2;
    for (int i = 0; i < (int)spells.size(); ++i) {
        SDL_Rect spell_rect = {offset_x + 50 * i, camera.h - 50, 50,50};
        if (is_hovered(spell_rect, m_x, m_y)) {
            if (selected_spell == i) { selected_spell = -1; std::cout << "unselect" << std::endl;}
            else {
                selected_spell = i;
                spells.at(selected_spell).set_spell_zone(p_x, p_y);
            }
            return;
        }
    }
}

void spells_t::cast(camera_t &camera, int m_x, int m_y) {
    if (selected_spell == -1) return;
    auto hovered = spells.at(selected_spell).get_hovered(camera, m_x, m_y);
    if (hovered == NULL)
        std::cout << "outside of range" << std::endl;
    else
        std::cout << "casting to : " << hovered->first << " " << hovered->second << std::endl;
}

void spells_t::render(camera_t &camera, texture_dict &textures, int m_x, int m_y) {
    int bar_width  = spells.size() * 50;
    int offset_x = camera.w / 2 - bar_width / 2;
    for (int i = 0; i < (int)spells.size(); ++i) {
        SDL_Rect spell_rect = {offset_x + 50 * i, camera.h - 50, 50,50};
        camera.render_texture_static(textures.get_texture_by_name("slot"), &spell_rect);
        camera.render_texture_static(spells.at(i).texture, &spell_rect);
        if (is_hovered(spell_rect, m_x, m_y))
            camera.render_texture_static(textures.get_texture_by_name("hovered"), &spell_rect);
        if  (i == selected_spell)
            camera.render_texture_static(textures.get_texture_by_name("selected"), &spell_rect);
    }

    if (selected_spell != -1) {
        spells.at(selected_spell).render_zone(camera, textures, m_x, m_y);
    }
}
