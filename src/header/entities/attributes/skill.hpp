// Skill class
#ifndef SKILL_HPP
#define SKILL_HPP

#include "elementtype.hpp"
#include <string>

class Skill {
    private:
        int skillID;
        std::string skillName;
        int basePower;
        ElementType skillElement;
        int masteryLevel;

    public:
        Skill(int sID, int base, std::string name, ElementType type);
        // Skill database constructor

        int getMasteryLevel();
        int getBasePower();
        int getSkillID();
        std::string getSkillName();
        ElementType getSkillElement();
        // Getter
        void levelUpMastery();
        // Add 1 level to mastery
        bool isElementCompatible(ElementType type);
        // Checking whether "type" compatible with element1 or element2
};

#endif
