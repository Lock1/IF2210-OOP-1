// 13519214
// Game Engine
#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "config.hpp"
#include "render.hpp"
#include "message.hpp"
#include "playerinput.hpp"
#include "entities/map.hpp"
#include "entities/player.hpp"

class Engine {
    private:
        Map map;
        Render renderer;
        Message messageList;
        PlayerInput userInput;
        bool isEngineRunning;
        Player player;
        void evaluteInput();
        // Evaluating input from PlayerInput class
    public:
        Engine();
        // Constructor
        ~Engine();
        // Destructor

        void startGame();
        // Start game
        void loadDatabase();
        // TODO : Needed (?)
};

#endif
