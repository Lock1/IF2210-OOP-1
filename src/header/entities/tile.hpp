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

        void setEntity(Entity *entity);
        // Change pointer with new pointer
        EntityID getEntityID();
        // Get EntityID from entity pointed
        TileID getTileID();
        // Get TileID
        Position getTilePos();
        // Get Tile Position
};

#endif
