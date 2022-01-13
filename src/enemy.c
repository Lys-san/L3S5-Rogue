#include "enemy.h"

Enemy generateEnemy(unsigned int level, unsigned int distance) {

    Enemy monster;
    unsigned int stat;
    
    /* Not random as to assure that the monster are progressively harder */
    stat = 10*level + distance;      /*Calculate the base stat based on the level and the distance to the center*/
    
    monster.attack = stat;
    monster.hp = stat;

    monster.exp = stat/2;            /* The number of exp given after death*/

    monster.crit.modificater = 3 ;   /* 300% */
    monster.crit.rate = 5;           /* 5% */
    monster.crit.accuracy = 20 ;     /* +/-20% */
    return monster;
}

int printEnemy(Enemy monster){

    printf("****Enemy STATS****\n");

    printf("strenght        : %d\n",  monster.attack);

    printf("hp              : %d\n", monster.hp);
    printf("exp             : %d\n", monster.exp);

    printf("CritRate        : %d%%\n", monster.crit.rate);
    /*changes made as to appear as the true pourcentage*/
    printf("CritModificater : %d%%\n", monster.crit.modificater*100);
    printf("Accuracy        : %d%% - %d%%\n", 100-monster.crit.accuracy, 100+monster.crit.accuracy);
    return 1;
}
