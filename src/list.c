#include "list.h"

ListStage* newListStage(Stage stage){
    
    ListStage* newList;

    newList = malloc(sizeof *newList);
    if(NULL != newList){
        newList->length = 0;
        newList->firstLevel = NULL;
        newList->lastLevel = NULL;
    }
    return newList;
}

Stage searchStage(ListStage* dungeon, unsigned int level){
    NodeStage* tmp;
    tmp = dungeon->lastLevel;
    while(tmp != NULL){
        if()
    }
    return NULL;
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