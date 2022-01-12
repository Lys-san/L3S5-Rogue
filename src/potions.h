/* Auteurs : Nicolas Mazeyrac, Lysandre Macke
 * Creation : 07/01/2022
 * Modification : 07/01/2022*/

/*Bibliothèque générale*/

/*Bibliothèque interne*/
#include "player.h"

#ifndef __POTIONS__
#define __POTIONS__

    void useMagicPotion(Player *player);

    void useHealingPotion(Player *player);

    void turnRegenPotion(Player *player);

    void gainRegenPotion(Player *player);

    void gainPrecision(Player *player);

    void losePrecision(Player *player);

    void gainLearning(Player *player);

    void loseLearning(Player *player);

    void gainAllEffect(Player *player);
#endif