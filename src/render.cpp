// 13519214

#include "header/config.hpp"
#include "header/entities/tile.hpp"
#include "header/entities/map.hpp"
#include "header/render.hpp"
#include "header/config.hpp" // TODO : Remove
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

void Render::drawMapBorder(Map &target) {
    // Left right border
    for (unsigned int i = mapOffsetY; i < mapOffsetY + target.getSizeY() + 1; i++) {
        setCursorPosition(mapOffsetX-1, i);
        cout << MAP_BORDER_NS;
        setCursorPosition(mapOffsetX+target.getSizeX(), i);
        cout << MAP_BORDER_NS;
    }
    // Top bottom border
    for (unsigned int j = mapOffsetX; j < mapOffsetX + target.getSizeX() + 1; j++) {
        setCursorPosition(j, mapOffsetY-1);
        cout << MAP_BORDER_WE;
        setCursorPosition(j, mapOffsetY+target.getSizeY());
        cout << MAP_BORDER_WE;
    }
    // 4 Corner pieces
    setCursorPosition(mapOffsetX-1, mapOffsetY-1);
    cout << MAP_BORDER_SE;
    setCursorPosition(mapOffsetX-1, mapOffsetY+target.getSizeY());
    cout << MAP_BORDER_NE;
    setCursorPosition(mapOffsetX+target.getSizeX(), mapOffsetY-1);
    cout << MAP_BORDER_SW;
    setCursorPosition(mapOffsetX+target.getSizeX(), mapOffsetY+target.getSizeY());
    cout << MAP_BORDER_NW;
    isEmptyMapBuffer = false;
}

void Render::drawMsgBorder(Message &target) {
    // Left right border
    for (unsigned int i = msgOffsetY; i < msgOffsetY + msgSizeY + 1; i++) {
        setCursorPosition(msgOffsetX-1, i);
        cout << MSG_BORDER_NS;
        setCursorPosition(msgOffsetX+msgSizeX, i);
        cout << MSG_BORDER_NS;
    }
    // Top bottom border
    for (unsigned int j = msgOffsetX; j < msgOffsetX + msgSizeX + 1; j++) {
        setCursorPosition(j, msgOffsetY-1);
        cout << MSG_BORDER_WE;
        setCursorPosition(j, msgOffsetY+msgSizeY);
        cout << MSG_BORDER_WE;
    }
    // 4 Corner pieces
    setCursorPosition(msgOffsetX-1, msgOffsetY-1);
    cout << MSG_BORDER_SE;
    setCursorPosition(msgOffsetX-1, msgOffsetY+msgSizeY);
    cout << MSG_BORDER_NE;
    setCursorPosition(msgOffsetX+msgSizeX, msgOffsetY-1);
    cout << MSG_BORDER_SW;
    setCursorPosition(msgOffsetX+msgSizeX, msgOffsetY+msgSizeY);
    cout << MSG_BORDER_NW;
}

void Render::drawMap(Map& target) {
    // TODO : Extra, maybe using static variable on Entity
    if (isEmptyMapBuffer) {
        for (int i = 0; i < target.getSizeY(); i++) {
            for (int j = 0; j < target.getSizeX(); j++) {
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
        drawMapBorder(target);
    }
    else {
        for (int i = 0; i < target.getSizeY(); i++) {
            for (int j = 0; j < target.getSizeX(); j++) {
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
        drawMsgBorder(target);
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
