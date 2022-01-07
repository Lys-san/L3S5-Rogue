#include "level.h"

Cell initCell(unsigned int stageLevel, Point coords, CellType type, enum contains obj, unsigned int dist) {
	Cell cell;
	cell.coords = coords;
	cell.type = type;
	switch(obj) {
		case CONTAINS_ENEMY :
			cell.contains = generateEnemy(stageLevel, dist);
			printf("initCell level = \n");
			quickPrintEnemy(cell.enemy);
		case CONTAINS_TREASURE :
			cell.treasure = generateTreasure(stageLevel, rand() % MAX_RARITY);
		default :
			break;
	}
	return cell;
}


int distanceWithL1Norm(Point a, Point b) {
	return ABS((b.x - a.x)) + ABS((b.y - a.y));
}


Point getStageCenter() {
	Point stageCenter;
	stageCenter.x = LEVEL_WIDTH/2;
	stageCenter.y = LEVEL_HEIGHT/2;
	return stageCenter;
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
	for(i = yStart; i < cell.coords.y + 2; i++) {
		for(j = xStart; j < cell.coords.x + 2; j++) {
			if(stage.cells[i][j].type == ROOM) {

				if(distanceWithL1Norm(cell.coords, (Point){j, i}) == 1) {
					if(++nbRoomCellsAtDist1 > 1)
						return 0;
				}
				if(distanceWithL1Norm(cell.coords, (Point){j, i}) == 2) {
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
	return stage;
}


Stage generateStage(unsigned int stageLevel) {
	int i, j;
	int ii, jj; /* we can't call them i' and j' (*sad maths student noises*) */
	unsigned int k = 0;
	unsigned int nbOfSurroundingWallCells;
	unsigned int nbOfCells = 4; /* number of cells in the array of Cells*/
	Cell cellsToExpand[LEVEL_HEIGHT*LEVEL_WIDTH]; /* adjust array size later */
	Stage stage;

	Point stageCenter = getStageCenter();

	Cell currentCell;

	stage = initStageWithWallCells();

	/* initializing the center as a room cell */
	stage.cells[stageCenter.y][stageCenter.x] = initCell(stageLevel, stageCenter, ROOM, CONTAINS_NOTHING, 0);

	/* initializing the adjacent cells list */
	for(i = stageCenter.y - 1; i <= stageCenter.y + 1; i += 2)
		cellsToExpand[k++] = stage.cells[i][stageCenter.x];

	for(j = stageCenter.x - 1; j <= stageCenter.x + 1; j += 2)
		cellsToExpand[k++] = stage.cells[stageCenter.y][j];

	/* generating ROOM cells */
	do {
		currentCell = drawRandomCellFromList(cellsToExpand, &nbOfCells);
		
		/* Loop until an eligible cell is found */
		while(!isEligible(currentCell, stage) && nbOfCells > 0) {
			currentCell = drawRandomCellFromList(cellsToExpand, &nbOfCells);
		}

		stage.cells[currentCell.coords.y][currentCell.coords.x].type = ROOM;

		/* searching for new eligible cells around the current cell if the current cell isn't at the edge */
		if(!isAtTheEdge(stage.cells[currentCell.coords.y][currentCell.coords.x])) {
			for(i = currentCell.coords.y - 1; i <= currentCell.coords.y + 1; i += 2) {
				if(isEligible(stage.cells[i][currentCell.coords.x], stage) && !isInArray(stage.cells[i][currentCell.coords.x], cellsToExpand, nbOfCells)) {
					cellsToExpand[nbOfCells] = stage.cells[i][currentCell.coords.x];
					nbOfCells++;
				}
			}
			for(j = currentCell.coords.x - 1; j <= currentCell.coords.x + 1; j += 2) {
				if(isEligible(stage.cells[currentCell.coords.y][j], stage) && !isInArray(stage.cells[currentCell.coords.y][j], cellsToExpand, nbOfCells)) {
					cellsToExpand[nbOfCells] = stage.cells[currentCell.coords.y][j];
					nbOfCells++;
				}
			}
		}
	}
	while(nbOfCells > 0);

	/* converting ROOM cells who are surrounded by 3 WALL cells to WALL cells */
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
				}
			}
		}
	}
	/* initializing the stair-up */
	stage.cells[stageCenter.y][stageCenter.x] = initCell(stageLevel, stageCenter, STAIR_UP, CONTAINS_NOTHING, 0);

	return stage;
}


int isDeadEnd(Cell cell, Stage stage) {
	int surroundingWalls = 0;
	int i, j;

	/* checking surrounding cells */
	for(i = cell.coords.x - 1; i <= cell.coords.x + 1; i += 2) {
		if(stage.cells[cell.coords.y][i].type == WALL && cell.type == ROOM)
			surroundingWalls++;
	}
		
	for(j = cell.coords.y - 1; j <= cell.coords.y + 1; j += 2)
		if(stage.cells[j][cell.coords.x].type == WALL && cell.type == ROOM)
			surroundingWalls++;

	/* is a dead end if and only if it has 3 surrounding walls */
	if(surroundingWalls == 3)
		return 1;

	/* else, is not */
	return 0;
}


