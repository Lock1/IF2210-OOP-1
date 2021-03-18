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
    private:
        EntityID entityID;
        Position currentPosition;
    public:
        Entity();
        ~Entity();

        virtual bool move(const Tile &dir);
        int getEntityID();
        Position getPos();
};

#endif
