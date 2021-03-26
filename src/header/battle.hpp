// Battle class
#ifndef BATTLE_HPP
#define BATTLE_HPP

#include "entities/engimon.hpp"
#include "entities/attributes/elementtype.hpp"
#include "engimoninteraction.hpp"


class Battle : public EngimonInteraction {
    private:
        int winnerNumber;
        float advantage1;
        float advantage2;
        float getElementAdvantage(ElementType elem1, ElementType elem2);
        float getMax(float a, float b);
    public:
        Battle(Engimon *e1, Engimon *e2);

        float getEngimon1Power();
        float getEngimon2Power();
        int getBattleWinner();

        virtual Engimon* getEngimonOne();
        virtual Engimon* getEngimonTwo();
};

#endif
