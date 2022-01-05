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

void addBasicEquipment(Player *player){
    player->equip[(int)ARMOR].equipment = generateEquipment(ARMOR, 0, 0);
    player->equip[(int)WEAPON].equipment = generateEquipment(WEAPON, 0, 0);
    player->equip[(int)WAND].equipment = generateEquipment(WAND, 0, 0);
}


void initializeStandard(Player *player, char* name) {
    initializeStat(player, name);
    addBasicSpell(&player->spell);
    addBasicEquipment(player);
}

void gainExp(Player *player, unsigned int exp){
    player->stat.current.exp += exp;
}

int gainLvl(Player *player){
    
    int nextLvlExp;

    nextLvlExp = standardExpToNextlevel(*player);
    
    /*If the player hasn't have enough exp*/
    if( player->stat.current.exp < nextLvlExp){
        return 0;
    }

    player->stat.current.exp -= nextLvlExp;
    player->stat.current.lvl += 1;
    return 1;
}

void useMagicPotion(Player *player){
    int maxMagic;
    maxMagic = standardMaxMP(*player);
    player->stat.current.mp += (10*maxMagic)/100;
    if(player->stat.current.mp > maxMagic){
        player->stat.current.mp = maxMagic;
    }
}

void useHealingPotion(Player *player){
    int maxHealth;
    maxHealth = standardMaxHP(*player);
    player->stat.current.hp += (10*maxHealth)/100;
    if(player->stat.current.hp > maxHealth){
        player->stat.current.hp = maxHealth;
    }
}

void turnRegenPotion(Player *player){
    int maxHealth, maxMagic;
    maxHealth = standardMaxHP(*player);
    maxMagic = standardMaxMP(*player);
    player->stat.current.hp += 20;
    player->stat.current.mp += 10;
    if(player->stat.current.hp > maxHealth){
        player->stat.current.hp = maxHealth;
    }
    if(player->stat.current.mp > maxMagic){
        player->stat.current.mp = maxMagic;
    }
}

void gainPrecision(Player *player){
    player->stat.base.CRIT.rate += 10;
}

void losePrecision(Player *player){
    player->stat.base.CRIT.rate -= 10;
    if(player->stat.base.CRIT.rate < 0){
        player->stat.base.CRIT.rate = 0;
    }
}

void gainLearning(Player *player){

}

void loseLearning(Player *player){

}

void updateArmorStat(Player *player, Equipment armor){

    Equipment oldArmor;

    oldArmor = player->equip[(int)ARMOR].equipment;
    player->stat.base.DEFENSE -= oldArmor.quality + oldArmor.rarity;

    player->equip[(int)ARMOR].equipment = armor;
    player->stat.base.DEFENSE += armor.quality + armor.rarity;
}

void updateWeaponStat(Player *player, Equipment weapon){
    Equipment oldWeapon;

    oldWeapon = player->equip[(int)WEAPON].equipment;
    player->stat.base.ATTACK -= oldWeapon.quality + oldWeapon.rarity;

    player->equip[(int)WEAPON].equipment = weapon;
    player->stat.base.ATTACK += weapon.quality + weapon.rarity;
}

void updateWandStat(Player *player, Equipment wand){
    Equipment oldWand;

    oldWand = player->equip[(int)WAND].equipment;
    player->stat.base.INTELLIGENCE -= oldWand.quality + oldWand.rarity;

    player->equip[(int)WAND].equipment = wand;
    player->stat.base.INTELLIGENCE += wand.quality + wand.rarity;
}

int checkEquip(Player *player, Equipment equip, int position){
    
    int currentStatBoost, equipStatBoost;

    currentStatBoost = player->equip[position].equipment.quality + player->equip[position].equipment.rarity;
    equipStatBoost = equip.quality + equip.rarity;

    if ( equipStatBoost > currentStatBoost ){
        return 1;
    }
    return 0;
}

int newEquipment(Player *player, Equipment equip){
    if(!checkEquip(player, equip, (int)equip.type)){
        return 1;
    }

    switch(equip.type){
        case ARMOR: updateArmorStat(player, equip) ;break;
        case WEAPON : updateWeaponStat(player, equip) ;break;
        case WAND: updateWandStat(player, equip)  ;break;
        default: printf("ERROR \n");
    }
    return 0;
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