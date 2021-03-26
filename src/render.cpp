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
    HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
    if (isEmptyMapBuffer) {
        for (unsigned int i = 0; i < mapSizeY; i++) {
            for (unsigned int j = 0; j < mapSizeX; j++) {
                Entity* tempEntityPointer = target.getEntityAt(j, i);
                if (tempEntityPointer != NULL) {
                    if (mapFrameBuffer[i][j] != tempEntityPointer->getEntityChar()) {
                        mapFrameBuffer[i][j] = tempEntityPointer->getEntityChar();
                        setCursorPosition(j + mapOffsetX, i + mapOffsetY);

                        // Coloring
                        switch (mapFrameBuffer[i][j]) {
                                case 'n': // Water Ground
                                case 'N':
                                    SetConsoleTextAttribute(hstdout, 0x0A);
                                    break;
                                case 's': // Water Ice
                                case 'S':
                                    SetConsoleTextAttribute(hstdout, 0x0D);
                                    break;
                                case 'w':
                                case 'W':
                                    SetConsoleTextAttribute(hstdout, 0x09);
                                    break;
                                case 'l': // Fire Electric
                                case 'L':
                                    SetConsoleTextAttribute(hstdout, 0x08);
                                    break;
                                case 'f': // Fire
                                case 'F':
                                    SetConsoleTextAttribute(hstdout, 0x0C);
                                    break;
                                case 'e': // Electric
                                case 'E':
                                    SetConsoleTextAttribute(hstdout, 0x06);
                                    break;
                                case 'g': // Ground
                                case 'G':
                                    SetConsoleTextAttribute(hstdout, 0x04);
                                    break;
                                case 'i':
                                case 'I':
                                    SetConsoleTextAttribute(hstdout, 0x0B);
                                    break;
                                default:
                                    SetConsoleTextAttribute(hstdout, 0x0F);
                                    break;
                        }
                        cout << mapFrameBuffer[i][j];
                        SetConsoleTextAttribute(hstdout, 0x0F);
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

                        // Coloring
                        switch (mapFrameBuffer[i][j]) {
                                case 'n': // Water Ground
                                case 'N':
                                    SetConsoleTextAttribute(hstdout, 0x0A);
                                    break;
                                case 's': // Water Ice
                                case 'S':
                                    SetConsoleTextAttribute(hstdout, 0x0D);
                                    break;
                                case 'w':
                                case 'W':
                                    SetConsoleTextAttribute(hstdout, 0x09);
                                    break;
                                case 'l': // Fire Electric
                                case 'L':
                                    SetConsoleTextAttribute(hstdout, 0x08);
                                    break;
                                case 'f': // Fire
                                case 'F':
                                    SetConsoleTextAttribute(hstdout, 0x0C);
                                    break;
                                case 'e': // Electric
                                case 'E':
                                    SetConsoleTextAttribute(hstdout, 0x06);
                                    break;
                                case 'g': // Ground
                                case 'G':
                                    SetConsoleTextAttribute(hstdout, 0x04);
                                    break;
                                case 'i':
                                case 'I':
                                    SetConsoleTextAttribute(hstdout, 0x0B);
                                    break;
                                default:
                                    SetConsoleTextAttribute(hstdout, 0x0F);
                                    break;
                        }
                        cout << mapFrameBuffer[i][j];
                        SetConsoleTextAttribute(hstdout, 0x0F);
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

void Render::drawMap(Map& target, Position posRendered) {
    HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
    vector<Position> renderPos = getRenderedArea(posRendered);
    if (isEmptyMapBuffer) {
        for (unsigned int i = 0; i < renderPos.size(); i++) {
            int coorX = renderPos[i].getX();
            int coorY = renderPos[i].getY();
            Entity* tempEntityPointer = target.getEntityAt(coorX, coorY);
            if (tempEntityPointer != NULL) {
                if (mapFrameBuffer[coorY][coorX] != tempEntityPointer->getEntityChar()) {
                    mapFrameBuffer[coorY][coorX] = tempEntityPointer->getEntityChar();
                    setCursorPosition(coorX + mapOffsetX, coorY + mapOffsetY);

                    // Coloring
                    switch (mapFrameBuffer[coorY][coorX]) {
                            case 'n': // Water Ground
                            case 'N':
                                SetConsoleTextAttribute(hstdout, 0x0A);
                                break;
                            case 's': // Water Ice
                            case 'S':
                                SetConsoleTextAttribute(hstdout, 0x0D);
                                break;
                            case 'w':
                            case 'W':
                                SetConsoleTextAttribute(hstdout, 0x09);
                                break;
                            case 'l': // Fire Electric
                            case 'L':
                                SetConsoleTextAttribute(hstdout, 0x08);
                                break;
                            case 'f': // Fire
                            case 'F':
                                SetConsoleTextAttribute(hstdout, 0x0C);
                                break;
                            case 'e': // Electric
                            case 'E':
                                SetConsoleTextAttribute(hstdout, 0x06);
                                break;
                            case 'g': // Ground
                            case 'G':
                                SetConsoleTextAttribute(hstdout, 0x04);
                                break;
                            case 'i':
                            case 'I':
                                SetConsoleTextAttribute(hstdout, 0x0B);
                                break;
                            default:
                                SetConsoleTextAttribute(hstdout, 0x0F);
                                break;
                    }
                    cout << mapFrameBuffer[coorY][coorX];
                    SetConsoleTextAttribute(hstdout, 0x0F);
                }
            }
            else {
                mapFrameBuffer[coorY][coorX] = target.getTileTypeAt(coorX, coorY);
                setCursorPosition(coorX + mapOffsetX, coorY + mapOffsetY);

                #ifdef LINE_OF_SIGHT
                cout << mapFrameBuffer[coorY][coorX];
                #endif

                #ifndef FOG_OF_WAR
                cout << mapFrameBuffer[coorY][coorX];
                #endif
            }
        }
        drawMapBorder();
    }
    else {
        for (unsigned int i = 0; i < renderPos.size(); i++) {
            int coorX = renderPos[i].getX();
            int coorY = renderPos[i].getY();
            Entity* tempEntityPointer = target.getEntityAt(coorX, coorY);
            if (tempEntityPointer != NULL) {
                if (mapFrameBuffer[coorY][coorX] != tempEntityPointer->getEntityChar()) {
                    mapFrameBuffer[coorY][coorX] = tempEntityPointer->getEntityChar();
                    setCursorPosition(coorX + mapOffsetX, coorY + mapOffsetY);

                    // Coloring
                    switch (mapFrameBuffer[coorY][coorX]) {
                            case 'n': // Water Ground
                            case 'N':
                                SetConsoleTextAttribute(hstdout, 0x0A);
                                break;
                            case 's': // Water Ice
                            case 'S':
                                SetConsoleTextAttribute(hstdout, 0x0D);
                                break;
                            case 'w':
                            case 'W':
                                SetConsoleTextAttribute(hstdout, 0x09);
                                break;
                            case 'l': // Fire Electric
                            case 'L':
                                SetConsoleTextAttribute(hstdout, 0x08);
                                break;
                            case 'f': // Fire
                            case 'F':
                                SetConsoleTextAttribute(hstdout, 0x0C);
                                break;
                            case 'e': // Electric
                            case 'E':
                                SetConsoleTextAttribute(hstdout, 0x06);
                                break;
                            case 'g': // Ground
                            case 'G':
                                SetConsoleTextAttribute(hstdout, 0x04);
                                break;
                            case 'i':
                            case 'I':
                                SetConsoleTextAttribute(hstdout, 0x0B);
                                break;
                            default:
                                SetConsoleTextAttribute(hstdout, 0x0F);
                                break;
                    }
                    cout << mapFrameBuffer[coorY][coorX];
                    SetConsoleTextAttribute(hstdout, 0x0F);
                }
            }
            else if (target.getTileTypeAt(coorX, coorY) != mapFrameBuffer[coorY][coorX]) {
                mapFrameBuffer[coorY][coorX] = target.getTileTypeAt(coorX, coorY);
                setCursorPosition(coorX + mapOffsetX, coorY + mapOffsetY);
                cout << mapFrameBuffer[coorY][coorX];
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
    HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
    system(CLEAR_SCREEN_CMD);
    SetConsoleTextAttribute(hstdout, 0x0C);
    cout << "\xdb\xdb\x20\xb0\xb0\xb0\xdb\xdb\x20\xb0\xdb\xdb\xdb\xdb\xdb\x20\xb0\xdb\xdb\x20\xb0\xb0\xb0\xdb\xdb\x20\x20\x20\xdb\xdb\xdb\xdb\xdb\xdb\x20\xb0\xdb\xdb\x20\xdb\xdb\xdb\xdb\xdb\xdb\xdb\x20\xdb\xdb\xdb\xdb\xdb\xdb\x20\xb0\xb0\xb0\xb0\x20\n";
    cout << "\x20\xdb\xdb\x20\xb0\xdb\xdb\x20\x20\xdb\xdb\x20\x20\x20\xdb\xdb\x20\xdb\xdb\x20\xb0\xb0\xb0\xdb\xdb\x20\x20\x20\xdb\xdb\x20\x20\x20\xdb\xdb\x20\xdb\xdb\x20\xdb\xdb\x20\x20\x20\x20\x20\x20\xdb\xdb\x20\x20\x20\xdb\xdb\x20\xb0\xb0\xb0\x20\n";
    cout << "\xb0\x20\xdb\xdb\xdb\xdb\x20\x20\xb0\xdb\xdb\x20\xb0\xb0\xdb\xdb\x20\xdb\xdb\x20\xb0\xb0\xb0\xdb\xdb\x20\x20\x20\xdb\xdb\x20\xb0\xb0\xdb\xdb\x20\xdb\xdb\x20\xdb\xdb\xdb\xdb\xdb\x20\xb0\xb0\xdb\xdb\x20\xb0\xb0\xdb\xdb\x20\xb0\xb0\xb0\x20\n";
    cout << "\xb0\xb0\x20\xdb\xdb\x20\x20\xb0\xb0\xdb\xdb\x20\xb0\xb0\xdb\xdb\x20\xdb\xdb\x20\xb0\xb0\xb0\xdb\xdb\x20\x20\x20\xdb\xdb\x20\xb0\xb0\xdb\xdb\x20\xdb\xdb\x20\xdb\xdb\x20\x20\x20\x20\xb0\xb0\xdb\xdb\x20\xb0\xb0\xdb\xdb\x20\xb0\xb0\xb0\x20\n";
    cout << "\xb0\xb0\xb0\xdb\xdb\x20\xb0\xb0\xb0\x20\xdb\xdb\xdb\xdb\xdb\x20\x20\x20\xdb\xdb\xdb\xdb\xdb\xdb\x20\x20\x20\x20\xdb\xdb\xdb\xdb\xdb\xdb\x20\x20\xdb\xdb\x20\xdb\xdb\xdb\xdb\xdb\xdb\xdb\x20\xdb\xdb\xdb\xdb\xdb\xdb\x20\x20\xdb\xdb\x20\x20\n";
    SetConsoleTextAttribute(hstdout, 0x0F);
}

void Render::clearMessageBox(Message& target) {
    target.fillEmptyBuffer();
    drawMessageBox(target);
    target.clearMessage();
    clearCursorRestArea();
}

bool Render::isRayBlocked(Position fromPos, Position toPos) {
    float xit = (float) fromPos.getX();
    float yit = (float) fromPos.getY();

    float xtarget = (float) toPos.getX();
    float ytarget = (float) toPos.getY();

    float delY = (ytarget-yit)/128;
    float delX = (xtarget-xit)/128;

    // No bound checking
    bool isRayHitOpaqueTile = false;
    while (xit < xtarget && yit < ytarget && not isRayHitOpaqueTile) {
        if (mapFrameBuffer[(int) yit][(int) xit] == '\xDB')
            isRayHitOpaqueTile = true;
        if (yit < ytarget)
            yit += delY;
        if (xit < xtarget)
            xit += delX;
    }

    return isRayHitOpaqueTile;
}

vector<Position> Render::getRenderedArea(Position pos) {
    vector<Position> renderedTile;
    for (int i = -8; i < 8; i++) {
        for (int j = -4; j < 4; j++) {
            Position tileToCheck = Position(pos.getX()+i , pos.getY()+j);
            if (0 <= tileToCheck.getX() && tileToCheck.getX() < mapSizeX) {
                if (0 <= tileToCheck.getY() && tileToCheck.getY() < mapSizeY) {
                    if (floorEuclidean(pos, tileToCheck) < 6) {
                        if (not isRayBlocked(pos, tileToCheck))
                            renderedTile.push_back(tileToCheck);
                    }
                }
            }
        }
    }
    return renderedTile;
}
