/* Auteurs : Nicolas Mazeyrac, Lysandre Macke
 * Creation : 27/11/2021
 * Modification : 13/01/2022*/

/*Bibliothèque générale*/

/*Bibliothèque interne*/
#include "loot.h"

#ifndef __TREASURE__
#define __TREASURE__


    /*Define*/

    #define MAX_RARITY            5 /* The maximum rarity of a loot */
    #define MAX_LOOT_PER_TREASURE 2 /* The maximum number of loot in a treasure */

    /*Struct*/

    typedef struct {
        Loot loot[MAX_LOOT_PER_TREASURE]; /*Basically, a treasure is a box full of loot*/
        int closed; /* indicates the status of the treasure either closed (= 1) or open (= 0) */
    } Treasure;

    /*Functions*/

    /* Returns a randomly generated loot box based on the current stage
     * The player's level argument will determine the average quality of the loot,*/
    Treasure generateTreasure(unsigned int level);

    /* Shell display of the treasure (to use for debug) */
    int quickPrintTreasure(Treasure treasure);


#endif