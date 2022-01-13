#include "gameControl.h"
#include "turn.h"

#undef main /*( 'o_o)*/

int main(int argc, char * argv[]) {
    printf(">>>Program starts.\n");
    /* random seed */
    srand(time(NULL));

    Stage stage;
    Player player;
    StageList dungeon;
    Loot loot;
    initializeStandard(&player);
    generateStageTest(&stage, &player, 1);

    /* initializing dungeon */
    dungeon = allocStage(stage);
    createGameWindow();
    loot = generateLoot(1,1,CONSUMMABLE);
    addToInventory(&player, loot);
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

                enum PLAYER_ACTION action = NO_ACTION;
                int actionDone = 0;
                play = 1;
                while(play) {
                    /* game */

                    /* display */
                    MLV_clear_window(MLV_COLOR_WHITE); /*pour les tests*/
                    displayStage(dungeon->stage, player, BASIC);
                    displayHUD(player);
                    displayAtkButtons();

                    /* events */
                    action = getPlayerAction();
                    while(action == NO_ACTION) {
                        action = getPlayerAction();
                    }
                    actionDone = doAction(action, &player, &dungeon);

                    /* exit game */
                    if(actionDone == -1) {
                        if(yesNoPopup("Exit game ?")) {
                            play = 0;
                            quit = 1;
                            break;
                        }
                    }
                    if(turnEnemyOnScreen(&(dungeon->stage), &player)){
                        printf("Game Over \n");
                        play = 0;
                        quit = 1;
                        break;
                    }
                }
                break;
            case PROFILE : 
                fadein = 0;
                playButtonSound_2();
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
    printf("Program ends.\n");
    return 0;
}