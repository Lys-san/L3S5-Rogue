/* Auteurs : Nicolas Mazeyrac, Lysandre Macke
 * Creation : 26/11/2021
 * Modification : 13/01/2022*/

/*Bibliothèque générale*/

/*Bibliothèque interne*/
#include"list.h"

#ifndef __SAVE__
#define __SAVE__

    /*Define*/

    #define MEMORY_FILE_NAME "game.bin" /* Name of the save file */

    /*Struct*/


    /*Functions*/

    /*creates a new memory file.
    *  If a memory file already exists this one will be replaced with the new one.*/
    int newGame(Player *player, StageList* dungeon);

    /*loads the game according the data found in the given memory file.*/
    int loadGame(Player *player, StageList* dungeon);

    /*saves the current progression in the given memory file.*/
    int saveGame(Player *player, StageList* dungeon);

#endif
