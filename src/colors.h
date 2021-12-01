/* Auteurs : Nicolas Mazeyrac, Lysandre Macke
 * Creation : 26/11/2021
 * Modification : 30/11/2021*/

 /*Bibliothèque générale*/
#include <MLV/MLV_all.h>

/*Bibliothèque interne*/


#ifndef __COLORS__
#define __COLORS__

    /*Define*/

    #define AVG(a, b)     (a + b)/2

    /*Struct*/


    /*Functions*/

    /*returns a color created from a given color, changing its alpha composite*/
    MLV_Color addOpacity(MLV_Color color, Uint8 alpha);

    /*returns a new color which is the average between two given colors*/
    MLV_Color avgOfColors(MLV_Color color1, MLV_Color color2);

#endif