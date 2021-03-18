#include "../header/entities/tile.hpp"
#include <iostream>

Tile::Tile(int x, int y, TileID tID) : Position(x, y), tileID(tID) {
    entityPtr = NULL;
}

Tile::~Tile() {

}

TileID Tile::getTileID() {
    return tileID;
}
