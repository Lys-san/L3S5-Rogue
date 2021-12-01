#include <stdio.h>

#define MAX_HP 10 * player->defense
#define MAX_MP (10*player->intellig - 50 > 0) ? (10 * player->intellig - 50) : 0
#define EXP_TO_NEXT_LVL 350 + 50*(player->lvl)

#define FIRST_LVL_STATS 10


typedef struct {
	unsigned int hp;
	unsigned int mp;
	unsigned int strenght;
	unsigned int intellig; 
	unsigned int defense;
	unsigned int exp;
	unsigned int lvl;
} Player;

/* Initialisatin of the player's stats */
void initPlayerStats(Player *player);

/* Debug */
void printPlayerStats(Player player);