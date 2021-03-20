// 13519214
#include "../header/entities/map.hpp"
#include <vector>

Map::Map(unsigned int sX, unsigned int sY, unsigned int seaX, unsigned int seaY) : sizeX(sX), sizeY(sY), seaStartX(seaX), seaStartY(seaY) {
    for (unsigned int i = 0; i < sizeX; i++) {
        std::vector<Tile> column;
        for (unsigned int j = 0; j < sizeY; j++) {
            if (i > seaStartX && j > seaStartY)
                column.push_back(Tile(i, j, Sea));
            else
                column.push_back(Tile(i, j, Grass));
        }
        tileMatrix.push_back(column);
    }
}

void Map::wildEngimonRandomMove() {
    // for (int i = 0; i < sizeX; i++) {
    //     for (int j = 0; j < sizeY; j++) {
    //
    //     }
    // }
}



void Map::setTileEntity(int x, int y, Entity *newEntity) {
    tileMatrix[x][y].setTileEntity(newEntity);
}

void Map::setTileEntity(Position pos, Entity *newEntity) {
    tileMatrix[pos.getX()][pos.getY()].setTileEntity(newEntity);
}

int Map::getSizeX() {
    return sizeX;
}

int Map::getSizeY() {
    return sizeY;
}


Tile& Map::getTileAt(int x, int y) {
    return tileMatrix[x][y];
}

Entity* Map::getEntityAt(int x, int y) {
    return tileMatrix[x][y].getEntity();
}

TileType Map::getTileTypeAt(int x, int y) {
    return tileMatrix[x][y].getTileType();
}

// Overloaded with Position
Tile& Map::getTileAt(Position pos) {
    return tileMatrix[pos.getX()][pos.getY()];
}

Entity* Map::getEntityAt(Position pos) {
    return tileMatrix[pos.getX()][pos.getY()].getEntity();
}

TileType Map::getTileTypeAt(Position pos) {
    return tileMatrix[pos.getX()][pos.getY()].getTileType();
}
