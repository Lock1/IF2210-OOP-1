// Tile class
#ifndef TILE_HPP
#define TILE_HPP

#include "entity.hpp"
#include "position.hpp"

enum TileID {
    Grass,
    Sea
};

class Tile : public Position {
    private:
        Entity *entityPtr;
        TileID tileID;
    public:
        Tile(int x, int y, TileID tID);
        ~Tile();

        Entity* getEntity();
        // Get Entity pointer
        void setTileEntity(Entity *entity);
        // Change pointer with new entity pointer
        TileID getTileID();
        // Get TileID
        Position getTilePos();
        // Get Tile Position


        bool operator==(const Tile& target);
        // Return true if tileID match, doesn't care with entityPtr
};

#endif
