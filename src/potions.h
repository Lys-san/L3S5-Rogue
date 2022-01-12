/* Auteurs : Nicolas Mazeyrac, Lysandre Macke
 * Creation : 07/01/2022
 * Modification : 07/01/2022*/

/*Bibliothèque générale*/

/*Bibliothèque interne*/
#include "player.h"

#ifndef __POTIONS__
#define __POTIONS__

    typedef struct {
        int turnActivation;
        int turnLeft;
        void (*bonus)(Player* player);
        void (*malus)(Player* player);
    }Effect;

    void useMagicPotion(Player *player);

    void useHealingPotion(Player *player);

    void turnRegenPotion(Player *player);

    void gainPrecision(Player *player);

    void losePrecision(Player *player);

    void gainLearning(Player *player);

    void loseLearning(Player *player);

    Effect createEffect(Consummables potion);
#endif