// 13519214

#include "../header/entities/engimon.hpp"
#include "../header/entities/entity.hpp"
#include "../header/entities/tile.hpp"


Engimon::Engimon(Position pos, ElementType type1, char icon, bool wild) : Entity(pos, EntityEngimon, icon),
        engimonElement1(type1) {
    isWild = wild;
}
// WARNING : Basic, only for debugging

// Engimon::Engimon(const Engimon& species) {
//
// }
// TODO : Get from database


bool Engimon::isTileCompatible(TileType type) {
    if ((engimonElement1 == Ice || engimonElement1 == Water) && (type == Sea))
        return true;
    else if (type == Grass)
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
