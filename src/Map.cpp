//
// Created by garrido-lestachebeli on 4/8/2026.
//

#include "Map.h"
#include "Player.h"
#include "Guard.h"
#include "Camera.h"
#include "Exit.h"
#include "Tunnel.h"
#include "EmptyRoom.h"

#include <algorithm>
#include <iostream>
#include <random>
#include <vector>


Map::Map(int nGuards, int kCameras, int bExits, int mTunnelPairs){
    generateRoomMap(kCameras, bExits, mTunnelPairs);
    generateCharacterMap(nGuards);
}

void Map::generateCharacterMap(int nGuards) {
    constexpr int SIZE = 7;
    constexpr int CENTER = 3;

    characterMap.resize(SIZE);
    for (int y = 0; y < SIZE; ++y) {
        characterMap[y].resize(SIZE);
        for (int x = 0; x < SIZE; ++x) {
            characterMap[y][x] = nullptr;
        }
    }

    Player* player = new Player();
    player->setPosition(CENTER, CENTER);
    characterMap[CENTER][CENTER] = player;

    populateCharacter(nGuards);
}

void Map::generateRoomMap(int bCameras, int cExits, int dTunnelPairs) {
    constexpr int SIZE = 7;

    roomMap.resize(SIZE);
    for (int y = 0; y < SIZE; ++y) {
        roomMap[y].resize(SIZE);
        for (int x = 0; x < SIZE; ++x) {
            roomMap[y][x] = new EmptyRoom();
            roomMap[y][x]->setPosition(x, y);
        }
    }
    populateRoom<Camera>(bCameras);
    populateRoom<Exit>(cExits);
    populateTunnelPairs(dTunnelPairs);
}

void Map::move(int x1, int y1, int x2, int y2){
    constexpr int SIZE = 7;

    if (x1 < 0 || x1 >= SIZE || y1 < 0 || y1 >= SIZE ||
        x2 < 0 || x2 >= SIZE || y2 < 0 || y2 >= SIZE) {
        return;
        }

    Character* character = characterMap[y1][x1];
    if (character == nullptr) {
        return;
    }

    if (characterMap[y2][x2] != nullptr) {
        return;
    }

    characterMap[y1][x1] = nullptr;
    characterMap[y2][x2] = character;
    character->setPosition(x2, y2);

    roomMap[y2][x2]->activate();
}

Map::~Map()
{
    for (auto& row : roomMap) {
        for (auto& cell : row) {
            delete cell;
        }
    }
    for (auto& row : characterMap) {
        for (auto& cell : row) {
            delete cell;
        }
    }
}

std::pair<int,int> Map::getRandomEmptyCellRoomMap() const{
    constexpr int SIZE = 7;

    while (true) {
        int x = rand() % SIZE;
        int y = rand() % SIZE;

        if (dynamic_cast<EmptyRoom*>(roomMap[y][x]) != nullptr) {
            return {x, y};
        }
    }
}

std::pair<int,int> Map::getRandomEmptyCellCharacterMap() const{
    constexpr int SIZE = 7;

    while (true) {
        int x = rand() % SIZE;
        int y = rand() % SIZE;

        if (characterMap[y][x] == nullptr){
            return {x, y};
        }
    }
}

template <typename T>
void Map::populateRoom(int n){
    for (int i = 0; i < n; ++i) {
        auto [x, y] = getRandomEmptyCellRoomMap();

        delete roomMap[y][x];
        roomMap[y][x] = new T();
        roomMap[y][x]->setPosition(x, y);
    }
}

void Map::populateCharacter(int n) {
    constexpr int CENTER = 3;

    for (int i = 0; i < n; ++i) {
        auto [x, y] = getRandomEmptyCellCharacterMap();

        if (x == CENTER && y == CENTER) {
            --i;
            continue;
        }

        characterMap[y][x] = new Guard();
        characterMap[y][x]->setPosition(x, y);
    }
}

void Map::populateTunnelPairs(int n) {
    for (int i = 0; i < n; ++i) {
        auto [x1, y1] = getRandomEmptyCellRoomMap();
        int x2, y2;
        do {
            auto temp = getRandomEmptyCellRoomMap();
            x2 = temp.first;
            y2 = temp.second;
        } while (x2 == x1 && y2 == y1);

        Tunnel* t1 = new Tunnel();
        Tunnel* t2 = new Tunnel();

        t1->setExit(t2);
        t2->setExit(t1);

        t1->setPosition(x1, y1);
        t2->setPosition(x2, y2);

        delete roomMap[y1][x1];
        delete roomMap[y2][x2];

        roomMap[y1][x1] = t1;
        roomMap[y2][x2] = t2;
    }
}

Room* Map::getRoom(int index) const{
    constexpr int SIZE = 7;
    constexpr int TOTAL = SIZE * SIZE;

    if (index < 0 || index >= TOTAL) {
        return nullptr;
    }

    int x = index % SIZE;
    int y = index / SIZE;

    return roomMap[y][x];
}

Character* Map::getCharacter(int index) const{
    constexpr int SIZE = 7;
    constexpr int TOTAL = SIZE * SIZE;

    if (index < 0 || index >= TOTAL) {
        return nullptr;
    }

    int x = index % SIZE;
    int y = index / SIZE;

    return characterMap[y][x];
}