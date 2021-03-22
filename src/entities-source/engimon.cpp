// 13519214

#include "../header/entities/engimon.hpp"
#include "../header/entities/entity.hpp"
#include "../header/entities/tile.hpp"
#include <set>

using namespace std;


Engimon::Engimon(Position pos, ElementType type1, char icon, bool wild) : Entity(pos, EntityEngimon, icon) {
    isWild = wild;
    // engimonElement.insert(type1);
    // WARNING : Basic, only for debugging
}

Engimon::Engimon(Species species, bool wild, Position pos) : Species(species), Entity(pos, EntityEngimon, species.getSpeciesChar()) {
    Level = 9; // TODO : Level random
    Experience = 0;
    CumulativeExperience = 0;
    isWild = wild;

    // bool addSkill(Skill newSkill);           TODO : Add skill from species
    // bool deleteskill(Skill targetSkill);
}

// bool addSkill(Skill newSkill);          TODO : Add
// bool deleteskill(Skill targetSkill);


set<ElementType> Engimon::getElement() {
    return elements;
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
