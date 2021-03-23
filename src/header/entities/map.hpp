// Map class
// Can be treated as "database of tile"
// NOTE : Map does not care with heap object
#ifndef MAP_HPP
#define MAP_HPP

#include "direction.hpp"
#include "position.hpp"
#include "entity.hpp"
#include "engimon.hpp"
#include "tile.hpp"
#include "species.hpp"
#include <vector>
#include <string>

class Map {
    private:
        std::vector<std::vector<Tile>> tileMatrix;
        unsigned int sizeX;
        unsigned int sizeY;
        unsigned int seaStartX;
        unsigned int seaStartY;
        const unsigned short int randomEngimonMoveProbability;
        // Probability in percent, default value is 15%

    public:
        Map(unsigned int sX, unsigned int sY, unsigned int seaX, unsigned int seaY);
        Map(std::string filename);

        int getSizeX();
        int getSizeY();
        // Getter

        void wildEngimonRandomMove();
        // Move all wild pokemon with element type checking
        Engimon* spawnWildEngimon(Species target);
        Engimon* spawnWildEngimon(Species target, int levelCap);
        // Spawn random wild engimon at random valid position,
        // returning allocated heap pointer
        // WARNING : Will allocating at heap memory

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
