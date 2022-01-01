#include "level.h"

Cell initCell(unsigned int stageLevel, Point coords, CellType type, enum contains obj) {
	Cell cell;
	cell.coords = coords;
	cell.type = type;
	switch(obj) {
		case CONTAINS_ENEMY :
			cell.enemy = generateEnemy(stageLevel);
		case CONTAINS_TREASURE :
			cell.treasure = generateTreasure(stageLevel, rand() % MAX_RARITY);
		default :
			break;
	}
	return cell;
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


int isInArray(Cell cell, Cell cellList[], unsigned int listSize) {
	int i;
	for(i = 0; i < listSize; i++) {
		if(cellList[i].coords.x == cell.coords.x
			&& cellList[i].coords.y == cell.coords.y)
			return 1;
	}
	return 0;
}


Cell drawRandomCellFromList(Cell cellList[], unsigned int *listSize) {
	/* Do not forget to initialize the random function with a proper seed in main */
	int randInt = rand() % (*listSize);
	int i;

	Cell drawnCell = cellList[randInt];

	/* pushing all the elements of the list at the top */
	for(i = randInt; i < (*listSize)-1; i++) {
		cellList[i] = cellList[i + 1];
	}
	listSize--;

	return drawnCell;
}


Stage initStageWithWallCells() {
	Stage stage;
	int i, j;
	for(j = 0; j < LEVEL_HEIGHT; j++) {
		for(i = 0; i < LEVEL_WIDTH; i++)
			stage.cells[i][j] = initCell(0, (Point){i, j}, WALL, CONTAINS_NOTHING);
	}
	return stage;
}


Stage generateStage(unsigned int stageLevel) {
	int i, j;
	int ii, jj; /* we can't call them i' and j' (*sad maths student noises*) */
	unsigned int k = 0;
	unsigned int nbOfSurroundingWallCells;
	unsigned int nbOfCells = 4;
	Cell cellsToExpand[LEVEL_HEIGHT*LEVEL_WIDTH]; /* adjust array size later */
	Stage stage;

	Point stageCenter;
	stageCenter.x = LEVEL_WIDTH/2;
	stageCenter.y = LEVEL_HEIGHT/2;

	Cell currentCell;

	stage = initStageWithWallCells();

	/* initializing the stair-up */
	stage.cells[stageCenter.y][stageCenter.x] = initCell(stageLevel, stageCenter, STAIR_UP, CONTAINS_NOTHING);

	/* initializing the adjacent cells list */
	for(j = stageCenter.y - 1; j <= stageCenter.y + 1; j += 2) {
		for(i = stageCenter.x - 1; i <= stageCenter.x + 1; i += 2)
			cellsToExpand[k++] = stage.cells[i][j];
	}

	/* generating ROOM cells */
	do {
		do {
			currentCell = drawRandomCellFromList(cellsToExpand, &nbOfCells);
		}
		while(!isEligible(currentCell, stage));

		currentCell.type = ROOM;

		/* searching for new eligible cells around the current cell */
		for(j = currentCell.coords.y - 1; j <= currentCell.coords.y + 1; j += 2) {
			for(i = currentCell.coords.x - 1; i <= currentCell.coords.x + 1; i += 2) {
				if(isEligible(stage.cells[i][j], stage) && !isInArray(stage.cells[i][j], cellsToExpand, nbOfCells)) {
					cellsToExpand[nbOfCells - 1] = stage.cells[i][j];
					nbOfCells++;
				}
			}
		}
	}
	while(nbOfCells > 0);

	/* converting ROOM cells who are surrounded by 3 WALL cells to WALL cells */
	for(j = 0; j < LEVEL_HEIGHT; j++) {
		for(i = 0; i < LEVEL_WIDTH; i++) {
			if(stage.cells[i][j].type == ROOM) {
				nbOfSurroundingWallCells = 0;
				/* checking the surrounding cells */
				for(jj = stage.cells[i][j].coords.y - 1; jj <= stage.cells[i][j].coords.y + 1; jj += 2) {
					for(ii = stage.cells[i][j].coords.x - 1; ii <= stage.cells[i][j].coords.x + 1; ii += 2) {
						if(stage.cells[ii][jj].type == WALL)
							nbOfSurroundingWallCells++;
					}
				}
				if(nbOfSurroundingWallCells == 3)
					stage.cells[i][j].type = WALL;
			}
		}
	}
	return stage;
}