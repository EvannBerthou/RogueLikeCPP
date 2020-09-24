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
 *      Différent type d'enemies
 *          Stats random
 *              Range aléatoire à partir de la valeur de base (ex:  100 +/- 5% -> [95;105])
 *          Difficulté augmenté en fonction de la salle
 *          Différent type d'attaque
 *              CAC, Distance
 * Ajouter inventaire
 *      Tooltip sur les items
 *          valeur en argent
 *          Ajuster le texte en fonction du nombre de ligne (mettre les stats en 2eme ligne si pas de desc)
 * Ajouter sorts
 *      Dégats de zone
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
 * Ajouter des stats pour le joueur et les ennemies
 *      Vie (up par des bagues)
 *      Force (up par l'épée)
 *      Magie (up par le baton)
 *      Défense (up par l'armure lourde, down l'agilité)
 *      Agilité (up par une armure légère) -> chance que les enemies ne se déplacent pas pendant un tour
 *
 * Interface avec les items equipés
 *      Ajouter des image pour montrer quel slot correspond à quel item
 * Message d'alerte quand une potion de heal redonne plus de vie que manquant
 *
 * Ajouter des effets
 *      Animation lors d'un sort
 *          Flash rouge quand l'ennemie se toucher
 *      Animations pour les sorts
 * Tooltip pour le sorts
 * Ajouter des drop tables
 * Ajouter des animations à chaque étape d'un tour
 * Ajouter des animations qui ne loop pas
 * Comparer avec l'équiement équipé sur le tooltip d'un item dans un coffre
 * Transitionner lors du déplacement du joueur
 *
 * TECHNIQUE:
 * La vitesse du joueur dépend du repeat key
 * render_text est lent a cause du SDL_DestroyTexture()
 * Ajouter un rect custom
 *
 * Faire l'UI
 */

int main() {
    game_t game = {};
    if (game.init() > 0)
        exit(1);
    game.run();
    game.exit();
    return 0;
}
