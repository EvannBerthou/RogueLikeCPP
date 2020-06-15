#include "stats.h"

void stats_t::render(camera_t &camera, TTF_Font *font, vec2i offset) {
    render_text(camera.renderer, font,
                ("Strength : " + std::to_string(strength)).c_str(),
                {offset.x + 15, offset.y}, {255,255,255,255});

    render_text(camera.renderer, font,
                ("Magic : " + std::to_string(magic)).c_str(),
                {offset.x + 15, offset.y + 30}, {255,255,255,255});
}
