#include "gameControl.h"

enum PLAYER_ACTION getPlayerAction() {
    unsigned int windowWidth, windowHeight;
    MLV_get_window_size(&windowWidth, &windowHeight);

    MLV_Keyboard_button sym   = MLV_KEYBOARD_NONE;
    MLV_Keyboard_modifier mod = MLV_KEYBOARD_KMOD_NONE;
    MLV_Input_box *input_box  = NULL;
    char* texte               = NULL;
    MLV_Button_state state;
    int x, y;

    int bttnSize   = windowWidth/11;
    int margin     = bttnSize/4;

    Point physicalBttnCoords, magicalBttnCoords;
    physicalBttnCoords.x = windowWidth - (margin + bttnSize);
    physicalBttnCoords.y = windowHeight - (margin + bttnSize);
    magicalBttnCoords.x  = windowWidth - 2*(margin + bttnSize);
    magicalBttnCoords.y  = physicalBttnCoords.y;

    /* getting the event */
    MLV_Event ev = MLV_get_event( 
            &sym, &mod, NULL,
            &texte, &input_box,
            &x, &y, NULL,
            &state
    );

    /* checking the event */
    switch( ev ) {
    	/* keyboard event */
    	case MLV_KEY :
    		if(state == MLV_PRESSED) {
    			switch( sym ) {
    				case MLV_KEYBOARD_ESCAPE :
    					return QUIT;
    				case MLV_KEYBOARD_z :
    					return UP;
    				case MLV_KEYBOARD_UP :
    					return UP;
    				case MLV_KEYBOARD_q :
    					return LEFT;
    				case MLV_KEYBOARD_LEFT :
    					return LEFT;
    				case MLV_KEYBOARD_s :
    					return DOWN;
    				case MLV_KEYBOARD_DOWN :
    					return DOWN;
    				case MLV_KEYBOARD_d :
    					return RIGHT;
    				case MLV_KEYBOARD_RIGHT :
    					return RIGHT;
    				case MLV_KEYBOARD_i :
    					return INVENTORY;
    				case MLV_KEYBOARD_o :
    					return OPTN;
    				default :
    					break;
    			}
    		}
    	/* mouse event */
    	case MLV_MOUSE_BUTTON :
    		if(state == MLV_PRESSED) {
                if(y > physicalBttnCoords.y && y < physicalBttnCoords.y + bttnSize) {
                    /* magical attack button */
                    if(x > magicalBttnCoords.x && x < magicalBttnCoords.x + bttnSize)
                        return MAGICAL;
                    /* physical attack button */
                    if(x > physicalBttnCoords.x && x < physicalBttnCoords.x + bttnSize)
                        return PHYSICAL;
                }
    		}
            break;
    	/* no event */
    	case MLV_NONE :
    		return NO_ACTION;

    	default :
    		return NO_ACTION;
    }
    return NO_ACTION;
}
int doAction(enum PLAYER_ACTION act, Player *player, StageList *dungeon) {
	switch( act ) {
		case UP :
			playerMove(player, N, dungeon);
			return 1;
		case DOWN :
			return playerMove(player, S, dungeon);
		case LEFT :
			playerMove(player, W, dungeon);
			return 1;
		case RIGHT :
			playerMove(player, E, dungeon);
			return 1;
		case PHYSICAL :
            player->status = PHYSICAL_ATTCK;
            printf("PHYSICAL ATTACK BUTTON CLICKED\n");
			return 1;
		case MAGICAL :
            player->status = MAGICAL_ATTCK;
            printf("MAGICAL ATTACK BUTTON CLICKED\n");
			return 1;
		case INVENTORY :
			quickPrintLoot(inventory(player->inventory, BASIC));
			return 1;
		case OPTN :
			/* function for the options */
			return 1;
		case QUIT :
			return -1;
		default :
			return 0;
	}
}