#include "gameControl.h"

#undef main /*( 'o_o)*/

int main(int argc, char * argv[]) {
	printf(">>>Program starts.\n");
	/* random seed */
	srand(time(NULL));
	Stage stage;
	Player player;
	ListStage *dungeon;
	char playerName[] = "Ruby"; /* random init for testing */

	/*printf("***TEST STARTS HERE***\n\n");
	printf(">>>Creating array of cells for testing.\n");
	
	Cell cellList[10];
	int i;
	for(i = 0; i < 10; i++) {
		printf(">>>Initializing cell no %d.\n", i);
		cellList[i] = initCell(i + 1, (Point){2, TEST_LEVEL_WIDTH-2}, ENEMY, CONTAINS_ENEMY, 1);
		printf("Cell %d initialized.\n", i);
	}
	printf(">>>Array initialized.\n");
	printf(">>>Checking values...\n");
	for(i = 0; i < 10; i++) {
		printf("Coords : %d %d\n", cellList[i].coords.x, cellList[i].coords.y);
		printf("Type   : ");
		if(cellList[i].type == ENEMY) {
			printf("ENEMY\n");
	    	quickPrintEnemy(cellList[i].enemy);
		}
		else {
			printf("NOT ENEMY\n");
		}
	}

    printf("***END OF TEST***\n\n");*/

	printf(">>>Initializing player stats.\n");
	initializeStandard(&player, playerName);
	printf("Player stats initialized.\n");
	/*player.coords = (Point){2, 2};*/
	quickPrintPlayer(player);

	printf(">>>Initializing stage.\n");
	initStage(&stage, &player, 1);
	printf("Stage initialized.\n");
	/*stage = generateStageTest();*/
	quickPrintStage(stage);

	/* initializing dungeon */
	dungeon = newListStage(stage);

	printf(">>>Creating game window.\n");
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

				enum PLAYER_ACTION action = NO_ACTION;
				int actionDone = 0;
				play = 1;
				while(play) {
					/* game */

					/* display */

					MLV_clear_window(MLV_COLOR_WHITE); /*pour les tests*/
					displayStage(stage, player, WITH_SPRITES);
					displayHUD(player);
					displayAtkButtons();

					/* events */
					action = getPlayerAction();
					while(action == NO_ACTION) {
						action = getPlayerAction();
						MLV_wait_milliseconds( 50 );
					}
					actionDone = doAction(action, &stage, &player, dungeon);

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