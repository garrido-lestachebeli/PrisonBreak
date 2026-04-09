//
// Created by garrido-lestachebeli on 4/8/2026.
//

#include "Tunnel.h"

Tunnel::Tunnel() : exitTunnel(nullptr) {}

void Tunnel::setExit(Tunnel* exit) {
    exitTunnel = exit;
}

Tunnel* Tunnel::getExit() const {
    return exitTunnel;
}

void Tunnel::print() const {}
