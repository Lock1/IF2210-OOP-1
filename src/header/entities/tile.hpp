// Tile class
// Empty Tile constructed with User Constructor (int, int, TileType)
// Empty Tile is defined with entityPtr == NULL, and arbitrary Position and
#ifndef TILE_HPP
#define TILE_HPP

#include "../config.hpp"
#include "entity.hpp"
#include "position.hpp"

enum TileType {
    Grass = TILE_GRASS,
    Sea = TILE_SEA
};

class Tile : public Position {
    private:
        Entity *entityPtr;
        TileType tileType;
    public:
        Tile(int x, int y, TileType tID);
        // User Constructor for empty tile
        ~Tile();

        Entity* getEntity();
        // Get Entity pointer
        void setTileEntity(Entity *entity);
        // Change pointer with new entity pointer
        TileType getTileType();
        // Get TileType
        Position getTilePos();
        // Get Tile Position


        bool operator==(const Tile& target);
        // Return true if TileType match, doesn't care with entityPtr
};

#endif
