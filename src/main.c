#include "gameControl.h"

#undef main /*( 'o_o)*/

int main(int argc, char * argv[]) {
	/* random seed */
	srand(time(NULL));
	Stage stage;
	Player player;
	char playerName[] = "Ruby"; /* random init for testing */

	initializeStandard(&player, playerName);
	/*quickPrintPlayer(player);*/

	initStage(&stage, &player, 1);
	quickPrintStage(stage);

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
				playButtonSound_2();
				fadein = 0; 

				enum PLAYER_ACTION action = NO_ACTION;
				int actionDone = 0;
				play = 1;
				while(play) {
					/* game */

					/* display */
					MLV_clear_window(MLV_COLOR_DARK_GRAY); /*pour les tests*/
					displayStage(stage, player, WITH_SPRITES);
					displayHUD(player);

					/* events */
					action = getPlayerAction();
					while(action == NO_ACTION) {
						action = getPlayerAction();
						MLV_wait_milliseconds( 50 );
					}
					actionDone = doAction(action, &stage, &player);

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
	return 0;
}