// Tile class
// Empty Tile constructed with User Constructor (int, int, TileType)
// Empty Tile is defined with entityPtr == NULL, and arbitrary Position and
#ifndef TILE_HPP
#define TILE_HPP

#include "entity.hpp"
#include "position.hpp"

enum TileType : char {
    Grass = '\xB1',
    Sea = '\xB0',
    Wall = '\xDB'
};

class Tile : public Position {
    private:
        Entity *entityPtr;
        TileType tileType;
    public:
        Tile(int x, int y, TileType tID);
        // User Constructor for empty tile

        Entity* getEntity();
        // Get Entity pointer
        void setTileEntity(Entity *entity);
        // Change pointer with new entity pointer
        TileType getTileType();
        // Get TileType
        Position getTilePos();
        // Get Tile Position

        bool operator==(TileType target);
        // Return true if TileType match, doesn't care with entityPtr
};

#endif
