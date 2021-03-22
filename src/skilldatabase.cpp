//13519206
#include "header/entities/engimon.hpp"
#include "header/skilldatabase.hpp"
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <set>

using namespace std;

SkillDatabase::SkillDatabase() {

}

void SkillDatabase::addSkill(Skill newSkill) {
    skillDatabase.push_back(newSkill);
}


void SkillDatabase::loadSkillDatabase(string filename) {
    ifstream skillFile = ifstream(filename);
    if (skillFile.is_open()) {
        string skillName;
        int skillPower;
        int skillID;
        string typeString;
        ElementType skillElement;
        while (!skillFile.eof()) {
            skillFile >> skillID;
            skillFile >> skillName;
            skillFile >> skillPower;
            skillFile >> typeString;

            if (typeString == "Ground")
                skillElement = Ground;
            else if (typeString == "Electric")
                skillElement = Electric;
            else if (typeString == "Fire")
                skillElement = Fire;
            else if (typeString == "Water")
                skillElement = Water;
            else if (typeString == "Ice")
                skillElement = Ice;
            else
                skillElement = NoElement;

            addSkill(Skill(skillID, skillPower, skillName, skillElement));
        }

        skillFile.close();
    }
    else
        throw filename;
}

bool SkillDatabase::isCompatible(Engimon& engimonTarget, int skillID) {
    // TODO : Testing after species database done
    ElementType targetType = getSkill(skillID).getSkillElement();
    set<ElementType> engimonElements = engimonTarget.getElement();
    if (engimonElements.find(targetType) != engimonElements.end())
        return true;
    else
        return false;
}

Skill SkillDatabase::getSkill(int skillID) {
    for (unsigned int i = 0; i < skillDatabase.size(); i++)
        if (skillDatabase[i].getSkillID() == skillID)
            return skillDatabase[i];
    throw skillID;
}
