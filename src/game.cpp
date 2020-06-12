#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <vector>
#include <iostream>
#include <ctime>
#include "room.h"
#include "pathfinding.h"
#include "enemy.h"
#include "game.h"

static item_t * get_hovered_item(player_t &player, camera_t &camera, vec2i mp, bool &in_chest) {
    item_t *inv_item = player.inventory.slot_hovered(camera, mp);
    if (inv_item != NULL) {
        in_chest = false;
        return inv_item;
    }

    if (player.in_chest != NULL) {
        item_t *chest_item = player.in_chest->inventory.slot_hovered(camera,mp);
        if (chest_item != NULL) {
            in_chest = true;
            return chest_item;
        }
    }

    return NULL;
}

static item_t * get_hovered_item(player_t &player, camera_t &camera, vec2i mp) {
    bool tmp = false;
    return get_hovered_item(player, camera, mp, tmp);
}

int game_t::init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("Could not initialize SDL: %s\n", SDL_GetError());
        return 1;
    }

    window = SDL_CreateWindow("Dungeon", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                   800,600, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    if (window == NULL){
        printf("Error while creating the window %s\n", SDL_GetError());
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1,
                                                SDL_RENDERER_PRESENTVSYNC |
                                                SDL_RENDERER_ACCELERATED);

    if (renderer == NULL) {
        printf("Error while creating the renderer: %s\n", SDL_GetError());
        return 1;
    }

    if (TTF_Init() == -1){
        printf("Error while init TTF: %s\n", TTF_GetError());
        return 1;
    }

    IMG_Init(IMG_INIT_PNG);
    font = create_font("font.ttf", 32);

    load_room_textures(room_textures, renderer);
    load_item_textures(items_textures, renderer);
    load_characters_textures(characters_textures, renderer);

    items = load_items(items_textures);

    dungeon = generate_dungeon(time(NULL), 10);
    generate_tiles(&dungeon, room_textures, renderer);
    player = {&dungeon.rooms[0]};
    player.inventory.init_inventory();
    player.spells.spells.at(0).texture = items_textures.get_texture_by_name("wand");
    player.spells.spells.at(1).texture = items_textures.get_texture_by_name("wand");
    player.spells.spells.at(2).texture = items_textures.get_texture_by_name("wand");
    player.spells.spells.at(3).texture = items_textures.get_texture_by_name("wand");
    camera = { renderer };

    dungeon.rooms.at(0).items.push_back({{2,5}, items["sword"]});
    dungeon.rooms.at(0).items.push_back({{8,2}, items["heal"] });
    dungeon.rooms.at(0).items.push_back({{9,2}, items["damage"] });
    dungeon.rooms.at(0).items.push_back({{4,5}, items["wand"] });
    dungeon.rooms.at(1).items.push_back({{7,5}, items["ds"]   });
    chest_t chest = {{6,5}};
    chest.inventory.init_inventory();
    chest.inventory.add_item(items["wand"]);
    dungeon.rooms.at(0).chests.push_back(chest);
    //dungeon.rooms.at(0).enemies.push_back({{5,8}, characters_textures.get_texture_by_name("ennemy")});
    dungeon.rooms.at(1).enemies.push_back({{8,3}, characters_textures.get_texture_by_name("ennemy")});
    dungeon.rooms.at(1).enemies.at(0).drop_table.push_back(items["wand"]);
    dungeon.rooms.at(1).enemies.push_back({{5,5}, characters_textures.get_texture_by_name("ennemy")});

    fps_clock = fps_clock_t();
    return 0;
}

void game_t::run() {
    SDL_Event event;
    int running = 1;
    while (running) {
        std::string title = "Titre " + std::to_string(fps_clock.dt) + " ms";
        SDL_SetWindowTitle(window, title.c_str());

        SDL_GetWindowSize(window, &camera.w, &camera.h);

        SDL_SetRenderDrawColor(camera.renderer, 37,19,26,255);
        SDL_RenderClear(camera.renderer);

        SDL_GetMouseState(&mouse_position.x,&mouse_position.y);

        while (SDL_PollEvent(&event)){
            switch (event.type){
            case SDL_QUIT:
                running = 0;
                break;
            case SDL_KEYDOWN:
                key_press(event);
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    if (!player.inventory.active) {
                        player.spells.select_spell(camera, player.pos, mouse_position);
                        if (player.spells.cast(camera, mouse_position, player.in_room)) {
                            new_turn();
                            break;
                        }
                    }

                    bool in_chest;
                    item_t *item = get_hovered_item(player, camera, mouse_position, in_chest);
                    if (item != NULL) {
                        if (in_chest) {
                            player.inventory.add_item(*item);
                            player.in_chest->inventory.remove_item(item);
                        }
                        else
                            player.consume(item);
                    }

                    chest_t *chest = player.in_room->has_chest(camera.vec2_screen_to_room(mouse_position));
                    if (chest != NULL && distance(chest->pos, player.pos) < 2.0f) {
                        player.inventory.open(true, false);
                        chest->inventory.open(true, true);
                        player.in_chest = chest;
                    }
                }

                if (event.button.button == SDL_BUTTON_RIGHT) {
                    if (player.inventory.active) {
                        item_t *item = player.inventory.slot_hovered(camera, mouse_position);
                        if (item != NULL) {
                            player.in_room->items.push_back({player.pos, *item});
                            player.inventory.remove_item(item);
                        }
                    }
                    else {
                        if (player.physical_damage(camera, mouse_position, player.in_room))
                            new_turn();
                    }
                }
                break;
            }
        }
        update();
        render();
    }
}

