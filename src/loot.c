#include "loot.h"

Consummables generateRandomConsummable(void){
	int randomnumber;

	randomnumber = rand() % 5;

	switch(randomnumber){
		case 0:return HEAL;
		case 1:return MAGIC;
		case 2:return REGEN;
		case 3:return LEARNING;
		case 4:return PRECISION;
		default :fprintf(stderr, "ERROR: not a consummable randomnumber = %d \n", randomnumber);
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