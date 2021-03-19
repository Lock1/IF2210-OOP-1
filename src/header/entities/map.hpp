// Map class
// Can be treated as "database of tile"
#ifndef MAP_HPP
#define MAP_HPP

#include <vector>
#include "position.hpp"
#include "entity.hpp"
#include "tile.hpp"

class Map {
    private:
        std::vector<std::vector<Tile>> tileMatrix;

    public:
        Map();

        void loadFile();
        // Load from file // TODO : Extra, optional
        void wildEngimonRandomMove();
        // Move all wild pokemon with element type checking
        void spawnEngimon();
        // Spawn random engimon at random valid position
        void setTileEntity(int x, int y, Entity *newEntity);
        // Change entity at position
        Tile& getTileAt(int x, int y);
        // Get Tile at index located at position
        Entity* getEntityAt(int x, int y);
        // Get Tile at index located at position
        TileID getTileIDAt(int x, int y);
        // Get Tile ID at index located at position
};

#endif
