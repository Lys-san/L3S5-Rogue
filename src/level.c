#include "level.h"

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