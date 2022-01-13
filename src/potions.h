/* Auteurs : Nicolas Mazeyrac, Lysandre Macke
 * Creation : 07/01/2022
 * Modification : 13q/01/2022*/

/*Bibliothèque générale*/

/*Bibliothèque interne*/
#include "player.h"

#ifndef __POTIONS__
#define __POTIONS__

    /*Define*/

    #define NUMBER_TURN_EFFECT 30

    /*Struct*/

    /*Functions*/

    /* Regain of the player for 10% of it's mp */
    void useMagicPotion(Player *player);

    /* Heal the player for 10% of it's hp */
    void useHealingPotion(Player *player);

    /* Heal the player for 20 hp and 10 mp */
    void turnRegenPotion(Player *player);

    /* Set the number of turn of regen potion to 30 */
    void gainRegenPotion(Player *player);

    /* Set the number of turn of precision potion to 30 and gain 10 point of percentage for the critRate */
    void gainPrecision(Player *player);

    /* Remove 10 point of percentage for the critRate */
    void losePrecision(Player *player);

    /* Set the number of turn of regen potion to 30 */
    void gainLearning(Player *player);

    /* Gain all of the active effects of the player */
    void gainAllEffect(Player *player);
#endif