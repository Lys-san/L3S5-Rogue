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

    assert(NULL != player);

    player->stat.base.CRIT.modificater = STANDARD_BASE_CRIT_MODIFIER ; /* 300% */
    player->stat.base.CRIT.rate = STANDARD_BASE_CRIT_RATE;             /* 5% */
    player->stat.base.CRIT.accuracy = STANDARD_BASE_ACCURACY;          /*  +/-20%  */
}

void initializeBaseStat(Player *player) {

    assert(NULL != player);
    
    /*Reminder : STANDARD_BASE_STAT = 10*/
    player->stat.base.ATTACK = STANDARD_BASE_STAT;
    player->stat.base.INTELLIGENCE = STANDARD_BASE_STAT;
    player->stat.base.DEFENSE = STANDARD_BASE_STAT;

    initializeCritStat(player);
}

void initializeCurrentStat(Player *player) {

    assert(NULL != player);

    /* Starts at level 1 with no exp */
    player->stat.current.lvl = 1;
    player->stat.current.exp = 0;

    /* Uses the DEFENSE and INTELLIGENCE stat to fix the current hp and mp */
    player->stat.current.hp = standardMaxHP(*player);/*100*/
    player->stat.current.mp = standardMaxMP(*player);/*50*/
}

void initializeStat(Player *player) {

    assert(NULL != player);
    
    initializeBaseStat(player);
    initializeCurrentStat(player);/* the current stat uses the base stat to initialize */
}

void addBasicSpell(Spell *spell){

    assert(NULL != spell);
    
    spell->cost = 20; /* The spell cost 20 MP */
    spell->power = 2; /* Spell cast = 2*Int */
}

void addBasicEquipment(Player *player){

    assert(NULL != player);
    
    /*Generates equipment that has no bearings on the stat to fix what kind of equipment there are*/
    player->equip[(int)ARMOR].equipment = generateEquipment(ARMOR, 0, 0);
    player->equip[(int)WEAPON].equipment = generateEquipment(WEAPON, 0, 0);
    player->equip[(int)WAND].equipment = generateEquipment(WAND, 0, 0);
}

void initializaInventory(Player *player){

    int i;

    assert(NULL != player);

    /* Fill the inventory with NO_ITEM (see loot.h) */
    for(i = 0; i < MAX_INVENTORY; i++) {
        player->inventory[i] = generateLoot(1, 1, NO_ITEM);
    }

}
void initializeStandard(Player *player) {

    assert(NULL != player);
    
    initializeStat(player);/* initialise the stat of the player */
    
    /* adds the other basic information that is not part of the stats*/
    addBasicSpell(&player->spell);
    addBasicEquipment(player);
    initializaInventory(player);
    player->nbrItemHeld = 0;
    player->underLearningPotion = 0;
    player->underRegenPotion = 0;
    player->underPrecisionPotion = 0;
}

int gainLvl(Player *player){
    
    int nextLvlExp;

    assert(NULL != player);

    nextLvlExp = standardExpToNextlevel(*player);
    
    /*If the player hasn't have enough exp doesn't do anything*/
    if( player->stat.current.exp < nextLvlExp){
        return 0;
    }

    player->stat.current.lvl += 1;/* gains a level */
    player->stat.current.exp -= nextLvlExp;/* remove the exp needed to pass the level */
    return 1;
}

int gainExp(Player *player, unsigned int exp){
    
    assert(NULL != player);

    int numberLevel;

    numberLevel = 0;

    if(player->underLearningPotion){
        player->stat.current.exp += (exp*30)/100;/*if the learning potion is active gain 30% more exp */
    }
    player->stat.current.exp += exp;/* add the exp */
    while(gainLvl(player)){/* while the exp is more than what is needed for one level */
        numberLevel += 1;
    }
    return numberLevel;
}


void equipArmor(Player *player, Equipment armor){

    Equipment oldArmor;

    assert(NULL != player);

    /* unequip the old equipment */
    oldArmor = player->equip[(int)ARMOR].equipment;
    player->stat.base.DEFENSE -= oldArmor.quality + oldArmor.rarity;

    /* equip the new equipment */
    player->equip[(int)ARMOR].equipment = armor;
    player->stat.base.DEFENSE += armor.quality + armor.rarity;
}

void equipWeapon(Player *player, Equipment weapon){

    Equipment oldWeapon;

    assert(NULL != player);

    /* unequip the old equipment */
    oldWeapon = player->equip[(int)WEAPON].equipment;
    player->stat.base.ATTACK -= oldWeapon.quality + oldWeapon.rarity;

    /* equip the new equipment */
    player->equip[(int)WEAPON].equipment = weapon;
    player->stat.base.ATTACK += weapon.quality + weapon.rarity;
}

void equipWand(Player *player, Equipment wand){
    
    Equipment oldWand;

    assert(NULL != player);

    /* unequip the old equipment */
    oldWand = player->equip[(int)WAND].equipment;
    player->stat.base.INTELLIGENCE -= oldWand.quality + oldWand.rarity;

    /* equip the new equipment */
    player->equip[(int)WAND].equipment = wand;
    player->stat.base.INTELLIGENCE += wand.quality + wand.rarity;
}

int checkEquip(Player *player, Equipment equip){
    
    int currentStatBoost, equipStatBoost;

    assert(NULL != player);
    assert((int)equip.type < MAX_EQUIP);/*check if the equipment can be worn */

    currentStatBoost = player->equip[(int)equip.type].equipment.quality + player->equip[(int)equip.type].equipment.rarity;
    equipStatBoost = equip.quality + equip.rarity;

    if ( equipStatBoost > currentStatBoost ){/* if the equipment is worse than the last one */
        return 1;
    }
    return 0;
}

void newEquipment(Player *player, Equipment equip){
    
    if(checkEquip(player, equip)){/* if the new equipment is better */

        switch(equip.type){/* equip the assigned weapon type */
            case ARMOR: equipArmor(player, equip) ;break;
            case WEAPON : equipWeapon(player, equip) ;break;
            case WAND: equipWand(player, equip)  ;break;
            default: fprintf(stderr, "ERROR: not an equipment that can be equipped \n");
        }

    }

}

void  addToInventory(Player* player, Loot loot){

    assert(NULL != player);

    if(player->nbrItemHeld < MAX_INVENTORY){/* if there is still place in it's inventory */
        player->inventory[player->nbrItemHeld] = loot;/* place it on a new place */
        player->nbrItemHeld += 1;
    }
}

int printPlayer(Player player){
    printf("****PLAYER STATS****\n");

    printf("lvl           : %d\n", player.stat.current.lvl);
    printf("exp           : %d\n", player.stat.current.exp);
    printf("expBar        : %d\n", standardExpToNextlevel(player));

    printf("strenght      : %d\n", player.stat.base.ATTACK);
    printf("intellig      : %d\n", player.stat.base.INTELLIGENCE);
    printf("def           : %d\n", player.stat.base.DEFENSE );

    printf("hp            : %d\n", player.stat.current.hp);
    printf("mp            : %d\n", player.stat.current.mp);

    printf("CritRate      : %d%%\n", player.stat.base.CRIT.rate);
    /*changes made as to appear as the true pourcentage*/
    printf("CritModifiyer : %d%%\n", player.stat.base.CRIT.modificater*100);
    printf("Accuracy      : %d%% - %d%%\n", 100-player.stat.base.CRIT.accuracy, 100+player.stat.base.CRIT.accuracy);
    return 1;
}