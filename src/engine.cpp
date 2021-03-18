// 13519214
#include "header/engine.hpp"
#include <iostream>

using namespace std;

Engine::Engine() {
    // TODO : Put private variable preparation here
}

void Engine::startGame() {
    // TODO : Put game here
    system(CLEAR_SCREEN_CMD);
    cout << "Hello World!\n";
}

Engine::~Engine() {
    // TODO : Cleanup variable
    cout << "Good Bye!\n";
}
