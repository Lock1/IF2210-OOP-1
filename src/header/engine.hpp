// 13519214
// Game Engine
#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "config.hpp"
#include "entities/map.hpp"

class Engine {
    private:
        // TODO : Add variables
        Map map;
    public:
        Engine();
        ~Engine();

        void startGame();
        void loadDatabase();
};

#endif
