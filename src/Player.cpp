//
// Created by garrido-lestachebeli on 4/8/2026.
//

#include "Map.h"
#include "Player.h"
#include <iostream>

/************************************************************
 * Player Constructor
 * ----------------------------------------------------------
 * Initializes player with specified EMP and flashbang ammo.
 ************************************************************/
Player::Player(int empAmmo, int flashbangAmmo) : empAmmo_(empAmmo), flashbangAmmo_(flashbangAmmo) {}


/************************************************************
 * Player::setPosition
 * ----------------------------------------------------------
 * Sets the player's position coordinates.
 ************************************************************/
void Player::setPosition(int x, int y) {
    this->x = x;
    this->y = y;
}

/************************************************************
 * Player::print
 * ----------------------------------------------------------
 * Displays the player character on the map.
 ************************************************************/
void Player::print() const {std::cout<<"P";}

/************************************************************
 * Player::getPosition
 * ----------------------------------------------------------
 * Returns the player's current position.
 ************************************************************/
std::pair<int, int> Player::getPosition() {
    return {x, y};
}

/************************************************************
 * Player::printPhrase
 * ----------------------------------------------------------
 * Displays player identification message.
 ************************************************************/
void Player::printPhrase() const {}

/************************************************************
 * Player::useWeapon
 * ----------------------------------------------------------
 * Uses specified weapon type if ammo is available.
 ************************************************************/
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
