// 13519214
#include "header/engine.hpp"
#include <iostream>
#include <stdio.h>

using namespace std;

enum Direction {
    Up,
    Down,
    Left,
    Right
};

Engine::Engine() {
    // TODO : Put private variable preparation here
}

void Engine::startGame() {
    // TODO : Put game here
    system(CLEAR_SCREEN_CMD);
    for (int j = 0; j < MAP_MAX_Y; j++) {
        for (int i = 0; i < MAP_MAX_X; i++) {
            if (map.getTileAt(i, j).getTileID() == Sea)
                printf("o");
            else
                printf("-");
        }
        printf("\n");
    }
    cout << "Hello World!\n";
}

Engine::~Engine() {
    // TODO : Cleanup variable
    cout << "Good Bye!\n";
}
