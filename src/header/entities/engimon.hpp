// Engimon class
// --- Constraint ---
// 1. Minimal 1 species for every type and combination element
#ifndef ENGIMON_HPP
#define ENGIMON_HPP

#include "attributes/elementtype.hpp"
#include "attributes/skill.hpp"
#include "tile.hpp"
#include "entity.hpp"
#include "species.hpp"
#include <string>
#include <vector>
#include <set>

class Engimon : public Entity, public Species {
    private:
        std::string engimonName;
        std::vector<Skill> learnedSkill;

        // TODO : Breeding interaction
        // vector<Species> parentSpecies;
        std::vector<std::string> parentNames;

        int level; // TODO : Getter
        int experience;
        int cumulativeExperience;
        bool isWild;

    public:
        Engimon(Position pos, ElementType type, char icon, bool wild);  // WARNING : Basic, only for debugging
        Engimon(Species species, bool wild, Position pos);
        // Engimon constructor
        // TODO : Breeding engimon constructor

        bool isMoveLocationValid(Tile &target) override;
        bool xpGain(int gainedXP);                                  // If Levelup -> return true, else false
        bool isMaxCXP();                                            // If over CumulativeExperience, return true
        bool addSkill(Skill newSkill);                             // Only add if skill slot enough
        bool deleteskill(Skill targetSkill);
        // TODO : isWild changer to false

        std::set<ElementType> getElement();
        std::string getEngimonName();

        bool isWildEngimon();
        std::string getInteractString();                               // Get description, only non-wild pokemon
};




#endif
