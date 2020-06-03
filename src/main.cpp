#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <vector>
#include <iostream>
#include <ctime>
#include <chrono>
#include "dungeon.h"
#include "room.h"
#include "player.h"
#include "camera.h"
#include "fonts.h"
#include "textures.h"
#include "items_loader.h"
#include "pathfinding.h"
#include "enemy.h"

#define WIDTH 800
#define HEIGHT 600

typedef struct {
    using clock = std::chrono::time_point<std::chrono::steady_clock>;
    clock LAST = std::chrono::steady_clock::now();
    clock NOW  = std::chrono::steady_clock::now();
    double dt = 0;

    void tick() {
        NOW = std::chrono::steady_clock::now();
        std::chrono::duration<double, std::milli> diff = (NOW - LAST);
        dt = diff.count();
        //std::cout << 1 / dt * 1000 << std::endl;
        LAST = NOW;
    }
} fps_clock_t;

/*
 * TODO:
 * GAMEPLAY:
 * Trouver un objectif au jeu ?
 *      Rogue like
 *      Tour par tour sur plateau
 *      Différents sorts pour attaquer les ennemies
 *
 * Ajouter des ennemies
 *      IA des ennemies
 *          A* pathfinding OK
 *          Cache le chemin et seulement l'actualiser au déplacement du joueur
 *              au lieu de le calculer chaque frame
 * Ajouter coffres
 *      Détecter la collision avec les coffres OK
 *      Ouvrir un menu avec le contenue du coffre lors de la collision
 * Ajouter inventaire
 *      Tooltip sur les items
 *          nom OK
 *          description OK
 *          rareté OK
 *          effets
 *          valeur en argent
 *          stats (dégat, armure...)
 *      Clique gauche pour consommer l'item (redonner de la vie avec potion par exemple)
 *          Consommer OK
 *          Répartir les effets dans différentes fonctions
 *      Clique droit pour drop les items par terre
 * Ajouter sorts
 *      Dégats de zone
 *      Dégats ciblés
 *      Status, soins
 * Portes qui s'ouvrent avec des clés
 * Rooms piégés (impossible de sortir tant que les monstres ne sont pas mort)
 * Différents étages avec plus de difficultés
 * Systeme de progression même à la mort du joueur
 *      Pouvoir augmenter ses stats
 *      Commencer les games avec du meilleurs équipement
 * Ajouter un systeme d'argent
 * Ajouter un chat de log des combats/objects, argent obtenues
 * Ajouter des décorations aux salles
 * Sorts:
 *      Inclure les diagonales dans les zones
 *      Différent type de zone:
 *          Cercle, ligne, éloignés du joueur
 *      Détecter quelle case est cliquée dans la zone OK
 *      Raccourcis clavier pour choisir le sort
 *      Cooldown (tours)
 * Ajouter des stats pour le joueur et les ennemies
 * Interface avec les stats
 * Ajouter le tour par tour
 *      Les enenemies suivent le joueur OK
 *      Les ennemies infligent des dégats au joueur
 *
 * Message d'alerte quand une potion de heal redonne plus de vie que manquant
 *
 * TECHNIQUE:
 * La vitesse du joueur dépend du repeat key
 * Meilleur parsing des items
 *      Plus de messages d'erreurs
 * render_text est lent a cause du SDL_DestroyTexture()
 */

