/* Autors : Nicolas Mazeyrac, Lysandre Macke
 * Creation : 14/12/2021
 * Last modified : 14/12/2021*/

#ifndef __GAME_CONTROL__
#define __GAME_CONTROL__
    /* Direction (West, North, East, South) */
    typedef enum {
        W,            /* DIRECTIONS: */
        N,            /*      N      */
        E,            /*    W + E    */
        S,            /*      S      */
    } Direction;
    

    /* Returns the opposite direction of a given direction */
    Direction oppositeDir(Direction dir);

    /* Stores the (x, y) shift values (-1, 0 or 1) in the given variables */
    void dirToShiftValues(Direction dir, int *xShift, int *yShift);

    
#endif