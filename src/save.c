#include "save.h"

int saveGame(Player *player, StageList* dungeon){

    FILE *file;
    StageList tmpDungeon;
    int numberLevels;
    int currentLevel;

    file=fopen(MEMORY_FILE_NAME,"wb");
    if(file == NULL){
        return 0;
    }
    printf(">>>Creating a SaveFile.\n");

    fwrite(player,sizeof(Player),1,file);

    tmpDungeon = (*dungeon);
    currentLevel = (*dungeon)->stage.level;
    numberLevels = countNumberLevels((*dungeon));

    while(tmpDungeon->nextLevel != NULL){
        tmpDungeon = tmpDungeon->nextLevel; /*Tails of the structure*/
    }

    fwrite(&currentLevel,sizeof(int),1,file);
    fwrite(&numberLevels,sizeof(int),1,file);

    while(tmpDungeon != NULL){
        fwrite(&(tmpDungeon->stage),sizeof(Stage),1,file);
        tmpDungeon = tmpDungeon->previousLevel;
    }

    fclose(file);
    return 1;
}


StageList loadGame(Player *player){

    FILE *file;
    int numberLevels;
    int currentLevel;
    int i;
    StageList dungeon;
    Stage tmpStage;

    file=fopen(MEMORY_FILE_NAME,"rb");
    
    if(file == NULL){
        return NULL;
    }

    printf(">>>Recuperating a SaveFile.\n");
    fread(player,sizeof(Player),1,file);

    fread(&currentLevel,sizeof(int),1,file);
    fread(&numberLevels,sizeof(int),1,file);
    for(i=0;i < numberLevels;i++){
        fread(&tmpStage,sizeof(Stage),1,file);
        printf("recuperating level %d \n", tmpStage.level);
        if(i==0){
            dungeon = allocStage(tmpStage);
        }
        else{
            addStageHead(&dungeon, tmpStage);
        }
    }
    while(dungeon != NULL && dungeon->stage.level != currentLevel){
        printf("%d != %d", dungeon->stage.level, currentLevel);
        dungeon = dungeon->nextLevel;
    }
    fclose(file);
    return dungeon;
}


int newGame(Player *player, StageList* dungeon){
    
    FILE *file;

    file=fopen(MEMORY_FILE_NAME,"wb");
    if(file == NULL){
        return 0;
    }
    saveGame(player,dungeon);
    return 1;
}