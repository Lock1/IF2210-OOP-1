// Player class

#include "../header/entities/player.hpp"
#include "../header/entities/entity.hpp"
#include <iostream>

Player::Player() : Entity(0, 0, EntityPlayer, 'o'), lastPosition(0, 0) {

}

Player::~Player() {
    // TODO : Maybe not needed
}

void Player::changeEngimon() {
    // TODO : Add
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
