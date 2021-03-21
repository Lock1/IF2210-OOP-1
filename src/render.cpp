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

void Render::drawBox(char borderCharset[6], unsigned int offset[2], unsigned int size[2]) {
    // [0] : NE, [1] : NW, [2] : SE
    // [3] : SW, [4] : NS, [5] : WE
    // Left right border
    for (unsigned int i = offset[1]; i < offset[1] + size[1] + 1; i++) {
        setCursorPosition(offset[0]-1, i);
        cout << borderCharset[4];
        setCursorPosition(offset[0]+size[0], i);
        cout << borderCharset[4];
    }
    // Top bottom border
    for (unsigned int j = offset[0]; j < offset[0] + size[0] + 1; j++) {
        setCursorPosition(j, offset[1]-1);
        cout << borderCharset[5];
        setCursorPosition(j, offset[1]+size[1]);
        cout << borderCharset[5];
    }
    // 4 Corner pieces
    setCursorPosition(offset[0]-1, offset[1]-1);
    cout << borderCharset[2];   // Upper left corner
    setCursorPosition(offset[0]-1, offset[1]+size[1]);
    cout << borderCharset[0];   // Bottom left corner
    setCursorPosition(offset[0]+size[0], offset[1]-1);
    cout << borderCharset[3];   // Upper right corner
    setCursorPosition(offset[0]+size[0], offset[1]+size[1]);
    cout << borderCharset[1];   // Bottom right corner
}

void Render::drawMapBorder() {
    // TODO : class Box
    char mapBorderCharset[6];
    mapBorderCharset[0] = mapBorderNE;
    mapBorderCharset[1] = mapBorderNW;
    mapBorderCharset[2] = mapBorderSE;
    mapBorderCharset[3] = mapBorderSW;
    mapBorderCharset[4] = mapBorderNS;
    mapBorderCharset[5] = mapBorderWE;

    unsigned int mapSize[2], mapOffset[2];

    mapSize[0] = mapSizeX;
    mapSize[1] = mapSizeY;

    mapOffset[0] = mapOffsetX;
    mapOffset[1] = mapOffsetY;
    drawBox(mapBorderCharset, mapOffset, mapSize);
    isEmptyMapBuffer = false;
}

void Render::drawMsgBorder() {
    char msgBorderCharset[6];
    msgBorderCharset[0] = msgBorderNE;
    msgBorderCharset[1] = msgBorderNW;
    msgBorderCharset[2] = msgBorderSE;
    msgBorderCharset[3] = msgBorderSW;
    msgBorderCharset[4] = msgBorderNS;
    msgBorderCharset[5] = msgBorderWE;

    unsigned int msgSize[2], msgOffset[2];

    msgSize[0] = msgSizeX;
    msgSize[1] = msgSizeY;

    msgOffset[0] = msgOffsetX;
    msgOffset[1] = msgOffsetY;
    drawBox(msgBorderCharset, msgOffset, msgSize);
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
