/* Auteurs : Nicolas Mazeyrac, Lysandre Macke
 * Creation : 26/12/2021
 * Modification : 27/12/2021*/

#include "turn.h"


int enemyTurn(Enemy monster, Player* player, Point* coordEnemy, Point coordPlayer/*, Stage level*/){
    
    /* If the hero is adjacent */
    if(isAdjacent(*coordEnemy, coordPlayer)){
        enemyAttak(monster, player);/* perform an attack */
        if(playerIsDead(*player)){
            return 1;
        }
    }

    /* If the hero is in the same screen */
    if(isInScreen(*coordEnemy, coordPlayer)){
        enemyMove(/*level,*/ coordEnemy, coordPlayer);/*Move to the player*/
    }
    return 0;
}