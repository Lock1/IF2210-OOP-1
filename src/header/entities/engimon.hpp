// Engimon class
// --- Constraint ---
// 1. Minimal 1 species for every type and combination element
#ifndef ENGIMON_HPP
#define ENGIMON_HPP

#include "attributes/elementtype.hpp"
#include "attributes/skill.hpp"
#include "entity.hpp"
#include <string>
#include <vector>

class Engimon : public Entity {
    private:
        int EngimonID;
        std::string Name;
        std::string parentName; // TODO : Species (?)
        // ii.    Parent Names & Species
        std::vector<Skill> learnedSkill;
        ElementType engimonElement1;
        ElementType engimonElement2;
        int Level;
        int Experience;
        int CumulativeExperience;
        bool isWild;
        bool isMultiElement;
        std::string InteractionDescription;
    public:
        Engimon(int newID, std::string newName); // WARNING : Basic, only for debugging
        Engimon(const Engimon& species); // TODO : Get from database

        // bool isMoveLocationValid() override; // TODO : Add
        bool xpGain(int gainedXP); // If Levelup -> return true, else false
        bool isMaxCXP(); // If over CumulativeExperience, return true
        bool addSkill(Skill& newSkill); // Only add if skill slot enough
        bool deleteskill(Skill& targetSkill);
        std::string playerInteract(); // Print description, only non-wild pokemon
};




#endif
