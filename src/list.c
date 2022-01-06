#include "list.h"


ListEnemy* searchEnemy(ListEnemy* allEnemies, Point coordEnemy){
	
	ListEnemy *newEnemy;
	
	newEnemy = allEnemies;/*Create a copy of the liste*/

	while(newEnemy != NULL){/* search while the list isn't empty*/
		if(isTheSame(newEnemy->coords, coordEnemy)){
            return newEnemy;
        }
        newEnemy = newEnemy->nextEnemy ;
	}
	return NULL;
}

ListEnemy* addEnemy(ListEnemy* allEnemies,int level , int x, int y, Point  stairUpCoords){
    
    ListEnemy *newEnemy;

    /* Create  a new element */
    newEnemy = malloc(sizeof(ListEnemy));
    newEnemy->coords = newPoint(x, y);
    newEnemy->enemy = generateEnemy(level, distanceWithL1Norm(stairUpCoords, newEnemy->coords));

    newEnemy->nextEnemy = allEnemies;/*Adds at the top of the list*/

    return newEnemy;
}

ListEnemy* removeEnemy(ListEnemy* allEnemies, Point coordEnemy){
    
    ListEnemy *newEnemy;
    newEnemy = allEnemies;

    if(newEnemy != NULL){
    	if(isTheSame(newEnemy->coords, coordEnemy)){
    		newEnemy = allEnemies->nextEnemy;
    		free(allEnemies);
    		return newEnemy;
    	}
    	else{
    		allEnemies->nextEnemy = removeEnemy(allEnemies->nextEnemy, coordEnemy);
    	}
    }
    return NULL;
}

ListEnemy* locatesAllEnemies(Stage stage, int level){
    
    int i,j;
    ListEnemy* allEnemies;
    Point  stairUpCoords;
    
    allEnemies = NULL;

    stairUpCoords = newPoint(LEVEL_WIDTH/2, LEVEL_HEIGHT/2);

    for(i = 0; i < LEVEL_HEIGHT; i++) {
        for(j = 0; j < LEVEL_WIDTH; j++) {
            if(stage.cells[i][j].type == ENEMY){
                allEnemies = addEnemy(allEnemies, level, j, i, stairUpCoords);
            }
        }
    }
    return allEnemies;
}

void printAllEnemies(ListEnemy *allEnemies){
	ListEnemy *tmp;
	tmp = allEnemies;
	while(tmp != NULL){
		printf("coord : \n x = %d \n y = %d \n", tmp->coords.x, tmp->coords.y);
		quickPrintEnemy(tmp->enemy);
		tmp = tmp->nextEnemy;
	}
}

ListTreasure* addTreasure(ListTreasure* allTreasures, int level , int x, int y, Player *player){
	ListTreasure *newTreasure;

    /* Create  a new element */
    newTreasure = malloc(sizeof(ListTreasure));
    newTreasure->coords = newPoint(x, y);
    newTreasure->treasure = generateTreasure(level, player->stat.current.lvl) ;

    newTreasure->nextTreasure = allTreasures;/*Adds at the top of the list*/

    return newTreasure;
}

ListTreasure* locatesAllTreasures(Stage stage, int level, Player *player){
    
    int i,j;
    ListTreasure* allTreasures;
    
    allTreasures = NULL;

    for(i = 0; i < LEVEL_HEIGHT; i++) {
        for(j = 0; j < LEVEL_WIDTH; j++) {
            if(stage.cells[i][j].type == ENEMY){
                allTreasures = addTreasure(allTreasures, level, j, i, player);
            }
        }
    }
    return allTreasures;
}
