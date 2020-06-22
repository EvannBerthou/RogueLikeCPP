#include "animation.h"

void animation_t::render(camera_t &camera, SDL_Rect *rect, bool flip) {
        camera.render_texture(sprites[frame], rect, flip);
}

void animation_t::update(double dt) {
    frame_time += dt / animation_speed;
    frame = (int)(((int)frame_time) % frame_count);
}

animation_t load_animation(texture_dict &textures, std::string sprite_name) {
    animation_t animation = {};
    const int n = 4;
    animation.sprites = new SDL_Texture*[n]; // should not be a const
    for (int i = 0; i < n; ++i) {
        animation.sprites[i] = textures.get_texture_by_name(sprite_name + std::to_string(i));
    }
    animation.frame_count = n;
    animation.animation_speed = 500;
    return animation;
}
