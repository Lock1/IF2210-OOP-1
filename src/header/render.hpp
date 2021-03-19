// 13519214
// Render class, used internally on engine
// NOTE : Render coordinate (0, 0) starting from upper left corner
// NOTE : Charset used = Extended ASCII
#ifndef RENDER_HPP
#define RENDER_HPP

#include "entities/map.hpp"
#include "messagebox.hpp"
#include "config.hpp"

class Render {
    private:
        int mapOffsetX;
        int mapOffsetY;

        int msgBoxOffsetX;
        int msgBoxOffsetY;

        unsigned char mapFrameBuffer[MAP_MAX_X][MAP_MAX_Y];
        // Map Frame buffer
        char msgFrameBuffer[MSG_MAX_X][MSG_MAX_Y];
        // Message Frame buffer
        bool isEmptyMapBuffer;
        bool isEmptyMsgBuffer;
        // Flag whether buffer is already filled or not

        // TODO : Cleanup stealing, set cursor pos as private method
        // Library importing
        // #define NOMINMAX
        // #define WIN32_LEAN_AND_MEAN
        // #include <Windows.h>	// Need for cls() and input()
        // #include <iostream>		// Usual i/o
        // #include <string>		// Need string for tooltip, name, etc
        // #include <queue>		// Queue system for input, action message
        // #include <vector>		// Maybe needed for keeping data
        // #include <chrono>		// Time and tick system
        // #include <thread>		// For sleep()
        // #include <stdlib.h>		// For random spread attack
        // void setCursorPosition(int x, int y) {
        //     static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        //     std::cout.flush();
        //     COORD coord = { (SHORT)x, (SHORT)y };
        //     SetConsoleCursorPosition(hOut, coord);
        // }


    public:
        Render(int offx, int offy, int msgoffx, int msgoffy);
        // User Constructor


        // -- Draw Method --
        // Use double buffering
        // TODO : Const
        void drawMap(Map& target);
        // Drawing map at offset location

        void drawMessageBox(MessageBox target);
        // Draw message box at offset location

};

#endif
