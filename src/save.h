/* Auteurs : Nicolas Mazeyrac, Lysandre Macke
 * Creation : 26/11/2021
 * Modification : 30/11/2021*/

/*Bibliothèque générale*/
#include <stdio.h>
#include <stdlib.h>

/*Bibliothèque interne*/

#ifndef __SAVE__
#define __SAVE__

    /*Define*/

    #define MEMORY_FILE_NAME "game.sav" /*temporaire : je cherche encore sous quelle forme sont écrits les fichiers .sav*/

    /*Struct*/


    /*Functions*/

    /*returns 1 if a given file is found and 0 otherwise.*/
    int memoryFileIsFound();

    /*creates a new memory file.
      If a memory file already exists this one will be replaced with the new one.*/
    void newGame();

    /*loads the game according the data found in the given memory file.*/
    void loadGame(FILE *memoryFile); /*RAJOUTER DES ARGUMENTS PAR LA SUITE (bawi sinon cette fonction sert à rien)*/

    /*saves the current progression in the given memory file.*/
    void saveGame(FILE *memoryFile);

    /*deletes a given memory file */
    void deleteMemoryFile(FILE *memoryFile);

#endif
