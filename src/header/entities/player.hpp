// Player class
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "entity.hpp"
#include "direction.hpp"
#include "engimon.hpp"
#include "tile.hpp"
#include "../inventory"

#define PLAYER_CHAR '\x99' // O with umlaut

class Player : public Entity {
    private:
        Inventory<EngimonItem> engimonInventory;
        Inventory<SkillItem> skillInventory;
        Engimon *currentEngimon;
        Direction lastDirection;
        const unsigned maxInventorySize;

    public:
        Player(unsigned maxInv, unsigned maxSkillID);
        ~Player();
        void changeEngimon(Engimon *targetEngimon);
        Engimon* getCurrentEngimon();
        bool isMoveLocationValid(Tile& target) override; // Overriding virtual move() Entity
        Direction getLastDirection();
        Direction& getLastDirectionRef();

        bool addSkillItem(int skillID);
        bool delSkillItem(int skillID);
        bool addEngimonItem(EngimonItem engimon);
        bool delEngimonItem(EngimonItem engimon);
        std::map<SkillItem, int> getSkillInventory();
        std::list<EngimonItem> getEngimonInventory();
        int getEngimonInventoryCount();
};

#endif
