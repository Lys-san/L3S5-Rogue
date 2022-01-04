#include "interface.h"

#undef main /*( 'o_o)*/

int main(int argc, char * argv[]) {
	/* random seed */
	srand(time(NULL));
	Stage stage;
	Player player;
	char playerName[] = "Ruby"; /* random init for testing */

	initializeStandard(&player, playerName);
	/*quickPrintPlayer(player);*/

	initStage(&stage, &player);


	createGameWindow();

	int quit = 0;
	int play = 1;
	int fadein = 1;

	if( MLV_init_audio() ) {
		fprintf(stderr, "L'infrastructure de la libMLV ne s'est pas correctement initialisée.");
		exit(1);
	}

	/* snowdrops( 500 ); */
	
	int xMouse, yMouse;
	while( !quit ) {
		switch(mainScreen(1, fadein)) {
			case PLAY : 
				fadein = 0; 
				playButtonSound_2();
				play = 1;
				while(play) {
					/* game */

					MLV_clear_window(MLV_COLOR_WHITE); /*pour les tests*/
					displayStage(stage, player, BASIC);
					/*displayHUD(player);*/
					MLV_wait_mouse(&xMouse, &yMouse);
					play = 0;
					quit = 1;
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