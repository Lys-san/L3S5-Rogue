/* Auteurs : Nicolas Mazeyrac, Lysandre Macke
 * Creation : 26/12/2021
 * Modification : 03/01/2022*/

/*Bibliothèque générale*/
#include <stdio.h>

/*Bibliothèque interne*/
#include "level.h"
#include "player.h"
#include "action.h"
#include "list.h"

#ifndef __TURN__
#define __TURN__

    /* Perform the turn of the monster, attack first then move */
    int enemyTurn(Enemy monster, Player* player, Point* coordEnemy, Stage* level);

    /* Perform the turn of all the monsters */
    int allEnemyTurn(Stage *level, Player* player, ListEnemy* allEnemies);
#endif