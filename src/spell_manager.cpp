#include "spell_manager.h"

static bool is_hovered(SDL_Rect &rect, vec2i mp) {
    return (mp.x > rect.x && mp.x < rect.x + rect.w && mp.y > rect.y && mp.y < rect.y + rect.h);
}

void spells_t::select_spell(camera_t &camera, vec2i pp, vec2i mp) {
    int bar_width  = spells.size() * 50;
    int offset_x = camera.w / 2 - bar_width / 2;
    for (int i = 0; i < (int)spells.size(); ++i) {
        SDL_Rect spell_rect = {offset_x + 50 * i, camera.h - 50, 50,50};
        if (is_hovered(spell_rect, mp)) {
            if (selected_spell == i) { selected_spell = -1; std::cout << "unselect" << std::endl;}
            else {
                selected_spell = i;
                spells.at(selected_spell).set_spell_zone(pp);
            }
            return;
        }
    }
}

bool spells_t::cast(camera_t &camera, vec2i mp, room_t *room) {
    if (selected_spell == -1) return false;
    vec2i *hovered = spells.at(selected_spell).get_hovered(camera, mp);
    if (hovered == NULL)
        std::cout << "outside of range" << std::endl;
    else {
        std::cout << "casting to : " << hovered->x << " " << hovered->y << std::endl;
        enemy_t *enemy = room->enemy_at(*hovered);
        if (enemy != NULL) {
            enemy->take_damage(spells.at(selected_spell).damage);
            return true;
        }
    }
    return false;
}

void spells_t::render(camera_t &camera, texture_dict &textures, vec2i mp) {
    int bar_width  = spells.size() * 50;
    int offset_x = camera.w / 2 - bar_width / 2;
    for (int i = 0; i < (int)spells.size(); ++i) {
        SDL_Rect spell_rect = {offset_x + 50 * i, camera.h - 50, 50,50};
        camera.render_texture_static(textures.get_texture_by_name("slot"), &spell_rect);
        camera.render_texture_static(spells.at(i).texture, &spell_rect);
        if (is_hovered(spell_rect, mp))
            camera.render_texture_static(textures.get_texture_by_name("hovered"), &spell_rect);
        if  (i == selected_spell)
            camera.render_texture_static(textures.get_texture_by_name("selected"), &spell_rect);
    }

    if (selected_spell != -1) {
        spells.at(selected_spell).render_zone(camera, textures, mp);
    }
}
