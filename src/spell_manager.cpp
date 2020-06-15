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
                if (spells.at(i).remaining_cooldown == 0) {
                    selected_spell = i;
                    spells.at(selected_spell).set_spell_zone(pp);
                }
            }
            return;
        }
    }
}

bool spells_t::cast(camera_t &camera, vec2i mp, room_t *room, int wand_damage) {
    if (selected_spell == -1) return false;
    spell_t &spell = spells.at(selected_spell);
    vec2i *hovered = spell.get_hovered(camera, mp);
    if (hovered == NULL)
        std::cout << "outside of range" << std::endl;
    else {
        std::cout << "casting to : " << hovered->x << " " << hovered->y << std::endl;
        enemy_t *enemy = room->enemy_at(*hovered);
        if (enemy != NULL) {
            int damage = spell.damage + wand_damage;
            enemy->take_damage(damage);
            spell.remaining_cooldown = spell.cooldown + 1;
            selected_spell = -1;
            return true;
        }
    }
    return false;
}

void spells_t::render(camera_t &camera, texture_dict &textures, vec2i mp, TTF_Font *font) {
    int bar_width  = spells.size() * 50;
    int offset_x = camera.w / 2 - bar_width / 2;
    for (int i = 0; i < (int)spells.size(); ++i) {
        SDL_Rect spell_rect = {offset_x + 50 * i, camera.h - 50, 50,50};
        camera.render_texture_static(textures.get_texture_by_name("slot"), &spell_rect);
        camera.render_texture_static(spells.at(i).texture, &spell_rect);
        if (spells.at(i).remaining_cooldown > 0) {
            render_text(camera.renderer, font, std::to_string(spells.at(i).remaining_cooldown).c_str(),
                        {spell_rect.x + 35, spell_rect.y + 20}, {255,0,0,255});
        }
        if (is_hovered(spell_rect, mp))
            camera.render_texture_static(textures.get_texture_by_name("hovered"), &spell_rect);
        if  (i == selected_spell)
            camera.render_texture_static(textures.get_texture_by_name("selected"), &spell_rect);
    }

    if (selected_spell != -1) {
        spells.at(selected_spell).render_zone(camera, textures);
    }
}
