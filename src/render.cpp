// 13519214

#include "header/entities/tile.hpp"
#include "header/entities/map.hpp"
#include "header/render.hpp"
#include <Windows.h>
#include <iostream>
#include <queue>
#include <vector>
#include <string>

using namespace std;

Render::Render(Map& target, Message& msgTarget) : mapSizeX(target.getSizeX()), mapSizeY(target.getSizeY()),
    msgSizeX(msgTarget.getMaxStringLength()), msgSizeY(msgTarget.getMaxMessage()) {
    // Default values
    isEmptyMapBuffer = true, isMessageBorderDrawn = false;
    cursorRestX = cursorRestY = 0;
    mapOffsetX = mapOffsetY = 1;
    msgOffsetX = 55;
    msgOffsetY = 1;


    // Map Border, using compass direction,
    // (ex. NW = connecting border from north and west direction)
    mapBorderNE = '\xC8';
    mapBorderNW = '\xBC';
    mapBorderSE = '\xC9';
    mapBorderSW = '\xBB';
    mapBorderNS = '\xBA';
    mapBorderWE = '\xCD';

    // Message border
    msgBorderNE = '\xC0';
    msgBorderNW = '\xD9';
    msgBorderSE = '\xDA';
    msgBorderSW = '\xBF';
    msgBorderNS = '\xB3';
    msgBorderWE = '\xC4';

    // TODO : Reinit, box class
    // Map frame buffer initialization
    for (unsigned int i = 0; i < mapSizeY; i++) {
        std::vector<char> mapRow;
        for (unsigned int j = 0; j < mapSizeX; j++)
            mapRow.push_back('\0');
        mapFrameBuffer.push_back(mapRow);
    }
}

void Render::setMapOffset(unsigned int offx, unsigned int offy) {
    mapOffsetX = offx;
    mapOffsetY = offy;
}

void Render::setMessageBoxOffset(unsigned int msgoffx, unsigned int msgoffy) {
    msgOffsetX = msgoffx;
    msgOffsetY = msgoffy;
}

void Render::setCursorRestLocation(unsigned int x, unsigned int y) {
    cursorRestX = x;
    cursorRestY = y;
}

void Render::setCursorPosition(int x, int y) {
    static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    std::cout.flush();
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(hOut, coord);
}

void Render::drawMapBorder() {
    // Left right border
    for (unsigned int i = mapOffsetY; i < mapOffsetY + mapSizeY + 1; i++) {
        setCursorPosition(mapOffsetX-1, i);
        cout << mapBorderNS;
        setCursorPosition(mapOffsetX+mapSizeX, i);
        cout << mapBorderNS;
    }
    // Top bottom border
    for (unsigned int j = mapOffsetX; j < mapOffsetX + mapSizeX + 1; j++) {
        setCursorPosition(j, mapOffsetY-1);
        cout << mapBorderWE;
        setCursorPosition(j, mapOffsetY+mapSizeY);
        cout << mapBorderWE;
    }
    // 4 Corner pieces
    setCursorPosition(mapOffsetX-1, mapOffsetY-1);
    cout << mapBorderSE;
    setCursorPosition(mapOffsetX-1, mapOffsetY+mapSizeY);
    cout << mapBorderNE;
    setCursorPosition(mapOffsetX+mapSizeX, mapOffsetY-1);
    cout << mapBorderSW;
    setCursorPosition(mapOffsetX+mapSizeX, mapOffsetY+mapSizeY);
    cout << mapBorderNW;
    isEmptyMapBuffer = false;
}

void Render::drawMsgBorder() {
    // Left right border
    for (unsigned int i = msgOffsetY; i < msgOffsetY + msgSizeY + 1; i++) {
        setCursorPosition(msgOffsetX-1, i);
        cout << msgBorderNS;
        setCursorPosition(msgOffsetX+msgSizeX, i);
        cout << msgBorderNS;
    }
    // Top bottom border
    for (unsigned int j = msgOffsetX; j < msgOffsetX + msgSizeX + 1; j++) {
        setCursorPosition(j, msgOffsetY-1);
        cout << msgBorderWE;
        setCursorPosition(j, msgOffsetY+msgSizeY);
        cout << msgBorderWE;
    }
    // 4 Corner pieces
    setCursorPosition(msgOffsetX-1, msgOffsetY-1);
    cout << msgBorderSE;
    setCursorPosition(msgOffsetX-1, msgOffsetY+msgSizeY);
    cout << msgBorderNE;
    setCursorPosition(msgOffsetX+msgSizeX, msgOffsetY-1);
    cout << msgBorderSW;
    setCursorPosition(msgOffsetX+msgSizeX, msgOffsetY+msgSizeY);
    cout << msgBorderNW;
}

void Render::drawMap(Map& target) {
    // TODO : Extra, maybe using static variable on Entity
    if (isEmptyMapBuffer) {
        for (unsigned int i = 0; i < mapSizeY; i++) {
            for (unsigned int j = 0; j < mapSizeX; j++) {
                Entity* tempEntityPointer = target.getEntityAt(j, i);
                if (tempEntityPointer != NULL) {
                    if (mapFrameBuffer[i][j] != tempEntityPointer->getEntityChar()) {
                        mapFrameBuffer[i][j] = tempEntityPointer->getEntityChar();
                        setCursorPosition(j + mapOffsetX, i + mapOffsetY);
                        cout << mapFrameBuffer[i][j];
                    }
                }
                else {
                    mapFrameBuffer[i][j] = target.getTileTypeAt(j, i);
                    setCursorPosition(j + mapOffsetX, i + mapOffsetY);
                    cout << mapFrameBuffer[i][j];
                }
            }
        }
        drawMapBorder();
    }
    else {
        for (unsigned int i = 0; i < mapSizeY; i++) {
            for (unsigned int j = 0; j < mapSizeX; j++) {
                Entity* tempEntityPointer = target.getEntityAt(j, i);
                if (tempEntityPointer != NULL) {
                    if (mapFrameBuffer[i][j] != tempEntityPointer->getEntityChar()) {
                        mapFrameBuffer[i][j] = tempEntityPointer->getEntityChar();
                        setCursorPosition(j + mapOffsetX, i + mapOffsetY);
                        cout << mapFrameBuffer[i][j];
                    }
                }
                else if (target.getTileTypeAt(j, i) != mapFrameBuffer[i][j]) {
                    mapFrameBuffer[i][j] = target.getTileTypeAt(j, i);
                    setCursorPosition(j + mapOffsetX, i + mapOffsetY);
                    cout << mapFrameBuffer[i][j];
                }
            }
        }
    }

    setCursorPosition(cursorRestX, cursorRestY);
}

void Render::drawMessageBox(Message& target) {
    if (!isMessageBorderDrawn) {
        drawMsgBorder();
        isMessageBorderDrawn = true;
    }

    queue<string> buffer = target.showMessage();
    int size = buffer.size();
    for (int i = 0; i < size; i++) {
        setCursorPosition(msgOffsetX, msgOffsetY+i);
        cout << buffer.front();
        buffer.pop();
    }

    setCursorPosition(cursorRestX, cursorRestY);
}
