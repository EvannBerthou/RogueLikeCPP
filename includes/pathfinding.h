#ifndef PATHFINDING_H
#define PATHFINDING_H

#include <vector>
#include "vec2.h"
#include "room.h"

typedef struct node_t {
    int x,y;
    node_t *parent;
    float local_f_cost;
    float global_f_cost;
    bool obstacle;
    bool visited = false;
} node_t;

std::vector<vec2i> find_path(vec2i start, vec2i goal, room_t *room);

#endif
