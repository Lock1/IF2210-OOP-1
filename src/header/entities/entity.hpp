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
        char entityChar;            // Entity representation on map
        static int entityCount;     // Total count of entity created

    public:
        Entity(int x, int y, EntityID eID, char eChar);
        Entity(Position pos, EntityID eID, char eChar);
        // User Constructor
        ~Entity();
        // Destructor

        virtual bool isMoveLocationValid(Tile &target);
        // Validity checker function, check whether tile is valid to move / not
        EntityID getEntityID();
        // Return entity ID
        Position& getPosRef();
        Position getPos();
        // Get position
        char getEntityChar();
        // Get entity character
        static unsigned int getEntityCount();
        // Get entity object count
};

#endif
