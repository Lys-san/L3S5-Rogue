/* Auteurs : Nicolas Mazeyrac, Lysandre Macke
 * Creation : 06/01/2022
 * Modification : 09/01/2022*/

/*Bibliothèque générale*/
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/*Bibliothèque interne*/

#ifndef __LOOT__
#define __LOOT__

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
        unsigned int rarity; /* Bonus value to the stat*/
        unsigned int quality; /* Value added to the base stat */
        EquipType type; /* Type of equipment */
    } Equipment;

    typedef enum {
        EQUIPMENT, /* permanent change */
        CONSUMMABLE /* temporary change */
    } LootType;

    typedef struct{
        LootType type; /* Type of loot */
        union {
            Equipment equipment; /* Change the base stat of the player */
            Consummables consummable; /* Change the current stat of the player */
        };
    } Loot;

    /* Create a new equipment */
    Equipment generateEquipment(EquipType type, unsigned int quality, unsigned int rarity);

    /* Returns a randomly generated equipment with the quality and rarity given */
    Equipment generateRandomEquipment(unsigned int quality, unsigned int rarity);

    /* Returns a randomly generated consummable */
    Consummables generateRandomConsummable(void);

    /* Returns a randomly generated item if it's an equipment also give the quality and rarity */
    Loot generateLoot(unsigned int quality, unsigned int rarity, LootType type);

#endif