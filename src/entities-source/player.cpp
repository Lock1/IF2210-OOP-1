// Player class

#include "../header/entities/player.hpp"
#include "../header/entities/entity.hpp"
#include "../header/entities/engimon.hpp"
#include <iostream>

Player::Player() : Entity(1, 1, EntityPlayer, PLAYER_CHAR), lastPosition(1, 0) {
    currentEngimon = NULL;
}

Player::~Player() {
    // TODO : Maybe not needed
}

void Player::changeEngimon(Engimon *targetEngimon) {
    currentEngimon = targetEngimon;
}

bool Player::isMoveLocationValid(Tile& target) {
    // TODO : If engimon -> false
    if (target.getEntity() == NULL)
        return true;
    else
        return false;
}

Position Player::getLastPosition() {
    return lastPosition;
}

Position& Player::getLastPositionRef() {
    return lastPosition;
}
