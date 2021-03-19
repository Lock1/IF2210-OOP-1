// 13519214


#include <iostream>
#include "header/entities/tile.hpp"
#include "header/entities/map.hpp"
#include "header/render.hpp"

Render::Render(int offx, int offy, int msgoffx, int msgoffy) : mapOffsetX(offx), mapOffsetY(offy), msgBoxOffsetX(msgoffx), msgBoxOffsetY(msgoffy) {
    isEmptyMapBuffer = isEmptyMsgBuffer = true;
    for (int i = 0; i < MAP_MAX_X; i++)
        for (int j = 0; j < MAP_MAX_Y; j++)
            mapFrameBuffer[i][j] = '\0';
    for (int i = 0; i < MSG_MAX_X; i++)
        for (int j = 0; j < MSG_MAX_Y; j++)
            msgFrameBuffer[i][j] = '\0';
}

void Render::drawMap(Map& target) {
    for (int j = 0; j < MAP_MAX_Y; j++) {
        for (int i = 0; i < MAP_MAX_X; i++) {
            if (target.getEntityAt(i, j)!= NULL) {

            }
            else if (target.getTileIDAt(i, j) == Sea)
                printf("o");
            else
                printf("-");
        }
        printf("\n");
    }
}

//         // Drawing map at offset location
//
//         void drawMessageBox(MessageBox target);
//         // Draw message box at offset location
