//
// Created by garrido-lestachebeli on 4/8/2026.
//

#include "EmptyRoom.h"

#include <iostream>

/************************************************************
 * EmptyRoom Constructor
 * ----------------------------------------------------------
 * Initializes empty room with default settings.
 ************************************************************/
EmptyRoom::EmptyRoom() {}

/************************************************************
 * EmptyRoom::activate
 * ----------------------------------------------------------
 * Activates empty room.
 ************************************************************/
void EmptyRoom::activate(Map& map) {}

/************************************************************
 * EmptyRoom::print
 * ----------------------------------------------------------
 * Displays the empty room character on the map.
 ************************************************************/
void EmptyRoom::print() const {std::cout<<".";}


/************************************************************
 * EmptyRoom::printPhrase
 * ----------------------------------------------------------
 * Displays empty room message.
 ************************************************************/
void EmptyRoom::printPhrase() const {}