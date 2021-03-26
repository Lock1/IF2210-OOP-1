#include "header/entities/engimon.hpp"
#include "header/skilldatabase.hpp"
#include "header/speciesdatabase.hpp"
#include "header/entities/species.hpp"
#include <string>
#include <set>

class Breed {
    private:
        Engimon* parent1;
        Engimon* parent2;
        float getElementAdvantage(ElementType elem1, ElementType elem2);
    public:
        Breed(Engimon* e1, Engimon* e2);
        Engimon* startBreeding(SpeciesDatabase& speciesDB);
};
