// Player class
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "entity.hpp"
#include "direction.hpp"
#include "engimon.hpp"
#include "tile.hpp"

#define PLAYER_CHAR '\x99' // O with umlaut

class Player : public Entity {
    private:
        // Inventory<EngimonItem> EngimonInventory;
        // Inventory<SkillItem> EngimonInventory; // TODO : ??
        Engimon *currentEngimon;
        Direction lastDirection;

    public:
        Player();
        ~Player();
        void changeEngimon(Engimon *targetEngimon);
        Engimon* getCurrentEngimon();
        bool isMoveLocationValid(Tile& target) override; // Overriding virtual move() Entity
        Direction getLastDirection();
        Direction& getLastDirectionRef();
};

#endif
