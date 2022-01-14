/* Autors : Nicolas Mazeyrac, Lysandre Macke
 * Creation : 27/11/2021
 * Last modified : 13/01/2021*/

/* General libraries */

/* Internal libraries */
#include "enemy.h"

#ifndef __LEVEL__
#define __LEVEL__

    /* Define */

    #define LEVEL_WIDTH  63
    #define LEVEL_HEIGHT 43

    #define SCREEN_WIDTH  13
    #define SCREEN_HEIGHT  9

    #define TEST_LEVEL_WIDTH  9
    #define TEST_LEVEL_HEIGHT 5

    #define ABS(a) ((a) > 0 ? (a) : -(a)) /* absolute value*/


    /* Struct */
     /* Direction (West, North, East, South) */
    typedef enum {
        W,            /* DIRECTIONS: */
        N,            /*      N      */
        E,            /*    W + E    */
        S,            /*      S      */
    } Direction;
    
    enum contains { /* to use with Cell functions */
        CONTAINS_NOTHING,
        CONTAINS_ENEMY,
        CONTAINS_TREASURE
    };

    /* Type of a cell in a level */
    typedef enum {
        WALL,
        ROOM,
        ENEMY,
        TREASURE,
        STAIR_UP,
        STAIR_DOWN,
        OOM /* out of map */
    } CellType;

    /* Structure of a cell in a level */
    typedef struct {
        Point coords;
        CellType type;
        /* Can contain a monster either a trasure (or none of above) */
        union {
            Enemy enemy;
            Treasure treasure;
        };
    } Cell;

    /* A stage is an array of cells */
    typedef struct {
        Cell cells[LEVEL_HEIGHT+4][LEVEL_WIDTH+4]; /* array of [lines][cells] (when called use this way : .cells[y][x]) */
        Point stairDown;
        int level;
    } Stage;

    /* Functions */
    
    /* Returns a cell initialized with the following informations */
    Cell initCell(unsigned int stageLevel, Point coords, CellType type, enum contains obj, unsigned int dist);

    /* Returns the distance between two points, based on the L1 norm fomula (aka Manhattan distance) */
    int distanceWithL1Norm(Point a, Point b);

    /* Returns the coords (Point) of the center of the stage. */
    Point getStageCenter();

    /* Returns 1 if a given cell is eligible and 0 otherwise */
    int isEligible(Cell cell, Stage stage);

    /* Returns 1 if a given cell is found in a given array and 0 otherwise.
     * In this function a cell is equal to another if they have the same coords (x, y). */
    int isInArray(Cell cell, Cell cellList[], unsigned int listSize);

    /* Return 1 if the specified cell is at the edge of the stage. */
    int isAtTheEdge(Cell cell);

    /* Returns a random cell from a given list. The returned cell is removed from the list. */
    Cell drawRandomCellFromList(Cell cellList[], unsigned int *listSize);

    /* Returns a stage which cells will be initialized with WALL type */
    Stage initStageWithWallCells();

    /* Returns a randomly generated stage based on a certain level.*/
    Stage generateStage(unsigned int stageLevel);

    /* Returns 1 if the given cell is a dead end and 0 otherwose. */
    int isDeadEnd(Cell cell, Stage stage);

    /* Places guarding enemy and Treasures on the specified stage. */
    void initEnemiesAndTreasuresOnStage(Stage *stage, int stageLevel);

    /* Randomly places Enemies on the specified stage. */
    void initEnemiesOnStage(Stage *stage);

    /* Randomly places a stair-down on the stage, far from the origin point (stair-up).*/
    void initStairDownOnStage(Stage *stage);

    /* Initializes the player's coordonates next to the stair-up. */
    void initPlayerOnStage(Player *player, Stage stage);

    /* Initializes the stage with all objects. */
    void initStage(Stage *stage, Player *player, unsigned int stageLevel);

    /* Returns the opposite direction of a given direction */
    Direction oppositeDir(Direction dir);

    /* printAllEnemies(ListEnemy allEnemies)Stores the (x, y) shift values (-1, 0 or 1) in the given variables */
    void dirToShiftValues(Direction dir, int *xShift, int *yShift);

    /* Return 1 if the points are adjacent to each other and 0 if they aren't */
    int isAdjacent(Point a, Point b);

    /* Return 1 if the points are in the same screen and 0 if they aren't */
    int isInScreen(Point a, Point b);

    /* Check if two points have the same coordinates */
    int isTheSame(Point a, Point b);

    /* Shell display of the specified stage (to use for debug) */
    void quickPrintStage(Stage stage);

    /*Generate a set stage to debug*/
    void generateStageTest(Stage *stage, Player *player, int level);

#endif