#include "enemy.h"
#include <stdio.h>

Enemy generateEnemy(unsigned int stage, unsigned int manhattan) {
    
    Enemy monster;
    unsigned int stat;

    monster.name = "Monster";

    stat = 10*stage + manhattan;
    monster.attack = stat;
    monster.hp = stat;

    monster.crit.modificater = 300 ; /* 300% */
    monster.crit.rate = 5;           /* 5% */
    monster.crit.accuracy = 20 ;    /* +/-20% */

    return monster;
}

int enemyIsDead(Enemy monster) {
    return 0;
}


void quickPrintEnemy(Enemy monster){
    printf("****Enemy STATS****\n");
    printf("name          : %s\n", monster.name);

    printf("strenght      : %d\n",  monster.attack);

    printf("hp            : %d\n", monster.hp);

    printf("CritModifiyer : %d%%\n", monster.crit.modificater);
    printf("CritRate      : %d%%\n", monster.crit.rate);
    printf("Accuracy      : %d%%\n", monster.crit.accuracy);
}