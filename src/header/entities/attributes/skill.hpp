// Skill class
#ifndef SKILL_HPP
#define SKILL_HPP

#include "elementtype.hpp"
#include <string>

class Skill {
    private:
        int skillID;
        string skillName;
        int basePower;
        int masteryLevel;
        ElementType skillElement1;
        ElementType skillElement2;
        bool isMultiElement;

    public:
        // Skill database constructor
        Skill(int sID, int base, const string& name, ElementType type1, ElementType type2);
        // Optional second element, if type2 == NoElement, isMultiElement = false

        int getMasteryLevel();
        // Returning mastery level
        void levelUpMastery();
        // Add 1 level to mastery
        bool isElementCompatible(ElementType type);
        // Checking whether "type" compatible with element1 or element2
};

#endif
