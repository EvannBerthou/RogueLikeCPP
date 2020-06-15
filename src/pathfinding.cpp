#include <vector>
#include <algorithm>
#include "pathfinding.h"

float distance(int x1, int y1, int x2, int y2) {
    return ((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

std::vector<vec2i> find_path(vec2i start, vec2i goal, room_t *room) {
    int constexpr width = 14;
    int constexpr height = 11;
    node_t *nodes = new node_t[width * height];
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            int index = j * width + i;
            nodes[index].x = i;
            nodes[index].y = j;
            nodes[index].parent = nullptr;
            nodes[index].global_f_cost = INFINITY;
            nodes[index].local_f_cost = INFINITY;
            nodes[index].obstacle = room->has_chest({i,j})||room->has_item({i,j})||room->is_wall({i,j});
        }
    }

    node_t *start_node = &nodes[start.y * width + start.x];
    node_t *end_node   = &nodes[goal.y * width + goal.x];

    start_node->local_f_cost = 0;
    start_node->global_f_cost = distance(start_node->x, start_node->y, end_node->x, end_node->y);

    node_t *current = start_node;
    std::vector<node_t*> not_tested = {start_node};

    while (!not_tested.empty() && current != end_node) {
        std::sort(not_tested.begin(), not_tested.end(), [](const node_t *lhs, const node_t *rhs) {
                return lhs->global_f_cost < rhs->global_f_cost;
        });
        while (!not_tested.empty() && not_tested.front()->visited) {
            not_tested.front() = std::move(not_tested.back());
            not_tested.pop_back();
        }
        if (not_tested.empty())
            break;
        current = not_tested.front();
        current->visited = true;

        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                if (i == 0 && j == 0) continue;
                vec2i new_position = {current->x + i, current->y + j};
                if (new_position.x > 15 || new_position.x < 0
                        || new_position.y > 11 || new_position.y < 0)
                    continue;
                int index = (new_position.y) * width + (new_position.x);
                node_t *node = &nodes[index];
                if (!node->visited && node->obstacle == false)
                    not_tested.push_back(node);

                float possible_f_cost = current->local_f_cost +
                                        distance(current->x, current->y, node->x, node->y);
                if (possible_f_cost < node->local_f_cost) {
                    node->parent = current;
                    node->local_f_cost = possible_f_cost;
                    node->global_f_cost = node->local_f_cost +
                                          distance(node->x, node->y, end_node->x, end_node->y);
                }
            }
        }
    }
    std::vector<vec2i> path = {};
    node_t *p = end_node;
    while (p->parent != nullptr) {
        path.push_back({p->x, p->y});
        p = p->parent;
    }
    delete []nodes;
    return path;
}
