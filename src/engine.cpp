// 13519214
#include "header/render.hpp"
#include "header/engine.hpp"
#include "header/entities/map.hpp"
#include <iostream>
#include <string>

using namespace std;

#include <chrono>		// Time and tick system
#include <thread>		// For sleep() // TODO : Use later on input

Engine::Engine() : map(), userInput(INPUT_BUFFER_COUNT), renderer(MAP_OFFSET_X, MAP_OFFSET_Y, MESSAGE_OFFSET_X, MESSAGE_OFFSET_Y, map) {
    // TODO : Put private variable preparation here
}

void Engine::startGame() {
    // TODO : Put game here
    system(CLEAR_SCREEN_CMD);
    int i = 0;
    bool isEngineRunning = true;
    while (isEngineRunning) {
        renderer.drawMap(map);
        renderer.drawMessageBox(messageList);
        std::this_thread::sleep_for(std::chrono::milliseconds(80));
        if (userInput.getUserInput() == EscKey)
            isEngineRunning = false;
        else
            messageList.addMessage(to_string(i));
        // messageList.addMessage(to_string(i)+"Longgabcdefghijklmnopqrstuvwxyz");
        i++;
    }
    // Entity *rand = new Entity(3, 3, EntityPlayer, '#');
    // map.setTileEntity(3, 3, rand);
    // map.setTileEntity(3, 3, NULL);
    // renderer.drawMap(map);
    // std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    // map.setTileEntity(3, 10, rand);
    // renderer.drawMap(map);
    // delete rand;
}

Engine::~Engine() {
    // TODO : Cleanup variable
}
