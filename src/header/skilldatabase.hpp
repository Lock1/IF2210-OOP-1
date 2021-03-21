// SkillDatabase class
// Need creating skill database with constraint
// - Every species have 1 unique skill

#ifndef SKILLDATABASE_HPP
#define SKILLDATABASE_HPP

#include "entities/attributes/skill.hpp"
#include "entities/engimon.hpp"
#include <string>
// #include <iostream>

class SkillDatabase {
    private:
        std::vector<Skill> skillDatabase;
    public:
        SkillDatabase();

        void loadSkillDatabase(std::string filename);
        // Load skill from database file, will throw filename if can't find file
        void addSkill(Skill newSkill);
        // Add skill to database
        bool isCompatible(Engimon engimonTarget, int skillID);
        // Search existing skillID in database and check engimon compatible or not
        // NOTE : Will throw skillID if not found
        Skill getSkill(int skillID);
        // Return skill with same skill ID, will throw skillID if not found
};

#endif
