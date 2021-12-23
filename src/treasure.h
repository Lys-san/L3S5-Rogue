/* Auteurs : Nicolas Mazeyrac, Lysandre Macke
 * Creation : 27/11/2021
 * Modification : 30/11/2021*/

/*Bibliothèque générale*/

/*Bibliothèque interne*/

#ifndef __TREASURE__
#define __TREASURE__

    /*Define*/
    #define MAX_RARITY            5 /* The maximum rarity of a loot */
    #define MAX_LOOT_PER_TREASURE 2 /* The maximum number of loot in a treasure */


    /*Struct*/

    typedef enum {
        HEAL, /* Heal 10% of max hp */
        MAGIC, /* Heal 10% of max mp */
        REGEN, /* Heal 20 hp and 10 mp every 3 turn for 30 turn, only one at a time */
        LEARNING, /* Up the critical rate by 10 point of percentage for 30 turn*/
        PRECISION, /*Up by 30% the exp gained for 30 turn*/
        EMPTY /* None equivalent for Consummables */
    } Consummables;

    typedef enum {
        ARMOR, /* Up the defense stat */
        WEAPON, /* Up the attack stat */
        WAND, /* Up the intelligence stat */
        NONE /* None equivalent for EquipType */
    } EquipType;

    typedef struct {
        unsigned int rarity; /* ??????????????????????????? */
        unsigned int quality; /* Value added to the base stat */
        EquipType type; /* Type of equipment */
    } Equipment;

    typedef enum {
        EQUIPMENT,
        CONSUMMABLE
    } LootType;

    typedef struct{
        LootType type; /* Type of loot */
        union {
            Equipment equipment; /* Change the base stat of the player */
            Consummables consummable; /* Change the current stat of the player */
        };
    } Loot;

    typedef struct {
        Loot loot[MAX_LOOT_PER_TREASURE]; /*Basically, a treasure is a box full of loot*/
    } Treasure;

    /*Functions*/

    /* Returns a randomly generated item based on the current stage and a rarityRate [1-?]
     * (= probability that a generated item may be a rare item) */
    Loot generateLoot(unsigned int quality, unsigned int rarity, LootType type);

    /* Returns a randomly generated loot box based on the current stage
     * The player's level argument will determine the average quality of the loot,*/
    Treasure generateTreasure(unsigned int stage, unsigned int playerlevel);

    /*Debug*/
    void quickPrintTreasure(Treasure chest);

#endif