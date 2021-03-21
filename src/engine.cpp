// 13519214
#include "header/render.hpp"
#include "header/engine.hpp"
#include "header/playerinput.hpp"
#include "header/entities/map.hpp"
#include "header/entities/player.hpp"
#include "header/entities/engimon.hpp"
#include "header/entities/attributes/elementtype.hpp"
#include <iostream>
#include <string>
#include <chrono>		// Time and tick system
#include <thread>		// For sleep() // TODO : Use later on input

using namespace std;


// TODO : Use enum direction

Engine::Engine() : messageList(MAX_MESSAGE, MSG_MAX_X), map(MAP_MAX_X, MAP_MAX_Y, SEA_STARTING_X, SEA_STARTING_Y), player(),
        userInput(INPUT_BUFFER_COUNT, INPUT_DELAY_MS),
        renderer(map, messageList) {
    // Internal variable setup
    isEngineRunning = true;
    renderer.setMapOffset(MAP_OFFSET_X, MAP_OFFSET_Y);
    renderer.setMessageBoxOffset(MESSAGE_OFFSET_X, MESSAGE_OFFSET_Y);
    renderer.setCursorRestLocation(CURSOR_REST_X, CURSOR_REST_Y);
}

Engine::~Engine() {
    // TODO : Cleanup variable
    // TODO : Destroy allocated engimonList
}

void Engine::startGame() {
    // TODO : Put game here
    system(CLEAR_SCREEN_CMD);
    int i = 0;

    map.setTileEntity(player.getPos(), &player);
    // DEBUG
    engimonList.push_back(new Engimon(Position(15, 10), Ground, 'x'));
    map.setTileEntity(engimonList[0]->getPos(), engimonList[0]);


    userInput.startReadInput();
    // TODO : Tick
    // TODO : Vector for saving engimon
    while (isEngineRunning) {
        renderer.drawMap(map);
        renderer.drawMessageBox(messageList);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        evaluteInput();
        messageList.addMessage(to_string(i));
        i++;
    }
    userInput.stopReadInput();
    // Entity *rand = new Entity(3, 3, EntityPlayer, '#');
    // map.setTileEntity(3, 3, rand);
    // map.setTileEntity(3, 3, NULL);
    // renderer.drawMap(map);
    // std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    // map.setTileEntity(3, 10, rand);
    // renderer.drawMap(map);
    // delete rand;
}

bool Engine::evaluteInput() {
    InputType inputKey = userInput.getUserInput();
    switch (inputKey) {
        case EscKey:
            isEngineRunning = false;
            break;
        case Up:
            if (player.getPos().getY() > 0) {
                if (player.isMoveLocationValid(map.getTileAt(player.getPos().getX(), player.getPos().getY()-1))) {
                    map.setTileEntity(player.getPos(), NULL);
                    player.getPosRef() += Position(0, -1);
                    map.setTileEntity(player.getPos(), &player);
                    return true;
                }
            }
            break;
        case Down:
            if (player.getPos().getY() < map.getSizeY() - 1) {
                if (player.isMoveLocationValid(map.getTileAt(player.getPos().getX(), player.getPos().getY()+1))) {
                    // TODO : Internal private method, move()
                    map.setTileEntity(player.getPos(), NULL);
                    player.getPosRef() += Position(0, 1);
                    map.setTileEntity(player.getPos(), &player);
                    return true;
                }
            }
            break;
        case Left:
            if (player.getPos().getX() > 0) {
                if (player.isMoveLocationValid(map.getTileAt(player.getPos().getX()-1, player.getPos().getY()))) {
                    map.setTileEntity(player.getPos(), NULL);
                    player.getPosRef() += Position(-1, 0);
                    map.setTileEntity(player.getPos(), &player);
                    return true;
                }
            }
            break;
        case Right:
            if (player.getPos().getX() < map.getSizeX() - 1) {
                if (player.isMoveLocationValid(map.getTileAt(player.getPos().getX()+1, player.getPos().getY()))) {
                    map.setTileEntity(player.getPos(), NULL);
                    player.getPosRef() += Position(1, 0);
                    map.setTileEntity(player.getPos(), &player);
                    return true;
                }
            }
            break;
    }
    return false;
}

void Engine::evaluteTick() {

}
// Evaluating next tick
