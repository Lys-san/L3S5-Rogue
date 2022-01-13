#include "draw.h"

void calculateNextCoord(Snowdrop *snowdrop, unsigned int windowWidth, unsigned int windowHeight) {
    int windIntensity     = 7;  /*[0-10]*/
    int gravityForce      = 2;  /*[0-10]*/

    int randomFluctuationX = (rand()%2 == 0)?(rand()%2):(-(rand()%2));
    int randomFluctuationY = rand()%5;

    snowdrop->x += (windIntensity + randomFluctuationX);
    snowdrop->y += (gravityForce + randomFluctuationY);

    snowdrop->x %= windowWidth;
    snowdrop->y %= windowHeight;
}


void displayNewSnowdropsFrame(Snowdrop snowdrops[], int nbOfSnowdrops, unsigned int windowWidth, unsigned int windowHeight) {
    int i;
    for(i = 0; i < nbOfSnowdrops; i++) {
        /*generation of the new coordonates*/
        calculateNextCoord(&snowdrops[i], windowWidth, windowHeight);

        /*white color : all the rgb values are 255*/
        MLV_Color color = MLV_convert_rgba_to_color(255, 255, 255, snowdrops[i].opacity);
        MLV_draw_filled_circle(snowdrops[i].x, snowdrops[i].y, snowdrops[i].radius, color);
    }
    MLV_actualise_window();
}

void snowdrops(unsigned int frames) {
    int fadeoutTime = 50;

    MLV_Color fadeoutColor = MLV_COLOR_GHOSTWHITE;
    MLV_Color backgroundColor = MLV_COLOR_POWDERBLUE;
    Uint8 backgroundRGBA[4];
    MLV_convert_color_to_rgba(backgroundColor, &backgroundRGBA[0], &backgroundRGBA[1], &backgroundRGBA[2], &backgroundRGBA[3]);

    int maxSnowdropRadius = 15;
    int nbOfSnowdrops     = 20; 
    int i;

    Snowdrop snowdrops[nbOfSnowdrops];

    unsigned int windowWidth, windowHeight;
    MLV_get_window_size(&windowWidth, &windowHeight);

    srand(time(NULL));

    /*random generation of the snowdrops*/
    for(i = 0; i < nbOfSnowdrops; i++) {
        snowdrops[i].x = rand() % windowWidth;
        snowdrops[i].y = rand() % windowHeight;
        snowdrops[i].radius = rand() % maxSnowdropRadius;
        snowdrops[i].opacity = rand() % 255;
    }

    /*animation of the generated snowdrops*/
    for(i = 0; i < frames; i++) {
        MLV_clear_window(backgroundColor);
        displayNewSnowdropsFrame(snowdrops, nbOfSnowdrops, windowWidth, windowHeight);

        /*fadeout at the end*/
        if(i > frames - fadeoutTime) {
            fadeoutColor = addOpacity(fadeoutColor, -(255 / fadeoutTime));
            backgroundColor = avgOfColors(backgroundColor, fadeoutColor);

            MLV_draw_filled_rectangle(0, 0, windowWidth, windowHeight, fadeoutColor);
            MLV_actualise_window();
            /* display will take more time so we don't have to wait 5 more ms */
        }
        else
            MLV_wait_milliseconds( 5 );
    }
}


int convertPointsToBarPercentg(int points, int maxPoints) {
    return (points * 100)/maxPoints;
}


int convertBarPercentgToLenght(int barPrctg, int barLength) {
    return (barPrctg * barLength)/100;
}


void drawBar(int xStart, int yStart, int length, int height, int fillPrctg, MLV_Color fillColor) {
    int xList[4] = {xStart, xStart + length, xStart + length + height/2, xStart};
    int yList[4] = {yStart, yStart, yStart + height, yStart + height};
    MLV_draw_polygon(xList, yList, 4, LINE_COLOR);

    int fillLength = convertBarPercentgToLenght(fillPrctg, length);
    MLV_draw_line(xStart + fillLength, yStart, xStart + fillLength + height/2, yStart + height, LINE_COLOR);
    boundaryFill(xStart + fillLength - 1, yStart + 1, fillColor, LINE_COLOR);
}


