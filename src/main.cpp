#include "game.h"

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
 *      Quand un ennemie meurt, il laisse un coffre avec son loot OK
 *      Nombre aléatoire dans chaque room OK
 *      Différent type d'enemies
 *          Stats random
 *              Range aléatoire à partir de la valeur de base (ex:  100 +/- 5% -> [95;105])
 *          Difficulté augmenté en fonction de la salle
 *          Différent type d'attaque
 *              CAC, Distance
 * Ajouter coffres
 *      Détecter la collision avec les coffres OK
 *      Faire disparaitre le coffre une fois vide OK
 *      Ouvrir un menu avec le contenue du coffre lors d'un clique dessus OK
 *          Ajouter un inventaire au coffre OK
 * Ajouter inventaire
 *      Tooltip sur les items
 *          nom OK
 *          description OK
 *          rareté OK
 *          valeur en argent
 *          stats (dégat, armure...)
 *      Clique gauche pour consommer l'item (redonner de la vie avec potion par exemple)
 *          Consommer OK
 *          Répartir les effets dans différentes fonctions
 *      Clique droit pour drop les items par terre OK
 * Ajouter sorts
 *      Dégats de zone
 *      Dégats ciblés OK
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
 *      Inclure les diagonales dans les zones OK
 *      Détecter quelle case est cliquée dans la zone OK
 *      Raccourcis clavier pour choisir le sort OK
 *      Cooldown (tours) OK
 * Ajouter des stats pour le joueur et les ennemies
 *      Vie (up par des bagues)
 *      Force (up par l'épée)
 *      Magie (up par le baton)
 *      Défense (up par l'armure lourde, down l'agilité)
 *      Agilité (up par une armure légère) -> chance que les enemies ne se déplacent pas pendant un tour
 * Interface avec les stats OK
 * Interface avec les items equipés
 *      Ajouter des image pour montrer quel slot correspond à quel item
 * Ajouter le tour par tour
 *      Les enenemies suivent le joueur OK
 *      Les ennemies infligent des dégats au joueur OK
 * Afficher la vie des enemies OK
 * Ajouter des dégats au corps à corps OK
 * Message d'alerte quand une potion de heal redonne plus de vie que manquant
 * Les enemies traversent les murs quand ils sont collés OK
 * Stats random sur le stuff
 *
 * Ajouter des effets
 *      Animation lors d'un sort
 *          Flash rouge quand l'ennemie se toucher
 *      Shake quand le joueur prend des dégats OK
 * Tooltip en survolant les items au sol OK
 * Tooltip pour le sorts
 * Ajouter des drop tables
 *
 * TECHNIQUE:
 * La vitesse du joueur dépend du repeat key
 * Meilleur parsing des items OK
 *      Plus de messages d'erreurs OK
 * render_text est lent a cause du SDL_DestroyTexture()
 * Scale l'inventaire en fonction de la résolution OK
 * Refaire le code du rendu de l'inventaire OK
 * Les textes ne changent pas de taille en fonction de la taille de la fenetre (camera.scale)
 */

int main(){
    game_t game = {};
    if (game.init() > 0) { exit(1); }
    game.run();
    game.exit();
    return 0;
}
