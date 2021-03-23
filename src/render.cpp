// 13519214
// TODO : A E S T H E T I C -> Message border shadow
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
    msgBoxTitle = "";

    // Map Border
    mapBorderCornerBottomLeft = '\xC8';
    mapBorderCornerBottomRight = '\xBC';
    mapBorderCornerTopLeft = '\xC9';
    mapBorderCornerTopRight = '\xBB';
    mapBorderLineVertical = '\xBA';
    mapBorderLineHorizontal = '\xCD';

    // Message border
    msgBorderCornerBottomLeft = '\xC0';
    msgBorderCornerBottomRight = '\xD9';
    msgBorderCornerTopLeft = '\xDA';
    msgBorderCornerTopRight = '\xBF';
    msgBorderLineVertical = '\xB3';
    msgBorderLineHorizontal = '\xC4';

    // Map frame buffer initialization
    for (unsigned int i = 0; i < mapSizeY; i++) {
        std::vector<char> mapRow;
        for (unsigned int j = 0; j < mapSizeX; j++)
            mapRow.push_back('\0');
        mapFrameBuffer.push_back(mapRow);
    }
}

Render::Render(Message& msgTarget) : mapSizeX(0), mapSizeY(0),
    msgSizeX(msgTarget.getMaxStringLength()), msgSizeY(msgTarget.getMaxMessage()) {
    // Default values
    isEmptyMapBuffer = true, isMessageBorderDrawn = false;
    cursorRestX = cursorRestY = 0;
    mapOffsetX = mapOffsetY = 1;
    msgOffsetX = 55;
    msgOffsetY = 1;
    msgBoxTitle = "";

    // Message border
    msgBorderCornerBottomLeft = '\xC0';
    msgBorderCornerBottomRight = '\xD9';
    msgBorderCornerTopLeft = '\xDA';
    msgBorderCornerTopRight = '\xBF';
    msgBorderLineVertical = '\xB3';
    msgBorderLineHorizontal = '\xC4';
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

void Render::drawBox(Box& target) {
    // Left right border
    for (unsigned int i = target.offsetY; i < target.offsetY + target.sizeY + 1; i++) {
        setCursorPosition(target.offsetX-1, i);
        cout << target.lineVertical;
        setCursorPosition(target.offsetX+target.sizeX, i);
        cout << target.lineVertical;
    }
    // Top bottom border
    for (unsigned int j = target.offsetX; j < target.offsetX + target.sizeX + 1; j++) {
        setCursorPosition(j, target.offsetY-1);
        cout << target.lineHorizontal;
        setCursorPosition(j, target.offsetY+target.sizeY);
        cout << target.lineHorizontal;
    }
    // 4 Corner pieces
    setCursorPosition(target.offsetX-1, target.offsetY-1);
    cout << target.cornerTopLeft;   // Upper left corner
    setCursorPosition(target.offsetX-1, target.offsetY+target.sizeY);
    cout << target.cornerBottomLeft;   // Bottom left corner
    setCursorPosition(target.offsetX+target.sizeX, target.offsetY-1);
    cout << target.cornerTopRight;   // Upper right corner
    setCursorPosition(target.offsetX+target.sizeX, target.offsetY+target.sizeY);
    cout << target.cornerBottomRight;   // Bottom right corner
}

void Render::drawMapBorder() {
    Box mapBox;
    mapBox.cornerBottomLeft = mapBorderCornerBottomLeft;
    mapBox.cornerBottomRight = mapBorderCornerBottomRight;
    mapBox.cornerTopLeft = mapBorderCornerTopLeft;
    mapBox.cornerTopRight = mapBorderCornerTopRight;
    mapBox.lineVertical = mapBorderLineVertical;
    mapBox.lineHorizontal = mapBorderLineHorizontal;

    mapBox.sizeX = mapSizeX;
    mapBox.sizeY = mapSizeY;

    mapBox.offsetX = mapOffsetX;
    mapBox.offsetY = mapOffsetY;
    drawBox(mapBox);
    isEmptyMapBuffer = false;
}

void Render::drawMsgBorder() {
    Box msgBox;
    msgBox.cornerBottomLeft = msgBorderCornerBottomLeft;
    msgBox.cornerBottomRight = msgBorderCornerBottomRight;
    msgBox.cornerTopLeft = msgBorderCornerTopLeft;
    msgBox.cornerTopRight = msgBorderCornerTopRight;
    msgBox.lineVertical = msgBorderLineVertical;
    msgBox.lineHorizontal = msgBorderLineHorizontal;

    msgBox.sizeX = msgSizeX;
    msgBox.sizeY = msgSizeY;

    msgBox.offsetX = msgOffsetX;
    msgBox.offsetY = msgOffsetY;
    drawBox(msgBox);
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
        drawMessageTitle();
        isMessageBorderDrawn = true;
    }

    queue<string> buffer = target.showMessage();
    int size = buffer.size();
    for (int i = 0; i < size; i++) {
        setCursorPosition(msgOffsetX, msgOffsetY+i);
        // String padding
        string message = buffer.front();
        for (int j = message.length(); j < target.getMaxStringLength(); j++)
            message += " ";
        cout << message;
        buffer.pop();
    }

    setCursorPosition(cursorRestX, cursorRestY);
}

void Render::setMessageTitle(string title) {
    msgBoxTitle = title;
    // If already draw, redraw
    if (isMessageBorderDrawn) {
        drawMsgBorder();
        drawMessageTitle();
    }
}

void Render::clearCursorRestArea() {
    setCursorPosition(cursorRestX, cursorRestY);
    cout << "                                         ";
    setCursorPosition(cursorRestX, cursorRestY);
}

void Render::drawMessageTitle() {
    setCursorPosition(msgOffsetX, msgOffsetY-1);
    cout << msgBoxTitle;
}
