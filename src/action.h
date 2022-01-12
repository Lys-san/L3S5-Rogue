/* Auteurs : Nicolas Mazeyrac, Lysandre Macke
 * Creation : 26/12/2021
 * Modification : 03/01/2022*/

/*Bibliothèque générale*/
#include <time.h>

/*Bibliothèque interne*/
#include "list.h"

#ifndef __ACTION__
#define __ACTION__

    /* Calculate the damage of a physical attack */
    unsigned int attackPhysical(unsigned int attack, Critical crit);

    /* Calculate the damage of a magical attack */
    unsigned int attackMagical(unsigned int intelligence, Spell spell);

    /* Calculate the accuracy of the critical */
    unsigned int calculateAccuracy(Critical crit);

    /* Return a new Point corresponding to the initial point moved according to the direction */
    Point Move(Point coordInit, Direction dir);

    /* Do a physical attack from the monster to the player */
    void enemyAttack(Enemy monster, Player* player);

    /* Move the ennemy to the player if he can */
    void enemyMove(Stage *level, Point coordEnemy, Point coordPlayer);

    /* Do a physical attack from the player to the monster */
    void playerPhysicalAttack(Player player, Enemy* monster);

    /* Do a magical attack from the player to the monster, if the player doesn't have mp doesnt do the attack and return 0 */
    int playerMagicalAttack(Player* player, Enemy* monster);

    /* Move the player to the next tile if he can, perform a special action if the tile isn't empty */
    int playerMove(Player *player, Direction dir, StageList *dungeon);
    
    /*Open a treasure chest*/
    void openTreasure(Player* player, Stage *stage, int x, int y);

    int consumeItem(Player* player, Consummables potion);

#endif