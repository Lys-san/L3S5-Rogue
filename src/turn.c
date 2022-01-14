#include "turn.h"


int enemyTurn(Enemy monster, Player* player, Point coordEnemy, Stage *stage){

    assert(NULL != stage);
    assert(NULL != player);
    
    /* If the hero is adjacent */
    if(isAdjacent(coordEnemy, player->coords)){
        enemyAttack(monster, player);/* Perform an attack */
        if(player->stat.current.hp < 0){/* The player is dead */
            return 1;
        }
    }

    /* If the hero is in the same screen */
    if(isInScreen(coordEnemy, player->coords)){
        enemyMove(stage, coordEnemy, player->coords);/* Move to the player */
    }

    return 0;
}

int allEnemyTurn(Stage *stage, Player* player, ListCoord* coordsEnnemies){
    
    ListCoord* tmp;
    
    assert(NULL != stage);
    assert(NULL != player);

    tmp = coordsEnnemies;

    while(tmp != NULL){
        if(enemyTurn(stage->cells[tmp->coords.y][tmp->coords.x].enemy, player, tmp->coords, stage)){
            return 1;/* The player is dead */
        }
        tmp = tmp->nextCoord; /* Activate the next enemy */
    }

    return 0;
}
int turnEnemyOnScreen(Stage *stage, Player* player){
    
    int i, j;
    int playerDeath;
    Point topLeft;
    ListCoord* coordsEnnemies;

    assert(NULL != stage);
    assert(NULL != player);

    coordsEnnemies = NULL;
    /* Point to the top left of the screen */
    topLeft.x = player->coords.x - (SCREEN_WIDTH/2);
    topLeft.y = player->coords.y - (SCREEN_HEIGHT/2);

    /* Make listCoord(see list.h) of all the coordinates of the enemy */
    for(i = 0;i < SCREEN_WIDTH; i++){
        for(j = 0;j < SCREEN_HEIGHT; j++){
            if(stage->cells[topLeft.y+i][topLeft.x+j].type == ENEMY){
                coordsEnnemies = addCoord(coordsEnnemies, topLeft.x+j, topLeft.y+i);
            }/* If there is an enemy add it's coordinates */
        }
    }

    /*Activates all enemies*/
    playerDeath = allEnemyTurn(stage, player, coordsEnnemies);
    free(coordsEnnemies);

    return playerDeath;
}

int playerTurn(Player *player, StageList *dungeon, int *play, int *quit){
    
    enum PLAYER_ACTION action = NO_ACTION;
    int actionDone = 0;

    /* display */
    MLV_clear_window(MLV_COLOR_WHITE); /*pour les tests*/
    displayStage((*dungeon)->stage, *player, BASIC);
    displayHUD(*player);
    displayAtkButtons();

    /* events */
    action = getPlayerAction();
    while(action == NO_ACTION) {
        action = getPlayerAction();
    }
    actionDone = doAction(action, player, dungeon);
    /* exit game */
    if(actionDone == -1) {
        if(yesNoPopup("Exit game ?")) {
            *play = 0;
            *quit = 1;
            if(!saveGame(player, dungeon)){
                fprintf(stderr, "the saveFile wasn't created");
                return 0;
            }
            return 1;
        }
    }

    if(actionDone && actionDone != -1){
        if(turnEnemyOnScreen(&((*dungeon)->stage), player)){
            printf("Game Over \n");
            *play = 0;
            *quit = 1;
            return 1;
        }
        gainAllEffect(player);
    }
    return 1;
}