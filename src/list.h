/* Auteurs : Nicolas Mazeyrac, Lysandre Macke
 * Creation : 06/01/2022
 * Modification : 06/01/2022*/

/*Bibliothèque générale*/

/*Bibliothèque interne*/
#include "level.h"
#include "player.h"
#include "treasure.h"
#include "enemy.h"

#ifndef __LIST__
#define __LIST__

    typedef struct NextCoord{
        Point coords;
        struct NextCoord *nextCoord;
    }ListCoord;

    typedef struct Node{
        Stage stage;
        struct Node *nextLevel;
        struct Node *previousLevel;
    }NodeStage;

    typedef struct{
        size_t length;
        NodeStage *firstLevel;
        NodeStage *lastLevel;
    }ListStage;

    ListStage* newListStage(Stage stage);

    Stage searchStage(unsigned int level);

    ListStage* addStage(ListStage *dungeon, Stage stage);

    ListCoord* addCoord(ListCoord *listCoords,int level , int x, int y);

    ListCoord* removeCoord(ListCoord *listCoords, Point coord);

    ListCoord* generateAllCoords(Stage stage, int level);

    void printAllCoords(ListCoord *listCoords);

#endif