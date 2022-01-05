#include "treasure.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


Consummables generateRandomConsummable(void){
	int randomnumber;

	randomnumber = rand() % 5;

	switch(randomnumber){
		case 0:return HEAL;
		case 1:return MAGIC;
		case 2:return REGEN;
		case 3:return LEARNING;
		case 4:return PRECISION;
		default :printf("ERROR: randomnumber = %d \n", randomnumber);
	}

	return EMPTY;
}

Equipment generateEquipment(EquipType type, unsigned int quality, unsigned int rarity){
	
	Equipment equipment;
	
	equipment.quality = quality;
	equipment.rarity = rarity;
	equipment.type = type;

	return equipment;
}

Equipment generateRandomEquipment(unsigned int quality, unsigned int rarity){
	
	Equipment equipment;
	int randomnumber;

	randomnumber = rand() % 3;
	switch(randomnumber){
		case 0:equipment = generateEquipment(ARMOR, quality, rarity);break;
		case 1:equipment = generateEquipment(WEAPON, quality, rarity);break;
		case 2:equipment = generateEquipment(WAND, quality, rarity);break;
		default :printf("ERROR: randomnumber = %d \n", randomnumber);
	}

	return equipment;
}

Loot generateLoot(unsigned int quality, unsigned int rarity, LootType type) {
	Loot loot;

	loot.type = type;
	if(loot.type == CONSUMMABLE){
		loot.consummable = generateRandomConsummable();
	}
	else{
		loot.equipment = generateRandomEquipment(quality, rarity);
	}
	return loot;
}

Treasure generateTreasure(unsigned int stage, unsigned int playerlevel) {
	
	int i;
	int rarity, quality, type;
	Treasure chest;

	/*Fills the two items of the treasure chest*/
	for( i = 0 ; i < 2 ; i++ ){

		/* calculate rarity */
		rarity = rand() % 4 + 1;/*random beetwen 1 and 5*/

		/* calculate type Equip/Consummable*/
		type = rand() % 2 + 1;/*random beetwen 1 and 2*/

		/* calculate quality */
		quality = rand() % stage + 1;/*random beetwen 1 and the level of stage*/

		if(type == 1){
			chest.loot[i] = generateLoot(quality, rarity, EQUIPMENT);
		}
		else{
			chest.loot[i] = generateLoot(quality, rarity, CONSUMMABLE);
		}
	}
	return chest;
}


void quickPrintEquipment(Equipment equip){
	switch(equip.type){
		case ARMOR: printf("ARMOR \n");break;
		case WEAPON: printf("WEAPON \n");break;
		case WAND: printf("WAND \n");break;
		default: printf("ERROR \n");
	}
	printf("- rarity : %d \n", equip.rarity);
	printf("- quality : %d \n", equip.quality);
}

void quickPrintConsummable(Consummables consummable){
	switch(consummable){
		case HEAL: printf("HEAL \n");break;
		case MAGIC: printf("MAGIC \n");break;
		case REGEN: printf("REGEN \n");break;
		case LEARNING: printf("LEARNING \n");break;
		case PRECISION: printf("PRECISION \n");break;
		case EMPTY: printf("EMPTY \n");break;
		default: printf("ERROR \n");
	}
}

void quickPrintLoot(Loot loot){
	if(loot.type == EQUIPMENT){
		quickPrintEquipment(loot.equipment);
	}
	else{
		quickPrintConsummable(loot.consummable);
	}
}


void quickPrintTreasure(Treasure chest){

	int i;

    printf("****TREASURE CHEST****\n");

    for( i = 0 ; i < 2 ; i++){
    	printf("item %d : \n", i);
		quickPrintLoot(chest.loot[i]);
    }
}
