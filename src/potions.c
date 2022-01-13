#include "potions.h"

void useMagicPotion(Player *player){

    int maxMagic;

    assert(NULL != player);
    
    maxMagic = standardMaxMP(*player);
    player->stat.current.mp += (10*maxMagic)/100;/* Heal 10% of max mp */

    /*if the mp stat is higher than the max */
    if(player->stat.current.mp > maxMagic){
        player->stat.current.mp = maxMagic;/* Reset to max MP */
    }
}

void useHealingPotion(Player *player){
    
    int maxHealth;

    assert(NULL != player);
    
    maxHealth = standardMaxHP(*player);
    player->stat.current.hp += (10*maxHealth)/100;/* Heal 10% of max hp */

    /*if the hp stat is higher than the max */
    if(player->stat.current.hp > maxHealth){
        player->stat.current.hp = maxHealth;/* Reset to max HP */
    }
}

void turnRegenPotion(Player *player){

    int maxHealth, maxMagic;

    assert(NULL != player);
    
    maxHealth = standardMaxHP(*player);
    maxMagic = standardMaxMP(*player);
    
    /* Heal the player */
    player->stat.current.hp += 20;
    player->stat.current.mp += 10;

    /*if the current stat is higher than the max */
    if(player->stat.current.hp > maxHealth){
        player->stat.current.hp = maxHealth;/* Reset to max HP */
    }
    if(player->stat.current.mp > maxMagic){
        player->stat.current.mp = maxMagic;/* Reset to max MP */
    }
}

void gainRegenPotion(Player *player){

    assert(NULL != player);
    
    player->underRegenPotion = NUMBER_TURN_EFFECT;
}

void gainPrecision(Player *player){

    assert(NULL != player);
    
    player->underPrecisionPotion = NUMBER_TURN_EFFECT;
    player->stat.base.CRIT.rate += 10;/* acquire the bonus of critRate */
}

void losePrecision(Player *player){

    assert(NULL != player);
    
    player->stat.base.CRIT.rate -= 10; /* decrease the critRate*/
}

void gainLearning(Player *player){

    assert(NULL != player);
    
    player->underLearningPotion = NUMBER_TURN_EFFECT;
}

void gainAllEffect(Player *player){

    assert(NULL != player);

    /* Decrease the remaining number of learningPotion */
    if(player->underLearningPotion != 0){
        player->underLearningPotion -= 1;
    }

    /* Decrease the remaining number of precisionPotion */
    if(player->underPrecisionPotion != 0){
        player->underPrecisionPotion -= 1;
        if(player->underPrecisionPotion == 0){
            losePrecision(player);/* at the last turn remove the precision acquired */
        }
    }
    if(player->underRegenPotion != 0){
        player->underRegenPotion -= 1;
        turnRegenPotion(player);/* heal 20 hp and 10 mp */
    }
}