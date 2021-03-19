#include "../header/entities/entity.hpp"


Entity::Entity(int x, int y, EntityID eID) : entityID(eID), currentPosition(x, y) {
    
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
