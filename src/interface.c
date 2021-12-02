#include "interface.h"

void createGameWindow() {
	unsigned int windowWidth, windowHeight;
	MLV_get_desktop_size(&windowWidth, &windowHeight);

	/*tu me diras de quelle taille s'affiche ta fenêtre*/

	/*MLV_create_full_screen_window_with_default_font(
		"[insérer titre qu'a d'la gueule]",
		"projet c L3S5",
		windowWidth/2,
		windowHeight/2,
		"src/files/Mouser D.otf",
		30
	);*/

	/*pour les tests c'est mieux d'avoir une petite fenêtre*/
	MLV_create_window_with_default_font(
		"[insérer titre qu'a d'la gueule]",
		"projet c L3S5",
		windowWidth/2,
		windowHeight/2,
		"src/files/Mouser D.otf",
		30
	);
	MLV_init_audio();
}


void blurBackground(MLV_Color color) {
	unsigned int windowWidth, windowHeight;
	MLV_get_window_size(&windowWidth, &windowHeight);

	MLV_draw_filled_rectangle(0, 0, windowWidth, windowHeight,addOpacity(color, 100));
}


void displayButton(int x, int y, int width, int height, int size, MLV_Color color, char *text) {
	int i;

	/*the width and height is re-calculated depending on the given size*/
	width += size;
	height += size;

	MLV_draw_filled_rectangle(x - size, y - height/2 - size, width, height, color);

	/*round corners*/
	for(i = 0; i < 2; i++) {
		MLV_draw_filled_circle(x + i*width - size, y - 1 - size, height/2, color);
	}

	MLV_draw_text(x + width/3.5, y - height/2 - size, text, MLV_COLOR_BLACK);
}


int displayYesNoPopup(int width, int height, char *text, int xMouse, int yMouse, int buttonSize[]) {
	unsigned int windowWidth, windowHeight;
	MLV_get_window_size(&windowWidth, &windowHeight);

	MLV_Color color  = MLV_COLOR_LIGHT_GREY;

	int xPopupStart  = (windowWidth - width) / 2;
	int yPopupStart  = (windowHeight - height) / 2;

	int buttonHeight = 50;
	int buttonWidth  = width/3;
	int space        = (width - 2*buttonWidth) / 3;

	int i;
	int returnValue  = -1;

	char buttonTexts[][4] = {"Yes", "No"};

	MLV_draw_filled_rectangle(xPopupStart, yPopupStart, width, height, POPUP_COLOR);
	MLV_draw_rectangle(xPopupStart, yPopupStart, width, height, MLV_COLOR_BLACK);

	MLV_draw_text(xPopupStart + space, yPopupStart + space, text, MLV_COLOR_BLACK);

	for(i = 0; i < 2; i++) {
		if(yMouse >= yPopupStart - buttonHeight/2 + height - buttonHeight - space
			&& yMouse <= yPopupStart - buttonHeight/2 + height - space
			&& xMouse >= xPopupStart + space + i*(buttonWidth + space)
			&& xMouse <= xPopupStart + space + i*(buttonWidth + space) + buttonWidth) {
			if((buttonSize[i] < MAX_BUTTON_SIZE)) {
				buttonSize[i]++;
			}
			color = MLV_COLOR_GHOSTWHITE;
			returnValue = 1 - i;
		}
		else {
			if(buttonSize[i] > 0) {
				buttonSize[i]--;
			}
			color = MLV_COLOR_LIGHT_GREY;
		}

		displayButton(
			xPopupStart + space + i*(buttonWidth + space),
			yPopupStart + height - buttonHeight - space,
			buttonWidth,
			buttonHeight,
			buttonSize[i],
			color,
			buttonTexts[i]
			);
	}
	return returnValue;
}


int yesNoPopup(char *text) {
	unsigned int windowWidth, windowHeight;
	MLV_get_window_size(&windowWidth, &windowHeight);

	int xMouse, yMouse;
	int choice = -1;
	int buttonSize[2] = {0, 0};

	int width   = windowWidth / 2;
	int height  = windowHeight / 2;

	int nbFramesEnlargmt = 4;
	int i;

	blurBackground(MLV_COLOR_GHOSTWHITE);

	for(i = 0; i < nbFramesEnlargmt; i++) {
		displayYesNoPopup(((float)i / (float)nbFramesEnlargmt)*width,
		((float)i / (float)nbFramesEnlargmt)*height, "", xMouse, yMouse, buttonSize);
		MLV_actualise_window();
		MLV_wait_milliseconds( 10 );
	}
	while(1) {
		MLV_get_mouse_position(&xMouse, &yMouse);
		choice = displayYesNoPopup(width, height, text, xMouse, yMouse, buttonSize);

		MLV_actualise_window();

		MLV_wait_milliseconds( 50 );
		if(MLV_get_mouse_button_state(MLV_BUTTON_LEFT) == MLV_PRESSED) {
			if(choice >= 0)
				break;
		}
	}
	return choice;
}


