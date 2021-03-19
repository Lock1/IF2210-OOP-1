// Entity class implementation
#include "../header/entities/entity.hpp"

int Entity::entityCount = 0;
// Starting count for entity

Entity::Entity(int x, int y, EntityID eID, char eChar) : entityID(eID), currentPosition(x, y), entityChar(eChar) {
    entityCount++;
}

Entity::~Entity() {
    entityCount--;
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

char Entity::getEntityChar() {
    return entityChar;
}

int Entity::getEntityCount() {
    return entityCount;
}
