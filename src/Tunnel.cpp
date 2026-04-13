//
// Created by garrido-lestachebeli on 4/8/2026.
//
#include <iostream>
#include "Tunnel.h"
#include "Map.h"

/************************************************************
 * Tunnel Constructor
 * ----------------------------------------------------------
 * Initializes tunnel with null exit and default position.
 ************************************************************/
Tunnel::Tunnel() : exit(nullptr) {}

/************************************************************
 * Tunnel::setExit
 * ----------------------------------------------------------
 * Sets the linked exit tunnel for teleportation.
 ************************************************************/
void Tunnel::setExit(Tunnel* exitTunnel) {
    exit = exitTunnel;
}


/************************************************************
 * Tunnel::print
 * ----------------------------------------------------------
 * Displays the tunnel character on the map.
 ************************************************************/
void Tunnel::print() const {std::cout<<"T";}

/************************************************************
 * Tunnel::activate
 * ----------------------------------------------------------
 * Teleports player to the linked exit tunnel.
 ************************************************************/
void Tunnel::activate(Map& map) {
    Player* player = map.getPlayer();
    auto [x, y] = player->getPosition();

    auto [tx, ty] = map.getOtherTunnel(x, y);

    std::cout << "You enter a tunnel...\n";

    map.move(x, y, tx, ty);
}

/************************************************************
 * Tunnel::printPhrase
 * ----------------------------------------------------------
 * Displays tunnel detection message to player.
 ************************************************************/
void Tunnel::printPhrase() const {std::cout<<"You feel a draft from somewhere..."<<std::endl;}