int displayMainScreen(int xMouse, int yMouse, int profileFound, int buttonSize[]) {
	MLV_clear_window(MAIN_SCREEN_BACKGROUND_COLOR);

	MLV_Color color = MLV_COLOR_MISTYROSE3;
	char buttonTexts[][10] = {"Play", "Profile", "Settings", "Leave"};
	int nbOfButtons = 4;

	unsigned int windowWidth, windowHeight;
	MLV_get_window_size(&windowWidth, &windowHeight);
	int xStart        = windowWidth - windowWidth/3;
	int yStart        = windowHeight/3;
	int margin        = 20;
	int buttonHeight  = 50;
	int buttonWidth   = windowWidth/4;
	int returnValue   = -1;
	int i;

	for(i = 0; i < nbOfButtons; i++) {
		if(yMouse >= yStart - buttonHeight/2 + i*(buttonHeight + margin)
			&& yMouse <= yStart - buttonHeight/2 + i*(buttonHeight + margin) + buttonHeight
			&& xMouse >= xStart && xMouse <= xStart + buttonWidth) {
			if(buttonSize[i] == 0 && IS_SELECTABLE) {
				playButtonSound_1();
			}
			if((buttonSize[i] < MAX_BUTTON_SIZE) && IS_SELECTABLE) {
				buttonSize[i]++;
			}
			color = MLV_COLOR_MISTYROSE1;
			returnValue = i;
		}
		else {
			if(buttonSize[i] > 0) {
				buttonSize[i]--;
			}
			color = MLV_COLOR_MISTYROSE3;
		}

		/*if the profile menu isn't available its color changes*/
		if(i == PROFILE && !profileFound)
			color = MLV_COLOR_MISTYROSE4;

		displayButton(xStart, yStart + i*(buttonHeight + margin), buttonWidth, buttonHeight, buttonSize[i], color, buttonTexts[i]);
	}
	return returnValue;
}


int mainScreen(int profileFound, int fadein) {
	unsigned int windowWidth, windowHeight;
	MLV_get_window_size(&windowWidth, &windowHeight);

	int xMouse, yMouse;
	int action = -1;
	int buttonSize[4] = {0, 0, 0, 0}; /*0 = default size, 100 = max size*/

	int fadeinTime = 20;
	int i = 0;

	while(1) {
		MLV_get_mouse_position(&xMouse, &yMouse);
		action = displayMainScreen(xMouse, yMouse, profileFound, buttonSize);

		/*fade-in*/
		if(i < fadeinTime && fadein) {
			MLV_draw_filled_rectangle(0, 0, windowWidth, windowHeight, addOpacity(MAIN_SCREEN_BACKGROUND_COLOR, -(i*(255 / fadeinTime))));
		}

		MLV_actualise_window();


		MLV_wait_milliseconds( 50 );
		if(MLV_get_mouse_button_state(MLV_BUTTON_LEFT) == MLV_PRESSED) {
			if(action >= 0 && (profileFound || (action != PROFILE)))
				break;
		}
		i++;
	}
	return action;
}


