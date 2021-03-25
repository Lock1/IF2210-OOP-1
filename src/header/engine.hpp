// 13519214
// Game Engine
#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "config.hpp"
#include "render.hpp"
#include "message.hpp"
#include "playerinput.hpp"
#include "skilldatabase.hpp"
#include "speciesdatabase.hpp"
#include "entities/map.hpp"
#include "entities/player.hpp"
#include "entities/engimon.hpp"
#include "entities/position.hpp"
#include "entities/direction.hpp"
#include <vector>

class Engine {
    private:
        Map map;
        Message messageList;
        Message statMessage;
        Message thisisfine; // <<< DEBUG
        PlayerInput userInput;
        SkillDatabase skillDB;
        SpeciesDatabase speciesDB;
        Player player;
        Render renderer;
        Render statRenderer;
        Render ok; // <<<< DEBUG
        bool isEngineRunning;
        bool isCommandMode;
        std::vector<Engimon*> engimonList;
        int spawnLevelCap;
        // Increment for every engimon level up
        const int maxSkillID;

        const unsigned int wildEngimonSpawnProbability;
        // Spawn probability in percent
        const unsigned int wildEngimonDropProbability;
        // Drop probability in percent
        const unsigned int xpMultiplier;
        // XP multiplier on win battle
        const unsigned int entitySpawnLimit;
        // Entity count limit, player included

        void clearConsoleInputBuffer();
        // Clearing getKeyState() from cin
        bool evaluteInput();
        // Evaluating input from PlayerInput class, if evaluated, return true
        void evaluteTick();
        // Evaluating next tick
        void commandMode();
        // Change from movement mode to command mode
        void updateCurrentEngimonMessageStatus();
        // Update current engimon stat to stat message box

        void showItemInventory();
        // Show player item inventory to message list box
        void showEngimonInventory();
        // Show player engimon inventory to message list box
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
