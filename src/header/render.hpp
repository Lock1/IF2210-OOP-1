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

        const int msgOffsetX;
        const int msgOffsetY;

        char mapFrameBuffer[MAP_MAX_Y][MAP_MAX_X];
        // Map Frame buffer
        bool isEmptyMapBuffer;
        // Flag whether buffer is already filled or not
        bool isMessageBorderDrawn;
        // Flag whether message box border is drawn or not

        void setCursorPosition(int x, int y);

        void drawMapBorder(Map& target);
        // Drawing map border

        void drawMsgBorder(Message& target);
        // Drawing message border
    public:
        Render(int offx, int offy, int msgoffx, int msgoffy, Map& target);
        // User Constructor


        // -- Draw Method --
        // Use double buffering
        // TODO : Const
        void drawMap(Map& target);
        // Drawing map at offset location

        void drawMessageBox(Message& target);
        // Draw message box at offset location

};

#endif
