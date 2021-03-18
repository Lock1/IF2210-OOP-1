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
        std::vector<std::vector<Tile>> map;

    public:
        Map();
        ~Map();

        void loadFile();
        // Load from file // TODO : Extra, optional
        void wildEngimonRandomMove();
        // Move all wild pokemon with element type checking
        void spawnEngimon();
        // Spawn random engimon at random valid position
        void setTileEntity(const Position &pos, Entity *newEntity);
        // Change entity at position



};

#endif
