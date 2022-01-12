/* Auteurs : Nicolas Mazeyrac, Lysandre Macke
 * Creation : 06/01/2022
 * Modification : 06/01/2022*/

/*Bibliothèque générale*/

/*Bibliothèque interne*/
#include "level.h"
#include "potions.h"

#ifndef __LIST__
#define __LIST__

    typedef struct NextCoord{
        Point coords;
        struct NextCoord *nextCoord;
    }ListCoord;

     /* DoubleLinked list of Stages */
    typedef struct level{
        Stage stage;                 /* Level data (Stage object, cf level.h) */
        struct level *nextLevel;     /* Pointer on the next level */
        struct level *previousLevel; /* Pointer on the previous level */
    }Levels, *StageList;

    StageList allocStage(Stage stage);

    void addStage(StageList *dungeon, Stage stage);

    void addStageHead(StageList *dungeon, Stage stage);
    
    void searchStage(StageList *dungeon, unsigned int level);

    int countNumberLevels(StageList dungeon);

    ListCoord* addCoord(ListCoord *listCoords,int level , int x, int y);

    ListCoord* removeCoord(ListCoord *listCoords, Point coord);

    ListCoord* generateAllCoords(Stage stage, int level);

    void printAllCoords(ListCoord *listCoords);

    void quickPrintStageList(StageList dungeon);
#endif