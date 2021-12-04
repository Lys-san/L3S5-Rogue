/* Autors : Nicolas Mazeyrac, Lysandre Macke
 * Creation : 27/11/2021
 * Modification : 30/11/2021*/

/* General libraries */

/* Internal libraries */
#include "player.h"

#ifndef __ENEMY__
#define __ENEMY__

    /*Define*/


    /*Struct*/

    typedef struct {
        Stat stat;
    } Enemy;


    /*Functions*/

    /* Returns an enemy which attributes will be determined by the current stage. */
    Enemy generateEnemy(unsigned int stage);

    /* Returns 1 if the given enemy is dead and 0 otherwise. */
    int enemyIsDead(Enemy enemy);

    /* ADD OTHER FUNCTIONS HERE */
#endif