void game_t::key_press(SDL_Event &event) {
    if (!camera.in_transisition) {
        if (player.move(event, &camera))
            new_turn();
    }
    if (event.key.keysym.sym == SDLK_e) player.stats.health -= 10;

    if (event.key.keysym.sym == SDLK_c && !player.inventory.active)
        player.stats.active = !player.stats.active;

    if (event.key.keysym.sym == SDLK_f && !player.stats.active) {
        player.inventory.toggle_inventory();
        if (player.in_chest != NULL) {
            player.in_chest->inventory.close_inventory();
            player.in_room->remove_chest(player.in_chest);
            player.in_chest = NULL;
        }
        player.spells.selected_spell = -1;
    }

    const char* name = SDL_GetKeyName(event.key.keysym.sym);
    if (name[0] > '0' && name[1] < '9') {
        int index = name[0] - '0' - 1;
        if (index < (int)player.spells.spells.size()) {
            spell_t &spell = player.spells.spells.at(index);
            if (index == player.spells.selected_spell) {
                player.spells.selected_spell = -1;
            }
            else if (spell.remaining_cooldown == 0) {
                player.spells.selected_spell = index;
                player.spells.spells.at(player.spells.selected_spell).set_spell_zone(player.pos);
            }
        }
    }
}

void game_t::update() {
    camera.update(fps_clock.dt);
    player.update(fps_clock.dt);

    //Center camera on the room where the player is
    if (!camera.in_transisition && !camera.shaking){
        camera.x = player.in_room->pos.x * (15 * camera.tile_size + offset) - 25;
        camera.y = player.in_room->pos.y * (11 * camera.tile_size + offset) - 25;
    }

    player.in_room->update(fps_clock.dt);
    if (camera.in_transisition)
        player.prev_room->update(fps_clock.dt);
}

void game_t::render() {
    player.in_room->render(camera, offset, items_textures);
    if (camera.in_transisition)
        player.prev_room->render(camera, offset, items_textures);

    player.render(camera, offset, characters_textures);
    player.inventory.render(camera, items_textures);
    if (player.in_chest != NULL)
        player.in_chest->inventory.render(camera, items_textures);
    player.stats.render(camera, items_textures, font);

    item_t *item = get_hovered_item(player, camera, mouse_position);
    if (item != NULL) {
        render_tooltip(camera, items_textures, item, font, mouse_position);
    }
    render_text(camera.renderer, font, std::to_string(player.stats.health).c_str(),
                {55,5}, {255,255,0,255});

    if (!player.inventory.active && !player.stats.active){
        world_item_t *world_item = player.in_room->has_item(camera.vec2_screen_to_room(mouse_position));
        if (world_item != NULL) {
            render_tooltip(camera,items_textures,&world_item->item, font, mouse_position);
        }
    }


    //spell bar
    player.spells.render(camera, items_textures, mouse_position, font);

    if (!player.inventory.active && !player.stats.active)
        camera.render_texture_to_room(items_textures.get_texture_by_name("selected"),
                                      camera.vec2_screen_to_room(mouse_position));

    SDL_RenderPresent(camera.renderer);
    fps_clock.tick();
    SDL_Delay(1);
}

void game_t::new_turn() {
    turn_count++;
    std::cout << "starting turn : " << turn_count << std::endl;
    for (auto &e: player.in_room->enemies) {
        if (!e.stats.alive) {
            if (e.drop_table.size() > 0) {
                chest_t chest = {e.pos};
                chest.inventory.init_inventory();
                for (auto item: e.drop_table)
                    chest.inventory.add_item(item);
                player.in_room->chests.push_back(chest);
            }
            continue;
        }
        std::vector<vec2i> path = find_path(e.pos, player.pos, player.in_room);
        vec2i pos = path.back();

        if (pos != player.pos && player.in_room->enemy_at(pos) == NULL)
            e.pos = pos;

        if (distance(e.pos, player.pos) < 2.0) {
            if (e.battle_started) {
                camera.begin_shake();
                player.take_damage(e.stats.strength);
            }
            else e.battle_started = true;
        }
    }

    for (spell_t &spell: player.spells.spells) {
        if (spell.remaining_cooldown > 0)
            spell.remaining_cooldown -= 1;
    }
}

void game_t::exit() {
    dungeon.free();
    room_textures.free();
    items_textures.free();
    characters_textures.free();
    SDL_DestroyRenderer(camera.renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    TTF_CloseFont(font);
    TTF_Quit();
}
