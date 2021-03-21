// 13519214

#include "../header/entities/engimon.hpp"
#include "../header/entities/entity.hpp"
#include "../header/entities/tile.hpp"
#include <set>

using namespace std;


Engimon::Engimon(Position pos, ElementType type1, char icon, bool wild) : Entity(pos, EntityEngimon, icon) {
    isWild = wild;
    engimonElement.insert(type1);
}
// WARNING : Basic, only for debugging

// Engimon::Engimon(const Engimon& species) {
//
// }
// TODO : Get from database


// Engimon::Engimon(const Species& species, bool wild, Position pos) : Species(species) {
//     this->isWild = wild;
//     this->currentPosition = pos;
// }


set<ElementType> Engimon::getElement() {
    return engimonElement;
}


bool Engimon::isTileCompatible(TileType type) {
    bool isAbleToTraverseSea = (engimonElement.find(Water) != engimonElement.end()) || (engimonElement.find(Ice) != engimonElement.end());
    bool isAbleToTraverseGrass = (engimonElement.find(Fire) != engimonElement.end())
                                    || (engimonElement.find(Ground) != engimonElement.end())
                                    || (engimonElement.find(Electric) != engimonElement.end());
    if (isAbleToTraverseSea && (type == Sea))
        return true;
    else if (isAbleToTraverseGrass && (type == Grass))
        return true;
    else
        return false;
}

bool Engimon::isMoveLocationValid(Tile& target) {
    if (target.getEntity() == NULL && isTileCompatible(target.getTileType()))
        return true;
    else
        return false;
}

bool Engimon::isWildEngimon() {
    return isWild;
}
