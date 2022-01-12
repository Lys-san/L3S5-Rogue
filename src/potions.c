#include "potions.h"

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
    player->underLearningPotion = 1;
}

void loseLearning(Player *player){
    player->underLearningPotion = 0;
}


Effect createEffect(Consummables potion){
    Effect effect;

    switch(potion){
        case REGEN:
            effect.turnActivation = 3;
            effect.turnLeft = 30;
            effect.bonus = &turnRegenPotion;
            effect.malus = NULL;
            break;
        case LEARNING:
            effect.turnActivation = 30;
            effect.turnLeft = 30;
            effect.bonus = &gainLearning;
            effect.malus = &loseLearning;
        break;
        case PRECISION:
            effect.turnActivation = 30;
            effect.turnLeft = 30;
            effect.bonus = &gainPrecision;
            effect.malus = &losePrecision;
            break;
        default: fprintf(stderr, "doesnt give effect") ;
    }
    return effect;
}