int main(){
    if (SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("Could not initialize SDL: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *window = NULL;
    window = SDL_CreateWindow("Dungeon", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              WIDTH, HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

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
    TTF_Font *font = create_font("font.ttf", 32);

    //SDL_RenderSetLogicalSize(renderer, 800,600);

    auto room_textures = texture_dict();
    load_room_textures(room_textures, renderer);
    auto items_textures = texture_dict();
    load_item_textures(items_textures, renderer);
    auto characters_textures = texture_dict();
    load_characters_textures(characters_textures, renderer);

    auto items = load_items(items_textures);

    dungeon_t d = generate_dungeon(time(NULL),5,5,10);
    generate_tiles(&d, room_textures, renderer);
    player_t player = {&d.rooms[0]};
    player.inventory.init_inventory();
    player.spells.spells.at(0).texture = items_textures.get_texture_by_name("wand");
    camera_t camera(renderer);

    d.rooms.at(0).items.push_back({{2,5}, items["sword"]});
    d.rooms.at(0).items.push_back({{8,2}, items["heal"] });
    d.rooms.at(0).items.push_back({{9,2}, items["damage"] });
    d.rooms.at(0).items.push_back({{4,5}, items["wand"] });
    d.rooms.at(1).items.push_back({{7,5}, items["ds"]   });
    d.rooms.at(0).chests.push_back({{3,8}, items_textures.get_texture_by_name("chest")});
    d.rooms.at(0).enemies.push_back({{5,8}, characters_textures.get_texture_by_name("ennemy")});
    d.rooms.at(1).enemies.push_back({{8,3}, characters_textures.get_texture_by_name("ennemy")});
    d.rooms.at(1).enemies.push_back({{5,5}, characters_textures.get_texture_by_name("ennemy")});

    auto fps_clock = fps_clock_t();

    int offset = 100;

    SDL_Event event;
    int running = 1;
    while (running) {
        std::string title = "Titre " + std::to_string(fps_clock.dt) + " ms";
        SDL_SetWindowTitle(window, title.c_str());

        SDL_GetWindowSize(window, &camera.w, &camera.h);

        SDL_SetRenderDrawColor(renderer, 37,19,26,255);
        SDL_RenderClear(renderer);

        vec2i mp(0,0);
        SDL_GetMouseState(&mp.x,&mp.y);

        while (SDL_PollEvent(&event)){
            switch (event.type){
            case SDL_QUIT:
                running = 0;
                break;
            case SDL_KEYDOWN:
                if (!camera.in_transisition) {
                    if (player.move(event, &camera)) {
                        for (auto &e: player.in_room->enemies) {
                            std::vector<vec2i> path = find_path(e.pos, player.pos, player.in_room);
                            vec2i pos = path.back();
                            if (pos != player.pos && player.in_room->enemy_at(pos) == NULL) {
                                e.pos = pos;
                                if (distance(e.pos, player.pos) < 2.0) {
                                    if (e.battle_started)
                                        player.take_damage(e.stats.strength);
                                    else e.battle_started = true;
                                }
                            }
                            else {
                                player.take_damage(e.stats.strength);
                            }
                        }
                    }
                }
                if (event.key.keysym.sym == SDLK_e) player.stats.health -= 10;
                if (event.key.keysym.sym == SDLK_c)
                    player.stats.active = !player.stats.active;
                if (event.key.keysym.sym == SDLK_f) {
                    player.inventory.active = !player.inventory.active;
                    player.spells.selected_spell = -1;
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (!player.inventory.active) {
                    player.spells.select_spell(camera, player.pos, mp);
                    player.spells.cast(camera, mp, player.in_room);
                }
                player.consume(player.inventory.slot_hovered(camera, mp));
                break;
            }
        }

        camera.update(fps_clock.dt);
        player.update(fps_clock.dt);

        //Center camera on the room where the player is
        if (!camera.in_transisition){
            camera.x = player.in_room->pos.x * (15 * camera.tile_size + offset) - 25;
            camera.y = player.in_room->pos.y * (11 * camera.tile_size + offset) - 25;
        }

        player.in_room->update(fps_clock.dt);
        player.in_room->render(camera, offset);
        if (camera.in_transisition) {
            player.prev_room->update(fps_clock.dt);
            player.prev_room->render(camera, offset);
        }

        player.render(camera, offset, characters_textures);
        player.inventory.render(camera, items_textures);
        player.stats.render(camera, items_textures, font);
        item_t *hovered_item = player.inventory.slot_hovered(camera, mp);
        if (hovered_item != NULL)
            player.inventory.render_tooltip(camera, items_textures, hovered_item, font, mp);
        render_text(renderer, font, std::to_string(player.stats.health).c_str(),{55,5}, {255,255,0,255});


        //spell bar
        player.spells.render(camera, items_textures, mp);

        SDL_RenderPresent(renderer);
        fps_clock.tick();
        SDL_Delay(1);
    }

    d.free();
    room_textures.free();
    items_textures.free();
    characters_textures.free();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    TTF_CloseFont(font);
    TTF_Quit();
    return 0;
}
