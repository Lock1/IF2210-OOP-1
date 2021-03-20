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
#include "entities/engimon.hpp"
#include <vector>

class Engine {
    private:
        Map map;
        Render renderer;
        Message messageList;
        PlayerInput userInput;
        bool isEngineRunning;
        Player player;
        std::vector<Engimon*> engimonList;

        bool evaluteInput();
        // Evaluating input from PlayerInput class, if evaluated, return true
        void evaluteTick();
        // Evaluating next tick
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
