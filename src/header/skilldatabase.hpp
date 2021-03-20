// SkillDatabase class
// Need creating skill database with constraint
// - Every species have 1 unique skill

#ifndef SKILLDATABASE_HPP
#define SKILLDATABASE_HPP

#include "entities/attributes/skill.hpp"
#include <vector>
// TODO : Include engimon.hpp
class SkillDatabase {
    private:
        std::vector<Skill> skillDatabase;
    public:
        SkillDatabase();

        void addSkill(Skill &newSkill);
        // Add skill to database
        bool isCompatible(Engimon engimonTarget, int skillID);
        // Search existing skillID in database and check engimon compatible or not
}

#endif
