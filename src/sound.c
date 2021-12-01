#include "sound.h"

void playButtonSound_1() {
	MLV_Sound *buttonSound_1 = MLV_load_sound("src/button_1.wav");
	MLV_play_sound(buttonSound_1, 0.1);
	/*MLV_free_sound(buttonSound_1);*/
}

void playButtonSound_2() {
	MLV_Sound *buttonSound_2 = MLV_load_sound("src/button_2.wav");
	MLV_play_sound(buttonSound_2, 0.1);
	/*MLV_free_sound(buttonSound_2);*/
}