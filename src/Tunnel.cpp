//
// Created by garrido-lestachebeli on 4/8/2026.
//
#include <iostream>
#include "Tunnel.h"

#include "Character.h"
#include "Map.h"

Tunnel::Tunnel() : exit(nullptr) {}

void Tunnel::setExit(Tunnel* exitTunnel) {
    exit = exitTunnel;
}

Tunnel* Tunnel::getExit() const {
    return exit;
}

void Tunnel::print() const {}

void Tunnel::activate(Map& map) {
    Character* player = map.getCharacter(0);
    auto [x, y] = player->getPosition();

    auto [tx, ty] = map.getOtherTunnel(x, y);

    std::cout << "You enter a tunnel...\n";

    map.move(x, y, tx, ty);
}

void Tunnel::setPosition(int x, int y) {}

void Tunnel::printPhrase() const {std::cout<<"You feel a draft from somewhere..."<<std::endl;}
