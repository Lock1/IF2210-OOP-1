// Position Class
// Standard static object for 2D position
// And standard enumeration for direction
#ifndef POSITION_HPP
#define POSITION_HPP

#include "direction.hpp"

class Tile;

class Position {
    private:
        int posX;
        int posY;

    public:
        Position(int x, int y);
        // User Constructor for position

        int getX();
        int getY();
        // Position getter

        Position operator+(const Position &pos2);
        Position operator+(const Tile &pos2);
        // Addition operator
        const Position& operator+=(const Position &pos2);
        const Position& operator+=(const Tile &pos2);
        // Addition Assignment operator
        const Position& operator=(const Position &pos2);
        const Position& operator=(const Tile &pos2);
        // Assignment operator
        bool operator==(const Position &pos2);
        // Return true if and only if both posX and posY are equal
};

#endif
