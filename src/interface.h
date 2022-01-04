#include <MLV/MLV_all.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "sound.h"
#include "colors.h"
#include "level.h"
#include "player.h"

#define WINDOW_WIDTH    (CELL_SIZE * SCREEN_WIDTH)
#define WINDOW_HEIGHT   (CELL_SIZE * SCREEN_HEIGHT)

#define MAX_BUTTON_SIZE 3

#define HP_BAR_WIDTH    200
#define MP_BAR_WIDTH    200
#define EXP_BAR_WIDTH   180

#define CELL_SIZE       100

#define MAIN_SCREEN_BACKGROUND_COLOR MLV_COLOR_GHOSTWHITE
#define POPUP_COLOR                  MLV_COLOR_MISTYROSE4

#define LINE_COLOR                   MLV_COLOR_BLACK
#define HP_BAR_COLOR                 MLV_COLOR_DEEP_PINK
#define MP_BAR_COLOR                 MLV_COLOR_LIGHT_CYAN
#define EXP_BAR_COLOR                MLV_COLOR_VIOLET_RED

/* Colors for basic display of cells */
#define PLAYER_COLOR_BAS             MLV_COLOR_DEEP_PINK
#define WALL_COLOR_BAS              MLV_COLOR_SNOW4
#define EMPTY_COLOR_BAS              MLV_COLOR_SNOW
#define ENEMY_COLOR_BAS              MLV_COLOR_VIOLET_RED
#define TREASURE_COLOR_BAS           MLV_COLOR_LIGHTGOLDENROD
#define STAIR_UP_COLOR_BAS           MLV_COLOR_RED
#define STAIR_DOWN_COLOR_BAS         MLV_COLOR_MEDIUMORCHID

#define IS_SELECTABLE      (profileFound || i != PROFILE)
#define BREAK_NESTED_LOOPS pixelFound = 1; break;

#define SQUARED(a) (a*a)

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

/* Displays a button of a given size, color, text and given dimensions at given coordonates */
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
int displayMainScreen(int xMouse, int yMouse, int profileFound, int buttonSize[]);

/* Display of the main menu until the user chooses an option.
 * Requires an integer (0 or 1) telling if a memory file is found or not,
 * which will indicate if the PROFILE menu is available or not, and and interger
 * telling if there is a fede-in effect or not */
int mainScreen(int profileFound, int fadein);

/* Generates a snowy cinematic using the libMLV functions. */
void snowdrops(unsigned int frames);

/* Basic display of a given cell using the libMLV drawing functions */
void displayCellBasic(Cell cell);

/* Display of a given cell with the corresponding sprite (image) */
void displayCellSprite(Cell cell);

/* Returns the top left cell to be displayed on screen knowing that the player is in
 * middle of the screen. */
Point topLeftCellOnScreen(Point playerCoords);

/* Basic display of the player in the middle of the screen using the libMLV
 * drawing functions. */
void displayPlayerBasic();

/* Display of the player in the middle of the screen with the corresponding sprite. */
void displayPlayerSprite();

/* Displays the given stage according to the specified mode (0 = basic, 1 = sprite) */
void displayStage(Stage stage, Player player, enum mode mode);

/* Display of the Head Up Display on the left top of the screen */
void displayHUD(Player player);

/* Frees what need to be freed and closes the window. */
void exitGame();