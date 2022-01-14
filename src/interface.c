#include "interface.h"

void createGameWindow() {
    unsigned int windowWidth, windowHeight;
    MLV_get_desktop_size(&windowWidth, &windowHeight);

    /*tu me diras de quelle taille s'affiche ta fenêtre*/

    /*MLV_create_full_screen_window_with_default_font(
        "[insérer titre qu'a d'la gueule]",
        "projet c L3S5",
        windowWidth,
        windowHeight,
        "src/files/Mouser D.otf",
        30
    );*/

    /*pour les tests c'est mieux d'avoir une petite fenêtre*/
    /*MLV_create_window_with_default_font(
        "TEST",
        "projet c L3S5",
        windowWidth/2,
        windowHeight/2,
        "src/files/Mouser D.otf",
        30
    );*/

        MLV_create_window_with_default_font(
        "TEST",
        "projet c L3S5",
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        "src/files/Mouser D.otf",
        30
    );

    MLV_init_audio();
}


void blurBackground(MLV_Color color) {
    unsigned int windowWidth, windowHeight;
    MLV_get_window_size(&windowWidth, &windowHeight);

    MLV_draw_filled_rectangle(0, 0, windowWidth, windowHeight,addOpacity(color, 150));
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


int displayMainScreen(int xMouse, int yMouse, int profileFound, int buttonSize[], MLV_Image *illus) {
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

    MLV_draw_image(illus, 0, 0);


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

    MLV_Image *illus = MLV_load_image("src/files/illustration_1.png");
    int imgWidth, imgHeight;
    MLV_get_image_size(illus, &imgWidth, &imgHeight);
    float ratio = imgHeight > windowHeight ? windowHeight/(float)imgHeight : (float)imgHeight/windowHeight;
    MLV_resize_image_with_proportions(illus, imgWidth*ratio, imgHeight*ratio);

    int xMouse, yMouse;
    int action = -1;
    int buttonSize[4] = {0, 0, 0, 0}; /*0 = default size, 100 = max size*/

    int fadeinTime = 20;
    int i = 0;

    while(1) {
        MLV_get_mouse_position(&xMouse, &yMouse);
        action = displayMainScreen(xMouse, yMouse, profileFound, buttonSize, illus);

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


MLV_Image *wallSprite(Cell cell, Stage stage) {
	int wallLeft  = 0;
	int wallRight = 0;
	int wallUp    = 0;
	int wallDown  = 0;

    int i, j;

	/* getting surrounding cells informations */
	for(i = cell.coords.x - 1; i <= cell.coords.x + 1; i += 2) {
		if(stage.cells[cell.coords.y][i].type == WALL) {
			if(i == cell.coords.x - 1)
				wallLeft = 1;
			if(i == cell.coords.x + 1)
				wallRight = 1;
		}
	}
	
	for(j = cell.coords.y - 1; j <= cell.coords.y + 1; j += 2) {
		if(stage.cells[cell.coords.y][i].type == WALL) {
			if(j == cell.coords.y - 1)
				wallUp = 1;
			if(j == cell.coords.y + 1)
				wallDown = 1;
		}
	}
	/* choosing the right sprite */

	/* 1 surrounding wall */
	if(wallLeft && !wallRight && !wallUp && !wallDown) /* wall left */
		return MLV_load_image("src/files/wall_1.png");

	if(!wallLeft && wallRight && !wallUp && !wallDown) /* wall right */
		return MLV_load_image("src/files/wall_1.png");

	if(!wallLeft && !wallRight && wallUp && !wallDown) /* wall down */
		return MLV_load_image("src/files/wall_1.png");

	if(!wallLeft && !wallRight && !wallUp && wallDown) /* wall up*/
		return MLV_load_image("src/files/wall_1.png");

	/* 2 surrounding walls*/
	if(wallLeft && wallRight && !wallUp && !wallDown) /* wall left and right */
		return MLV_load_image("src/files/wall_1.png");

	if(wallLeft && !wallRight && wallUp && !wallDown) /* wall left and up */
		return MLV_load_image("src/files/wall_1.png");

	if(wallLeft && !wallRight && !wallUp && wallDown) /* wall left and down */
		return MLV_load_image("src/files/wall_1.png");

	if(!wallLeft && wallRight && !wallUp && wallDown) /* wall right and down */
		return MLV_load_image("src/files/wall_1.png");

	if(!wallLeft && wallRight && wallUp && !wallDown) /* wall right and up */
		return MLV_load_image("src/files/wall_1.png");

	if(!wallLeft && !wallRight && wallUp && wallDown) /* wall up and down */
		return MLV_load_image("src/files/wall_1.png");

	/* 3 surrounding walls */
	if(wallLeft && wallRight && wallUp && !wallDown)
		return MLV_load_image("src/files/wall_1.png"); /* wall left, right and up */

	if(wallLeft && wallRight && !wallUp && wallDown)
		return MLV_load_image("src/files/wall_1.png"); /* wall left, right and down */

    if(wallLeft && !wallRight && wallUp && wallDown)
        return MLV_load_image("src/files/wall_1.png"); /* wall left, up and down */

    if(!wallLeft && wallRight && wallUp && wallDown)
        return MLV_load_image("src/files/wall_1.png"); /* wall right, up and down */

	/* 4 surrounding walls */
    else
        return MLV_load_image("src/files/wall_1.png");
}


void displayCellBasic(Cell cell) {
    int x = (cell.coords.x) * CELL_SIZE;
    int y = (cell.coords.y) * CELL_SIZE;
    Cell tmp = cell;
    /* checking the cell type */
    switch(cell.type) {
        case WALL : 
            MLV_draw_filled_rectangle(x, y, CELL_SIZE, CELL_SIZE, WALL_COLOR_BAS);
            break;
        case ROOM : 
            MLV_draw_filled_rectangle(x, y, CELL_SIZE, CELL_SIZE, EMPTY_COLOR_BAS);
            break;
        case ENEMY : 
            tmp.type = ROOM;
        	displayCellSprite(tmp); /* floor display */
            MLV_draw_filled_circle(x + CELL_SIZE/2, y + CELL_SIZE/2, CELL_SIZE/3, ENEMY_COLOR_BAS);
            break;
        case TREASURE : 
            MLV_draw_filled_rectangle(x, y, CELL_SIZE, CELL_SIZE, TREASURE_COLOR_BAS);
            break;
        case STAIR_UP :
            MLV_draw_filled_rectangle(x, y, CELL_SIZE, CELL_SIZE, STAIR_UP_COLOR_BAS);
            break;
        case STAIR_DOWN :
            MLV_draw_filled_rectangle(x, y, CELL_SIZE, CELL_SIZE, STAIR_DOWN_COLOR_BAS);
            break;
        default :
            MLV_draw_filled_rectangle(x, y, CELL_SIZE, CELL_SIZE, OUT_OF_MAP_COLOR_BAS);
    }
}


int displayCellSprite(Cell cell) {
    int x = (cell.coords.x) * CELL_SIZE;
    int y = (cell.coords.y) * CELL_SIZE;
    int imgWidth, imgHeight;
    Cell tmp = cell;
    float ratio;
    MLV_Image *sprite;

    /* checking the cell type to load the sprite */
    switch(cell.type) {
        case WALL : 
        	displayCellBasic(cell);
            return 1;
        case ROOM : 
        	if((cell.coords.x + cell.coords.y)%3 == 0)
        		sprite = MLV_load_image("src/files/floor_1.png");
        	else {
        		if((cell.coords.x + cell.coords.y)%3 == 1)
        			sprite = MLV_load_image("src/files/floor_2.png");
        		else
        			sprite = MLV_load_image("src/files/floor_3.png");
        	}
            break;
        case ENEMY : 
        	tmp.type = ROOM;
        	displayCellSprite(tmp); /* floor display */
            MLV_draw_filled_circle(x + CELL_SIZE/2, y + CELL_SIZE/2, CELL_SIZE/3, ENEMY_COLOR_BAS); /* TODO */
            return 1;
        case TREASURE : 
            displayCellBasic(cell); /* TODO */
            return 1;
            break;
        case STAIR_UP :
            sprite = MLV_load_image("src/files/stairup.png");
            break;
        case STAIR_DOWN :
            MLV_draw_filled_rectangle(x, y, CELL_SIZE, CELL_SIZE, MLV_COLOR_GRAY1);
            sprite = MLV_load_image("src/files/stairup.png");
            break;
        default : /* out of map */
            displayCellBasic(cell);
            return 0; /* nothing to display */

        
    }
    /* resizing, adjusting coords and drawing */
    MLV_get_image_size(sprite, &imgWidth, &imgHeight);
    ratio = imgWidth > CELL_SIZE ? CELL_SIZE/(float)imgWidth : (float)imgWidth/CELL_SIZE;
    MLV_resize_image_with_proportions(sprite, imgWidth*ratio + 1, imgHeight*ratio + 1);

    if(cell.type == STAIR_UP) {
        y = y + CELL_SIZE - imgHeight*ratio;
    }

    MLV_draw_image(sprite, x, y);
    return 1;
}


Point topLeftCellOnScreen(Point playerCoords) {
    return (Point){playerCoords.x - SCREEN_WIDTH/2, playerCoords.y - SCREEN_HEIGHT/2};
}


MLV_Color playerColor(Player player) {
    if(player.status == MAGICAL_ATTCK)
        return MAGICAL_MODE_COLOR_BAS;
    return PHYSICAL_MODE_COLOR_BAS; /* default */
}


void displayPlayerBasic(Player player) {
    MLV_draw_filled_circle(
        WINDOW_WIDTH/2,
        WINDOW_HEIGHT/2,
        CELL_SIZE/3,
        playerColor(player)
        );
}


void displayPlayerSprite(Player player) {
    displayPlayerBasic(player); /* TODO */
}


void displayStage(Stage stage, Player player, enum mode mode) {
    Point tlc = topLeftCellOnScreen(player.coords);
    int i, j;
    Cell tmp;
    for(i = tlc.x; i < tlc.x + SCREEN_WIDTH; i++) {
        for(j = tlc.y; j < tlc.y + SCREEN_HEIGHT; j++) {
            /* tmp indexes for display to be centered on the player */
            tmp = stage.cells[j][i];

            tmp.coords.x = i - tlc.x;
            tmp.coords.y = j - tlc.y;
            /* out of map */
            if(i < 0 || j < 0 || 
               i > LEVEL_WIDTH || j > LEVEL_HEIGHT) {
                tmp.type = OOM;
            }

            if(mode == WITH_SPRITES)
                displayCellSprite(tmp);
            else /* BASIC */
                displayCellBasic(tmp);
        }
    }

    /* displaying the player : */
    if(mode == WITH_SPRITES)
        displayPlayerSprite(player);
    else
        displayPlayerBasic(player);

    MLV_actualise_window();
}


void displayAtkButtons() {
    unsigned int windowWidth, windowHeight;
    MLV_get_window_size(&windowWidth, &windowHeight);

    int bttnSize   = windowWidth/11;
    int margin     = bttnSize/4;
    int borderSize = 5;

    int i;

    Point physicalBttnCoords, magicalBttnCoords;
    physicalBttnCoords.x = windowWidth - (margin + bttnSize);
    physicalBttnCoords.y = windowHeight - (margin + bttnSize);
    magicalBttnCoords.x  = windowWidth - 2*(margin + bttnSize);
    magicalBttnCoords.y  = physicalBttnCoords.y;

    /* Physical attack button */
    MLV_draw_filled_rectangle(
        physicalBttnCoords.x,
        physicalBttnCoords.y,
        bttnSize,
        bttnSize,
        PHYS_ATK_BUTTON_COLOR
        );

    /* Basic display */
    MLV_draw_text(
        physicalBttnCoords.x,
        physicalBttnCoords.y + margin,
        "ATTCK",
        MLV_COLOR_WHITE
        );

    for(i = 0; i < borderSize; i++) {
        MLV_draw_rectangle(
            physicalBttnCoords.x + i,
            physicalBttnCoords.y + i,
            bttnSize - 2*i,
            bttnSize - 2*i,
            MLV_COLOR_WHITE
            );
    }

    /* Magical attack button */
    MLV_draw_filled_rectangle(
        magicalBttnCoords.x,
        magicalBttnCoords.y,
        bttnSize,
        bttnSize,
        MAGC_ATK_BUTTON_COLOR
        );

    for(i = 0; i < borderSize; i++) {
        MLV_draw_rectangle(
            magicalBttnCoords.x + i,
            magicalBttnCoords.y + i,
            bttnSize - 2*i,
            bttnSize - 2*i,
            MLV_COLOR_WHITE
            );
    }

    /* Basic display */
    MLV_draw_text(
        magicalBttnCoords.x,
        magicalBttnCoords.y + margin,
        "MAGIC",
        MLV_COLOR_WHITE
        );

    MLV_actualise_window();
}

/*
MLV_Image *itemSprite(Loot loot) {
}*/


void displayItemBasic(Loot loot, Point coordsOnScreen, int itemBoxSize) {

    switch( loot.type ) {
        case EQUIPMENT :
            MLV_draw_filled_rectangle(
                coordsOnScreen.x,
                coordsOnScreen.y,
                itemBoxSize,
                itemBoxSize,
                ITEM_BOX_COLOR
                );
            MLV_draw_text(
                coordsOnScreen.x,
                coordsOnScreen.y,
                "EQP",
                MLV_COLOR_WHITE
                );
            break;

        case CONSUMMABLE :
            MLV_draw_filled_rectangle(
                coordsOnScreen.x,
                coordsOnScreen.y,
                itemBoxSize,
                itemBoxSize,
                ITEM_BOX_COLOR
                );

            MLV_draw_text(
                coordsOnScreen.x,
                coordsOnScreen.y,
                "CSM",
                MLV_COLOR_WHITE
                );
            break;

        default :
            MLV_draw_filled_rectangle(
                coordsOnScreen.x,
                coordsOnScreen.y,
                itemBoxSize,
                itemBoxSize,
                EMPTY_BOX_COLOR
                );
            break;
    }
}


void displayItemSprite(Loot loot, Point coordsOnScreen, int itemBoxSize) {
    /* TODO */
}


void displayInventory(Loot inventory[], enum mode mode, int selection) {
    unsigned int windowWidth, windowHeight;
    MLV_get_window_size(&windowWidth, &windowHeight);

    /* note for me : MAX_INVENTORY exists and is equals to 9 */
    int menuWidth   = windowWidth/3;
    int margin      = menuWidth/100;
    int itemPerRow  = 3;
    int itemBoxSize = (menuWidth - (itemPerRow + 1)*margin)/itemPerRow;

    int i, j;
    Point boxCoords;

    MLV_draw_filled_rectangle(
        0,
        0,
        menuWidth,
        margin + ((MAX_INVENTORY)/itemPerRow)*(itemBoxSize + margin),
        INVENTORY_MENU_COLOR
        );

    /* iventory display */
    for(i = 0; i < MAX_INVENTORY; i++) {
        boxCoords.x = margin + (i%itemPerRow)*(itemBoxSize + margin);
        boxCoords.y = margin + (i/itemPerRow)*(itemBoxSize + margin);

        if(mode == WITH_SPRITES) {
            displayItemSprite(inventory[i], boxCoords, itemBoxSize);
        }
        else /* basic display */
            displayItemBasic(inventory[i], boxCoords, itemBoxSize);

        if(i == selection) {
            for(j = 0; j < 5; j++) {
                MLV_draw_rectangle(
                    boxCoords.x + j,
                    boxCoords.y + j,
                    itemBoxSize - 2*j,
                    itemBoxSize - 2*j,
                    MLV_COLOR_WHITE
                    );
            }
        }
    }
}


char *itemName(Loot item) {
    switch( item.type ) {
        case EQUIPMENT :
            switch( item.equipment.type ) {
                case ARMOR :
                    return "Armor";
                case WEAPON : 
                    return "Weapon";
                case WAND :
                    return "Wand";
                default :
                    return "";
            }
        case CONSUMMABLE :
            switch( item.consummable ) {
                case HEAL :
                    return "Heal potion";
                case MAGIC :
                    return "Magic battery";
                case REGEN :
                    return "Special potion";
                case LEARNING :
                    return "Exp potion";
                case PRECISION :
                    return "Special lens";
                default :
                    return "";
            }
        default :
            return "";
    }
}

void displayItemInfo(Loot item, Point start, int boxWidth, int boxHeight) {
    /*MLV_draw_filled_rectangle(start.x, start.y, boxWidth, boxHeight, INVENTORY_MENU_COLOR);*/
    MLV_draw_text(start.x + 20, start.y, "%s", MLV_COLOR_WHITE, itemName(item));
    if(item.type == EQUIPMENT) {
        MLV_draw_text(
            start.x + boxWidth/2,
            start.y,
            "(class : %d)",
            MLV_COLOR_WHITE,
            item.equipment.quality
            );
    }

    MLV_change_default_font("src/files/Mouser D.otf", 20);
    if(item.type != NO_ITEM)
        MLV_draw_text(start.x + 20, start.y + 50, "Description :", MLV_COLOR_WHITE);

    switch( item.type ) {
        case EQUIPMENT :
            switch( item.equipment.type ) {
                case ARMOR :
                    MLV_draw_text(
                        start.x + 30,
                        start.y + 100,
                        "Increase your defense.",
                        MLV_COLOR_WHITE,
                        item.equipment.quality
                        );
                    break;

                case WEAPON : 
                    MLV_draw_text(
                        start.x + 30,
                        start.y + 100,
                        "Increase your attack.",
                        MLV_COLOR_WHITE,
                        item.equipment.quality
                        );
                    break;

                case WAND :
                    MLV_draw_text(
                        start.x + 30,
                        start.y + 100,
                        "Increase your magic",
                        MLV_COLOR_WHITE,
                        item.equipment.quality
                        );
                    MLV_draw_text(
                        start.x + 30,
                        start.y + 120,
                        "power.",
                        MLV_COLOR_WHITE,
                        item.equipment.quality
                        );
                    break;

                default :
                    break;
            }
            break;

        case CONSUMMABLE :
            switch( item.consummable ) {
                case HEAL :
                    MLV_draw_text(
                        start.x + 30,
                        start.y + 100,
                        "Instantly restores 10%% of",
                        MLV_COLOR_WHITE,
                        item.equipment.quality
                        );
                    MLV_draw_text(
                        start.x + 30,
                        start.y + 120,
                        "your HP bar.",
                        MLV_COLOR_WHITE,
                        item.equipment.quality
                        );
                    break;

                case MAGIC :
                    MLV_draw_text(
                        start.x + 30,
                        start.y + 100,
                        "Instantly restores 10%% of",
                        MLV_COLOR_WHITE,
                        item.equipment.quality
                        );
                    MLV_draw_text(
                        start.x + 30,
                        start.y + 120,
                        "your MP bar.",
                        MLV_COLOR_WHITE,
                        item.equipment.quality
                        );
                    break;

                case REGEN :
                    MLV_draw_text(
                        start.x + 30,
                        start.y + 100,
                        "Restores 20 HP and 10 MP",
                        MLV_COLOR_WHITE,
                        item.equipment.quality
                        );
                    MLV_draw_text(
                        start.x + 30,
                        start.y + 120,
                        "every 3 turn during 30 turns.",
                        MLV_COLOR_WHITE,
                        item.equipment.quality
                        );
                    break;

                case LEARNING :
                    MLV_draw_text(
                        start.x + 30,
                        start.y + 100,
                        "Boost your gained exp by",
                        MLV_COLOR_WHITE,
                        item.equipment.quality
                        );
                    MLV_draw_text(
                        start.x + 30,
                        start.y + 120,
                        "30%% for the next 30 turns.",
                        MLV_COLOR_WHITE,
                        item.equipment.quality
                        );
                    break;

                case PRECISION :
                    MLV_draw_text(
                        start.x + 30,
                        start.y + 100,
                        "Boost your critical rate",
                        MLV_COLOR_WHITE,
                        item.equipment.quality
                        );
                    MLV_draw_text(
                        start.x + 30,
                        start.y + 120,
                        "by 10%% for the next 30",
                        MLV_COLOR_WHITE,
                        item.equipment.quality
                        );
                    MLV_draw_text(
                        start.x + 30,
                        start.y + 140,
                        "turns.",
                        MLV_COLOR_WHITE,
                        item.equipment.quality
                        );
                    break;

                default :
                    break;
            }
            break;

        default :
            break;
    }
    MLV_change_default_font("src/files/Mouser D.otf", 30);
}

int inventory(Loot inventory[], enum mode mode, int* discard) {
    unsigned int windowWidth, windowHeight;
    MLV_get_window_size(&windowWidth, &windowHeight);

    MLV_Keyboard_button sym   = MLV_KEYBOARD_NONE;
    MLV_Keyboard_modifier mod = MLV_KEYBOARD_KMOD_NONE;
    MLV_Input_box *input_box  = NULL;
    char* texte               = NULL;
    MLV_Button_state state;
    int xMouse, yMouse;

    int yIndex;
    int xIndex;
    int itemIndex = 0;
    int selection = -1;
    int canSelect = 0;

    int menuWidth     = windowWidth/3;
    int margin        = menuWidth/100;
    int itemPerRow    = 3;
    int itemBoxSize   = (menuWidth - (itemPerRow + 1)*margin)/itemPerRow;
    int infoBoxWidth  = menuWidth;
    int infoBoxHeight = windowHeight/2;
    int xButton       = menuWidth/5;
    int yButton       = windowHeight - windowHeight/8;
    int buttonHeight  = 50;
    int buttonWidth   = menuWidth - 4*xButton;
    int buttonSize    = 0;
    int mouseOnButton = 0;
    int xButton2      = xButton + 2*buttonWidth;
    int buttonSize2   = 0;
    int mouseOnButton2 = 0;
    char *buttonText;

    Point infoBox;
    infoBox.x = 0;
    infoBox.y = windowHeight - infoBoxHeight;

    blurBackground(MLV_COLOR_GRAY1);

    int i;
    int frames = 5;

    blurBackground(MLV_COLOR_GRAY1);
    for(i = 0; i < frames; i++) {
        MLV_draw_filled_rectangle(0, 0, ((float)i/(float)frames)*menuWidth, windowHeight, INVENTORY_MENU_COLOR);
        MLV_wait_milliseconds( 10 );
        MLV_actualise_window();
    }

    MLV_draw_filled_rectangle(0, 0, menuWidth, windowHeight, INVENTORY_MENU_COLOR);

    /* display and choose */
    MLV_draw_text(
        infoBox.x + 90,
        infoBox.y + infoBoxHeight/2 - 40,
        "Select an object",
        EMPTY_BOX_COLOR);
    MLV_draw_text(
        infoBox.x + 30,
        infoBox.y + infoBoxHeight/2,
        "to display informations",
        EMPTY_BOX_COLOR);


    /* loops until the user closes the inventory */
    while(1) {
        /* getting the event */
        MLV_Event ev = MLV_get_event( 
                &sym, &mod, NULL,
                &texte, &input_box,
                &xMouse, &yMouse, NULL,
                &state
        );

        displayInventory(inventory, mode, selection);
        MLV_actualise_window();

        if(xMouse > xButton && xMouse < xButton + buttonWidth &&
            yMouse > yButton - buttonHeight/2 && yMouse < yButton + buttonHeight/2) {

            mouseOnButton = 1;
            if(buttonSize < MAX_BUTTON_SIZE) {
                MLV_wait_milliseconds( 50 );
                buttonSize++;
            }
        }
        else {
            mouseOnButton = 0;
            if(buttonSize > 0) {
                MLV_wait_milliseconds( 50 );
                buttonSize--;
                MLV_draw_filled_rectangle(
                    0,
                    yButton - 100,
                    menuWidth,
                    windowHeight - yButton + 100,
                    INVENTORY_MENU_COLOR
                    );
            }
        }
        /* Second button */
        if(xMouse > xButton2 && xMouse < xButton2 + buttonWidth &&
            yMouse > yButton - buttonHeight/2 && yMouse < yButton + buttonHeight/2) {

            mouseOnButton2 = 1;
            if(buttonSize2 < MAX_BUTTON_SIZE) {
                MLV_wait_milliseconds( 50 );
                buttonSize2++;
            }
        }
        else {
            mouseOnButton2 = 0;
            if(buttonSize2 > 0) {
                MLV_wait_milliseconds( 50 );
                buttonSize2--;
                MLV_draw_filled_rectangle(
                    0,
                    yButton - 100,
                    menuWidth,
                    windowHeight - yButton + 100,
                    INVENTORY_MENU_COLOR
                    );
            }
        }

        if(canSelect) {
            if(inventory[itemIndex].type == EQUIPMENT)
                buttonText = "EQUIP";
            
            else {
                if(inventory[itemIndex].type == CONSUMMABLE)
                    buttonText = "USE";
                else
                    buttonText = "";
            }
            displayButton(
                xButton,
                yButton,
                buttonWidth,
                buttonHeight,
                buttonSize,
                MLV_COLOR_GHOSTWHITE,
                buttonText);
            displayButton(
                xButton2,
                yButton,
                buttonWidth,
                buttonHeight,
                buttonSize2,
                MLV_COLOR_GHOSTWHITE,
                "DROP");
        }

        switch(ev) {
            case MLV_KEY :
                switch( sym) {
                    case MLV_KEYBOARD_ESCAPE :
                        printf("ESC keyboard\n");
                        return -1;
                    default :
                        break;
                }
                break;

            case MLV_MOUSE_BUTTON :
                if(state == MLV_PRESSED) {
                    /* item selection */
                    if(xMouse > margin
                        && xMouse < menuWidth - margin
                        && yMouse > margin
                        && yMouse < margin + (MAX_INVENTORY/itemPerRow)*(itemBoxSize + margin))
                    {
                        yIndex = (yMouse - ((yMouse % (MAX_INVENTORY/itemPerRow))*margin)) / itemBoxSize;
                        xIndex = (xMouse - ((xMouse % itemPerRow)*margin)) / itemBoxSize;
                        itemIndex = yIndex*itemPerRow + xIndex;
                        selection = itemIndex;
                        MLV_draw_filled_rectangle(0, 0, menuWidth, windowHeight, INVENTORY_MENU_COLOR);
                        displayItemInfo(inventory[itemIndex], infoBox, infoBoxWidth, infoBoxHeight);
                        if(inventory[itemIndex].type != NO_ITEM)
                            canSelect = 1;
                        else
                            canSelect = 0;
                    }

                    /* click on button to use item */
                    if(mouseOnButton){
                        *discard = 0;
                        return itemIndex; /* end of function */
                    }
                    /* click on 2nd button to discard item */
                    if(mouseOnButton2){
                        *discard = 1;
                        return itemIndex; /* end of function */
                    }
                }


                break;
            case MLV_NONE :
                break;
            default :
                break;
        }
    }
    return -1;
}

Loot chooseBetweenTwo(Loot item_a, Loot item_b) {
    unsigned int windowWidth, windowHeight;
    MLV_get_window_size(&windowWidth, &windowHeight);

    int x, y;
    int i;

    Point aStart, bStart, aInfoStart, bInfoStart;
    int itemBoxSize = windowWidth/6;
    aStart.x        = windowWidth/3.5;
    aStart.y        = windowHeight/4;
    bStart.x        = windowWidth - itemBoxSize - aStart.x;
    bStart.y        = aStart.y;
    aInfoStart.x    = aStart.x - 20;
    aInfoStart.y    = aStart.y + itemBoxSize + 50;
    bInfoStart.x    = bStart.x - 20;
    bInfoStart.y    = bStart.y + itemBoxSize + 50;

    Loot chosenItem;

    blurBackground(OUT_OF_MAP_COLOR_BAS);

    MLV_draw_text(windowWidth/2.35, windowHeight/8, "You found", MLV_COLOR_WHITE);

    

    displayItemInfo(item_a, aInfoStart, itemBoxSize + 70, 2*itemBoxSize);
    displayItemInfo(item_b, bInfoStart, itemBoxSize + 70, 2*itemBoxSize);

    while(1) {
        MLV_get_mouse_position(&x, &y);
        /* A item */
        if(x > aStart.x && x < aStart.x + itemBoxSize &&
            y > aStart.y && y < aStart.y + itemBoxSize ) {
            for(i = 0; i < 5; i++) {
                displayItemBasic(item_a, aStart, itemBoxSize);
                MLV_draw_rectangle(
                    aStart.x + i,
                    aStart.y + i,
                    itemBoxSize - 2*i,
                    itemBoxSize - 2*i,
                    MLV_COLOR_WHITE
                    );
            }
            if(MLV_get_mouse_button_state(MLV_BUTTON_LEFT) == MLV_PRESSED) {
                chosenItem = item_a;
                break;
            }
        }
        else
            displayItemBasic(item_a, aStart, itemBoxSize);

        /* B item */

        if(x > bStart.x && x < bStart.x + itemBoxSize &&
            y > bStart.y && y < bStart.y + itemBoxSize) {
            for(i = 0; i < 5; i++) {
                displayItemBasic(item_b, bStart, itemBoxSize);
                MLV_draw_rectangle(
                    bStart.x + i,
                    bStart.y + i,
                    itemBoxSize - 2*i,
                    itemBoxSize - 2*i,
                    MLV_COLOR_WHITE
                    );
            }
            if(MLV_get_mouse_button_state(MLV_BUTTON_LEFT) == MLV_PRESSED) {
                chosenItem = item_b;
                break;
            }
        }
        else 
            displayItemBasic(item_b, bStart, itemBoxSize);

        MLV_actualise_window();

    }
    printf("chosen\n");
    return chosenItem;
}

void displayHUD(Player player) {    
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
    int HPBarPrctg = convertPointsToBarPercentg(player.stat.current.hp, standardMaxHP(player));
    drawBar(xHPBar, yHPBar, HPBarLength, HPBarHeight, HPBarPrctg, HP_BAR_COLOR);
    /* MP Bar */
    int MPBarPrctg = convertPointsToBarPercentg(player.stat.current.mp, standardMaxMP(player));
    drawBar(xMPBar, yMPBar, MPBarLength, MPBarHeight, MPBarPrctg, MP_BAR_COLOR);
    /* Character status */
    MLV_draw_filled_circle(xCircle, yCircle, circleRadius, MLV_COLOR_GHOSTWHITE);
    MLV_draw_circle(xCircle, yCircle, circleRadius, LINE_COLOR);
    /* Exp bar */
    int expBarPrctg = convertPointsToBarPercentg(player.stat.current.exp, standardExpToNextlevel(player));
    drawQuarterCircleBar(xCircle, yCircle, circleRadius + 5, expBarPrctg, EXP_BAR_COLOR);
    
    MLV_actualise_window();
}


void displayStat(Point aStart, int itemBoxSize, char *statName, int statNumber){
    MLV_draw_filled_rectangle(aStart.x, aStart.y, itemBoxSize, itemBoxSize, ITEM_BOX_COLOR);
    MLV_draw_text( aStart.x, aStart.y, statName, MLV_COLOR_WHITE);
    MLV_draw_text( aStart.x, aStart.y + (itemBoxSize/2) , "%d", MLV_COLOR_WHITE, statNumber);
}


int selectStat(Point aStart, int x, int y, int itemBoxSize,char *statName, int statNumber){
    int i;

    if(x > aStart.x && x < aStart.x + itemBoxSize &&
        y > aStart.y && y < aStart.y + itemBoxSize ) {
        for(i = 0; i < 5; i++) {
            displayStat(aStart, itemBoxSize, statName, statNumber);
            MLV_draw_rectangle(
                aStart.x + i,
                aStart.y + i,
                itemBoxSize - 2*i,
                itemBoxSize - 2*i,
                MLV_COLOR_WHITE
                );
        }
        if(MLV_get_mouse_button_state(MLV_BUTTON_LEFT) == MLV_PRESSED) {
            return 0;
        }
    }
    displayStat(aStart, itemBoxSize, statName, statNumber);
    return 1;
}

void applyStatPoint(Player *player){
    unsigned int windowWidth, windowHeight;
    MLV_get_window_size(&windowWidth, &windowHeight);

    int itemBoxSize = windowWidth/6;

    Point aStart, bStart, cStart;

    int x, y;

    aStart.x        = windowWidth/1.5;
    aStart.y        = windowHeight/3;
    bStart.x        = windowWidth - itemBoxSize - aStart.x;
    bStart.y        = aStart.y;
    cStart.x        = windowWidth - itemBoxSize - aStart.x + 300;
    cStart.y        = aStart.y;

    blurBackground(OUT_OF_MAP_COLOR_BAS);

    MLV_draw_text(windowWidth/2.35, windowHeight/8, "Choose stats to up", MLV_COLOR_WHITE);
    while(1) {
        MLV_get_mouse_position(&x, &y);
        MLV_wait_milliseconds( 100 );
        /* ATK */
        if(!selectStat(aStart, x, y, itemBoxSize, "ATK", player->stat.base.ATTACK)){
            player->stat.base.ATTACK += 1 ;
            return;
        }
        /* DEF */
        if(!selectStat(bStart, x, y, itemBoxSize, "DEF", player->stat.base.DEFENSE)){
            player->stat.base.DEFENSE += 1 ;
            return;
        }

        /* INT */
        if(!selectStat(cStart, x, y, itemBoxSize, "INT", player->stat.base.INTELLIGENCE)){
            player->stat.base.INTELLIGENCE += 1 ;
            return;
        }
        MLV_actualise_window();
    }
}

void displayGameOverScreen(Player player, StageList dungeon) {
    unsigned int windowWidth, windowHeight;
    MLV_get_window_size(&windowWidth, &windowHeight);

    MLV_Keyboard_button sym   = MLV_KEYBOARD_NONE;
    MLV_Keyboard_modifier mod = MLV_KEYBOARD_KMOD_NONE;
    MLV_Input_box *input_box  = NULL;
    char* texte               = NULL;
    MLV_Button_state state;

    int nbLevelsExplored = 0;
    int actualLevel = dungeon->stage.level;

    int waitTime = 1200;
    Point buttonStart;
    buttonStart.x = windowWidth/3;
    buttonStart.y = windowHeight - windowHeight/3;
    int buttonWidth = windowWidth - 2*buttonStart.x;
    int buttonHeight = 50;
    int buttonSize = 0;
    int x, y; /* for mouse */
    int mouseOnButton = 0;

    while(dungeon->nextLevel != NULL)
        dungeon = dungeon->nextLevel;

    nbLevelsExplored = dungeon->stage.level;

    MLV_clear_window(OUT_OF_MAP_COLOR_BAS);


    /* text */
    MLV_change_default_font("src/files/Mouser D.otf", 60);
    MLV_draw_text(windowWidth/4, windowHeight/5 - 15, "DEATH", PLAYER_COLOR_BAS);
    MLV_wait_milliseconds( waitTime );
    MLV_actualise_window();
    MLV_change_default_font("src/files/Mouser D.otf", 30);
    MLV_draw_text(windowWidth/2.2 - 20, windowHeight/5 + 20, "is nothing at all.", MLV_COLOR_GHOSTWHITE);
    MLV_wait_milliseconds( waitTime );
    MLV_actualise_window();
    MLV_draw_text(windowWidth/4, windowHeight/5 + 70, "It does not count.", MLV_COLOR_GHOSTWHITE);
    MLV_wait_milliseconds( waitTime );
    MLV_actualise_window();
    MLV_draw_text(windowWidth/4, windowHeight/5 + 120, "I have only slipped away into the next room.", MLV_COLOR_GHOSTWHITE);
    MLV_wait_milliseconds( waitTime );
    MLV_actualise_window();
    MLV_draw_text(windowWidth/4, windowHeight/5 + 170, "Nothing has happened.", MLV_COLOR_GHOSTWHITE);
    MLV_wait_milliseconds( waitTime + (float)waitTime/3);
    MLV_actualise_window();

    /* score button display */
    MLV_wait_milliseconds( 2*waitTime );

    /* loops until the user clicks on the button */
    while(1) {
        MLV_get_mouse_position(&x, &y);

        if(x > buttonStart.x && x < buttonStart.x + buttonWidth &&
            y > buttonStart.y - buttonHeight/2 && y < buttonStart.y + buttonHeight/2) {
            mouseOnButton = 1;
            if(buttonSize < MAX_BUTTON_SIZE) {
                MLV_wait_milliseconds( 50 );
                buttonSize++;
            }
        }
        else {
            mouseOnButton = 0;
            if(buttonSize > 0) {
                MLV_wait_milliseconds( 50 );
                MLV_draw_filled_rectangle(
                    buttonStart.x - 70,
                    buttonStart.y - 50,
                    buttonWidth + 100,
                    buttonHeight + 50,
                    OUT_OF_MAP_COLOR_BAS
                    );
                buttonSize--;
            }
        }

        displayButton(buttonStart.x, buttonStart.y, buttonWidth, buttonHeight, buttonSize, MLV_COLOR_GHOSTWHITE, "VIEW SCORE");
        MLV_actualise_window();

        if(MLV_get_mouse_button_state(MLV_BUTTON_LEFT) == MLV_PRESSED) {
            if(mouseOnButton)
                break;
        }
    }

    MLV_clear_window(OUT_OF_MAP_COLOR_BAS);

    MLV_change_default_font("src/files/Mouser D.otf", 30);
    MLV_draw_text(windowWidth/4, windowHeight/5 + 20, "Level : %d", MLV_COLOR_GHOSTWHITE, player.stat.current.lvl);
    MLV_wait_milliseconds( waitTime );
    MLV_actualise_window();
    MLV_draw_text(windowWidth/4, windowHeight/5 + 70, "Attack : %d", MLV_COLOR_GHOSTWHITE, player.stat.base.ATTACK);
    MLV_wait_milliseconds( waitTime );
    MLV_actualise_window();
    MLV_draw_text(windowWidth/4, windowHeight/5 + 120, "Defense : %d", MLV_COLOR_GHOSTWHITE, player.stat.base.DEFENSE);
    MLV_wait_milliseconds( waitTime );
    MLV_actualise_window();
    MLV_draw_text(windowWidth/4, windowHeight/5 + 170, "Intelligence : %d", MLV_COLOR_GHOSTWHITE, player.stat.base.INTELLIGENCE);
    MLV_wait_milliseconds( waitTime );
    MLV_actualise_window();
    MLV_draw_text(windowWidth/4, windowHeight/5 + 220, "Number of levels explored : %d", MLV_COLOR_GHOSTWHITE, nbLevelsExplored);
    MLV_wait_milliseconds( waitTime );
    MLV_actualise_window();
    MLV_draw_text(windowWidth/4, windowHeight/5 + 270, "Died on level : %d", MLV_COLOR_GHOSTWHITE, actualLevel);
    MLV_wait_milliseconds( waitTime );
    MLV_actualise_window();

    MLV_wait_milliseconds( waitTime );

    while(1) {
        /* getting the event */
        MLV_Event ev = MLV_get_event( 
            &sym, &mod, NULL,
            &texte, &input_box,
            &x, &y, NULL,
            &state
            );

        /* break if key event */
        if(ev == MLV_KEY && state == MLV_PRESSED) {
            break;
        }
    }


}

void exitGame() {
    MLV_free_window();
}