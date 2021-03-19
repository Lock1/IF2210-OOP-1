// 13519214
// Render class, used internally on engine
// NOTE : Render coordinate (0, 0) starting from upper left corner
// NOTE : Charset used = Extended ASCII
#ifndef RENDER_HPP
#define RENDER_HPP

#include "entities/map.hpp"
#include "message.hpp"
#include "config.hpp"

class Render {
    private:
        const int mapOffsetX;
        const int mapOffsetY;

        const int msgBoxOffsetX;
        const int msgBoxOffsetY;

        char mapFrameBuffer[MAP_MAX_Y][MAP_MAX_X];
        // Map Frame buffer
        bool isEmptyMapBuffer;
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
        void setCursorPosition(int x, int y);

        void drawMapBorder(Map& target);
        // Drawing map border

    public:
        Render(int offx, int offy, int msgoffx, int msgoffy, Map& target);
        // User Constructor


        // -- Draw Method --
        // Use double buffering
        // TODO : Const
        void drawMap(Map& target);
        // Drawing map at offset location

        void drawMessageBox(Message target);
        // Draw message box at offset location

};

#endif
