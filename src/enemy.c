#include "enemy.h"

Enemy generateEnemy(unsigned int level, unsigned int distance) {

    Enemy monster;
    unsigned int maxStat;
    int baseExp;
    
    maxStat = distance*level;      /*Calculate the max stat based on the level and the distance to the center*/
    
    monster.attack = (rand() % (maxStat-level)) + level; /* Calculate the max stat and the currentlevel */
    monster.hp = (rand() % (maxStat-level)) + level;    /* Calculate the max stat and the currentlevel */

    baseExp = (MINIMUM_EXP+((level-1)*2));        /* Minimum exp of a monster base, max exp of the last level plus MINIMUM_EXP */
    monster.exp = (rand() % (level*2)) + baseExp; /* In order to gain at least two levels per stage level if you have beaten every enemy*/

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
