/* Autors : Nicolas Mazeyrac, Lysandre Macke
 * Creation : 27/11/2021
 * Last modified : 06/12/2021*/

/* General libraries */
#include <stdlib.h>
#include <stdio.h>

/* Internal libraries */
#include "enemy.h" /*includes player.h*/
#include "treasure.h"

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
		Cell cells[LEVEL_HEIGHT][LEVEL_WIDTH]; /* array of [lines][cells] (when called use this way : .cells[y][x]) */
	} Stage;

	/* Functions */
	
	/* Returns a cell initialized with the following informations */
	Cell initCell(unsigned int stageLevel, Point coords, CellType type, enum contains obj, unsigned int dist);

	/* Returns the distance between two points, based on the L1 norm fomula (aka Manhattan distance) */
	int distanceWithL1Norm(Point a, Point b);

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

	/* Initializes the player's coordonates next to the stair-up. */
	void initPlayerOnStage(Player *player, Stage stage);

	/* Initializes the stage with the player in the middle. */
	void initStage(Stage *stage, Player *player, unsigned int stageLevel);

	/* Returns the opposite direction of a given direction */
	Direction oppositeDir(Direction dir);

	/* printAllEnemies(ListEnemy allEnemies)Stores the (x, y) shift values (-1, 0 or 1) in the given variables */
	void dirToShiftValues(Direction dir, int *xShift, int *yShift);

	/* Return 1 if the points are adjacent to each other and 0 if they aren't */
    int isAdjacent(Point a, Point b);

	/* Return 1 if the points are in the same screen and 0 if they aren't */
    int isInScreen(Point a, Point b);

    /* Shell display of the specified stage (to use for debug) */
    void quickPrintStage(Stage stage);

    /*Generate a set stage to debug*/
    Stage generateStageTest( void );

    /* Generate a New point from the coordonates*/
    Point newPoint(int x, int y);

    /* Check if two points have the same coordinates */
    int isTheSame(Point a, Point b);

#endif