#include "stats.h"

void stats_t::render(camera_t &camera, texture_dict &textures, TTF_Font *font) {
    if (!active) return;
    int offset_x = camera.w / 2 - stats_width / 2;
    int offset_y = camera.h / 2 - stats_height / 2;

    SDL_Rect bg_rect = { offset_x - 15, offset_y - 15, stats_width, stats_height};
    camera.render_texture_static(textures.get_texture_by_name("bg"), &bg_rect);
    render_text(camera.renderer, font,
                ("Strength : " + std::to_string(strength)).c_str(),
                {offset_x + 15, offset_y + 15}, {255,255,255,255});
}
