// 13519214
// Render class, used internally on engine
// NOTE : Render coordinate (0, 0) starting from upper left corner

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

        // TODO : Decide frame buffer style
        char mapFrameBuffer[MAP_MAX_X][MAP_MAX_Y];
        // Map Frame buffer
        char msgFrameBuffer[MAP_MAX_X][MAP_MAX_Y];
        // Message Frame buffer
        bool isEmptyBuffer;
        // Flag whether buffer is already filled or not
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
