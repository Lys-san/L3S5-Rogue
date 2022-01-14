/* Autors        : Nicolas Mazeyrac, Lysandre Macke
 * Created       : 13/01/2022
 * Last modified : 13/01/2022*/

#include <MLV/MLV_all.h>
#include <time.h>


#include "colors.h"

#ifndef __DRAW__
#define __DRAW__

	#define BREAK_NESTED_LOOPS pixelFound = 1; break;
	#define LINE_COLOR                   MLV_COLOR_BLACK

	#define SQUARED(a) (a*a)


	typedef struct {
        int x;         /*x coordonate*/
        int y;         /*y coordonate*/
        int radius;    /*in px*/
        Uint8 opacity; /*[0-255]*/
    } Snowdrop;

    /*updates the (x, y) coordonates of a Snowdrop*/
    void calculateNextCoord(Snowdrop *snowdrop, unsigned int windowWidth, unsigned int windowHeight);

    /*display update*/
    void displayNewSnowdropsFrame(Snowdrop snowdrops[], int nbOfSnowdrops, unsigned int windowWidth, unsigned int windowHeight);

    /* Generates a snowy cinematic using the libMLV functions. */
	void snowdrops(unsigned int frames);

	/* Converts a number of points (hp/mp/exp) into a bar percentage */
    int convertPointsToBarPercentg(int points, int maxPoints);

    /* Converts a bar percentage into a length depending on a bar length (px) */
	int convertBarPercentgToLenght(int barPrctg, int barLength);

	/* Draws a bar filled at fillPrctg % */
    void drawBar(int xStart, int yStart, int length, int height, int fillPrctg, MLV_Color fillColor);

    /* Draws a quarter circle bar of center (xCenter, yCenter) and radius radius filled at fillPrctg % */
    void drawQuarterCircleBar(int xCenter, int yCenter, int radius, int fillPrctg, MLV_Color fillColor);

#endif