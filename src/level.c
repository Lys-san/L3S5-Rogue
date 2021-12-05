#include "level.h"

void initCell(Cell *cell, Point coords, CellType type) {
	cell->coords = coords;
	cell->type = type;
}


int distanceWithL1Norm(Point a, Point b) {
	return ABS((a.x - b.x)) + ABS((a.y - b.y));
}


int isEligible(Cell cell, Stage stage) {
	if(cell.type != WALL)
		return 0;

	int i, j;
	int nbRoomCellsAtDist1 = 0;
	int nbRoomCellsAtDist2 = 0;

	int xStart, yStart;

	if(cell.coords.y <= 2)
		yStart = 0;
	else
		yStart = cell.coords.y - 2;

	if(cell.coords.x <= 2)
		xStart = 0;
	else
		xStart = cell.coords.x - 2;

	/* checking the cells around the reference cell*/
	for(j = yStart; j < cell.coords.y + 2; j++) {
		for(i = xStart; i < cell.coords.x + 2; i++) {
			if(stage.cells[j][i].type == ROOM) {
				if(distanceWithL1Norm(cell.coords, (Point){i, j}) == 1) {
					if(++nbRoomCellsAtDist1 > 1)
						return 0;
				}
				if(distanceWithL1Norm(cell.coords, (Point){i, j}) == 2) {
					if(++nbRoomCellsAtDist2 > 2)
						return 0;
				}
			}
		}
	}
	if(nbRoomCellsAtDist1 == 0 || nbRoomCellsAtDist2 == 0)
		return 0;

	return 1;
}


Cell drawRandomCellFromList(Cell cellList[], int *ListSize) {
	/* Do not forget to initialize the random function with a proper seed in main */
	int randInt = rand() % (*ListSize);
	int i;

	Cell drawnCell = cellList[randInt];

	/* pushing all the elements of the list at the top */
	for(i = randInt; i < (*ListSize)-1; i++) {
		cellList[i] = cellList[i + 1];
	}
	ListSize--;

	return drawnCell;
}


Stage generateStage() {
	int nbOfCells = 4;
	Cell toExpand[4]; /* adjacent cells to the stair up*/
	Cell currentCell;

}


Direction oppositeDir(Direction dir) {
	return (dir + 2) % 4;
}


void dirToShiftValues(Direction dir, int *xShift, int *yShift) {
	if(dir % 2) { /* if dir is 1 (N) or 3 (S)*/
		*xShift = 0;
		*yShift = dir - 2;
	}
	else {        /* if dir is 0 (W) or 2 (E)*/
		*xShift = dir - 1;
		*yShift = 0;
	}
}