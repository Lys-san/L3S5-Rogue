/* Auteurs : Nicolas Mazeyrac, Lysandre Macke
 * Creation : 26/12/2021
 * Modification : 03/01/2022*/

/*Bibliothèque générale*/
#include <stdio.h>

/*Bibliothèque interne*/
#include "level.h"
#include "player.h"
#include "action.h"

#ifndef __TURN__
#define __TURN__

    /* Perform the turn of the monster, attack first then move */
    int enemyTurn(Enemy monster, Player* player, Point* coordEnemy, Stage* level);

    /*Check if the hp is negative*/
    int isDead(unsigned int hp);

#endif