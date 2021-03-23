// Battle class
#ifndef BATTLE_HPP
#define BATTLE_HPP

#include "entities/engimon.hpp"
#include "entities/attributes/elementtype.hpp"

class Battle {
    private:
        int winnerNumber;
        float getElementAdvantage(ElementType elem1, ElementType elem2);
    public:
        Battle(Engimon *e1, Engimon *e2);

        int getBattleWinner();
};

#endif
