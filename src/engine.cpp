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
#include <chrono>       // Time and tick system
#include <thread>       // For sleep()

using namespace std;


Engine::Engine() : messageList(MAX_MESSAGE, MSG_MAX_X), map(MAP_MAX_X, MAP_MAX_Y, SEA_STARTING_X, SEA_STARTING_Y), player(),
        userInput(INPUT_BUFFER_COUNT, INPUT_DELAY_MS),
        renderer(map, messageList) {
    // Internal variable setup
    isEngineRunning = true;
    renderer.setMapOffset(MAP_OFFSET_X, MAP_OFFSET_Y);
    renderer.setMessageBoxOffset(MESSAGE_OFFSET_X, MESSAGE_OFFSET_Y);
    renderer.setCursorRestLocation(CURSOR_REST_X, CURSOR_REST_Y);
    // TODO : Database loading
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
    engimonList.push_back(new Engimon(Position(15, 10), Ground, 'x', true));
    engimonList.push_back(new Engimon(Position(40, 20), Water, 'a', true));
    engimonList.push_back(new Engimon(Position(25, 15), Ground, 'b', false));
    map.setTileEntity(engimonList[0]->getPos(), engimonList[0]);
    map.setTileEntity(engimonList[1]->getPos(), engimonList[1]);
    map.setTileEntity(engimonList[2]->getPos(), engimonList[2]);


    userInput.startReadInput();
    // TODO : Tick
    // TODO : Vector for saving engimon
    while (isEngineRunning) {
        renderer.drawMap(map);
        renderer.drawMessageBox(messageList);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        if (evaluteInput())
            evaluteTick();
        messageList.addMessage(to_string(i));
        i++;
    }
    userInput.stopReadInput();
}

bool Engine::evaluteInput() {
    InputType inputKey = userInput.getUserInput();
    switch (inputKey) {
        case EscKey:
            isEngineRunning = false;
            break;
        case Up:
            // TODO : Interaction
            if (player.getPos().getY() > 0) {
                if (player.isMoveLocationValid(map.getTileAt(player.getPos().getX(), player.getPos().getY()-1))) {
                    map.moveEntity(player.getPos(), North);
                    return true;
                }
            }
            break;
        case Down:
            if (player.getPos().getY() < map.getSizeY() - 1) {
                if (player.isMoveLocationValid(map.getTileAt(player.getPos().getX(), player.getPos().getY()+1))) {
                    map.moveEntity(player.getPos(), South);
                    return true;
                }
            }
            break;
        case Left:
            if (player.getPos().getX() > 0) {
                if (player.isMoveLocationValid(map.getTileAt(player.getPos().getX()-1, player.getPos().getY()))) {
                    map.moveEntity(player.getPos(), West);
                    return true;
                }
            }
            break;
        case Right:
            if (player.getPos().getX() < map.getSizeX() - 1) {
                if (player.isMoveLocationValid(map.getTileAt(player.getPos().getX()+1, player.getPos().getY()))) {
                    map.moveEntity(player.getPos(), East);
                    return true;
                }
            }
            break;
    }
    return false;
}

void Engine::evaluteTick() {
    // TODO : Add here
    map.wildEngimonRandomMove();
}
