// 13519214
#include "../header/entities/map.hpp"
#include "../header/config.hpp"
#include <vector>

Map::Map() : sizeX(MAP_MAX_X), sizeY(MAP_MAX_Y) {
    for (int i = 0; i < MAP_MAX_Y; i++) {
        std::vector<Tile> column;
        for (int j = 0; j < MAP_MAX_X; j++) {
            if (i > SEA_STARTING_Y && j > SEA_STARTING_X)
                column.push_back(Tile(i, j, Sea));
            else
                column.push_back(Tile(i, j, Grass));
        }
        tileMatrix.push_back(column);
    }
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
