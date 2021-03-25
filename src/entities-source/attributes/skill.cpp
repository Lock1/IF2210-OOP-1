// Skill class implementation

#include "../../header/entities/attributes/elementtype.hpp"
#include "../../header/entities/attributes/skill.hpp"
#include <string>

using namespace std;

Skill::Skill(int sID, int base, string name, ElementType type) {
    skillID = sID;
    skillName = name;
    basePower = base;
    masteryLevel = 0;
    skillElement = type;
}

int Skill::getMasteryLevel() {
    return masteryLevel;
}

int Skill::getBasePower() {
    return basePower;
}

string Skill::getSkillName() {
    return skillName;
}

ElementType Skill::getSkillElement() {
    return skillElement;
}

int Skill::getSkillID() {
    return skillID;
}

void Skill::levelUpMastery() {
    masteryLevel += 1;
}

bool Skill::isElementCompatible(ElementType type) {
    if (skillElement == type)
        return true;
    else
        return false;
}

bool Skill::operator==(const Skill& target) {
    if (target.skillID == skillID)
        return true;
    else
        return false;
}
