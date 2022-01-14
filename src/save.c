#include "save.h"

int saveGame(Player *player, StageList* dungeon){

    FILE *file;
    StageList tmpDungeon;
    int numberLevels;
    int currentLevel;

    assert(NULL != player);
    assert(NULL != dungeon);

    file=fopen(MEMORY_FILE_NAME,"wb");
    if(file == NULL){
        return 0;
    }

    fwrite(player,sizeof(Player),1,file); /* Save the information of the player */

    tmpDungeon = (*dungeon);
    currentLevel = (*dungeon)->stage.level;
    numberLevels = countNumberLevels((*dungeon));

    /* Go to the tail of the dungeon */
    while(tmpDungeon->nextLevel != NULL){
        tmpDungeon = tmpDungeon->nextLevel;
    }

    fwrite(&currentLevel,sizeof(int),1,file);/* Save the information of the current level */
    fwrite(&numberLevels,sizeof(int),1,file);/* Save the information of the number of level in total */

    /* Save all of the dungeon */
    while(tmpDungeon != NULL){
        fwrite(&(tmpDungeon->stage),sizeof(Stage),1,file);
        tmpDungeon = tmpDungeon->previousLevel;
    }

    fclose(file);
    return 1;
}


int loadGame(Player *player, StageList* dungeon){

    FILE *file;
    int numberLevels;
    int currentLevel;
    int i;
    Stage tmpStage;

    file=fopen(MEMORY_FILE_NAME,"rb");
    
    if(file == NULL){
        return 0;
    }

    /* Recuperating player information */
    fread(player,sizeof(Player),1,file);


    /* Recuperating dungeon information */
    fread(&currentLevel,sizeof(int),1,file);
    fread(&numberLevels,sizeof(int),1,file);
    for(i=0;i < numberLevels;i++){
        fread(&tmpStage,sizeof(Stage),1,file);
        if(i==0){
            (*dungeon) = allocStage(tmpStage);
        }
        else{
            addStageHead(dungeon, tmpStage);
        }
    }

    /* Move the dungeon to the current level */
    searchStage(dungeon, currentLevel);

    fclose(file);
    return 1;
}


int newGame(Player *player, StageList* dungeon){
    
    FILE *file;
    Stage stage;

    file=fopen(MEMORY_FILE_NAME,"wb");
    if(file == NULL){
        return 0;
    }
    
    /*Create a game from Level 1*/
    initializeStandard(player);
    initStage(&stage, player, 1);
    (*dungeon) = allocStage(stage);

    /* Save the dungeon in a new saveFile*/
    saveGame(player,dungeon);
    return 1;
}