// Player class
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "entity.hpp"
#include "tile.hpp"

#define PLAYER_CHAR '\x99' // O with umlaut

class Player : public Entity {
    private:
        // Inventory<EngimonItem> EngimonInventory;
        // Inventory<SkillItem> EngimonInventory; // TODO : ??
        // Engimon *currentEngimon;
        Position lastPosition;

    public:
        Player();
        ~Player();
        void changeEngimon();       // TODO : Add
        bool isMoveLocationValid(Tile& target) override; // Overriding virtual move() Entity
        Position getLastPosition(); // TODO : Add
};

#endif
