#include "treasure.h"

Treasure generateTreasure(unsigned int level) {
    
    int i;
    int rarity, quality, type;
    Treasure treasure;

    /*Fills the two items of the treasure */
    for( i = 0 ; i < MAX_LOOT_PER_TREASURE ; i++ ){

        /* calculate rarity */
        rarity = (rand() % (MAX_RARITY-1)) + 1;/*random beetwen 1 and MAX_RARITY*/

        /* calculate type Equip/Consummable*/
        type = rand() % 2;/*random beetwen 0 and 1*/

        /* calculate quality */
        quality = rand() % level + 1;/*random beetwen 1 and the level of stage*/

        if(type){/* no loot is rarer than the other */
            treasure.loot[i] = generateLoot(quality, rarity, EQUIPMENT);/* Generate an equipment */
        }
        else{
            treasure.loot[i] = generateLoot(quality, rarity, CONSUMMABLE);/* Generate a consummable */
        }
    }
    return treasure;
}

int quickPrintTreasure(Treasure treasure){

    int i;

    assert(NULL != treasure.loot);

    printf("****TREASURE CHEST****\n");

    for( i = 0 ; i < 2 ; i++){
        printf("item %d : \n", i);
        if(!quickPrintLoot(treasure.loot[i])){
            return 0;
        } /* print all of it's content */
    }
    return 1;
}
