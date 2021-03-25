// 13519214
#include "../header/entities/map.hpp"
#include "../header/entities/direction.hpp"
#include "../header/entities/tile.hpp"
#include "../header/entities/entity.hpp"
#include "../header/entities/engimon.hpp"
#include <vector>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>

using namespace std;

Map::Map(unsigned int sX, unsigned int sY, unsigned int seaX, unsigned int seaY) : sizeX(sX), sizeY(sY),
        seaStartX(seaX), seaStartY(seaY), randomEngimonMoveProbability(15) {
    // Random seed initialize
    srand((unsigned int) time(NULL));
    for (unsigned int i = 0; i < sizeX; i++) {
        vector<Tile> column;
        for (unsigned int j = 0; j < sizeY; j++) {
            if (i > seaStartX && j > seaStartY)
                column.push_back(Tile(i, j, Sea));
            else
                column.push_back(Tile(i, j, Grass));
        }
        tileMatrix.push_back(column);
    }
}

Map::Map(string filename) : randomEngimonMoveProbability(20) {
    // Unused
    seaStartX = 0;
    seaStartY = 0;
    // TODO : Engimon loading (???), maybe not needed
    ifstream mapFile = ifstream(filename);
    if (mapFile.is_open()) {
        vector<vector<Tile>> flippedMap;
        string mapRow;
        unsigned int i = 0;
        while (getline(mapFile, mapRow)) {
            vector<Tile> column;
            sizeX = mapRow.length();
            for (unsigned int j = 0; j < mapRow.length(); j++) {
                if (mapRow[j] == 'o')
                    column.push_back(Tile(i, j, Sea));
                else
                    column.push_back(Tile(i, j, Grass));
            }
            i++;
            flippedMap.push_back(column);
        }
        sizeY = i;
        mapFile.close();

        // Flipping map
        for (i = 0; i < sizeX; i++) {
            vector<Tile> row;
            for (unsigned int j = 0; j < sizeY; j++)
                row.push_back(flippedMap[j][i]);
            tileMatrix.push_back(row);
        }
    }
    else
        throw filename;
}


void Map::wildEngimonRandomMove() {
    // TODO : Extra, flatten the conditional ladder, this is dumb
    for (unsigned int i = 0; i < sizeX; i++) {
        for (unsigned int j = 0; j < sizeY; j++) {
            // NULL pointer checking
            Entity *targetEntity = getEntityAt(i, j);
            if (targetEntity != NULL) {
                // Entity type checking
                if (targetEntity->getEntityID() == EntityEngimon) {
                    // Only cast if ID match
                    Engimon *targetEngimon = (Engimon *) targetEntity;
                    int randomNumber = rand() % 100;
                    if (randomNumber < randomEngimonMoveProbability && targetEngimon->isWildEngimon()) {
                        // TODO : Extra, More equal probability distribution
                        int randomDirection = rand() % 4;
                        Position targetPos = targetEntity->getPos();
                        switch (randomDirection) {
                            case 0:
                                if (targetPos.getY() > 0)
                                    if (getEntityAt(targetPos + Position(0, -1)) == NULL)
                                        if (targetEntity->isMoveLocationValid(getTileAt(targetPos + Position(0, -1))))
                                            moveEntity(targetPos, North);
                                break;
                            case 1:
                                if ((unsigned) targetPos.getY() < sizeY - 1)
                                    if (getEntityAt(targetPos + Position(0, 1)) == NULL)
                                        if (targetEntity->isMoveLocationValid(getTileAt(targetPos + Position(0, 1))))
                                            moveEntity(targetPos, South);
                                break;
                            case 2:
                                if (targetPos.getX() > 0)
                                    if (getEntityAt(targetPos + Position(-1, 0)) == NULL)
                                        if (targetEntity->isMoveLocationValid(getTileAt(targetPos + Position(-1, 0))))
                                            moveEntity(targetPos, West);
                                break;
                            case 3:
                                if ((unsigned) targetPos.getX() < sizeX - 1)
                                    if (getEntityAt(targetPos + Position(1, 0)) == NULL)
                                        if (targetEntity->isMoveLocationValid(getTileAt(targetPos + Position(1, 0))))
                                            moveEntity(targetPos, East);
                                break;
                        }
                    }
                }
            }
        }
    }
}

Engimon* Map::spawnWildEngimon(Species target) {
    bool isValidLocation = false;
    int randomX, randomY;
    do {
        randomX = rand() % sizeX;
        randomY = rand() % sizeY;
        if (getEntityAt(randomX, randomY) == NULL) {
            if (target.isTileCompatible(getTileTypeAt(randomX, randomY)))
                isValidLocation = true;
        }
    } while (!isValidLocation);

    Position targetPos = Position(randomX, randomY);
    Entity *wildEngimon = new Engimon(target, true, targetPos);
    setTileEntity(targetPos, wildEngimon);
    return (Engimon *) wildEngimon;
}

Engimon* Map::spawnWildEngimon(Species target, int levelCap) {
    bool isValidLocation = false;
    int randomX, randomY;
    do {
        randomX = rand() % sizeX;
        randomY = rand() % sizeY;
        if (getEntityAt(randomX, randomY) == NULL) {
            if (target.isTileCompatible(getTileTypeAt(randomX, randomY)))
                isValidLocation = true;
        }
    } while (!isValidLocation);

    Position targetPos = Position(randomX, randomY);
    Entity *wildEngimon = new Engimon(target, true, targetPos, (rand() % levelCap) + 1);

    setTileEntity(targetPos, wildEngimon);
    return (Engimon *) wildEngimon;
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

void Map::moveEntity(Position pos, Direction dir) {
    Entity* targetEntity = getEntityAt(pos);
    // Removing entity from current position at map
    setTileEntity(targetEntity->getPos(), NULL);
    // Changing entity position
    switch (dir) {
        case North:
            targetEntity->getPosRef() += Position(0, -1);
            break;
        case South:
            targetEntity->getPosRef() += Position(0, 1);
            break;
        case West:
            targetEntity->getPosRef() += Position(-1, 0);
            break;
        case East:
            targetEntity->getPosRef() += Position(1, 0);
            break;
    }
    // Set entity at new location in map
    setTileEntity(targetEntity->getPos(), targetEntity);
}
