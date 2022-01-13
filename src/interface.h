#include <stdio.h>
#include <stdlib.h>

#include "draw.h"
#include "sound.h"
#include "level.h"
#include "player.h"

#define WINDOW_WIDTH    (CELL_SIZE * SCREEN_WIDTH)
#define WINDOW_HEIGHT   (CELL_SIZE * SCREEN_HEIGHT)

#define MAX_BUTTON_SIZE 3

#define HP_BAR_WIDTH    200
#define MP_BAR_WIDTH    200
#define EXP_BAR_WIDTH   180

#define CELL_SIZE       100

/* Main interface colors */
#define MAIN_SCREEN_BACKGROUND_COLOR MLV_COLOR_GHOSTWHITE
#define POPUP_COLOR                  MLV_COLOR_MISTYROSE4

/* Colors for inventory menu */
#define INVENTORY_MENU_COLOR         MLV_COLOR_MISTYROSE2
#define ITEM_BOX_COLOR               MLV_COLOR_MISTYROSE4
#define EMPTY_BOX_COLOR              MLV_COLOR_MISTYROSE3

/* Colors for HUD */
#define HP_BAR_COLOR                 MLV_COLOR_DEEP_PINK
#define MP_BAR_COLOR                 MLV_COLOR_LIGHT_CYAN
#define EXP_BAR_COLOR                MLV_COLOR_VIOLET_RED

/* Colors for in-game buttons */
#define PHYS_ATK_BUTTON_COLOR        MLV_COLOR_DEEP_PINK
#define MAGC_ATK_BUTTON_COLOR        MLV_COLOR_DARK_CYAN

/* Colors for basic display of player */
#define PHYSICAL_MODE_COLOR_BAS      MLV_COLOR_DEEP_PINK
#define MAGICAL_MODE_COLOR_BAS       MLV_COLOR_DARK_CYAN

/* Colors for basic display of cells */
#define PLAYER_COLOR_BAS             MLV_COLOR_DEEP_PINK
#define WALL_COLOR_BAS               MLV_COLOR_SNOW4
#define EMPTY_COLOR_BAS              MLV_COLOR_SNOW
#define ENEMY_COLOR_BAS              MLV_COLOR_BLUE_VIOLET
#define TREASURE_COLOR_BAS           MLV_COLOR_LIGHTGOLDENROD
#define STAIR_UP_COLOR_BAS           MLV_COLOR_RED
#define STAIR_DOWN_COLOR_BAS         MLV_COLOR_MEDIUMORCHID
#define OUT_OF_MAP_COLOR_BAS         MLV_COLOR_GRAY1

/* expressions */
#define IS_SELECTABLE      (profileFound || i != PROFILE)


enum MENU { /*accessible via the main screen*/
	PLAY,
	PROFILE,
	SETTINGS,
	EXIT
};

enum mode { BASIC, WITH_SPRITES }; /* display mode */

/* Creates the game window */
void createGameWindow();

/* Overlays a reduced opacity rectangle of a given color on the current screen */
void blurBackground(MLV_Color color);

/* Displays a button of a given size, color, text and given dimensions at given coordonates.
 * 0 = default size, MAX_BUTTON_SIZE = max size. */
void displayButton(int x, int y, int width, int height, int size, MLV_Color color, char *text);

/* Displays a popup in the middle of the screen and returns the corresponding number of
 * the button at the coordonates of the mouse (1 = yes/0 = no)
 * Requires the (xMouse, yMouse) coordonates of the mouse, which are integers */
int displayYesNoPopup(int width, int height, char *text, int xMouse, int yMouse, int buttonSize[]);

/* Displays a popup window with a given message until the 
 * user chooses an option (yes/no).
 * 1 : 'yes' clicked
 * 0 : 'no' clicked */
int yesNoPopup(char *text);

/* Displays the main menu of the game and returns the corresponding number of
 * the button at the coordonates of the mouse.
 * Requires the (xMouse, yMouse) coordonates of the mouse, which are integers */
int displayMainScreen(int xMouse, int yMouse, int profileFound, int buttonSize[], MLV_Image *illus);

/* Display of the main menu until the user chooses an option.
 * Requires an integer (0 or 1) telling if a memory file is found or not,
 * which will indicate if the PROFILE menu is available or not, and and interger
 * telling if there is a fede-in effect or not */
int mainScreen(int profileFound, int fadein);

/* Returns the corresponding sprite according to the position of the wall cell in the 
 * stage. */
MLV_Image *wallSprite(Cell cell, Stage stage);

/* Basic display of a given cell using the libMLV drawing functions */
void displayCellBasic(Cell cell);

/* Display of a given cell with the corresponding sprite (image).
 * Returns 0 if the cell couldn't be displayed. */
int displayCellSprite(Cell cell);

/* Returns the top left cell to be displayed on screen knowing that the player is in
 * middle of the screen. */
Point topLeftCellOnScreen(Point playerCoords);

/* Returns the corresponding color according to the player status. */
MLV_Color playerColor(Player player);

/* Basic display of the player in the middle of the screen using the libMLV
 * drawing functions. */
void displayPlayerBasic(Player player);

/* Display of the player in the middle of the screen with the corresponding sprite. */
void displayPlayerSprite(Player player);

/* Displays the given stage according to the specified mode. */
void displayStage(Stage stage, Player player, enum mode mode);

/* Displays physical and magical attack buttons on the screen. */
void displayAtkButtons();

/* Returns the corresponding sprite according to the given Loot object. */
MLV_Image *itemSprite(Loot loot);

/* Basic display for a Loot object using libMLV drawing functions. 
 * The item box size and its coords on screen are needed for the display. */
void displayItemBasic(Loot loot, Point coordsOnScreen, int itemBoxSize);

/* Display of a given Loot object with the corresponding sprite (image).
 * The item box size and its coords on screen are needed for the display. */
void displayItemSprite(Loot loot, Point coordsOnScreen, int itemBoxSize);

/* Displays the inventory board on screen according to the specified mode.*/
void displayInventory(Loot inventory[], enum mode mode, int selection);

/* Returns the name (string) of a given Loot object. */
char *itemName(Loot item);

/* Displays informations about a given item. 
 * The informations will be displayed in the area delimited by
 * a starting point, a width and a height. */
void displayItemInfo(Loot item, Point start, int boxWidth, int boxHeight);

/* Display of the given inventory until the user does an action (closing the menu or
 * choosing to consume or getting rid of an objet).
 * Returns the chosen objet. */
Loot inventory(Loot inventory[], enum mode mode);

/* Display of the Head Up Display on the left top of the screen */
void displayHUD(Player player);

/* Displays a menu where the user can choose between two Loot items. 
 * Loops until the user makes a choice. */
Loot chooseBetweenTwo(Loot item_a, Loot item_b);

/* Frees what need to be freed and closes the window. */
void exitGame();