#include "list.h"

StageList allocStage(Stage stage) {
    StageList tmp;

    tmp = (Levels *)malloc(sizeof(Levels));

    /* initializing the level informations */
    if(tmp != NULL) {
        tmp->stage         = stage;
        tmp->nextLevel     = NULL;
        tmp->previousLevel = NULL;
    }
    return tmp;
}

void addStageTail(StageList *dungeon, Stage stage){
    StageList newStage = NULL;
    
    /* Creating the new element in the list */
    newStage = allocStage(stage);

    /* If we're adding the first element */
    if(*dungeon == NULL) {
        newStage->stage.level = 1;
        *dungeon = newStage;
    }

    /* Else, linking the stage at the end of the list */
    else {
        newStage->previousLevel = *dungeon;
        (*dungeon)->nextLevel   = newStage;
        *dungeon                = (*dungeon)->nextLevel; /* updating the position */ 
        (*dungeon)->stage.level = (*dungeon)->previousLevel->stage.level + 1; /* updating the level index*/
    }
}

void addStageHead(StageList *dungeon, Stage stage){

    StageList newStage = NULL;
    
    /* Creating the new element in the list */
    newStage = allocStage(stage);

    /* If we're adding the first element */
    if(*dungeon == NULL) {
        newStage->stage.level = 1;
        *dungeon = newStage;
    }

    /* Else, linking the stage at the start of the list */
    else {
        newStage->nextLevel         = *dungeon;
        (*dungeon)->previousLevel   = newStage;
        *dungeon                    = (*dungeon)->previousLevel; /* updating the position */ 
        (*dungeon)->stage.level     = (*dungeon)->nextLevel->stage.level - 1; /* updating the level index*/
    }
}

void searchStage(StageList *dungeon, unsigned int level){

    StageList* tmpStage;

    tmpStage = dungeon;
    
    if(dungeon != NULL){
        if((*dungeon)->stage.level != level){
            searchStage(&((*tmpStage)->previousLevel), level);/* check the next level */
        }
        else{/* The current level is the right one */
            (*dungeon)->nextLevel   = (*tmpStage)->nextLevel;
            (*dungeon)->previousLevel   = (*tmpStage)->previousLevel;
            (*dungeon)->stage            =(*tmpStage)->stage;
        }
    }
}

int countNumberLevels(StageList dungeon){

    int numberLevels;

    StageList currentStage = dungeon;
    numberLevels = 0;

    /* Go to the tail of the structure */
    while(currentStage->nextLevel != NULL){
        currentStage = currentStage->nextLevel;
    }

    /* Count all Elements */
    while(currentStage != NULL){
        numberLevels += 1;
        currentStage = currentStage->previousLevel;
    }

    return numberLevels;
}

void freeStageList(StageList dungeon){
    StageList tmp;
    StageList delete;

    tmp = dungeon;
    /* Go to the head of the structure */
    while(tmp->previousLevel != NULL){
        tmp = tmp->previousLevel;
    }

    while(NULL != tmp){
        delete = tmp;
        tmp = tmp->nextLevel;
        /*free(&(delete->stage));*/
        free(delete);
    }
    dungeon = NULL;
}

ListCoord* addCoord(ListCoord* listCoords, int x, int y){
    
    ListCoord *newCoord;

    /* Create  a new element */
    newCoord = malloc(sizeof(ListCoord));

    /* If the allocation didn't fail */
    if( NULL != newCoord ){
        newCoord->coords = (Point){x,y};
        newCoord->nextCoord = listCoords;/*Adds at the top of the list because the order doesn't really matter*/
    }

    return newCoord;
}

ListCoord* removeCoord(ListCoord* listCoords, Point coord){
    
    ListCoord *newCoord;
    newCoord = listCoords;

    if(newCoord != NULL){
        if(isTheSame(newCoord->coords, coord)){
            newCoord = listCoords->nextCoord;
            free(listCoords);
            return newCoord;/*return the new list*/
        }
        else{
            listCoords->nextCoord = removeCoord(listCoords->nextCoord, coord);/* change the next part of the list*/
        }
    }
    return NULL;
}

ListCoord* generateAllEnemyCoords(Stage stage){
    
    int i,j;
    ListCoord* listCoords;
    
    listCoords = NULL;

    /* Search the whole level */
    for(i = 0; i < LEVEL_HEIGHT; i++) {
        for(j = 0; j < LEVEL_WIDTH; j++) {
            if(stage.cells[i][j].type == ENEMY){/* if there's an enemy collect it */
                listCoords = addCoord(listCoords, j, i);
            }
        }
    }

    return listCoords;
}

int printAllCoords(ListCoord *listCoords){
    
    ListCoord *tmp;
    
    tmp = listCoords;

    printf("***ListCoords***\n");
    
    while(tmp != NULL){
        printf("coord : \n x = %d \n y = %d \n\n", tmp->coords.x, tmp->coords.y);
        tmp = tmp->nextCoord;
    }

    printf("***END***\n");

    return 1;
}

int printStageList(StageList dungeon){

   StageList currentStage = dungeon; /* Starting with the last element in the list */

   printf("***Dungeon***\n");
   printf("Printing stages from last inserted to first.\n");
   
   while(currentStage != NULL){
     printf("Level %d\n",currentStage->stage.level);
     currentStage = currentStage->previousLevel;
   }

   return 1;
}