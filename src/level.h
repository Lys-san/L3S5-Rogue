/* Autors : Nicolas Mazeyrac, Lysandre Macke
 * Creation : 27/11/2021
 * Last modified : 05/12/2021*/

/* General libraries */
#include <stdlib.h>
/* Internal libraries */
#include "enemy.h"
#include "treasure.h"

#ifndef __LEVEL__
#define __LEVEL__

 	/* Define */

	#define LEVEL_WIDTH  63
	#define LEVEL_HEIGHT 43

	#define ABS(a) a > 0 ? (a) : (-a) /* absolute value*/


 	/* Struct */

	typedef enum {
		W,            /* DIRECTIONS: */
		N,            /*      N      */
		E,            /*    W + E    */
		S,            /*      S      */
	} Direction;

	/* Type of a cell in a level */
	typedef enum {
		WALL,
		ROOM,
		ENEMY,
		TREASURE,
		STAIR_UP,
		STAIR_DOWN
	} CellType;

	typedef struct {
		int x;
		int y;
	} Point;

	/* Structure of a cell in a level */
	typedef struct {
		Point coords;
		CellType type;
		/* Can be either a monster either a trasure */
		union {
			Enemy enemy;
			Treasure treasure;
		};
	} Cell;

	/* A stage is an array of cells */
	typedef struct {
		Cell cells[43][63];
	} Stage;


	/* Functions */
	
	/* Initialize a given cell with the following informations */
	void initCell(Cell *cell, Point coords, CellType type);

	/* Returns the distance between two points, based on the L1 norm fomula (aka Manhattan distance) */
	int distanceWithL1Norm(Point a, Point b);

	/* Returns 1 if a given cell is eligible and 0 otherwise */
	int isEligible(Cell cell, Stage stage);

	/* Returns a random cell from a given list. The returned cell is removed from the list. */
	Cell drawRandomCellFromList(Cell cellList[], int *ListSize);

	/* Returns a randomly generated stage */
	Stage generateStage();

	/* Returns the opposite direction of a given direction */
	Direction oppositeDir(Direction dir);

	/* Stores the (x, y) shift values (-1, 0 or 1) in the given variables */
	void dirToShiftValues(Direction dir, int *xShift, int *yShift);
#endif