#include "../header/entities/tile.hpp"

Tile::Tile(int x, int y, TileID tID) : Position(x, y) {
    tileID = tID;
}

Tile::~Tile() {

}
