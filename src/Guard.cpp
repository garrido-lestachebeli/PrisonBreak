//
// Created by garrido-lestachebeli on 4/8/2026.
//

#include "Guard.h"
#include <iostream>

void Guard::move(char direction, int space) {}

void Guard::detectHazard() {}

void Guard::moveTowardsPlayer() {}

void Guard::setPosition(int x, int y) {}

void Guard::print() const {}

void Guard::printPhrase() const {std::cout<<"You see the glow of a flashlight up ahead..."<<std::endl;}

std::pair<int, int> Guard::getPosition() {return {x, y};}