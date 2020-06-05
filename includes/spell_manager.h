#ifndef SPELL_MANAGER_H
#define SPELL_MANAGER_H

#include <SDL2/SDL_ttf.h>
#include <vector>
#include "camera.h"
#include "textures.h"
#include "spell.h"
#include "vec2.h"
#include "room.h"

typedef struct {
    std::vector<spell_t> spells = {{2,50,false}, {2,50,true}, {3,50, false}, {3,50,true}};
    void select_spell(camera_t &camera, vec2i player_position, vec2i mouse_position);
    void render(camera_t &camera, texture_dict &textures, vec2i mp, TTF_Font *font);
    bool cast(camera_t &camera, vec2i mouse_position, room_t *room);
    int selected_spell = -1;
} spells_t;

#endif
