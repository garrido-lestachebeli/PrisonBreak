//
// Created by garrido-lestachebeli on 4/8/2026.
//

#include "Exit.h"
#include <iostream>

/************************************************************
 * Exit Constructor
 * ----------------------------------------------------------
 * Initializes exit room with default settings.
 ************************************************************/
Exit::Exit() {}

/************************************************************
 * Exit::activate
 * ----------------------------------------------------------
 * Activates exit room to trigger win condition.
 ************************************************************/
void Exit::activate(Map& map) {
    std::cout << "You found the exit...\n";
}

/************************************************************
 * Exit::print
 * ----------------------------------------------------------
 * Displays the exit character on the map.
 ************************************************************/
void Exit::print() const {std::cout<<"E";}

/************************************************************
 * Exit::printPhrase
 * ----------------------------------------------------------
 * Displays exit detection message to player.
 ************************************************************/
void Exit::printPhrase() const {std::cout<<"You see the warm glow of sunlight..."<<std::endl;}

