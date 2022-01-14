/* Autors : Nicolas Mazeyrac, Lysandre Macke
 * Creation : 27/11/2021
 * Modification : 13/01/2022*/

/* General libraries */

/* Internal libraries */
#include "player.h"

#ifndef __ENEMY__
#define __ENEMY__

    /*Define*/

    #define MINIMUM_EXP 8 /* The minimum Exp a monster can give in the first stage */

    /*Struct*/

    typedef struct {
        int hp;/*hp*/
        unsigned int attack;/* Used to calculate the power of a melee attack */
        unsigned int exp;/*Exp given after its death*/
        Critical crit;/* Information about critical attack */
    } Enemy;


    /*Functions*/

    /* Returns an enemy which attributes will be determined by the current stage and his distance from the stairs */
    Enemy generateEnemy(unsigned int level, unsigned int distance);


    /* Shell display of the enemy (to use for debug) */
    int printEnemy(Enemy enemy);
    
#endif