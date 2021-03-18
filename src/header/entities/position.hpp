// Position Class
// Standard static object for 2D position
// And standard enumeration for direction
#ifndef POSITION_HPP
#define POSITION_HPP

enum Direction {
    Up,
    Down,
    Left,
    Right
};

class Position {
    private:
        int posX;
        int posY;

    public:
        Position(int x, int y);
        bool operator==(const Position &pos2);
};

#endif
