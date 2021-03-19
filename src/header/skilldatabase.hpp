    // SkillDatabase class
// Need creating skill database with constraint
// - Every species have 1 unique skill

#ifndef SKILLDATABASE_HPP
#define SKILLDATABASE_HPP

#include "entities/attributes/skill.hpp"
// TODO : Include engimon.hpp
class SkillDatabase {
    private:
        Skill* skillList; // TODO : Resolve List
        int nSkill;
    public:
        SkillDatabase();
        ~SkillDatabase();

        // void loadSkillDatabase(); // TODO : Resolve databate problem
        // Load from file

        void addSkill(const Skill &newSkill);
        // Add skill to database
        bool isCompatible(Engimon engimonTarget, int skillID);
        // Search existing skillID in database and check engimon compatible or not
}

#endif
