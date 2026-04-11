//
// Created by garrido-lestachebeli on 4/10/2026.
//

#include "GameManager.h"

#include <cstdlib>
#include <ctime>
#include <iostream>

#include "Exit.h"
#include "Guard.h"

GameManager::GameManager() : map_(3,2,1,1) {
    srand(time(0));
}

GameManager::~GameManager() {}

void GameManager::gameplayLoop() {
    bool running = true;

    while (running) {
        // 1) print limited map
        printVisibleMap();

        // 2) player input
        char input = getPlayerInput();
        handlePlayerMove(input);

        // 3) activate room
        auto pos = map_.getCharacter(0)->getPosition(); // assuming player is index 0
        Room* room = map_.getRoom(pos.first * 5 + pos.second); // adjust indexing if needed
        room->activate(map_);

        // 4) check lose (guard collision)
        if (checkLose()) {
            std::cout << "You were caught by a guard. Game Over.\n";
            break;
        }

        moveGuards();

        if (checkLose()) {
            std::cout << "A guard caught you. Game Over.\n";
            break;
        }

        // 3b) check win (exit)
        if (checkWin()) {
            std::cout << "You found the exit! You win!\n";
            break;
        }

        // 5) surroundings info
        checkSurroundings();
    }
}

void GameManager::printVisibleMap() {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            map_.print();
            Character* c = map_.getCharacter(i * 5 + j);

            if (c != nullptr) {
                c->print(); // player or guard
            } else {
                std::cout << ". ";
            }
        }
        std::cout << "\n";
    }
}

char GameManager::getPlayerInput() {
    char input;
    std::cout << "Move (WASD): ";
    std::cin >> input;
    return tolower(input);
}

void GameManager::handlePlayerMove(char input) {
    Character* player = map_.getCharacter(0);

    auto [x, y] = player->getPosition();

    int newX = x;
    int newY = y;

    switch (input) {
        case 'w': newX--; break;
        case 's': newX++; break;
        case 'a': newY--; break;
        case 'd': newY++; break;
        default: return;
    }

    map_.move(x, y, newX, newY);
}

bool GameManager::checkWin() {
    Character* player = map_.getCharacter(0);
    auto [x, y] = player->getPosition();

    Room* room = map_.getRoom(x * 5 + y);

    // safest: dynamic_cast
    if (dynamic_cast<Exit*>(room) != nullptr) {
        return true;
    }

    return false;
}

bool GameManager::checkLose() {
    Character* player = map_.getCharacter(0);
    auto [px, py] = player->getPosition();

    for (int i = 1; i < 25; i++) { // assuming guards are others
        Character* c = map_.getCharacter(i);
        if (c != nullptr) {
            auto [gx, gy] = c->getPosition();
            if (gx == px && gy == py) {
                return true;
            }
        }
    }

    return false;
}

void GameManager::checkSurroundings() {
    Character* player = map_.getCharacter(0);
    auto [x, y] = player->getPosition();

    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (nx >= 0 && nx < 5 && ny >= 0 && ny < 5) {

            // check room
            Room* room = map_.getRoom(nx * 5 + ny);
            if (room) {
                room->print(); // acts like printPhrase()
            }

            // check character
            Character* c = map_.getCharacter(nx * 5 + ny);
            if (c) {
                c->print(); // or printPhrase() if you add it
            }
        }
    }
}


void GameManager::moveGuards() {
    Character* player = map_.getCharacter(0);
    auto [px, py] = player->getPosition();

    for (int i = 1; i < 25; i++) {
        Character* c = map_.getCharacter(i);

        if (c == nullptr) continue;

        Guard* guard = dynamic_cast<Guard*>(c);
        if (!guard) continue;

        auto [gx, gy] = guard->getPosition();

        int newX = gx;
        int newY = gy;

        int targetX = px;
        int targetY = py;

        if (map_.isAlertActive()) {
            auto alertPos = map_.getAlertPosition();
            targetX = alertPos.first;
            targetY = alertPos.second;
        }

        int dx = targetX - gx;
        int dy = targetY - gy;

        if (abs(dx) + abs(dy) <= 3) {
            // move toward player
            if (abs(dx) > abs(dy)) {
                newX += (dx > 0) ? 1 : -1;
            } else {
                newY += (dy > 0) ? 1 : -1;
            }
        } else {
            // random movement
            int dir = rand() % 4;

            switch (dir) {
                case 0: newX--; break; // up
                case 1: newX++; break; // down
                case 2: newY--; break; // left
                case 3: newY++; break; // right
            }
        }

        if (newX < 0 || newX >= 5 || newY < 0 || newY >= 5) continue;

        Character* target = map_.getCharacter(newX * 5 + newY);
        if (target != nullptr && dynamic_cast<Guard*>(target)) continue;

        map_.move(gx, gy, newX, newY);
    }
}

