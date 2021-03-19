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
        unsigned char entityChar;

    public:
        Entity(int x, int y, EntityID eID, unsigned char eChar);
        // User Constructor

        virtual bool move(const Tile &dir);
        EntityID getEntityID();
        const Position& getPos();
        unsigned char getEntityChar();
};

#endif
