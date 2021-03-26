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
        std::vector<Species> parentSpecies;
        std::vector<std::string> parentNames;

        int level;
        int experience;
        int cumulativeExperience;
        bool isWild;

    public:
        Engimon(Species species, bool wild, Position pos);
        Engimon(Species species, bool wild, Position pos, int startLevel);
        // Engimon constructor

        bool isMoveLocationValid(Tile& target) override;
        int xpGain(int gainedXP); // Returning level up count
        bool isMaxCXP();                                            // If over CumulativeExperience, return true
        bool addSkill(Skill newSkill);
        // Only add if skill slot enough and not learned returning false if failed
        bool deleteSkill(int targetSkillID);
        void tameEngimon();

        std::vector<Skill> getSkillList();
        std::vector<Skill>& getSkillListRef();

        std::vector<Species> getParentSpecies();
        std::vector<std::string> getParentNames();

        void addParentSpecies(Species parent);
        void addParentName(std::string parent);

        std::set<ElementType> getElement();
        std::string getEngimonName();
        void setEngimonName(std::string target);
        int getLevel();
        int getXP();
        int getLearnedSkillCount();

        void breedingLevelDown();

        bool isWildEngimon();
        std::string getInteractString();                               // Get description, only non-wild pokemon
};




#endif
