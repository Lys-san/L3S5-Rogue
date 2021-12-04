/* Auteurs : Nicolas Mazeyrac, Lysandre Macke
 * Creation : 26/11/2021
 * Modification : 30/11/2021*/

 /*Bibliothèque générale*/
#include <MLV/MLV_all.h>

/*Bibliothèque interne*/


#ifndef __COLORS__
#define __COLORS__

    /*Define*/

    #define AVG(a, b)     ((a + b)/2)

    /*Struct*/


    /*Functions*/

	/* returns 1 if two rgba arrays are the same and 0 otherwise */
	int isSameRGBA(Uint8 color1[4], Uint8 color2[4]);

    /* returns a color created from a given color, changing its alpha composite */
    MLV_Color addOpacity(MLV_Color color, Uint8 alpha);

    /* returns a new color which is the average between two given colors */
    MLV_Color avgOfColors(MLV_Color color1, MLV_Color color2);

    /* fills the area around a given point. The area is delimited by a given color. */
    void boundaryFill(int x, int y, MLV_Color fillColor, MLV_Color borderColor, int windowWidth, int windowHeight);

#endif