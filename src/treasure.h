/* Auteurs : Nicolas Mazeyrac, Lysandre Macke
 * Creation : 27/11/2021
 * Modification : 30/11/2021*/

/*Bibliothèque générale*/

/*Bibliothèque interne*/

#ifndef __TREASURE__
#define __TREASURE__

    /*Define*/

    #define MAX_LOOT_PER_TREASURE 5


    /*Struct*/

    typedef enum {
        ENERGY, /* = potion*/
        ARMOR,
        WEAPON,
        WAND
    } Loot;


    /*Functions*/

    typedef struct {
        Loot loot[MAX_LOOT_PER_TREASURE]; /*Basically, a treasure is a box full of loot*/
    } Treasure;


    /* Returns a randomly generated item based on the current stage and a rarityRate [1-?]
     * (= probability that a generated item may be a rare item) */
    Loot generateLoot(unsigned int stage, unsigned int rarityRate);

    /* Returns a randomly generated loot box based on the current stage
     * and rarity integer ([1-?]).
     * The player's level argument will determine the average quality of the loot,
     * and the rarity argument will determine if the treasure may contain rare items
     * (also based on the current stage). */
    Treasure generateTreasure(unsigned int stage, unsigned int rarity);

    /* ADD OTHER FUNCTIONS HERE */
#endif