void drawQuarterCircleBar(int xCenter, int yCenter, int radius, int fillPrctg, MLV_Color fillColor) {
    unsigned int windowWidth, windowHeight;
    MLV_get_window_size(&windowWidth, &windowHeight);

    int x, y;

    /* since we only want the bottom left quarter of the circle, we focus on the following area : */
    int xAreaStart = xCenter - radius;
    int yAreaStart = yCenter;
    int xAreaEnd   = xCenter;
    int yAreaEnd   = yCenter + radius;

    int x1LastPixel, y1LastPixel;
    int x1FillPixel, y1FillPixel;
    int nbPixelsInsideBorder = 0;

    unsigned int epsilon = windowWidth/20;

    /* Drawing pixel by pixel of the inside border*/
    for(y = yAreaStart; y <= yAreaEnd; y++) {
        for(x = xAreaStart; x <= xAreaEnd; x++) {
            /* circle equation formula */
            if(SQUARED((x - xCenter)) + SQUARED((y - yCenter)) <= SQUARED(radius) + epsilon
                && SQUARED((x - xCenter)) + SQUARED((y - yCenter)) >= SQUARED(radius) - epsilon) {
                nbPixelsInsideBorder++;
                MLV_draw_pixel(x, y, LINE_COLOR);
                x1LastPixel = x;
                y1LastPixel = y;
            }
        }
    }

    float r0 = (float)radius;
    float commonDifference =  1.0/(windowHeight / 2);

    int x2LastPixel, y2LastPixel;
    int x2FillPixel, y2FillPixel;
    int nbPixelsOutsideBorder = 0;

    /*outside border*/
    for(y = yAreaStart; y <= yAreaEnd + 100; y++) {
        for(x = xAreaStart - xAreaStart/2; x <= xAreaEnd; x++) {
            r0 += commonDifference;
            /* circle equation formula */
            if(SQUARED((x - xCenter)) + SQUARED((y - yCenter)) <= SQUARED(r0) + (1.1)*epsilon
                && SQUARED((x - xCenter)) + SQUARED((y - yCenter)) >= SQUARED(r0) - (1.1)*epsilon) {
                nbPixelsOutsideBorder++;
                MLV_draw_pixel(x, y, LINE_COLOR);
                x2LastPixel = x;
                y2LastPixel = y;
            }
        }
    }

    MLV_draw_line(x1LastPixel, y1LastPixel, x2LastPixel, y2LastPixel, LINE_COLOR);

    /* fill */
    if(fillPrctg > 5 && fillPrctg < 100) {
        int searchedPixel = convertBarPercentgToLenght(fillPrctg, nbPixelsInsideBorder);
        int pixelIndex = 0;
        int pixelFound = 0; /* flag to break out of the nested loops */

        for(y = yAreaStart; y <= yAreaEnd && !pixelFound; y++) {
            for(x = xAreaStart; x <= xAreaEnd; x++) {
                if(SQUARED((x - xCenter)) + SQUARED((y - yCenter)) <= SQUARED(radius) + epsilon
                    && SQUARED((x - xCenter)) + SQUARED((y - yCenter)) >= SQUARED(radius) - epsilon) {
                    if(searchedPixel == pixelIndex) {
                        x1FillPixel = x;
                        y1FillPixel = y;
                        printf("y : %d\n", y);
                        BREAK_NESTED_LOOPS
                    }
                    pixelIndex++;

                }
            }
        }

        searchedPixel = convertBarPercentgToLenght(fillPrctg, nbPixelsOutsideBorder);
        r0 = (float)radius;
        pixelIndex = 0;
        pixelFound = 0;

        for(y = yAreaStart; y <= yAreaEnd + 100 && !pixelFound; y++) {
            for(x = xAreaStart - 10; x <= xAreaEnd; x++) {
                r0 += commonDifference;
                if(SQUARED((x - xCenter)) + SQUARED((y - yCenter)) <= SQUARED(r0) + (1.1)*epsilon
                    && SQUARED((x - xCenter)) + SQUARED((y - yCenter)) >= SQUARED(r0) - (1.1)*epsilon) {
                    if(searchedPixel == pixelIndex) {
                        x2FillPixel = x;
                        y2FillPixel = y;
                        BREAK_NESTED_LOOPS
                    }
                    pixelIndex++;

                }
            }
        }
    MLV_draw_line(x1FillPixel, y1FillPixel, x2FillPixel, y2FillPixel, LINE_COLOR);
    if(fillPrctg >= 15)
        boundaryFill(x1FillPixel - 1, y1FillPixel + 1, fillColor, LINE_COLOR);
    else
        boundaryFill(x2FillPixel + 1, y2FillPixel - 2, fillColor, LINE_COLOR);
    }
    else if(fillPrctg == 100){
        boundaryFill(x1LastPixel - 1, y1LastPixel + 1, fillColor, LINE_COLOR);
    }
}