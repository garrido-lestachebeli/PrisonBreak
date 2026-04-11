//
// Created by garrido-lestachebeli on 4/8/2026.
//

#include "Player.h"
#include <iostream>

#include "Map.h"

void Player::move(char direction, int spaces) {}

void Player::detectHazard() {}

void Player::setPosition(int x, int y) {}

void Player::print() const {std::cout<<"P";}

std::pair<int, int> Player::getPosition() {
    return {x, y};
}

void Player::printPhrase() const {}