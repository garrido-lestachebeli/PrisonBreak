//
// Created by garrido-lestachebeli on 4/8/2026.
//

#include "Exit.h"
#include <iostream>

Exit::Exit() {}

void Exit::activate(Map& map) {
    std::cout << "You found the exit...\n";
}
void Exit::print() const {}

void Exit::setPosition(int x, int y) {}

void Exit::printPhrase() const {std::cout<<"You see the warm glow of sunlight..."<<std::endl;}

