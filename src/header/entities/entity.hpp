// Entity class
// Any object in map is derived class from entity
#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "position.hpp"
class Tile;
// Forward declaration of class Tile, for resolving circular reference problem

enum EntityID {
    EntityPlayer,
    EntityEngimon,
    NullEntity
};

class Entity {
    protected:
        EntityID entityID;
        Position currentPosition;

    public:
        Entity(int x, int y, EntityID eID);

        virtual bool move(const Tile &dir);
        EntityID getEntityID();
        const Position& getPos();
};

#endif
