/* Auteurs : Nicolas Mazeyrac, Lysandre Macke
 * Creation : 26/12/2021
 * Modification : 27/12/2021*/

#include "turn.h"


int enemyTurn(Enemy monster, Player* player, Point* coordEnemy, Point coordPlayer/*, Stage level*/){
    
    /* If the hero is adjacent */
    if(isAdjacent(*coordEnemy, coordPlayer)){
        enemyAttack(monster, player);/* perform an attack */
        if(isDead(player->stat.current.hp)){
            return 1;
        }
    }

    /* If the hero is in the same screen */
    if(isInScreen(*coordEnemy, coordPlayer)){
        enemyMove(/*level,*/ coordEnemy, coordPlayer);/*Move to the player*/
    }
    return 0;
}

int isDead(unsigned int hp){
    if(hp <= 0){
        return 0;
    }
    return 1;
}