void snowdrops(unsigned int frames) {
	typedef struct {
		int x;         /*x coordonate*/
		int y;         /*y coordonate*/
		int radius;    /*in px*/
		Uint8 opacity; /*[0-255]*/
	} Snowdrop;

	/*updates the (x, y) coordonates of a Snowdrop*/
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

	/*display update*/
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

	int fadeoutTime = 50;

	MLV_Color fadeoutColor = MLV_COLOR_GHOSTWHITE;
	Uint8 fadeoutRGBA[4];
	MLV_convert_color_to_rgba(fadeoutColor, &fadeoutRGBA[0], &fadeoutRGBA[1], &fadeoutRGBA[2], &fadeoutRGBA[3]);
	fadeoutRGBA[3] = 255; /*at first, we need the color to be transparent*/
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


void displayCellBasic(Cell cell) { /*TODO*/
	switch(cell.type) {
		case WALL_OR_OBSTACLE : 
			break;
		case EMPTY : 
			break;
		case ENEMY : 
			break;
		case TREASURE : 
			break;
		case STAIR_UP : 
			break;
		case STAIR_DOWN : 
			break;
	}
}


void displayHUD(Player player) {
	/* Converts a number of points (hp/mp/exp) into a bar percentage */
	int convertPointsToBarPercentg(int points, int maxPoints) {
		return (points * 100)/maxPoints;
	}

	/* Converts a bar percentage into a length depending on a bar length (px) */
	int convertBarPercentgToLenght(int barPrctg, int barLength) {
		return (barPrctg * barLength)/100;
	}

	/* Draws a bar filled at fillPrctg % */
	void drawBar(int xStart, int yStart, int length, int height, int fillPrctg, MLV_Color fillColor) {
		int xList[4] = {xStart, xStart + length, xStart + length + height/2, xStart};
		int yList[4] = {yStart, yStart, yStart + height, yStart + height};
		MLV_draw_polygon(xList, yList, 4, LINE_COLOR);

		int fillLength = convertBarPercentgToLenght(fillPrctg, length);
		MLV_draw_line(xStart + fillLength, yStart, xStart + fillLength + height/2, yStart + height, LINE_COLOR);
		/* ADD FLOOD FILL HERE */
	}

	/* Draws a quarter circle bar of center (xCenter, yCenter) and radius radius filled at fillPrctg % */
	void drawQuarterCircleBar(int xCenter, int yCenter, int radius, int fillPrctg, MLV_Color fillColor) {
		int x, y;

		/* since we only want the bottom left quarter of the circle, we focus on the following area : */
		int xAreaStart = xCenter - radius;
		int yAreaStart = yCenter;
		int xAreaEnd   = xCenter;
		int yAreaEnd   = yCenter + radius;

		int x1LastPixel, y1LastPixel;
		int x1FillPixel, y1FillPixel;
		int nbPixelsInsideBorder = 0;

		unsigned int epsilon = 50;

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

		float increasingRadius = (float)radius;

		int x2LastPixel, y2LastPixel;
		int x2FillPixel, y2FillPixel;
		int nbPixelsOutsideBorder = 0;

		/*outside border*/
		for(y = yAreaStart; y <= yAreaEnd + 100; y++) {
			for(x = xAreaStart; x <= xAreaEnd; x++) {
				increasingRadius += 1.0/300;
				/* circle equation formula */
				if(SQUARED((x - xCenter)) + SQUARED((y - yCenter)) <= SQUARED(increasingRadius) + (2)*epsilon
					&& SQUARED((x - xCenter)) + SQUARED((y - yCenter)) >= SQUARED(increasingRadius) - (2)*epsilon) {
					nbPixelsOutsideBorder++;
					MLV_draw_pixel(x, y, LINE_COLOR);
					x2LastPixel = x;
					y2LastPixel = y;
				}
			}
		}

		MLV_draw_line(x1LastPixel, y1LastPixel, x2LastPixel, y2LastPixel, LINE_COLOR);

		/* fill */
		int searchedPixel = convertBarPercentgToLenght(fillPrctg, nbPixelsInsideBorder);
		int pixelIndex = 0;
		int pixelFound = 0; /* flag to break out of the nested loops */

		for(y = yAreaStart; y <= yAreaEnd && !pixelFound; y++) {
			for(x = xAreaStart; x <= xAreaEnd; x++) {
				if(SQUARED((x - xCenter)) + SQUARED((y - yCenter)) <= SQUARED(radius) + epsilon
					&& SQUARED((x - xCenter)) + SQUARED((y - yCenter)) >= SQUARED(radius) - epsilon) {
					pixelIndex++;
					if(searchedPixel == pixelIndex) {
						x1FillPixel = x;
						y1FillPixel = y;
						BREAK_NESTED_LOOPS
					}
				}
			}
		}

		searchedPixel = convertBarPercentgToLenght(fillPrctg, nbPixelsOutsideBorder);
		increasingRadius = (float)radius;
		pixelIndex = 0;
		pixelFound = 0;

		for(y = yAreaStart; y <= yAreaEnd + 100 && !pixelFound; y++) {
			for(x = xAreaStart; x <= xAreaEnd; x++) {
				increasingRadius += 1.0/300;
				if(SQUARED((x - xCenter)) + SQUARED((y - yCenter)) <= SQUARED(increasingRadius) + (2)*epsilon
					&& SQUARED((x - xCenter)) + SQUARED((y - yCenter)) >= SQUARED(increasingRadius) - (2)*epsilon) {
					pixelIndex++;
					if(searchedPixel == pixelIndex) {
						x2FillPixel = x;
						y2FillPixel = y;
						BREAK_NESTED_LOOPS
					}
				}
			}
		}
		MLV_draw_line(x1FillPixel, y1FillPixel, x2FillPixel, y2FillPixel, LINE_COLOR);
		/* ADD FLOOD FILL HERE */
	}

	unsigned int windowWidth, windowHeight;
	MLV_get_window_size(&windowWidth, &windowHeight);

	int margin        = 20;
	int circleRadius  = windowWidth/20;
	int xCircle       = margin + circleRadius;
	int yCircle       = margin + circleRadius;

	int HPBarHeight   = circleRadius/2;
	int HPBarLength   = windowWidth/6;
	int xHPBar        = margin + (1.9)*circleRadius;
	int yHPBar        = margin + circleRadius - HPBarHeight;
	
	int separation    = 2;

	int MPBarHeight   = HPBarHeight/2;
	int MPBarLength   = HPBarLength + 10;
	int xMPBar        = xHPBar;
	int yMPBar        = yHPBar + HPBarHeight + separation;

	/* HP Bar */
	drawBar(xHPBar, yHPBar, HPBarLength, HPBarHeight, 50, HP_BAR_COLOR);
	/* MP Bar */
	drawBar(xMPBar, yMPBar, MPBarLength, MPBarHeight, 80, MP_BAR_COLOR);
	/* Character status */
	MLV_draw_filled_circle(xCircle, yCircle, circleRadius, LINE_COLOR);
	/* Exp bar */
	drawQuarterCircleBar(xCircle, yCircle, circleRadius + 5, 70, EXP_BAR_COLOR);
	
	MLV_actualise_window();
}

void exitGame() {
	MLV_free_window();
}