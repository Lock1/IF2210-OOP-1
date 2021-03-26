// 13519214
// TODO : A E S T H E T I C -> Message border shadow
#include "header/config.hpp"
#include "header/entities/tile.hpp"
#include "header/entities/map.hpp"
#include "header/render.hpp"
#include <Windows.h>
#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <math.h>

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
    HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hstdout, 0x0E);
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
    SetConsoleTextAttribute(hstdout, 0x0F);
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

                    #ifndef FOG_OF_WAR
                    cout << mapFrameBuffer[i][j];
                    #endif
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

    HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
    int color = 0x0F;
    
    queue<string> buffer = target.showMessage();
    int size = buffer.size();
    for (int i = 0; i < size; i++) {
        setCursorPosition(msgOffsetX, msgOffsetY+i);
        // String padding
        string message = buffer.front();
        if (message == " \xCD\xCD\xCD\xCD Learned skill \xCD\xCD\xCD\xCD ") {
            color = 0x0E;
        }
        else if (message == "        \xCD\xCD Legend \xCD\xCD ") {
            color = 0x0E;
        }
        else if (message == "   W \xAF Water type") {
            color = 0x09;
        }
        else if (message == "   F \xAF Fire type") {
            color = 0x0C;
        }
        else if (message == "   G \xAF Ground type") {
            color = 0x04;
        }
        else if (message == "   E \xAF Electric type") {
            color = 0x06;
        }
        else if (message == "   I \xAF Ice type") {
            color = 0x0B;
        }
        else if (message == "   L \xAF Fire & Electric type") {
            color = 0x08;
        }
        else if (message == "   S \xAF Water & Ice type") {
            color = 0x0D;
        }
        else if (message == "   N \xAF Water & Ground type") {
            color = 0x0A;
        }
        SetConsoleTextAttribute(hstdout, color);
        for (int j = message.length(); j < target.getMaxStringLength(); j++)
            message += " ";
        cout << message;
        color = 0x0F;
        buffer.pop();
    }

    setCursorPosition(cursorRestX, cursorRestY);
    SetConsoleTextAttribute(hstdout, 0x0F);
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
    HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hstdout, 0x0E);
    setCursorPosition(msgOffsetX, msgOffsetY-1);
    cout << msgBoxTitle;
    SetConsoleTextAttribute(hstdout, 0x0F);
}

int Render::floorEuclidean(Position pos1, Position pos2) {
    double xDiff = pos1.getX()-pos2.getX();
    double yDiff = pos1.getY()-pos2.getY();
    return (int) sqrt((xDiff*xDiff) + (yDiff*yDiff));
}

void Render::drawLoseScreen() {
    system(CLEAR_SCREEN_CMD);
    // TODO : Steal prolog red lose screen
}

void Render::clearMessageBox(Message& target) {
    target.fillEmptyBuffer();
    drawMessageBox(target);
    target.clearMessage();
    clearCursorRestArea();
}
