#include "enemy.h"

Enemy generateEnemy(unsigned int stage, unsigned int distance) {
    
    Enemy monster;
    unsigned int stat;

    monster.name = "Monster";

    stat = 10*stage + distance;
    
    monster.attack = stat;/*Stat*/
    monster.hp = stat;/*Stat*/

    monster.exp = stat/2;/*the number of exp given after death*/

    monster.crit.modificater = 3 ;   /* 300% */
    monster.crit.rate = 5;           /* 5% */
    monster.crit.accuracy = 20 ;    /* +/-20% */

    return monster;
}

void quickPrintEnemy(Enemy monster){
    printf("****Enemy STATS****\n");
    printf("name            : %s\n", monster.name);

    printf("strenght        : %d\n",  monster.attack);

    printf("hp              : %d\n", monster.hp);
    printf("exp             : %d\n", monster.exp);

    printf("CritModificater : %d%%\n", monster.crit.modificater*100);
    printf("CritRate        : %d%%\n", monster.crit.rate);
    printf("Accuracy        : %d%% - %d%%\n", 100-monster.crit.accuracy, 100+monster.crit.accuracy);
}