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

    typedef struct NextEffect{ 
        Effect effect;
        struct NextEffect *NextEffect;
    }turnEffect;

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

    ListStage* newListStage(void);

    ListStage* searchStage(ListStage* dungeon, unsigned int level);

    ListStage* addStage(ListStage *dungeon, Stage stage);

    ListCoord* addCoord(ListCoord *listCoords,int level , int x, int y);

    ListCoord* removeCoord(ListCoord *listCoords, Point coord);

    ListCoord* generateAllCoords(Stage stage, int level);

    turnEffect* addEffect(turnEffect* effects, Effect effect);

    turnEffect* gainAllEffects(turnEffect* effects, Player *player);

    void printAllCoords(ListCoord *listCoords);

#endif