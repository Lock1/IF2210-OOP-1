// Entity class implementation
#include "../header/entities/entity.hpp"
#include "../header/entities/tile.hpp"
#include <iostream>

int Entity::entityCount = 0;
// Starting count for entity

Entity::Entity(int x, int y, EntityID eID, char eChar) : entityID(eID), currentPosition(x, y), entityChar(eChar) {
    entityCount++;
}

Entity::~Entity() {
    entityCount--;
}

bool Entity::isMoveLocationValid(Tile &target) {
    if (target.getEntity() != NULL)
        return false;
    else
        return true;
}

EntityID Entity::getEntityID() {
    return entityID;
}

Position& Entity::getPosRef() {
    return currentPosition;
}

Position Entity::getPos() {
    return currentPosition;
}

char Entity::getEntityChar() {
    return entityChar;
}

int Entity::getEntityCount() {
    return entityCount;
}
