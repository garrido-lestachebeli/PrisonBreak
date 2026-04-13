//
// Created by garrido-lestachebeli on 4/8/2026.
//

#include "Camera.h"
#include <iostream>

/************************************************************
 * Camera Constructor
 * ----------------------------------------------------------
 * Initializes camera with zero deactivated turns.
 ************************************************************/
Camera::Camera() : deactivatedTurns_(0) {}

/************************************************************
 * Camera::activate
 * ----------------------------------------------------------
 * Activates camera to detect player and alert guards
 * if camera is not deactivated.
 ************************************************************/
void Camera::activate(Map& map) {
    // Skip activation if camera is deactivated
    if (deactivatedTurns_ > 0) {
        return;
    }
    
    Player* player = map.getPlayer();
    auto [x, y] = player->getPosition();

    std::cout << "A camera spots you! Guards are alerted!\n";

    map.setAlert(x, y);
}

/************************************************************
 * Camera::print
 * ----------------------------------------------------------
 * Displays the camera character on the map.
 ************************************************************/
void Camera::print() const {std::cout<<"C";}


/************************************************************
 * Camera::printPhrase
 * ----------------------------------------------------------
 * Displays camera detection message to player.
 ************************************************************/
void Camera::printPhrase() const {std::cout<<"You hear a faint mechanical whirring..."<<std::endl;}

/************************************************************
 * Camera::deactivate
 * ----------------------------------------------------------
 * Sets the camera's deactivated turn counter.
 ************************************************************/
void Camera::deactivate(int turns) {
    deactivatedTurns_ = turns;
}

/************************************************************
 * Camera::updateTurn
 * ----------------------------------------------------------
 * Decrements deactivated turn counter if camera is deactivated.
 ************************************************************/
void Camera::updateTurn() {
    if (deactivatedTurns_ > 0) {
        deactivatedTurns_--;
    }
}
