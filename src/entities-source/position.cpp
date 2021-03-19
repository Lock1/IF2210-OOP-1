// 13519214
#include "../header/entities/position.hpp"
#include "../header/entities/tile.hpp"

Position::Position(int x, int y) : posX(x), posY(y) {
}

int Position::getX() {
    return posX;
}

int Position::getY() {
    return posY;
}

bool Position::operator==(const Position &pos2) {
    return (this->posX == pos2.posX) && (this->posY == pos2.posY);
}

const Position& Position::operator=(const Position &pos2) {
    posX = pos2.posX;
    posY = pos2.posY;
    return (*this);
}

const Position& Position::operator+(const Position &pos2) {
    posX += pos2.posX;
    posY += pos2.posY;
    return (*this);
}

const Position& Position::operator+=(const Position &pos2) {
    *this = *this + pos2;
    return (*this);
}


// TODO : Cleanup (?)
const Position& Position::operator=(const Tile &pos2) {
    posX = pos2.posX;
    posY = pos2.posY;
    return (*this);
}

const Position& Position::operator+(const Tile &pos2) {
    posX += pos2.posX;
    posY += pos2.posY;
    return (*this);
}

const Position& Position::operator+=(const Tile &pos2) {
    *this = *this + pos2;
    return (*this);
}
