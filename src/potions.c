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

void gainRegenPotion(Player *player){
    player->underRegenPotion = 30;
}

void gainPrecision(Player *player){
    player->underPrecisionPotion = 30;
    player->stat.base.CRIT.rate += 10;
}

void losePrecision(Player *player){
    player->stat.base.CRIT.rate -= 10;
    if(player->stat.base.CRIT.rate < 0){
        player->stat.base.CRIT.rate = 0;
    }
}

void gainLearning(Player *player){
    player->underLearningPotion = 30;
}

void gainAllEffect(Player *player){
    if(player->underLearningPotion != 0){
        player->underLearningPotion -= 1;
    }

    if(player->underPrecisionPotion != 0){
        player->underPrecisionPotion -= 1;
        if(player->underPrecisionPotion == 0){
            losePrecision(player);
        }
    }
    if(player->underRegenPotion != 0){
        player->underRegenPotion -= 1;
        turnRegenPotion(player);
    }
}