#include "header/entities/engimon.hpp"
#include "header/skilldatabase.hpp"
#include "header/speciesdatabase.hpp"
#include "header/entities/species.hpp"
#include "engimoninteraction.hpp"
#include <string>
#include <set>

class Breed : public EngimonInteraction {
    private:
        float getElementAdvantage(ElementType elem1, ElementType elem2);
    public:
        Breed(Engimon* e1, Engimon* e2);
        Engimon* startBreeding(SpeciesDatabase& speciesDB);
        virtual Engimon* getEngimonOne();
        virtual Engimon* getEngimonTwo();
};
