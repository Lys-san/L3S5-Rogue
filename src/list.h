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

    typedef struct NextEnemy{
        Enemy enemy;
        Point coords;
        struct NextEnemy* nextEnemy;
    }ListEnemy;

    typedef struct NextTreasure{
        Treasure treasure;
        Point coords;
        struct NextTreasure* nextTreasure;
    }ListTreasure;

    ListTreasure* addTreasure(ListTreasure* allTreasures, int level , int x, int y, Player *player);

    ListTreasure* locatesAllTreasures(Stage stage, int level, Player *player);

    ListEnemy* addEnemy(ListEnemy* allEnemies,int level , int x, int y, Point  stairUpCoords);

    ListEnemy* locatesAllEnemies(Stage stage, int level);

    ListEnemy* searchEnemy(ListEnemy* allEnemies, Point coordEnemy);

    ListEnemy* removeEnemy(ListEnemy* allEnemies, Point coordEnemy);

    void printAllEnemies(ListEnemy *allEnemies);

    void printAllTreasures(ListTreasure *allTresures);
#endif