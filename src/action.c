/* Auteurs : Nicolas Mazeyrac, Lysandre Macke
 * Creation : 26/12/2021
 * Modification : 27/12/2021*/

#include "action.h"

/* Attack */
unsigned int attackPhysical(unsigned int attack, Critical crit){
    
    unsigned int accuracy;
    unsigned int critical;
    unsigned int chance;

    srand( time( NULL ) );

    accuracy = calculateAccuracy(crit);

    chance = rand() % 101;/*Chance for a crit*/

    if(crit.rate >= chance){
        critical = crit.modificater;
    }
    else{
        critical = 1;
    }

    return (unsigned int)(((attack * accuracy)/100)*critical);/*dmg for the physical attack*/
}

unsigned int calculateAccuracy(Critical crit){
    unsigned int bonus;
    unsigned int chance;
    unsigned int accuracy;

    accuracy = 100;

    chance = rand() % 2 + 1;/* Chance for the accuracy to be a bonus or a malus*/

    bonus = (rand() % crit.accuracy);/* Number for the bonus/malus change */

    if(chance == 1){
        accuracy -= bonus;
    }
    else{
        accuracy += bonus;
    }

    return accuracy;
}

void enemyAttak(Enemy monster, Player* player){
    unsigned int damage;
    damage = attackPhysical(monster.attack, monster.crit);
    player->stat.current.hp -= damage;
}

/* Move */

Point Move(Point coordInit, Direction dir){

    Point newCoord;
    int x, y;

    dirToShiftValues(dir, &x, &y);
    newCoord.x = coordInit.x + x;/* Change the coord */
    newCoord.y = coordInit.y + y;
    return newCoord;
}

void enemyMove(/*Stage level,*/ Point* coordEnemy, Point coordPlayer){
    
    int lateralDistance;
    int verticalDistance;
    Point newCoord;

    lateralDistance = coordPlayer.x - coordEnemy->x;
    verticalDistance = coordPlayer.y - coordEnemy->y;

    if(abs(verticalDistance) >= abs(lateralDistance)){
        if(verticalDistance < 0){
            newCoord = Move(*coordEnemy, N);/* Move up */
        }
        else{
            newCoord = Move(*coordEnemy, S);/* Move down */
        }
    }
    else{
        /*left and right*/
        if(lateralDistance < 0){
            newCoord = Move(*coordEnemy, W);/* Move left */
        }
        else{
            newCoord = Move(*coordEnemy, E);/* Move right */
        }
    }

    /*if( ( level.cells[newCoord.y][newCoord.x].type == ROOM ) && ( coordEnemy != coordPlayer ) ){*/
        coordEnemy->x = newCoord.x;
        coordEnemy->y = newCoord.y;
    /*}*/
}