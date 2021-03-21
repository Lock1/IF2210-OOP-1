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
#include <stdlib.h>
#include <Windows.h>
#include <time.h>

using namespace std;


Engine::Engine() : messageList(MAX_MESSAGE, MSG_MAX_X), statMessage(MAX_MESSAGE-10, MSG_MAX_X),
        map(MAP_MAX_X, MAP_MAX_Y, SEA_STARTING_X, SEA_STARTING_Y), player(),
        userInput(INPUT_BUFFER_COUNT, INPUT_DELAY_MS), wildEngimonSpawnProbability(2), entitySpawnLimit(20),
        renderer(map, messageList), statRenderer(statMessage) {
    // Internal variable setup
    srand((unsigned) time(NULL));
    isEngineRunning = true;
    isCommandMode = false;
    renderer.setMapOffset(MAP_OFFSET_X, MAP_OFFSET_Y);
    renderer.setMessageBoxOffset(MESSAGE_OFFSET_X, MESSAGE_OFFSET_Y);
    renderer.setCursorRestLocation(CURSOR_REST_X, CURSOR_REST_Y);

    statRenderer.setMessageBoxOffset(MESSAGE_OFFSET_X+messageList.getMaxStringLength()+3, MESSAGE_OFFSET_Y);
    statRenderer.setCursorRestLocation(CURSOR_REST_X, CURSOR_REST_Y);
    // TODO : Database loading
}

Engine::~Engine() {
    // TODO : Cleanup variable
    // TODO : Destroy allocated engimonList
}

void Engine::clearConsoleInputBuffer() {
    // Source : http://cplusplus.com/forum/beginner/248262/
    PINPUT_RECORD ClearingVar1 = new INPUT_RECORD[256];
    DWORD ClearingVar2;
    ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE),ClearingVar1,256,&ClearingVar2);
    delete[] ClearingVar1;
}


void Engine::startGame() {
    // TODO : Put game here
    system(CLEAR_SCREEN_CMD);
    int i = 0;

    map.setTileEntity(player.getPos(), &player);
    // DEBUG
    engimonList.push_back(new Engimon(Position(0, 0), Electric, 'z', false));
    player.changeEngimon(engimonList[0]);
    // ^ Starter
    engimonList.push_back(new Engimon(Position(15, 10), Ground, 'x', true));
    engimonList.push_back(new Engimon(Position(40, 20), Water, 'a', true));
    engimonList.push_back(new Engimon(Position(25, 15), Ground, 'b', false));
    map.setTileEntity(engimonList[0]->getPos(), engimonList[0]);
    map.setTileEntity(engimonList[1]->getPos(), engimonList[1]);
    map.setTileEntity(engimonList[2]->getPos(), engimonList[2]);
    map.setTileEntity(engimonList[3]->getPos(), engimonList[3]);


    userInput.startReadInput();
    while (isEngineRunning) {
        renderer.drawMap(map);
        renderer.drawMessageBox(messageList);
        statRenderer.drawMessageBox(statMessage);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        if (evaluteInput() && not isCommandMode) {
            evaluteTick();
            messageList.addMessage("Move to : " + to_string(player.getPos().getX()) + "," + to_string(player.getPos().getY()));
        }
        else if (isCommandMode) {
            // TODO : Add and fix
            // evaluateCommand();
            string trash;
            clearConsoleInputBuffer();
            cout << "> ";
            getline(cin, trash);
            cout << endl << trash << endl;
            isCommandMode = false;
        }
        statMessage.addMessage(to_string(i));
        i++;
    }
    userInput.stopReadInput();
}

bool Engine::evaluteInput() {
    InputType inputKey = userInput.getUserInput();
    bool isMovementValid = false;
    Direction targetDirection;
    // TODO : Flatten the conditional ladder
    switch (inputKey) {
        case EscKey:
            isEngineRunning = false;
            break;
        case Up:
            // TODO : Interaction
            if (player.getPos().getY() > 0) {
                if (player.isMoveLocationValid(map.getTileAt(player.getPos().getX(), player.getPos().getY()-1))) {
                    targetDirection = North;
                    isMovementValid = true;
                }
            }
            break;
        case Down:
            if (player.getPos().getY() < map.getSizeY() - 1) {
                if (player.isMoveLocationValid(map.getTileAt(player.getPos().getX(), player.getPos().getY()+1))) {
                    targetDirection = South;
                    isMovementValid = true;
                }
            }
            break;
        case Left:
            if (player.getPos().getX() > 0) {
                if (player.isMoveLocationValid(map.getTileAt(player.getPos().getX()-1, player.getPos().getY()))) {
                    targetDirection = West;
                    isMovementValid = true;
                }
            }
            break;
        case Right:
            if (player.getPos().getX() < map.getSizeX() - 1) {
                if (player.isMoveLocationValid(map.getTileAt(player.getPos().getX()+1, player.getPos().getY()))) {
                    targetDirection = East;
                    isMovementValid = true;
                }
            }
            break;
        case KeyboardE:
            // TODO : Open menu / help, command mode
            isCommandMode = true;
            messageList.addMessage("MASUKKKKKKKK");
            break;
    }

    if (isMovementValid) {
        map.moveEntity(player.getPos(), targetDirection);
        map.moveEntity(player.getCurrentEngimon()->getPos(), player.getLastDirection());
        player.getLastDirectionRef() = targetDirection;
        return true;
    }

    return false;
}

void Engine::evaluteTick() {
    // TODO : Add here
    map.wildEngimonRandomMove();
    unsigned int randomNumber = rand() % 100;
    if (Entity::getEntityCount() < entitySpawnLimit && randomNumber < wildEngimonSpawnProbability)
        map.spawnWildEngimon();
}
