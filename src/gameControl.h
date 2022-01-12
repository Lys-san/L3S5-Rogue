/* Autors : Nicolas Mazeyrac, Lysandre Macke
 * Creation : 14/12/2021
 * Last modified : 14/12/2021*/

#include "action.h"
#include "interface.h"

#ifndef __GAME_CONTROL__
#define __GAME_CONTROL__
    enum PLAYER_ACTION { NO_ACTION, UP, LEFT, DOWN, RIGHT, PHYSICAL, MAGICAL, INVENTORY, QUIT, OPTN };

    /* Returns a player action by checking the events. */
    enum PLAYER_ACTION getPlayerAction();

    /* Performs the specified action. Returns 1 if the action was performed
     * correctly, 0 otherwise, and -1 if QUIT. */
    int doAction(enum PLAYER_ACTION act, Player *player, StageList *dungeon);
    
#endif