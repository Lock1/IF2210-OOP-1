// Map class
// Can be treated as "database of tile"
// NOTE : Map does not care with heap object
#ifndef MAP_HPP
#define MAP_HPP

#include <vector>
#include "direction.hpp"
#include "position.hpp"
#include "entity.hpp"
#include "tile.hpp"

class Map {
    private:
        std::vector<std::vector<Tile>> tileMatrix;
        const unsigned int sizeX;
        const unsigned int sizeY;
        const unsigned int seaStartX;
        const unsigned int seaStartY;
    public:
        Map(unsigned int sX, unsigned int sY, unsigned int seaX, unsigned int seaY);

        int getSizeX();
        int getSizeY();
        // Getter

        void loadFile();                // TODO : Extra, optional
        // Load from file
        void wildEngimonRandomMove();   // TODO : Add
        // Move all wild pokemon with element type checking
        void spawnEngimon();            // TODO : Add
        // Spawn random engimon at random valid position
        void setTileEntity(int x, int y, Entity *newEntity);
        void setTileEntity(Position pos, Entity *newEntity);
        // Change entity at position
        Tile& getTileAt(int x, int y);
        Tile& getTileAt(Position pos);
        // Get Tile at index located at position
        Entity* getEntityAt(int x, int y);
        Entity* getEntityAt(Position pos);
        // Get Tile at index located at position
        TileType getTileTypeAt(int x, int y);
        TileType getTileTypeAt(Position pos);
        // Get Tile ID at index located at position

        void moveEntity(Position pos, Direction dir);
        // Move entity at map to target direction without checking
};

#endif
