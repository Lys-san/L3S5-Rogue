#include "turn.h"


int enemyTurn(Enemy monster, Player* player, Point coordEnemy, Stage *level){
    
    /* If the hero is adjacent */
    if(isAdjacent(coordEnemy, player->coords)){
        /*printf("the player is adjacent \n");
        enemyAttack(monster, player);*//* perform an attack */
        /*printf("the player is at %d \n", player->stat.current.hp);
        if(player->stat.current.hp < 0){
            printf("The player is dead \n");
            return 1;
        }*/
    }
    else{
        printf("the player isn't adjacent \n");
    }

    /* If the hero is in the same screen */
    if(isInScreen(coordEnemy, player->coords)){
        printf("the player is on the screen \n");
        enemyMove(level, coordEnemy, player->coords);/*Move to the player*/
    }
    else{
        printf("the player isn't on the screen \n");
    }
    return 0;
}

int allEnemyTurn(Stage *level, Player* player, ListCoord* coordsEnnemies){
    ListCoord* tmp;
    tmp = coordsEnnemies;
    while(tmp != NULL){
        if(enemyTurn(level->cells[tmp->coords.y][tmp->coords.x].enemy, player, tmp->coords, level)){
            printf("Game Over \n");
            return 1;
        }
        tmp = tmp->nextCoord;
    }
    return 0;
}
int turnEnemyOnScreen(Stage *level, Player* player){
    int i, j;
    int playerDeath;
    ListCoord* coordsEnnemies;
    coordsEnnemies = NULL;
    
    for(i = 0;i < SCREEN_WIDTH; i++){
        for(j = 0;j < SCREEN_HEIGHT; j++){
            if(level->cells[i][j].type == ENEMY){
                coordsEnnemies = addCoord(coordsEnnemies, 1, j, i);
            }
        }
    }
    playerDeath = allEnemyTurn(level, player, coordsEnnemies);
    free(coordsEnnemies);
    return playerDeath;
}
/*
    
    Stage stage;
    Player player;
    Enemy enemy;
    Point coordEnemy;
    int i;

    stage = generateStageTest();
    enemy = generateEnemy(1, 1);

    coordEnemy.x = 7;
    coordEnemy.y = 2;

    
    initializeStandard(&player, "Bob");
    player.coords.x = 1;
    player.coords.y = 2;
    
    quickPrintEnemy(enemy);
    quickPrintStage(stage);

    for(i=0;i<10;i++){
        enemyTurn(enemy,&player, &coordEnemy, &stage);
        quickPrintStage(stage);
    }

    return 0;
*/