void initEnemiesAndTreasuresOnStage(Stage *stage, int stageLevel) {
	int i, j;
	int ii, jj;
	int distToOrigin;

	Point stageCenter = getStageCenter();

	for(i = 0; i < LEVEL_HEIGHT; i++) {
		for(j = 0; j < LEVEL_WIDTH; j++) {
			if(isDeadEnd(stage->cells[i][j], *stage)) {
				/* generating treasure cell */
				distToOrigin = distanceWithL1Norm(stageCenter, (Point){j, i});
				stage->cells[i][j] = initCell(stageLevel, (Point){j, i}, TREASURE, CONTAINS_TREASURE, distToOrigin);
				
				/* generating guardian enemy */
				for(ii = i - 1; ii < i + 2; ii++) {
					for(jj = j - 1; jj < j + 2; jj++) {
						/* looking for the coordonates next to the treasure */
						if(stage->cells[ii][jj].type == ROOM && distanceWithL1Norm((Point){jj, ii}, (Point){j, i}) == 1) {
							distToOrigin = distanceWithL1Norm(stageCenter, (Point){jj, ii});
							stage->cells[ii][jj] = initCell(stageLevel, (Point){jj, ii}, ENEMY, CONTAINS_ENEMY, distToOrigin);
							/*quickPrintEnemy(stage->cells[jj][ii].enemy);*/
							break;
						}
					}
				}
			}
		}
	}
}


void initEnemiesOnStage(Stage *stage) {
	/* TODO */
}


void initStairDownOnStage(Stage *stage) {
	int maxDistance   = 25;
	Point stageCenter = getStageCenter();
	int i, j; /* to avoid infinite loop */
	int distance;
	int stairsInitialized = 0;

	/* loops until the stair-down isn't initialized. */
	while(!stairsInitialized) {
		for(i = 0; i < LEVEL_WIDTH && !stairsInitialized; i++) {
			for(j = 0; j < LEVEL_HEIGHT && !stairsInitialized; j++) {
				distance = distanceWithL1Norm((Point){i, j}, stageCenter);
				if(distance >= maxDistance) {
					if(stage->cells[j][i].type == ROOM) {
						if(rand()%100 == 1) {
							stage->cells[j][i] = initCell(0, (Point){i, j}, STAIR_DOWN, CONTAINS_NOTHING, distance);
							stairsInitialized = 1;
						}
					}
				}
			}
		}
		i++;
		if(i > 50) {
			fprintf(
				stderr,
				"Error : something strange happened while generating the stair down. "
				"This either means the person who programmed this is stupid, either you "
				"are an incredibly unlucky person.\n"
				"Please restart the program."
				);

			exit(0);
		}
	}
}


void initPlayerOnStage(Player *player, Stage stage) {
	Point stageCenter;
	stageCenter.x = LEVEL_WIDTH/2;
	stageCenter.y = LEVEL_HEIGHT/2;
	
	Cell adjacent[4];
	unsigned int k = 0;

	int i, j;

	/* getting the cells next to the stair-up */
	for(i = stageCenter.y - 1; i <= stageCenter.y + 1; i += 2)
		adjacent[k++] = stage.cells[i][stageCenter.x];

	for(j = stageCenter.x - 1; j <= stageCenter.x + 1; j += 2)
		adjacent[k++] = stage.cells[stageCenter.y][j];

	/* choosing a cell for the player to be in */
	Cell startingCell = drawRandomCellFromList(adjacent, &k);
	while( startingCell.type != ROOM)
		startingCell = drawRandomCellFromList(adjacent, &k);

	/* updating the player's coordonates */
	player->coords = startingCell.coords;
}

void initStage(Stage *stage, Player *player, unsigned int stageLevel) {
	(*stage) = generateStage(stageLevel);
	initEnemiesAndTreasuresOnStage(stage, stageLevel);
	initStairDownOnStage(stage);
	initPlayerOnStage(player, *stage);
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
    if( a.x == b.x-1 || a.x == b.x || a.x == b.x+1 ){   /*x are adjacent*/
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
				default:
					break;
			}
		}
		printf("\n");
	}
}

/*

#########
#^     v#
#P  T  !#
#       #
#########

*/

Stage generateStageTest( void ){
	
	Stage stage;
	Cell test;
	Cell test2;
	int i, j;

	/* The empty spaces */
	for(i = 1; i < TEST_LEVEL_HEIGHT; i++) {
		for(j = 1; j < TEST_LEVEL_WIDTH-1; j++  ){
			stage.cells[i][j] = initCell(1, (Point){j, i}, ROOM, CONTAINS_NOTHING, 1);
		}
	}

	/*stairs*/
	stage.cells[1][1] = initCell(0, (Point){1, 1}, STAIR_UP, CONTAINS_NOTHING, 1);
	stage.cells[1][TEST_LEVEL_WIDTH-2] = initCell(1, (Point){1, TEST_LEVEL_WIDTH-2}, STAIR_DOWN, CONTAINS_NOTHING, 1);

	/*treasure*/
	stage.cells[2][4] = initCell(1, (Point){2, 4}, TREASURE, CONTAINS_NOTHING, 0);

	/* Enemy */
	test = initCell(1, (Point){2, TEST_LEVEL_WIDTH-2}, ENEMY, CONTAINS_ENEMY, 1);
	printf("Cell test level = \n");
	quickPrintEnemy(test.enemy);
	stage.cells[2][TEST_LEVEL_WIDTH-2] = initCell(1, (Point){2, TEST_LEVEL_WIDTH-2}, ENEMY, CONTAINS_NOTHING, 1);
	printf("in stage level = \n");
	quickPrintEnemy(stage.cells[2][TEST_LEVEL_WIDTH-2].enemy);

	return stage;
}

Point newPoint(int x, int y){
	Point new;
	new.x = x;
	new.y = y;
	return new;
}

int isTheSame(Point a, Point b){
	if(a.x == b.x && a.y == b.y){
		return 1;
	}
	return 0;
}
