// 13519214
// Game Engine
#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "config.hpp"
#include "render.hpp"
#include "entities/map.hpp"
// TODO : Input Class
class Engine {
    private:
        // TODO : Add variables
        Map map;
        Render renderer;
    public:
        Engine();
        ~Engine();

        void startGame();
        void loadDatabase();
};

#endif
