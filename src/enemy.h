/* Autors : Nicolas Mazeyrac, Lysandre Macke
 * Creation : 27/11/2021
 * Modification : 09/01/2022*/

/* General libraries */

/* Internal libraries */
#include "player.h"

#ifndef __ENEMY__
#define __ENEMY__

    /*Define*/

    #define LEVEL_WIDTH  63
    #define LEVEL_HEIGHT 43

    /*Struct*/

    typedef struct {
        unsigned int exp;/*Exp given after its death*/
        unsigned int attack;/* Used to calculate the power of a melee attack */
        int hp;/*hp*/
        Critical crit;/* Information about critical attack */
    } Enemy;


    /*Functions*/

    /* Returns an enemy which attributes will be determined by the current stage and his distance from the stairs */
    Enemy generateEnemy(unsigned int stage, unsigned int distance);


    /* Debug */
    void quickPrintEnemy(Enemy enemy);
#endif