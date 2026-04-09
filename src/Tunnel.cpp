//
// Created by garrido-lestachebeli on 4/8/2026.
//

#include "Tunnel.h"

Tunnel::Tunnel() : exit(nullptr) {}

void Tunnel::setExit(Tunnel* exitTunnel) {
    exit = exitTunnel;
}

Tunnel* Tunnel::getExit() const {
    return exit;
}

void Tunnel::print() const {}

void Tunnel::activate(){}

void Tunnel::setPosition(int x, int y) {}