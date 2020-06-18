#include "stats.h"

void stats_t::render(camera_t &camera, TTF_Font *font, vec2i offset) {
    offset.x += (int)(15 * camera.scale);
    render_text(camera.renderer, font,
                ("Strength : " + std::to_string(strength)).c_str(),
                {offset.x, offset.y}, {255,255,255,255});

    offset.y += (int)(30 * camera.scale);
    render_text(camera.renderer, font,
                ("Magic : " + std::to_string(magic)).c_str(),
                {offset.x, offset.y}, {255,255,255,255});
}
