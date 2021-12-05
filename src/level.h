/* Auteurs : Nicolas Mazeyrac, Lysandre Macke
 * Creation : 27/11/2021
 * Modification : 30/11/2021*/

/*Bibliothèque générale*/

/*Bibliothèque interne*/
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


	/* Functions */

	/* Returns the distance between two points, based on the L1 norm fomula (aka Manhattan distance) */
	int calcDistanceWithL1Norm(Point a, Point b);

	/* Returns 1 if a given cell is eligible compared to a given reference cell */
	int isEligible(Cell cell, Cell referenceCell);

	/* Returns the opposite direction of a given direction */
	Direction oppositeDir(Direction dir);

	/* Stores the (x, y) shift values (-1, 0 or 1) in the given variables */
	void dirToShiftValues(Direction dir, int *xShift, int *yShift);
#endif