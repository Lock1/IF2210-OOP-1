#include "../header/entities/tile.hpp"
#include <iostream>

Tile::Tile(int x, int y, TileType tID) : Position(x, y), tileType(tID) {
    entityPtr = NULL;
}

Tile::~Tile() {

}

void Tile::setTileEntity(Entity *entity) {
    entityPtr = entity;
}

TileType Tile::getTileType() {
    return tileType;
}

Entity* Tile::getEntity() {
    return entityPtr;
}
