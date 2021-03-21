// Player class

#include "../header/entities/player.hpp"
#include "../header/entities/entity.hpp"
#include "../header/entities/engimon.hpp"
#include <iostream>

Player::Player() : Entity(1, 0, EntityPlayer, PLAYER_CHAR), lastDirection(East) {
    currentEngimon = NULL;

}

Player::~Player() {
    // TODO : Maybe not needed
}

void Player::changeEngimon(Engimon *targetEngimon) {
    currentEngimon = targetEngimon;
}

Engimon* Player::getCurrentEngimon() {
    return currentEngimon;
}

bool Player::isMoveLocationValid(Tile& target) {
    // TODO : If engimon -> false
    if (target.getEntity() == NULL)
        return true;
    else
        return false;
}

Direction Player::getLastDirection() {
    return lastDirection;
}

Direction& Player::getLastDirectionRef() {
    return lastDirection;
}
