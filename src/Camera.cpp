//
// Created by garrido-lestachebeli on 4/8/2026.
//

#include "Camera.h"
#include <iostream>

#include "Character.h"

Camera::Camera() : deactivatedTurns_(0) {}

void Camera::activate(Map& map) {
    if (deactivatedTurns_ > 0) {
        return; // Camera is deactivated
    }
    
    Player* player = map.getPlayer();
    auto [x, y] = player->getPosition();

    std::cout << "A camera spots you! Guards are alerted!\n";

    map.setAlert(x, y);
}

void Camera::print() const {}

void Camera::setPosition(int x, int y) {}

void Camera::printPhrase() const {std::cout<<"You hear a faint mechanical whirring..."<<std::endl;}

void Camera::deactivate(int turns) {
    deactivatedTurns_ = turns;
}

void Camera::updateTurn() {
    if (deactivatedTurns_ > 0) {
        deactivatedTurns_--;
    }
}
