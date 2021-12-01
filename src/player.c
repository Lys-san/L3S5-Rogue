#include "player.h"

void initPlayerStats(Player *player) {
	player->lvl = 1;
	player->exp = 0;

	player->strenght = FIRST_LVL_STATS; /*10*/
	player->intellig = FIRST_LVL_STATS; /*10*/
	player->defense  = FIRST_LVL_STATS; /*10*/

	player->hp = MAX_HP; /*100*/
	player->mp = MAX_MP; /*50*/
}


void printPlayerStats(Player player) {
	printf("****PLAYER STATS****\n");
	printf("lvl      : %d\n", player.lvl);
	printf("exp      : %d\n", player.exp);

	printf("strenght : %d\n", player.strenght);
	printf("intellig : %d\n", player.intellig);
	printf("strenght : %d\n", player.strenght);

	printf("hp       : %d\n", player.hp);
	printf("mp       : %d\n", player.mp);
}