//
// Created by garrido-lestachebeli on 4/8/2026.
//

#include "Player.h"
#include <iostream>

#include "Map.h"

Player::Player(int empAmmo, int flashbangAmmo) : empAmmo_(empAmmo), flashbangAmmo_(flashbangAmmo) {}

void Player::move(char direction, int spaces) {}

void Player::detectHazard() {}

void Player::setPosition(int x, int y) {
    this->x = x;
    this->y = y;
}

void Player::print() const {std::cout<<"P";}

std::pair<int, int> Player::getPosition() {
    return {x, y};
}

void Player::printPhrase() const {}

bool Player::useWeapon(WeaponType type) {
    switch (type) {
        case WeaponType::EMP:
            if (empAmmo_ > 0) {
                empAmmo_--;
                return true;
            }
            break;
        case WeaponType::FLASHBANG:
            if (flashbangAmmo_ > 0) {
                flashbangAmmo_--;
                return true;
            }
            break;
    }
    return false;
}
