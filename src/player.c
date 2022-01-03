/* Auteurs : Nicolas Mazeyrac, Lysandre Macke
 * Creation : 30/11/2021
 * Modification : 30/11/2021*/

/*Bibliothèque générale*/
#include <stdio.h>

/*Bibliothèque interne*/
#include "player.h"

int standardMaxHP(Player player) {
    return 10 * player.stat.base.DEFENSE;
}


int standardMaxMP(Player player) {
    return (10*player.stat.base.INTELLIGENCE - 50 > 0) ? (10 * player.stat.base.INTELLIGENCE - 50) : 0;
}


int standardExpToNextlevel(Player player) {
    return 350 + 50*(player.stat.current.lvl);
}


void initializeCritStat(Player *player) {
    player->stat.base.CRIT.modificater = STANDARD_BASE_CRIT_MODIFIER ; /* 300% */
    player->stat.base.CRIT.rate = STANDARD_BASE_CRIT_RATE;             /* 5% */
    player->stat.base.CRIT.accuracy = STANDARD_BASE_ACCURACY;          /*  +/-20%  */
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
    player->stat.current.lvl = 1;
    player->stat.current.hp = standardMaxHP(*player);/*100*/
    player->stat.current.mp = standardMaxMP(*player);/*50*/
    player->stat.current.exp = 0;
}

void initializeStat(Player *player, char* name) {
    initializeBaseStat(player, name);
    initializeCurrentStat(player);
}

void addBasicSpell(Spell *spell){
    spell->cost = 20; /* The spell cost 20 MP */
    spell->power = 2; /* Spell cast = 2*Int */
}


void initializeStandard(Player *player, char* name) {
    initializeStat(player, name);
    addBasicSpell(&player->spell);
}

void gainExp(Player *player, unsigned int exp){
    player->stat.current.exp += exp;
}

int gainLvl(Player *player){
    
    int nextLvlExp;

    nextLvlExp = standardExpToNextlevel(*player);
    
    if( player->stat.current.exp < nextLvlExp){
        return 0;
    }

    player->stat.current.exp -= nextLvlExp;
    player->stat.current.lvl += 1;
    return 1;
}

void quickPrintPlayer(Player player){
    printf("****PLAYER STATS****\n");
    printf("name          : %s\n", player.stat.base.name);

    printf("lvl           : %d\n", player.stat.current.lvl);
    printf("exp           : %d\n", player.stat.current.exp);
    printf("expBar        : %d\n", standardExpToNextlevel(player));

    printf("strenght      : %d\n", player.stat.base.ATTACK);
    printf("intellig      : %d\n", player.stat.base.INTELLIGENCE);
    printf("def           : %d\n", player.stat.base.DEFENSE );

    printf("hp            : %d\n", player.stat.current.hp);
    printf("mp            : %d\n", player.stat.current.mp);

    printf("CritModifiyer : %d%%\n", player.stat.base.CRIT.modificater);
    printf("CritRate      : %d%%\n", player.stat.base.CRIT.rate);
    printf("Accuracy      : %d%%\n", player.stat.base.CRIT.accuracy);
}