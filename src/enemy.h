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
        char* name;/*Name of the monster*/
        unsigned int attack;/* Used to calculate the power of a melee attack */
        unsigned int hp;/*Max hp*/
        Critical crit;/* Information about critical attack */
    } Enemy;


    /*Functions*/

    /* Returns an enemy which attributes will be determined by the current stage and his distance from the stairs */
    Enemy generateEnemy(unsigned int stage, unsigned int manhattan);

    /* Returns 1 if the given enemy is dead and 0 otherwise. */
    int enemyIsDead(Enemy enemy);

    /*Debug*/
    void quickPrintEnemy(Enemy enemy);
#endif