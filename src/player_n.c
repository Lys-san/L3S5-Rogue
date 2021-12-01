/* Auteurs : Nicolas Mazeyrac, Lysandre Macke
 * Creation : 30/11/2021
 * Modification : 30/11/2021*/

/*Bibliothèque générale*/
#include <stdio.h>

/*Bibliothèque interne*/
#include "player.h"

void initializeCritStat(Player *player){

    player->stat.base.CRIT.Modificater = STANDARD_BASE_CRIT_MODIFIER ; /*300%*/
    player->stat.base.CRIT.Rate = STANDARD_BASE_CRIT_RATE; /*5%*/
    player->stat.base.CRIT.accuracy = STANDARD_BASE_ACCURACY; /*20*/

}


void initializeBaseStat(Player *player, char* name) {
    
    player->stat.base.name = name;
    
    /*Reminder : STANDARD_BASE_STAT = 10*/
    player->stat.base.ATTACK = STANDARD_BASE_STAT;
    player->stat.base.INTELLIGENCE = STANDARD_BASE_STAT;
    player->stat.base.DEFENSE = STANDARD_BASE_STAT;

    initializeCritStat(player);
}

void initializeCurrentStat(Player *player) {
    player->stat.current.Lvl = 1;
    player->stat.current.Hp = STANDARD_MAX_HP;/*100*/
    player->stat.current.Mp = STANDARD_MAX_MP;/*50*/
    player->stat.current.Exp = 0;
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
    printf("name : %s\n", player->stat.base.name);

    printf("lvl           : %d\n", player->stat.current.Lvl);
    printf("exp           : %d\n", player->stat.current.Exp);
    printf("expBar        : %d\n", STANDARD_EXP_TO_NEXT_LVL);

    printf("strenght      : %d\n", player->stat.base.ATTACK);
    printf("intellig      : %d\n", player->stat.base.INTELLIGENCE);
    printf("def           : %d\n", player->stat.base.DEFENSE );

    printf("hp            : %d\n", player->stat.current.Hp);
    printf("mp            : %d\n", player->stat.current.Mp);

    printf("CritModifiyer : %d%%\n", player->stat.base.CRIT.Modificater);
    printf("CritRate      : %d%%\n", player->stat.base.CRIT.Rate);
    printf("Accuracy      : %d%%\n", player->stat.base.CRIT.accuracy);
}