#include "interface.h"

#undef main /*( 'o_o)*/

int main(int argc, char * argv[]) {
	Player player;
	char playerName[] = "Ruby"; /* random init for testing */

	initializeStandard(&player, playerName);
	quickPrintPlayer(player);

	createGameWindow();

	int quit = 0;
	int play = 1;
	int fadein = 1;

	if( MLV_init_audio() ) {
		fprintf(stderr, "L'infrastructure de la libMLV ne s'est pas correctement initialisée.");
		exit(1);
	}


	/* test floodfill */
	/*unsigned int windowWidth, windowHeight;
	MLV_get_window_size(&windowWidth, &windowHeight);
	MLV_draw_filled_rectangle(0, 0, windowWidth, windowHeight, MLV_COLOR_WHITE);
	MLV_draw_circle(50, 50, 50, MLV_COLOR_BLACK);

	MLV_actualise_window();
	boundaryFill(50, 50, MLV_COLOR_RED, MLV_COLOR_BLACK, windowWidth, windowHeight);
	MLV_actualise_window();
	int xMouse, yMouse;
	MLV_wait_mouse(&xMouse, &yMouse);*/
	/* fin du test */


	snowdrops( 500 );
	
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

					displayHUD(player);
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