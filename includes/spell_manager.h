#ifndef SPELL_MANAGER_H
#define SPELL_MANAGER_H

#include <vector>
#include "camera.h"
#include "textures.h"
#include "spell.h"

typedef struct {
    std::vector<spell_t> spells = {{}};
    void select_spell(camera_t &camera, int p_x, int p_y, int m_x, int m_y);
    void render(camera_t &camera, texture_dict &textures, int m_x, int m_y);
    void cast(camera_t &camera, int m_x, int m_y);
    int selected_spell = -1;
} spells_t;

#endif
