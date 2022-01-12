#include "action.h"

/* Attack */
unsigned int attackPhysical(unsigned int attack, Critical crit){
    
    unsigned int accuracy;
    unsigned int critical;
    unsigned int chance;

    accuracy = calculateAccuracy(crit);

    chance = rand() % 101;/*Chance for a crit*/

    if(crit.rate >= chance){
        critical = crit.modificater;
    }
    else{
        critical = 1;
    }

    return (unsigned int)(((attack * accuracy)/100)*critical);/*dmg for the physical attack*/
}

unsigned int attackMagical(unsigned int intelligence, Spell spell){
    return spell.power * intelligence;
}


unsigned int calculateAccuracy(Critical crit){
    unsigned int bonus;
    unsigned int chance;
    unsigned int accuracy;

    accuracy = 100;

    chance = rand() % 2 + 1;/* Chance for the accuracy to be a bonus or a malus*/

    bonus = (rand() % crit.accuracy);/* Number for the bonus/malus change */

    if(chance == 1){
        accuracy -= bonus;
    }
    else{
        accuracy += bonus;
    }

    return accuracy;
}

/* Move */

Point Move(Point coordInit, Direction dir){

    Point newCoord;
    int x, y;

    dirToShiftValues(dir, &x, &y);
    newCoord.x = coordInit.x + x;/* Change the coord */
    newCoord.y = coordInit.y + y;
    return newCoord;
}

/* Enemy */

void enemyAttack(Enemy monster, Player* player){
    unsigned int damage;
    damage = attackPhysical(monster.attack, monster.crit);
    printf("I attack for %d damage \n", damage);
    player->stat.current.hp -= damage;
}


void enemyMove(Stage* level, Point coordEnemy, Point coordPlayer){
    
    int lateralDistance;
    int verticalDistance;
    Point newCoord;
    Cell tmp;

    lateralDistance = coordPlayer.x - coordEnemy.x;
    verticalDistance = coordPlayer.y - coordEnemy.y;

    if(ABS(verticalDistance) >= ABS(lateralDistance)){
        if(verticalDistance < 0){
            printf("Try to move up \n");
            newCoord = Move(coordEnemy, N);/* Move up */
        }
        else{
            printf("Try to move down \n");
            newCoord = Move(coordEnemy, S);/* Move down */
        }
    }
    else{
        /*left and right*/
        if(lateralDistance < 0){
            printf("Try to move left \n");
            newCoord = Move(coordEnemy, W);/* Move left */
        }
        else{
            printf("Try to move right \n");
            newCoord = Move(coordEnemy, E);/* Move right */
        }
    }

    if( ( level->cells[newCoord.y][newCoord.x].type == ROOM ) && ( !isTheSame(newCoord, coordPlayer) ) ){
        printf("I moved \n");
        printf("new coord x = %d, y = %d \n", newCoord.x, newCoord.y);
        tmp =  level->cells[coordEnemy.y][coordEnemy.x];
        level->cells[coordEnemy.y][coordEnemy.x] = level->cells[newCoord.y][newCoord.x];
        level->cells[newCoord.y][newCoord.x] = tmp;
    }
    else{
        printf("There isn't space \n");
    }
}


/* Player */

void playerPhysicalAttack(Player player, Enemy* monster){
    
    unsigned int damage;

    /* do the damage */
    damage = attackPhysical(player.stat.base.ATTACK, player.stat.base.CRIT);
    monster->hp -= damage;
    printf("damage dealt = %d \n", damage);

}

int playerMagicalAttack(Player* player, Enemy* monster){
    
    unsigned int damage;

    /* Check the mp */
    if(player->spell.cost <= player->stat.current.mp){
        return 0;
    }
    player->stat.current.mp -= player->spell.cost;

    /* do the damage */
    damage = attackMagical(player->stat.base.INTELLIGENCE, player->spell);
    monster->hp -= damage;
    return 1;
}

