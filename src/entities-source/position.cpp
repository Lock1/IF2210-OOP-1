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

// Operator overloading on Position
bool Position::operator==(const Position &pos2) {
    return (this->posX == pos2.posX) && (this->posY == pos2.posY);
}

const Position& Position::operator=(const Position &pos2) {
    posX = pos2.posX;
    posY = pos2.posY;
    return (*this);
}

Position Position::operator+(const Position &pos2) {
    Position newPos = Position(this->posX, this->posY);
    newPos.posX += pos2.posX;
    newPos.posY += pos2.posY;
    return newPos;
}

const Position& Position::operator+=(const Position &pos2) {
    *this = *this + pos2;
    return (*this);
}


// Operator overloading on Tile
const Position& Position::operator=(const Tile &pos2) {
    posX = pos2.posX;
    posY = pos2.posY;
    return (*this);
}

Position Position::operator+(const Tile &pos2) {
    Position newPos = Position(this->posX, this->posY);
    newPos.posX += pos2.posX;
    newPos.posY += pos2.posY;
    return newPos;
}

const Position& Position::operator+=(const Tile &pos2) {
    *this = *this + pos2;
    return (*this);
}
