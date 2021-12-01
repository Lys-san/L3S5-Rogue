/* Auteurs : Nicolas Mazeyrac, Lysandre Macke
 * Creation : 30/11/2021
 * Modification : 30/11/2021*/

/*Bibliothèque générale*/
#include <stdio.h>

/*Bibliothèque interne*/
#include "player.h"

void initializeCritStat(Player *player){

    PLAYER_BASE_STATS.CRIT.Modificater = STANDARD_BASE_CRIT_MODIFIER ; /*300%*/
    PLAYER_BASE_STATS.CRIT.Rate = STANDARD_BASE_CRIT_RATE;             /*5%*/
    PLAYER_BASE_STATS.CRIT.accuracy = STANDARD_BASE_ACCURACY;          /*20*/
}


void initializeBaseStat(Player *player, char* name) {
    
    PLAYER_BASE_STATS.name = name;
    
    /*Reminder : STANDARD_BASE_STAT = 10*/
    PLAYER_BASE_STATS.ATTACK = STANDARD_BASE_STAT;
    PLAYER_BASE_STATS.INTELLIGENCE = STANDARD_BASE_STAT;
    PLAYER_BASE_STATS.DEFENSE = STANDARD_BASE_STAT;

    initializeCritStat(player);
}

void initializeCurrentStat(Player *player) {
    PLAYER_CURRT_STATS.Lvl = 1;
    PLAYER_CURRT_STATS.Hp = STANDARD_MAX_HP;/*100*/
    PLAYER_CURRT_STATS.Mp = STANDARD_MAX_MP;/*50*/
    PLAYER_CURRT_STATS.Exp = 0;
}

void initializeStat(Player *player, char* name) {
    initializeBaseStat(player, name);
    initializeCurrentStat(player);
}


void initializeStandard(Player *player, char* name) {
    initializeStat(player, name);
}


void quickPrintPlayer(Player* player){
    printf("****PLAYER STATS****\n");
    printf("name : %s\n", PLAYER_BASE_STATS.name);

    printf("lvl           : %d\n", PLAYER_CURRT_STATS.Lvl);
    printf("exp           : %d\n", PLAYER_CURRT_STATS.Exp);
    printf("expBar        : %d\n", STANDARD_EXP_TO_NEXT_LVL);

    printf("strenght      : %d\n", PLAYER_BASE_STATS.ATTACK);
    printf("intellig      : %d\n", PLAYER_BASE_STATS.INTELLIGENCE);
    printf("def           : %d\n", PLAYER_BASE_STATS.DEFENSE );

    printf("hp            : %d\n", PLAYER_CURRT_STATS.Hp);
    printf("mp            : %d\n", PLAYER_CURRT_STATS.Mp);

    printf("CritModifiyer : %d%%\n", PLAYER_BASE_STATS.CRIT.Modificater);
    printf("CritRate      : %d%%\n", PLAYER_BASE_STATS.CRIT.Rate);
    printf("Accuracy      : %d%%\n", PLAYER_BASE_STATS.CRIT.accuracy);
}