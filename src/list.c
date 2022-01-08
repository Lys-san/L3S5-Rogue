#include "list.h"

ListStage* newListStage(void){
    
    ListStage* newList;

    newList = malloc(sizeof *newList);
    if(NULL != newList){
        newList->length = 0;
        newList->firstLevel = NULL;
        newList->lastLevel = NULL;
    }
    return newList;
}

ListStage* searchStage(ListStage* dungeon, unsigned int level){
    
    ListStage* res;
    NodeStage* tmp;
    int found;

    res = NULL;
    tmp = dungeon->firstLevel;
    found = 0;
    printf("Searching for level %d \n", level);
    while(tmp != NULL && !found){
        printf("%d\n", tmp->stage.level);
        if(tmp->stage.level == level){
            res = newListStage();
            res = addStage(res, tmp->stage);
            found = 1;
        }
        else{
            tmp = tmp->nextLevel;
        }
    }
    return res;
}

ListStage* addStage(ListStage *dungeon, Stage stage){
    
    NodeStage *newStage;
    
    /* Create  a new element */
    newStage = malloc(sizeof *newStage);
    if(NULL != newStage){
        newStage->stage = stage;
        newStage->nextLevel = NULL;
        if(NULL == dungeon->lastLevel){
            newStage->previousLevel = NULL;
            dungeon->firstLevel = newStage;
            dungeon->lastLevel = newStage;
        }
        else{
            dungeon->lastLevel->nextLevel = newStage;
            newStage->previousLevel = dungeon->lastLevel;
            dungeon->lastLevel = newStage;
        }
        dungeon->length += 1;
    }
    return dungeon;
}

ListCoord* addCoord(ListCoord* listCoords,int level , int x, int y){
    
    ListCoord *newCoord;

    /* Create  a new element */
    newCoord = malloc(sizeof(ListCoord));
    newCoord->coords = newPoint(x, y);

    newCoord->nextCoord = listCoords;/*Adds at the top of the list because the order doesn't really matter*/

    return newCoord;
}

ListCoord* removeCoord(ListCoord* listCoords, Point coord){
    
    ListCoord *newCoord;
    newCoord = listCoords;

    if(newCoord != NULL){
        if(isTheSame(newCoord->coords, coord)){
            newCoord = listCoords->nextCoord;
            free(listCoords);
            return newCoord;
        }
        else{
            listCoords->nextCoord = removeCoord(listCoords->nextCoord, coord);
        }
    }
    return NULL;
}

ListCoord* generateAllCoords(Stage stage, int level){
    
    int i,j;
    ListCoord* listCoords;
    
    listCoords = NULL;

    for(i = 0; i < LEVEL_HEIGHT; i++) {
        for(j = 0; j < LEVEL_WIDTH; j++) {
            if(stage.cells[i][j].type == ENEMY){
                listCoords = addCoord(listCoords, level, j, i);
            }
        }
    }
    return listCoords;
}

void printAllCoords(ListCoord *listCoords){
    ListCoord *tmp;
    tmp = listCoords;
    while(tmp != NULL){
        printf("coord : \n x = %d \n y = %d \n", tmp->coords.x, tmp->coords.y);
        tmp = tmp->nextCoord;
    }
}

turnEffect* addEffect(turnEffect* effects, Effect effect){
    
    turnEffect *newEffect;

    /* Create  a new element */
    newEffect = malloc(sizeof(turnEffect));
    newEffect->effect = effect;

    newEffect->NextEffect = effects;/*Adds at the top of the list because the order doesn't really matter*/

    return newEffect;
}

turnEffect* gainAllEffects(turnEffect* effects, Player *player){
    
    turnEffect *tmp;
    tmp = effects;

    if(tmp != NULL){
        if(tmp->effect.turnLeft == 0){
            if(NULL != tmp->effect.malus){
                tmp->effect.malus(player);
            }
            tmp = effects->NextEffect;
            free(effects);
            tmp = gainAllEffects(tmp, player);
            return tmp;
        }
        else{
            if(NULL != tmp->effect.bonus && tmp->effect.turnLeft%tmp->effect.turnActivation == 0){
                effects->effect.bonus(player);
            }
            effects->effect.turnLeft -= 1;
            effects->NextEffect = gainAllEffects(effects->NextEffect, player);
            return effects;
        }
    }
    return NULL;
}