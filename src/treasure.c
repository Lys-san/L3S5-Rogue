#include "treasure.h"

Treasure generateTreasure(unsigned int stage, unsigned int playerlevel) {
	
	int i;
	int rarity, quality, type;
	Treasure treasure;

	/*Fills the two items of the treasure */
	for( i = 0 ; i < 2 ; i++ ){

		/* calculate rarity */
		rarity = rand() % 4 + 1;/*random beetwen 1 and 5*/

		/* calculate type Equip/Consummable*/
		type = rand() % 2 + 1;/*random beetwen 1 and 2*/

		/* calculate quality */
		quality = rand() % stage + 1;/*random beetwen 1 and the level of stage*/

		if(type == 1){
			treasure.loot[i] = generateLoot(quality, rarity, EQUIPMENT);/* Generate an equipment */
		}
		else{
			treasure.loot[i] = generateLoot(quality, rarity, CONSUMMABLE);/* Generate a consummable */
		}
	}
	treasure.closed = 1;
	return treasure;
}

void quickPrintTreasure(Treasure treasure){

	int i;

	assert(NULL != treasure.loot);

    printf("****TREASURE CHEST****\n");

    for( i = 0 ; i < 2 ; i++){
    	printf("item %d : \n", i);
		quickPrintLoot(treasure.loot[i]); /* print all of it's content */
    }
}
