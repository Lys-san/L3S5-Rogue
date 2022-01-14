#include "turn.h"

#undef main /*( 'o_o)*/

int main(int argc, char * argv[]) {
    printf(">>>Program starts.\n");
    
    /* random seed */
    srand(time(NULL));

    Player player;
    StageList dungeon;

    createGameWindow();

    int quit = 0;
    int play = 1;
    int fadein = 1;

    if( MLV_init_audio() ) {
        fprintf(stderr, "L'infrastructure de la libMLV ne s'est pas correctement initialisée.");
        exit(1);
    }

    /*snowdrops( 500 );*/
    
    while( !quit ) {
        switch(mainScreen(1, fadein)) {
            case PLAY : 
                printf(">>>Game start.\n");
                playButtonSound_2();
                fadein = 0; 

                play = 1;
                if(!newGame(&player, &dungeon)){
                    fprintf(stderr, "the saveFile wasn't created \n");
                    return 1;
                }
                addToInventory(&player, generateLoot(0,0,CONSUMMABLE));

                while(play) {
                    playerTurn(&player, &dungeon, &play, &quit);
                }
                break;
            case PROFILE : 
                playButtonSound_2();
                fadein = 0;
                play = 1;
                
                if(!loadGame(&player, &dungeon)){
                    if(!newGame(&player, &dungeon)){
                        fprintf(stderr, "the saveFile wasn't created \n");
                        return 1;
                    }
                }

                while(play) {
                    playerTurn(&player, &dungeon, &play, &quit);
                }
                break;
            case SETTINGS :
                fadein = 0;
                playButtonSound_2();
                break;
            case EXIT : 
                fadein = 0;
                playButtonSound_2();
                if(yesNoPopup("Exit game ?")) {
                    quit = 1;
                    break;
                }
            default :;
        }

    }
    exitGame();
    freeStageList(dungeon);
    printf("Program ends.\n");
    return 0;
}