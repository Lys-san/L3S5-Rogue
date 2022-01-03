#include "level.h"

Cell initCell(unsigned int stageLevel, Point coords, CellType type, enum contains obj, unsigned int dist) {
	Cell cell;
	cell.coords = coords;
	cell.type = type;
	switch(obj) {
		case CONTAINS_ENEMY :
			cell.enemy = generateEnemy(stageLevel, dist);
		case CONTAINS_TREASURE :
			cell.treasure = generateTreasure(stageLevel, rand() % MAX_RARITY);
		default :
			break;
	}
	return cell;
}


int distanceWithL1Norm(Point a, Point b) {
	printf("   (abs(%d - %d) + abs(%d - %d))\n", b.x, a.x, b.y, a.y);
	return ABS((b.x - a.x)) + ABS((b.y - a.y));
}


int isEligible(Cell cell, Stage stage) {
	printf("Checking if %d %d is eligible.\n", cell.coords.x, cell.coords.y);
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
	for(i = yStart; i < cell.coords.y + 2; i++) {
		for(j = xStart; j < cell.coords.x + 2; j++) {
			printf("%d %d TYPE : %d\n", stage.cells[i][j].coords.x, stage.cells[i][j].coords.y, stage.cells[i][j].type);
			if(stage.cells[i][j].type == ROOM) {
				printf("ROOM found at dist : %d \n", distanceWithL1Norm(cell.coords, (Point){j, i}));

				if(distanceWithL1Norm(cell.coords, (Point){j, i}) == 1) {
					printf("DIST 1\n");
					if(++nbRoomCellsAtDist1 > 1)
						return 0;
				}
				if(distanceWithL1Norm(cell.coords, (Point){j, i}) == 2) {
					printf("DIST 2\n");
					if(++nbRoomCellsAtDist2 > 2)
						return 0;
				}
			}
		}
	}
	if(nbRoomCellsAtDist1 == 0 && nbRoomCellsAtDist2 == 0)
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

int isAtTheEdge(Cell cell) {
	return cell.coords.x == 0 || cell.coords.x == LEVEL_WIDTH - 1 ||
		cell.coords.y == 0 || cell.coords.y == LEVEL_HEIGHT - 1;

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
	/* updating the size */
	(*listSize)--;

	return drawnCell;
}


Stage initStageWithWallCells() {
	Stage stage;
	int i, j;
	for(i = 0; i < LEVEL_HEIGHT; i++) {
		for(j = 0; j < LEVEL_WIDTH; j++) {
			stage.cells[i][j] = initCell(0, (Point){j, i}, WALL, CONTAINS_NOTHING, 0);
		}
	}
	printf("end of init stage with wall cells function\n");
	return stage;
}


Stage generateStage(unsigned int stageLevel) {
	printf("starting generating the stage\n");
	int i, j;
	int ii, jj; /* we can't call them i' and j' (*sad maths student noises*) */
	unsigned int k = 0;
	unsigned int nbOfSurroundingWallCells;
	unsigned int nbOfCells = 4; /* number of cells in the array of Cells*/
	Cell cellsToExpand[LEVEL_HEIGHT*LEVEL_WIDTH]; /* adjust array size later */
	Stage stage;

	Point stageCenter;
	stageCenter.x = LEVEL_WIDTH/2;
	stageCenter.y = LEVEL_HEIGHT/2;

	Cell currentCell;

	int rooms = 0;

	printf(">>>initializing the stage with wall cells\n");
	stage = initStageWithWallCells();

	/* initializing the center as a room cell */
	printf(">>>initializing the stair-up as a room cell\n");
	stage.cells[stageCenter.y][stageCenter.x] = initCell(stageLevel, stageCenter, ROOM, CONTAINS_NOTHING, 0);
	printf("%d %d TYPE : %d\n", stage.cells[stageCenter.y][stageCenter.x].coords.x, stage.cells[stageCenter.y][stageCenter.x].coords.y, stage.cells[stageCenter.y][stageCenter.x].type);

	/* initializing the adjacent cells list */
	printf(">>>initializing the adjacent cells list :\n");
	for(i = stageCenter.y - 1; i <= stageCenter.y + 1; i += 2) {
		cellsToExpand[k++] = stage.cells[i][stageCenter.x];
		printf("%d - cell : %d %d\n", k, cellsToExpand[k-1].coords.x, cellsToExpand[k-1].coords.y);
	}

	for(j = stageCenter.x - 1; j <= stageCenter.x + 1; j += 2) {
		cellsToExpand[k++] = stage.cells[stageCenter.y][j];
		printf("%d - cell : %d %d\n", k, cellsToExpand[k-1].coords.x, cellsToExpand[k-1].coords.y);
	}

	/* generating ROOM cells */
	printf(">>>generating ROOM cells\n");
	do {
		do {
			for(i = 0; i < nbOfCells; i++) {
				printf("(%d, %d) ", cellsToExpand[i].coords.x, cellsToExpand[i].coords.y);
			}
			currentCell = drawRandomCellFromList(cellsToExpand, &nbOfCells);
			printf("\n>>>CELL : %d %d  ", currentCell.coords.x, currentCell.coords.y);
			printf("eligible ? \n");
			printf(isEligible(currentCell, stage) ? "yes\n" : "no\n");
		}
		while(!isEligible(currentCell, stage) && nbOfCells > 0);
		printf(">>>Converting %d %d to ROOM type.\n", currentCell.coords.x, currentCell.coords.y);
		currentCell.type = ROOM;
		stage.cells[currentCell.coords.y][currentCell.coords.x].type = ROOM;
		rooms++;
		printf("Converted %d %d to ROOM type.\n", stage.cells[currentCell.coords.y][currentCell.coords.x].coords.x, stage.cells[currentCell.coords.y][currentCell.coords.x].coords.y);

		/* searching for new eligible cells around the current cell if the current cell isn't at the edge */
		if(!isAtTheEdge(stage.cells[currentCell.coords.y][currentCell.coords.x])) {
			for(i = currentCell.coords.y - 1; i <= currentCell.coords.y + 1; i += 2) {
				if(isEligible(stage.cells[i][currentCell.coords.x], stage) && !isInArray(stage.cells[i][currentCell.coords.x], cellsToExpand, nbOfCells)) {
					printf("adding %d %d to cellsToExpand.\n", stage.cells[i][currentCell.coords.x].coords.x, stage.cells[i][currentCell.coords.x].coords.y);
					cellsToExpand[nbOfCells] = stage.cells[i][currentCell.coords.x];
					nbOfCells++;
				}
			}
			for(j = currentCell.coords.x - 1; j <= currentCell.coords.x + 1; j += 2) {
				if(isEligible(stage.cells[currentCell.coords.y][j], stage) && !isInArray(stage.cells[currentCell.coords.y][j], cellsToExpand, nbOfCells)) {
					printf("adding %d %d to cellsToExpand.\n", stage.cells[currentCell.coords.y][j].coords.x, stage.cells[currentCell.coords.y][j].coords.y);
					cellsToExpand[nbOfCells] = stage.cells[currentCell.coords.y][j];
					nbOfCells++;
				}
			}
		}
		printf("FINISHED WORKING ON %d %d.\n", currentCell.coords.x, currentCell.coords.y);
	}
	while(nbOfCells > 0);

	/* converting ROOM cells who are surrounded by 3 WALL cells to WALL cells */
	printf(">>>converting ROOM cells who are surrounded by 3 WALL cells to WALL cells\n");
	for(i = 0; i < LEVEL_HEIGHT; i++) {
		for(j = 0; j < LEVEL_WIDTH; j++) {
			if(stage.cells[i][j].type == ROOM) {
				nbOfSurroundingWallCells = 0;
				/* checking the surrounding cells */
				for(ii = stage.cells[i][j].coords.y - 1; ii <= stage.cells[i][j].coords.y + 1; ii += 2) {
					if(stage.cells[ii][stage.cells[i][j].coords.x].type == WALL)
						nbOfSurroundingWallCells++;
				}
				for(jj = stage.cells[i][j].coords.x - 1; jj <= stage.cells[i][j].coords.x + 1; jj += 2) {
					if(stage.cells[stage.cells[i][j].coords.y][jj].type == WALL)
						nbOfSurroundingWallCells++;
				}

				if(nbOfSurroundingWallCells == 3) {
					stage.cells[i][j].type = WALL;
					rooms--;
				}
			}
		}
	}
	/* initializinf the stair-up */
	stage.cells[stageCenter.y][stageCenter.x] = initCell(stageLevel, stageCenter, STAIR_UP, CONTAINS_NOTHING, 0);

	printf("Stage generated. %d room cells created.\n", rooms+1);
	return stage;
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

int isAdjacent(Point a, Point b){
    if( a.x == b.x-1 || a.x == b.x || a.x == b.x+1 ){/*x are adjacent*/
        if(a.y == b.y-1 || a.y == b.y || a.y == b.y+1 ){/*y are adjacent*/
            return 1;
        }
    }
    return 0;
}

int isInScreen(Point a, Point b){
	/*the screen is 13/9*/
    if( a.x >= b.x - SCREEN_WIDTH && a.x <= b.x + SCREEN_WIDTH ){      /*x are in the same screen*/
        if(a.y >= b.y - SCREEN_HEIGHT && a.x <= b.x + SCREEN_HEIGHT ){ /*y are in the same screen*/
            return 1;
        }
    }
    return 0;
}

void quickPrintStage(Stage stage) {
	int i, j;
	for(i = 0; i < LEVEL_HEIGHT; i++) {
		for(j = 0; j < LEVEL_WIDTH; j++) {
			switch(stage.cells[i][j].type) {
				case WALL:
					printf("#");
					break;
				case ROOM:
					printf(".");
					break;
				case ENEMY:
					printf("!");
					break;
				case TREASURE:
					printf("T");
					break;
				case STAIR_UP:
					printf("^");
					break;
				case STAIR_DOWN:
					printf("v");
					break;
			}
		}
		printf("\n");
	}
}
