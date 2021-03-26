// Abstract class
#ifndef ENGIMONINTERACTION_HPP
#define ENGIMONINTERACTION_HPP

#include "entities/engimon.hpp"
class EngimonInteraction {
    protected:
        Engimon* e1;
        Engimon* e2;

    public:
        EngimonInteraction(Engimon* engimon1, Engimon* engimon2);
};

#endif