void openTreasure(Player* player, Stage* stage, int x, int y){
    Loot loot;

    if(stage->cells[y][x].treasure.closed){
        loot = stage->cells[y][x].treasure.loot[0];/*choose a treasure*/
        quickPrintLoot(loot);
        switch(loot.type){
            case EQUIPMENT:
                newEquipment(player, loot.equipment);
                break;
            case CONSUMMABLE:
                pickUp(player, loot);
                break;
            default:fprintf(stderr, "this loot doesn't exist");
        }
        stage->cells[y][x].treasure.closed = 0;
    }
}

int consumeItem(Player* player, Consummables potion){
    switch(potion){
        case HEAL:
            useHealingPotion(player);
            return 1;
            break;
        case MAGIC:
            useMagicPotion(player);
            return 1;
            break;
        case REGEN:
            if(player->underRegenPotion == 0){
                gainRegenPotion(player);
                return 1;
            }
            break;
        case LEARNING:
            if(player->underLearningPotion == 0){
                gainLearning(player);
                return 1;
            }
            break;
        case PRECISION:
            if(player->underPrecisionPotion == 0){
                gainPrecision(player);
                return 1;
            }
            break;
        default:fprintf(stderr, "This item doesn't exist");
    }
    return 0;
}

int playerMove(Player* player, Direction dir, StageList *dungeon){
    
    Point newCoord;
    CellType type;
    Stage *stage;
    Stage newStage;

    /* Calculate the new coord */
    newCoord = Move(player->coords,dir);
    stage = &((*dungeon)->stage);
    type = stage->cells[newCoord.y][newCoord.x].type;

    /* Special Action based on the next tile*/
    switch(type){

        case WALL:
            /*printf("Stopped \n");*/
            return 0;/* The player doesn't move */
        break;

        case ENEMY:
            printf("Attack \n");
            quickPrintEnemy(stage->cells[newCoord.y][newCoord.x].enemy);
            playerPhysicalAttack(*player, &(stage->cells[newCoord.y][newCoord.x].enemy));
            if(stage->cells[newCoord.y][newCoord.x].enemy.hp <= 0){
                printf("The enemy is dead \n");
                gainExp(player, stage->cells[newCoord.y][newCoord.x].enemy.exp);
                stage->cells[newCoord.y][newCoord.x] = initCell(1, newCoord, ROOM, CONTAINS_NOTHING, 0);
            }
            return 0;/* The player will perform a physical attack */
        break;

        case TREASURE:/* The player will open a Treasure */
            printf("Open treasure \n");
            openTreasure(player, stage, newCoord.x, newCoord.y);
            quickPrintPlayer(*player);
            return 0;
        break;

        case STAIR_DOWN:/* The player will descend to the next level */
            printf("Go downstair \n");
            player->coords.x = newCoord.x;
            player->coords.y = newCoord.y;
            if((*dungeon)->nextLevel == NULL){
                /*generateStageTest(&newStage, player, stage->level+1);*/
                initStage(&newStage, player, stage->level+1);
                addStage(dungeon, newStage);
                quickPrintStage(newStage);
            }
            else{
                (*dungeon) =(*dungeon)->nextLevel ;
                initPlayerOnStage(player,  (*dungeon)->stage);
                /*player->coords = (Point){2, 2};*/
            }
            return 1;
        break;

        case STAIR_UP:/* The player will ascend to the previous level */
            printf("Go upstair \n");
            player->coords.x = newCoord.x;
            player->coords.y = newCoord.y;
            if((*dungeon)->previousLevel != NULL){
                printf("target level is %d \n", stage->level-1);
                (*dungeon) =(*dungeon)->previousLevel ;
                printf("Current level is %d \n", (*dungeon)->stage.level);
                /*initPlayerOnStage(player,  (*dungeon)->stage);*/
                player->coords = (Point){2, 2};
            }
            return 1;
        break;

        default:/*Doesn't do anything, no special action*/;
    }

    /*the player moved*/
    printf("Moves \n");
    printf("New coord = x=%d, y=%d \n", newCoord.x, newCoord.y);
    player->coords.x = newCoord.x;
    player->coords.y = newCoord.y;
    return 0;
}