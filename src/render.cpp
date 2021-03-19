// 13519214

#include "header/config.hpp"
#include "header/entities/tile.hpp"
#include "header/entities/map.hpp"
#include "header/render.hpp"
#include <Windows.h>
#include <iostream>

using namespace std;

Render::Render(int offx, int offy, int msgoffx, int msgoffy, Map& target) : mapOffsetX(offx), mapOffsetY(offy), msgBoxOffsetX(msgoffx), msgBoxOffsetY(msgoffy) {
    isEmptyMapBuffer = isEmptyMsgBuffer = true;
    for (int i = 0; i < target.getSizeY(); i++)
        for (int j = 0; j < target.getSizeX(); j++)
            mapFrameBuffer[i][j] = '\0';

    for (int i = 0; i < MSG_MAX_Y; i++) // TODO : Maybe delete
        for (int j = 0; j < MSG_MAX_X; j++)
            msgFrameBuffer[i][j] = '\0';
}

void Render::setCursorPosition(int x, int y) {
    static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    std::cout.flush();
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(hOut, coord);
}

void Render::drawMapBorder(Map &target) {
    // Left right border
    for (int i = 0; i < target.getSizeY() + 2; i++) {
        setCursorPosition(mapOffsetX-1, i);
        cout << MAP_BORDER_NS;
        setCursorPosition(mapOffsetX+target.getSizeX(), i);
        cout << MAP_BORDER_NS;
    }
    // Top bottom border
    for (int j = 0; j < target.getSizeX() + 2; j++) {
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

void Render::drawMap(Map& target) {
    // TODO : Extra, maybe using static variable on Entity
    if (isEmptyMapBuffer) {
        for (int i = 0; i < target.getSizeY(); i++) {
            for (int j = 0; j < target.getSizeX(); j++) {
                Entity* tempEntityPointer = target.getEntityAt(j, i);
                if (tempEntityPointer != NULL) {
                    // TODO : Get char from entity
                    // mapFrameBuffer[i][j] != tempEntityPointer.getEntityChar()
                    // cout <<
                }
                else {
                    mapFrameBuffer[i][j] = target.getTileTypeAt(j, i);
                    setCursorPosition(j + mapOffsetX, i + mapOffsetY);
                    cout << mapFrameBuffer[i][j];
                }
            }
            cout << '\n';
        }
        drawMapBorder(target);
    }
    else {
        for (int i = 0; i < target.getSizeY(); i++) {
            for (int j = 0; j < target.getSizeX(); j++) {
                Entity* tempEntityPointer = target.getEntityAt(j, i);
                if (tempEntityPointer != NULL) {
                    // TODO : Get char from entity
                    // mapFrameBuffer[i][j] != tempEntityPointer.getEntityChar()
                }
                else if (target.getTileTypeAt(j, i) != mapFrameBuffer[i][j]) {
                    mapFrameBuffer[i][j] = target.getTileTypeAt(j, i);
                    setCursorPosition(j + mapOffsetX, i + mapOffsetY);
                    cout << mapFrameBuffer[i][j];
                }
            }
        }
    }
    setCursorPosition(60, 20);
}

//         // Drawing map at offset location
//
//         void drawMessageBox(MessageBox target);
//         // Draw message box at offset location
