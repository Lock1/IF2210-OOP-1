#include "../header/entities/entity.hpp"


Entity::Entity(int x, int y, EntityID eID, unsigned char eChar) : entityID(eID), currentPosition(x, y), entityChar(eChar) {

}


bool Entity::move(const Tile &dir) {
    currentPosition += dir;
    return true;
}

EntityID Entity::getEntityID() {
    return entityID;
}

const Position& Entity::getPos() {
    return currentPosition;
}
