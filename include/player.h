/* Auteurs : Nicolas Mazeyrac, Lysandre Macke
 * Creation : 30/11/2021
 * Modification : 13/01/2022*/

/*Bibliothèque générale*/

/*Bibliothèque interne*/
#include "treasure.h"

#ifndef __PLAYER__
#define __PLAYER__

    /*Define*/
    #define MAX_EQUIP     3   /* Number of equipment a player can wield */
    #define MAX_INVENTORY 9   /* Number of non-equipment a player can carry*/

    /*Base stat at lvl one for a Standard player*/
    #define STANDARD_BASE_STAT          10
    #define STANDARD_BASE_CRIT_MODIFIER 3   /*percentage*/
    #define STANDARD_BASE_CRIT_RATE     5   /*percentage*/
    #define STANDARD_BASE_ACCURACY      20  /*percentage*/

    /*Struct*/
    enum playerStatus { PHYSICAL_ATTCK, MAGICAL_ATTCK }; /* will determine which attack will be done */

    typedef struct {
        int x; /* The cell's number on the line of the stage(see level.h) */
        int y; /* The line's on the stage(see level.h) */
    } Point;
    
    typedef struct {
        int modificater;             /* Damage modifier when a crit hit */
        unsigned int rate;           /* Chances of a crit to proc */
        unsigned int accuracy;       /* Range of effective damage when a hit lands, exemple: accuracy 20 -> 80%-120% of ATTACK */
    } Critical;

    typedef struct {
        unsigned int cost;            /* Cost of the spell */
        unsigned int power;           /* damage inflicted by the spell */
    } Spell;

    typedef struct {
        int hp;                       /* Current hp of the player, different from max HP */
        unsigned int lvl;             /* Current lvl of the player */
        unsigned int mp;              /* Current mp of the player, different from max MP */
        unsigned int exp;             /* Current exp of the player */
    } CurrentStat;

    typedef struct {
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
        enum playerStatus status;           /* Physical attack mode or magical */
        Point coords;                       /* Coords of the player in the stage */
        Stat stat;                          /* Stats of the player */
        Spell spell;                        /* Description of the spell that can be cast */
        Loot equip[MAX_EQUIP];              /* Equipment item that changes Player current stat 0=ARMOR, 1=WEAPON, 2=WAND*/
        Loot inventory[MAX_INVENTORY];      /* Inventory of non-equipment item */
        unsigned int nbrItemHeld;           /* Number of items held */
        unsigned int underLearningPotion;   /* Number of turn left under a learning potion */
        unsigned int underRegenPotion;      /* Number of turn left under a regen potion */
        unsigned int underPrecisionPotion;  /* Number of turn left under a precision potion */
    } Player;


    /*Functions*/

    /* Returns the maximum HP of a given player */
    int standardMaxHP(Player player);

    /* Returns the maximum MP of a given player */
    int standardMaxMP(Player player);

    /* Returns the total exp needed to go to next level */
    int standardExpToNextlevel(Player player);

    /* Initialize standard base critical stat */
    void initializeCritStat(Player *player);

    /* Initialize all standard base stat */
    void initializeBaseStat(Player *player);

    /* Initialize all standard current stat  */
    void initializeCurrentStat(Player *player);

    /* Initialize all standard stat  */
    void initializeStat(Player *player);

    /* Initialize an empty inventory  */
    void initializaInventory(Player *player);

    /* Initialize a Player character with standard stats */
    void initializeStandard(Player *player);

    /* Gain a lvl if the current exp is higher than the exp needed to pass the next lvl */
    int gainLvl(Player *player);

    /* Gain exp to the player and level up the player has many times as necessary given the amount of exp 
    * and return the number of level gained*/
    int gainExp(Player *player, unsigned int exp);

    /* Equip a weaponType weapon to the player and adjust his stat accordingly  */
    void equipWeapon(Player *player, Equipment weapon);

    /* Equip a weaponType wand to the player and adjust his stat accordingly */
    void equipWand(Player *player, Equipment wand);

    /* Equip a weaponType armor to the player and adjust his stat accordingly */
    void equipArmor(Player *player, Equipment armor);

    /* Check if the Equipment equip is better than the currently held equipment */
    int checkEquip(Player *player, Equipment equip);

    /* Equip the Equipment equip to the player if the equipment is better */
    void newEquipment(Player *player, Equipment equip);

    /* Add the loot to the players inventory if there is place */
    void  addToInventory(Player* player, Loot loot);

    /* Shell display of the player (to use for debug) */
    int printPlayer(Player player);

#endif