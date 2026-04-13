//
// Created by garrido-lestachebeli on 4/8/2026.
//

#include "Guard.h"
#include <iostream>


/************************************************************
 * Guard Constructor
 * ----------------------------------------------------------
 * Initializes guard with zero stunned turns.
 ************************************************************/
Guard::Guard() : stunnedTurns_(0) {}

/************************************************************
 * Guard::setPosition
 * ----------------------------------------------------------
 * Sets the guard's position coordinates.
 ************************************************************/
void Guard::setPosition(int x, int y) {
    this->x = x;
    this->y = y;
}

/************************************************************
 * Guard::print
 * ----------------------------------------------------------
 * Displays the guard character on the map.
 ************************************************************/
void Guard::print() const {std::cout << "G" ; }

/************************************************************
 * Guard::printPhrase
 * ----------------------------------------------------------
 * Displays guard detection message to player.
 ************************************************************/
void Guard::printPhrase() const {std::cout<<"You see the glow of a flashlight up ahead..."<<std::endl;}

/************************************************************
 * Guard::getPosition
 * ----------------------------------------------------------
 * Returns the guard's current position.
 ************************************************************/
std::pair<int, int> Guard::getPosition() {return {x, y};}

/************************************************************
 * Guard::stun
 * ----------------------------------------------------------
 * Sets the guard's stunned turn counter.
 ************************************************************/
void Guard::stun(int turns) {
    stunnedTurns_ = turns;
}

/************************************************************
 * Guard::updateTurn
 * ----------------------------------------------------------
 * Decrements stunned turn counter if guard is stunned.
 ************************************************************/
void Guard::updateTurn() {
    if (stunnedTurns_ > 0) {
        stunnedTurns_--;
    }
}
