/* Auteurs : Nicolas Mazeyrac, Lysandre Macke
 * Creation : 30/11/2021
 * Modification : 30/11/2021*/

/*Bibliothèque générale*/

/*Bibliothèque interne*/
#include "treasure.h"

#ifndef __PLAYER__
#define __PLAYER__

    /*Define*/
    #define MAX_EQUIP     3 /*Number of equipment a player can wield */
    #define MAX_INVENTORY 9 /*Number of non-equipment a player can carry*/

    /*Base stat at lvl one for a Standard player*/
    #define STANDARD_BASE_STAT          10
    #define STANDARD_BASE_CRIT_MODIFIER 300 /*percentage*/
    #define STANDARD_BASE_CRIT_RATE     5   /*percentage*/
    #define STANDARD_BASE_ACCURACY      20  /*percentage*/

    /*Maxed stat for different value*/
    /*#define STANDARD_MAX_HP(DEFENSE) 10*DEFENSE
    #define STANDARD_MAX_MP(INTELLIGENCE) (10*INTELLIGENCE - 50 > 0) ? (10 * INTELLIGENCE - 50) : 0
    #define STANDARD_EXP_TO_NEXT_LVL(Lvl) 350 + 50*(Lvl)
    #define STANDARD_MAX_HP          10 * player->stat.base.DEFENSE
    #define STANDARD_MAX_MP          (10*player->stat.base.INTELLIGENCE - 50 > 0) ? (10 * player->stat.base.INTELLIGENCE - 50) : 0
    #define STANDARD_EXP_TO_NEXT_LVL 350 + 50*(player->stat.current.Lvl)*/

    /*Struct*/

    typedef struct {
        int modificater;             /* Damage modifier when a crit hit */
        unsigned int rate;           /* Chances of a crit to proc */
        unsigned int accuracy;       /* Range of effective damage when a hit lands, exemple: accuracy 20 -> 80%-120% of ATTACK */
    } Critical;

    typedef struct {
        unsigned int cost;            /* Cost of the spell */
        unsigned int currentPower;    /* damage inflicted by the spell */
    } Spell;

    typedef struct {
        unsigned int lvl;             /* Current lvl of the player */
        unsigned int hp;              /* Current hp of the player, different from max HP */
        unsigned int mp;              /* Current mp of the player, different from max MP */
        unsigned int exp;             /* Current exp of the player */
    } CurrentStat;

    typedef struct {
        char* name;                   /* name of the player*/
        unsigned int ATTACK;          /* Used to calculate the power of a melee attack */
        unsigned int INTELLIGENCE;    /* Used to calculate the max Mp and the Power of a Spell */
        unsigned int DEFENSE;         /* Used to calculate the max Hp of the player */
        Critical CRIT;                /* Information about critical attack */
    } BaseStat;

    typedef struct{
        CurrentStat current;          /* Current state of the stats in-game */
        BaseStat base;                /* Initial stats of the player */
    } Stat;

    typedef struct {
        Stat stat;                    /* Stats of the player */
        Spell spell;                  /* description of the spell that can be cast */
        Loot equip[MAX_EQUIP];        /* Equipment item that changes Player current stat */
        Loot inventory[MAX_INVENTORY];/* Inventory of non-equipment item */
    } Player;


    /*Functions*/

    /* Returns the maximum HP of a given player */
    int standardMaxHP(Player player);

    /* Returns the maximum MP of a given player */
    int standardMaxMP(Player player);

    /* Returns the total exp needed to go to next level */
    int standardExpToNextlevel(Player player);

    /* ... */
    void initializeCritStat(Player *player);

    /* ... */
    void initializeBaseStat(Player *player, char* name);

    /* ... */
    void initializeCurrentStat(Player *player);

    /* ... */
    void initializeStat(Player *player, char* name);

    /*Initialize a Player character with standard stats*/
    void initializeStandard(Player *player, char *name);

    /*Debug*/
    void quickPrintPlayer(Player player);

#endif