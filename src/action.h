/* Auteurs : Nicolas Mazeyrac, Lysandre Macke
 * Creation : 26/12/2021
 * Modification : 26/12/2021*/

/*Bibliothèque générale*/
#include <time.h>
#include <stdlib.h>

/*Bibliothèque interne*/
#include "level.h"
#include "player.h"

#ifndef __ACTION__
#define __ACTION__

    /* Calculate the damage of a physical attack */
    unsigned int attackPhysical(unsigned int attack, Critical crit);

    /* Calculate the accuracy of the critical */
    unsigned int calculateAccuracy(Critical crit);

    /* Return a new Point corresponding to the initial point moved according to the direction */
    Point Move(Point coordInit, Direction dir);

    /* Do a physical attack from the monster to the player */
    void enemyAttak(Enemy monster, Player* player);

    /* Move the ennemy to the player if he can */
    void enemyMove(/*Stage level,*/ Point* coordEnemy, Point coordPlayer);

#endif