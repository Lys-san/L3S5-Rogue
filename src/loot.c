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
		default :printf("ERROR: not a consummable randomnumber = %d \n", randomnumber);
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

