/* Auteurs : Nicolas Mazeyrac, Lysandre Macke
 * Creation : 27/11/2021
 * Modification : 30/11/2021*/

/*Bibliothèque générale*/

/*Bibliothèque interne*/
/*#include "player.h"*/

#ifndef __ENEMY__
#define __ENEMY__

    /*Define*/


        /*Struct*/

    typedef struct {
        int Modificater;
        unsigned int Rate;
        unsigned int accuracy;
    } Critical;

    typedef struct {
        int Modificater;
        unsigned int Bar;
    } Exp;

    typedef struct {
        unsigned int Cost;
        unsigned int currentPower;
    } Spell;

    typedef struct {
        unsigned int Lvl;
        unsigned int Hp;
        unsigned int Mp;
        unsigned int Exp;
    } CurrentStat;

    typedef struct {
        char* name;
        unsigned int ATK;
        unsigned int INTEL;
        unsigned int DEF;
        Critical CRIT;
        Exp EXP;
    } BaseStat;

    typedef struct{
        CurrentStat current;
        BaseStat base;
    } Stat;

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