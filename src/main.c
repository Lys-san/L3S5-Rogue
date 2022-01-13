#include "gameControl.h"

#undef main /*( 'o_o)*/

int main(int argc, char * argv[]) {
    printf(">>>Program starts.\n");
    /* random seed */
    srand(time(NULL));

    Stage stage;
    Player player;
    StageList dungeon;
    Loot loot;

    printf(">>>Initializing player stats.\n");
    initializeStandard(&player);
    printf("Player stats initialized.\n");
    /*player.coords = (Point){2, 2};*/
    quickPrintPlayer(player);
    loot = generateLoot(0, 0, HEAL);
    pickUp(&player, loot);

    printf(">>>Initializing stage.\n");
    printf("Stage initialized.\n");
    generateStageTest(&stage, &player, 1);
    quickPrintStage(stage);

    /* initializing dungeon */
    dungeon = allocStage(stage);

    printf(">>>Creating game window.\n");
    createGameWindow();

    int quit = 0;
    int play = 1;
    int fadein = 1;

    if( MLV_init_audio() ) {
        fprintf(stderr, "L'infrastructure de la libMLV ne s'est pas correctement initialisée.");
        exit(1);
    }

    /* test start here (remove after) */
    int i_test;
    for(i_test = 0; i_test < 5; i_test++) {
        player.inventory[i_test] = generateLoot(1, 1, EQUIPMENT);
    }
    for(i_test = 4; i_test < 7; i_test++) {
        player.inventory[i_test] = generateLoot(1, 1, CONSUMMABLE);
    }
    for(i_test = 6; i_test < MAX_INVENTORY; i_test++) {
        player.inventory[i_test] = generateLoot(1, 1, NO_ITEM);
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
                    displayStage(dungeon->stage, player, WITH_SPRITES);
                    displayHUD(player);
                    displayAtkButtons();

                    /* events */
                    action = getPlayerAction();
                    while(action == NO_ACTION) {
                        action = getPlayerAction();
                        MLV_wait_milliseconds( 50 );
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