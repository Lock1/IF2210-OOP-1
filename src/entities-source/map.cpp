// 13519214
#include "../header/entities/map.hpp"
#include "../header/config.hpp"
#include <vector>

Map::Map() {
    for (int i = 0; i < MAP_MAX_X; i++) {
        std::vector<Tile> column;
        for (int j = 0; j < MAP_MAX_Y; j++) {
            if (i > 20 && j > 10)
                column.push_back(Tile(i, j, Sea));
            else
                column.push_back(Tile(i, j, Grass));
        }
        tileMatrix.push_back(column);
    }
}

Tile& Map::getTileAt(int x, int y) {
    return tileMatrix[x][y];
}

TileID Map::getTileIDAt(int x, int y) {
    return tileMatrix[x][y].getTileID();
}
