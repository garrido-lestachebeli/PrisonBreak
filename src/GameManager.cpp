#include "GameManager.h"

#include <cstdlib>
#include <ctime>
#include <iostream>

#include "Exit.h"
#include "Guard.h"

GameManager::GameManager() : map_(3,2,1,1) {
}

GameManager::~GameManager() {}

void GameManager::gameplayLoop() {
    while (true) {
        // 1) print map
        map_.print();

        // 2) input
        char input = getPlayerInput();
        handlePlayerMove(input);

        // 3) activate room
        auto [x, y] = map_.getPlayer()->getPosition();
        Room* room = map_.getRoom(x, y);
        room->activate(map_);

        // 4) check lose
        if (checkLose()) {
            std::cout << "You were caught by a guard. Game Over.\n";
            break;
        }

        // 5) move guards
        moveGuards();

        // 6) check lose again
        if (checkLose()) {
            std::cout << "A guard caught you. Game Over.\n";
            break;
        }

        // 7) check win
        if (checkWin()) {
            std::cout << "You found the exit! You win!\n";
            break;
        }

        // 8) surroundings
        checkSurroundings();
    }
}

void GameManager::handlePlayerMove(char input) {
    Player* player = map_.getPlayer();

    auto [x, y] = player->getPosition();

    int newX = x;
    int newY = y;

    switch (input) {
        case 'w': newY--; break;
        case 's': newY++; break;
        case 'a': newX--; break;
        case 'd': newX++; break;
        default: return;
    }

    map_.move(x, y, newX, newY);
}

bool GameManager::checkWin() {
    auto [x, y] = map_.getPlayer()->getPosition();
    Room* room = map_.getRoom(x, y);

    return dynamic_cast<Exit*>(room) != nullptr;
}

bool GameManager::checkLose() {
    auto [px, py] = map_.getPlayer()->getPosition();

    int rows = 7;
    int cols = 7;

    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
            Character* c = map_.getCharacter(x, y);

            Guard* g = dynamic_cast<Guard*>(c);
            if (g) {
                auto [gx, gy] = g->getPosition();
                if (gx == px && gy == py) {
                    return true;
                }
            }
        }
    }

    return false;
}

void GameManager::checkSurroundings() {
    auto [x, y] = map_.getPlayer()->getPosition();

    int dx[] = {0, 0, -1, 1};
    int dy[] = {-1, 1, 0, 0};

    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        Character* c = map_.getCharacter(nx, ny);
        if (c) c->printPhrase();

        Room* room = map_.getRoom(nx, ny);
        if (room) room->printPhrase();
    }
}

void GameManager::moveGuards() {
    auto [px, py] = map_.getPlayer()->getPosition();

    int rows = 7;
    int cols = 7;

    std::vector<Guard*> guards;

    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
            Guard* g = dynamic_cast<Guard*>(map_.getCharacter(x, y));
            if (g) {
                guards.push_back(g);
            }
        }
    }

    for (Guard* guard : guards) {
        auto [gx, gy] = guard->getPosition();

        int newX = gx;
        int newY = gy;

        int targetX = px;
        int targetY = py;

        if (map_.isAlertActive()) {
            auto alert = map_.getAlertPosition();
            targetX = alert.first;
            targetY = alert.second;
        }

        int dx = targetX - gx;
        int dy = targetY - gy;

        if (abs(dx) + abs(dy) <= 3) {
            if (abs(dx) > abs(dy))
                newX += (dx > 0 ? 1 : -1);
            else
                newY += (dy > 0 ? 1 : -1);
        } else {
            int dir = rand() % 4;
            if (dir == 0) newY--;
            if (dir == 1) newY++;
            if (dir == 2) newX--;
            if (dir == 3) newX++;
        }

        if (newX < 0 || newX >= cols || newY < 0 || newY >= rows)
            continue;

        Character* target = map_.getCharacter(newX, newY);

        if (target == nullptr || target == map_.getPlayer()) {
            map_.move(gx, gy, newX, newY);
        }
    }

    map_.clearAlert();
}

char GameManager::getPlayerInput() {
    char input;
    std::cout << "Move (WASD): ";
    std::cin >> input;
    return tolower(input);
}