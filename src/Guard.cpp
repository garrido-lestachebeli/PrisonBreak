//
// Created by garrido-lestachebeli on 4/8/2026.
//

#include "Guard.h"
#include <iostream>

void Guard::move(char direction, int space) {}

void Guard::detectHazard() {}

Guard::Guard() : stunnedTurns_(0) {}

void Guard::setPosition(int x, int y) {
    this->x = x;
    this->y = y;
}

void Guard::print() const {std::cout << "G" ; }

void Guard::printPhrase() const {std::cout<<"You see the glow of a flashlight up ahead..."<<std::endl;}

std::pair<int, int> Guard::getPosition() {return {x, y};}

void Guard::stun(int turns) {
    stunnedTurns_ = turns;
}

void Guard::updateTurn() {
    if (stunnedTurns_ > 0) {
        stunnedTurns_--;
    }
}
