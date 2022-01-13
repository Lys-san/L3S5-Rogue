/* Auteurs : Nicolas Mazeyrac, Lysandre Macke
 * Creation : 26/12/2021
 * Modification : 13/01/2022*/

/*Bibliothèque générale*/

/*Bibliothèque interne*/
#include "action.h"

#ifndef __TURN__
#define __TURN__

    /*Define*/

    #define SCREEN_WIDTH  13
    #define SCREEN_HEIGHT  9

    /*Struct*/


    /*Functions*/

    /* Perform the turn of the monster, attack first then move */
    int enemyTurn(Enemy monster, Player* player, Point coordEnemy, Stage* level);

    /* Perform the turn of all the monsters */
    int allEnemyTurn(Stage *level, Player* player, ListCoord* coordsEnnemies);

    /* Perform the turn of all the monsters present on screen */
    int turnEnemyOnScreen(Stage *stage, Player* player);
#endif