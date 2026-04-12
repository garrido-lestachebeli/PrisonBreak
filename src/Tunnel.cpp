//
// Created by garrido-lestachebeli on 4/8/2026.
//
#include <iostream>
#include "Tunnel.h"

#include "Character.h"
#include "Map.h"

Tunnel::Tunnel() : exit(nullptr) {
    this->x = 0;
    this->y = 0;
}

void Tunnel::setExit(Tunnel* exitTunnel) {
    exit = exitTunnel;
}

Tunnel* Tunnel::getExit() const {
    return exit;
}

void Tunnel::print() const {std::cout<<"T";}

void Tunnel::activate(Map& map) {
    Player* player = map.getPlayer();
    auto [x, y] = player->getPosition();

    auto [tx, ty] = map.getOtherTunnel(x, y);

    std::cout << "You enter a tunnel...\n";

    map.move(x, y, tx, ty);
}

void Tunnel::setPosition(int x2, int y2) {x=x2; y=y2;}

void Tunnel::printPhrase() const {std::cout<<"You feel a draft from somewhere..."<<std::endl;}
