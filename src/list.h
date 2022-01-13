/* Auteurs : Nicolas Mazeyrac, Lysandre Macke
 * Creation : 06/01/2022
 * Modification : 13/01/2022*/

/*Bibliothèque générale*/

/*Bibliothèque interne*/
#include "level.h"
#include "potions.h"

#ifndef __LIST__
#define __LIST__

    typedef struct NextCoord{
        Point coords;                /* Current coord */
        struct NextCoord *nextCoord; /* Pointer to the next coord */
    }ListCoord;

     /* DoubleLinked list of Stages */
    typedef struct level{
        Stage stage;                 /* Level data (Stage object, cf level.h) */
        struct level *nextLevel;     /* Pointer on the next level */
        struct level *previousLevel; /* Pointer on the previous level */
    }Levels, *StageList;

    /* Allocates the needed memory for a stage objet and returns an object
     * ready to be used as a StageList. */
    StageList allocStage(Stage stage);

    /* Adds the given stage at the end of specified dungeon. */
    void addStageTail(StageList *dungeon, Stage stage);

    /* Adds the given stage at the start of specified dungeon. */
    void addStageHead(StageList *dungeon, Stage stage);
    
    /* Changes the StageList so that he points to be the correct stage based on its level
    * if he exists */
    void searchStage(StageList *dungeon, unsigned int level);

    /* Count the number of stages in the dungeon */
    int countNumberLevels(StageList dungeon);

    /* Add a point to the list */
    ListCoord* addCoord(ListCoord *listCoords, int x, int y);

    /* Remove a point to the list  */
    ListCoord* removeCoord(ListCoord *listCoords, Point coord);

    /* Generate the a list containing all of the coordonnates of the enemy in a stage  */
    ListCoord* generateAllEnemyCoords(Stage stage);

    /* Shell display of a ListCoord (to use for debug) */
    int printAllCoords(ListCoord *listCoords);

    /* Shell display of a StageList (to use for debug) */
    int printStageList(StageList dungeon);
#endif