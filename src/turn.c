#include "turn.h"


int enemyTurn(Enemy monster, Player* player, Point* coordEnemy, Stage *level){
    
    /* If the hero is adjacent */
    if(isAdjacent(*coordEnemy, player->coords)){
        printf("the player is adjacent \n");
        enemyAttack(monster, player);/* perform an attack */
        printf("the player is at %d \n", player->stat.current.hp);
        if(player->stat.current.hp < 0){
            printf("The player is dead \n");
            return 1;
        }
    }
    else{
        printf("the player isn't adjacent \n");
    }

    /* If the hero is in the same screen */
    if(isInScreen(*coordEnemy, player->coords)){
        printf("the player is on the screen \n");
        enemyMove(level, coordEnemy, player->coords);/*Move to the player*/
    }
    else{
        printf("the player isn't on the screen \n");
    }
    return 0;
}
int allEnemyTurn(Stage *level, Player* player, ListEnemy* allEnemies){
    ListEnemy* tmp;
    tmp = allEnemies;
    while(tmp != NULL){
        if(enemyTurn(tmp->enemy, player, &tmp->coords, level)){
            printf("Game Over \n");
            return 1;
        }
        tmp = tmp->nextEnemy;
    }
    return 0;
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