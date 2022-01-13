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
            newCoord = Move(coordEnemy, N);/* Move up */
        }
        else{
            newCoord = Move(coordEnemy, S);/* Move down */
        }
    }
    else{
        /*left and right*/
        if(lateralDistance < 0){
            newCoord = Move(coordEnemy, W);/* Move left */
        }
        else{
            newCoord = Move(coordEnemy, E);/* Move right */
        }
    }

    if( ( level->cells[newCoord.y][newCoord.x].type == ROOM ) && ( !isTheSame(newCoord, coordPlayer) ) ){
        tmp =  level->cells[coordEnemy.y][coordEnemy.x];
        level->cells[coordEnemy.y][coordEnemy.x] = level->cells[newCoord.y][newCoord.x];
        level->cells[newCoord.y][newCoord.x] = tmp;
    }
}


/* Player */

void playerPhysicalAttack(Player player, Enemy *enemy){
    
    unsigned int damage;

    /* do the damage */
    damage = attackPhysical(player.stat.base.ATTACK, player.stat.base.CRIT);
    enemy->hp -= damage;
}

int playerMagicalAttack(Player *player, Enemy *enemy){
    
    unsigned int damage;

    /* Check the mp */
    if(player->spell.cost > player->stat.current.mp){
        return 0;
    }
    player->stat.current.mp -= player->spell.cost;

    /* do the damage */
    damage = attackMagical(player->stat.base.INTELLIGENCE, player->spell);
    enemy->hp -= damage;
    return 1;
}

void openTreasure(Player* player, Stage* stage, int x, int y){
    Loot loot;

    if(stage->cells[y][x].treasure.closed){
        loot = stage->cells[y][x].treasure.loot[0];/*choose a treasure*/
        switch(loot.type){
            case EQUIPMENT:
                newEquipment(player, loot.equipment);
                break;
            case CONSUMMABLE:
                addToInventory(player, loot);
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
            return 0;/* The player doesn't move */
        break;

        case ENEMY:
            if(player->status == PHYSICAL_ATTCK){
                playerPhysicalAttack(*player, &(stage->cells[newCoord.y][newCoord.x].enemy));
            }
            else{
                playerMagicalAttack(player, &(stage->cells[newCoord.y][newCoord.x].enemy));
                player->status = PHYSICAL_ATTCK;
            }

            if(stage->cells[newCoord.y][newCoord.x].enemy.hp <= 0){
                gainExp(player, stage->cells[newCoord.y][newCoord.x].enemy.exp);
                stage->cells[newCoord.y][newCoord.x] = initCell(1, newCoord, ROOM, CONTAINS_NOTHING, 0);
            }
            return 0;/* The player will perform a physical attack */
        break;

        case TREASURE:/* The player will open a Treasure */
            openTreasure(player, stage, newCoord.x, newCoord.y);
            return 0;
        break;

        case STAIR_DOWN:/* The player will descend to the next level */
            if((*dungeon)->nextLevel == NULL){
                initStage(&newStage, player, stage->level+1);
                addStageTail(dungeon, newStage);
            }
            else{
                (*dungeon) =(*dungeon)->nextLevel ;
                player->coords = getStageCenter();
            }
            return 0;
        break;

        case STAIR_UP:/* The player will ascend to the previous level */
            if((*dungeon)->previousLevel != NULL){
                (*dungeon) =(*dungeon)->previousLevel ;
                player->coords = (*dungeon)->stage.stairDown;
            }
            return 0;
        break;

        default:/*Doesn't do anything, no special action*/;
    }

    /*the player moved*/
    player->coords.x = newCoord.x;
    player->coords.y = newCoord.y;
    return 1;
}