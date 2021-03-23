// 13519214

#include "../header/entities/engimon.hpp"
#include "../header/entities/entity.hpp"
#include "../header/entities/tile.hpp"
#include <set>
#include <vector>

using namespace std;


Engimon::Engimon(Species species, bool wild, Position pos) : Species(species), Entity(pos, EntityEngimon, species.getSpeciesChar()) {
    level = rand() % 20;
    experience = 0;
    cumulativeExperience = 0;
    isWild = wild;
    engimonName = speciesName;

    Skill speciesSkill = baseSkill;
    speciesSkill.levelUpMastery();
    addSkill(speciesSkill);
}

Engimon::Engimon(Species species, bool wild, Position pos, int startLevel) : Species(species), Entity(pos, EntityEngimon, species.getSpeciesChar()) {
    level = startLevel;
    experience = 0;
    cumulativeExperience = 0;
    isWild = wild;
    engimonName = speciesName;

    Skill speciesSkill = baseSkill;
    speciesSkill.levelUpMastery();
    addSkill(speciesSkill);
}

bool Engimon::addSkill(Skill newSkill) {
    if (learnedSkill.size() < 4) {
        auto it = learnedSkill.begin();
        bool isFound = false;
        while (it != learnedSkill.end() && not isFound) {
            if ((*it) == newSkill)
                isFound = true;
            ++it;
        }
        if (not isFound) {
            learnedSkill.push_back(newSkill);
            return true;
        }
    }
    return false;
}

bool Engimon::deleteSkill(int targetSkillID) {
    auto it = learnedSkill.begin();
    bool isFound = false;
    while (it != learnedSkill.end() && not isFound) {
        if ((*it).getSkillID() == targetSkillID) {
            learnedSkill.erase(it);
            isFound = true;
        }
        ++it;
    }
    if (isFound)
        return true;
    else
        return false;
}

bool Engimon::isMaxCXP() {
    if (cumulativeExperience > 100)
        return true;
    else
        return false;
}

bool Engimon::xpGain(int gainedXP) {
    experience += gainedXP;
    cumulativeExperience += gainedXP;
    if (experience > 100) {
        level += (experience/100);
        experience %= 100;
        return true;
    }
    return false;
}

vector<Skill> Engimon::getSkillList() {
    return learnedSkill;
}


set<ElementType> Engimon::getElement() {
    return elements;
}

string Engimon::getEngimonName() {
    return engimonName;
}

bool Engimon::isMoveLocationValid(Tile& target) {
    if (target.getEntity() == NULL && Species::isTileCompatible(target.getTileType()))
        return true;
    else
        return false;
}

bool Engimon::isWildEngimon() {
    return isWild;
}

int Engimon::getLevel() {
    return level;
}

int Engimon::getXP() {
    return experience;
}

void Engimon::tameEngimon() {
    isWild = false;
}

string Engimon::getInteractString() {
    return interactionDescription;
}

vector<Species> Engimon::getParentSpecies() {
    return parentSpecies;
}

vector<std::string> Engimon::getParentNames() {
    return parentNames;
}
