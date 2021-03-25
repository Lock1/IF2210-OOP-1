// 13519214
#include "header/render.hpp"
#include "header/engine.hpp"
#include "header/playerinput.hpp"
#include "header/entities/map.hpp"
#include "header/entities/player.hpp"
#include "header/entities/engimon.hpp"
#include "header/entities/species.hpp"
#include "header/skilldatabase.hpp"
#include "header/speciesdatabase.hpp"
#include "header/battle.hpp"
#include "header/entities/attributes/elementtype.hpp"
#include "header/inventory"
#include <iostream>
#include <string>
#include <chrono>       // Time and tick system
#include <thread>       // For sleep()
#include <map>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>

using namespace std;


Engine::Engine() : messageList(MAX_MESSAGE, MSG_MAX_X), statMessage(MAX_MESSAGE-10, MSG_MAX_X-5),
        thisisfine(MAX_MESSAGE-12, MSG_MAX_X-5), // DEBUG
        player(MAX_INVENTORY, MAX_SKILL_ID), maxSkillID(MAX_SKILL_ID),
        // map(MAP_MAX_X, MAP_MAX_Y, SEA_STARTING_X, SEA_STARTING_Y), // DEBUG
        map("../other/mapfile.txt"),
        userInput(INPUT_BUFFER_COUNT, INPUT_DELAY_MS),
        wildEngimonSpawnProbability(4), wildEngimonDropProbability(30),
        entitySpawnLimit(20), xpMultiplier(XP_MULTIPLIER),
        renderer(map, messageList), statRenderer(statMessage), ok(thisisfine) {
    // Internal variable setup
    srand((unsigned) time(NULL));
    isEngineRunning = true;
    isCommandMode = false;
    spawnLevelCap = 10;
    renderer.setMapOffset(MAP_OFFSET_X, MAP_OFFSET_Y);
    renderer.setMessageBoxOffset(MESSAGE_OFFSET_X, MESSAGE_OFFSET_Y);
    renderer.setCursorRestLocation(CURSOR_REST_X, CURSOR_REST_Y);

    statRenderer.setMessageBoxOffset(MESSAGE_OFFSET_X+messageList.getMaxStringLength()+3, MESSAGE_OFFSET_Y);
    statRenderer.setCursorRestLocation(CURSOR_REST_X, CURSOR_REST_Y);

    // DEBUG
    ok.setMessageBoxOffset(MESSAGE_OFFSET_X+messageList.getMaxStringLength()+3, MESSAGE_OFFSET_Y+12);
    ok.setCursorRestLocation(CURSOR_REST_X, CURSOR_REST_Y);

    // Set message box titles
    renderer.setMessageTitle("Ini kotak gan");
    statRenderer.setMessageTitle("Ini bukan kotak");
    ok.setMessageTitle("Ini bo'ongan"); // <<< DEBUG

    // TODO : Add prompt (?)
    // TODO : Add splash screen (?)
    try {
        skillDB.loadSkillDatabase("../other/skilldb.txt");
    }
    catch (string e) {
        cout << "Skill database not found\n";
    }

    try {
        speciesDB.loadSpeciesDatabase("../other/speciesdb.txt", skillDB);
    }
    catch (string e) {
        cout << "Species database not found\n";
    }
}

Engine::~Engine() {
    // TODO : Cleanup variable
    // TODO : Destroy allocated engimonList
}

void Engine::clearConsoleInputBuffer() {
    // Source : http://cplusplus.com/forum/beginner/248262/
    PINPUT_RECORD ClearingVar1 = new INPUT_RECORD[256];
    DWORD ClearingVar2;
    ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE),ClearingVar1,256,&ClearingVar2);
    delete[] ClearingVar1;
}


void Engine::startGame() {
    system(CLEAR_SCREEN_CMD);

    map.setTileEntity(player.getPos(), &player);
    // Starting item
    Engimon *starterEngimon = new Engimon(speciesDB.getSpecies((rand() % 10) + 1), false, Position(0, 0), (rand() % 10) + 1);
    engimonList.push_back(starterEngimon);
    player.changeEngimon(starterEngimon);
    player.addEngimonItem(starterEngimon);
    map.setTileEntity(starterEngimon->getPos(), starterEngimon);


    userInput.startReadInput();
    updateCurrentEngimonMessageStatus();

    while (isEngineRunning) {
        // Drawing map and message box
        renderer.drawMap(map);
        renderer.drawMessageBox(messageList);
        statRenderer.drawMessageBox(statMessage);
        ok.drawMessageBox(thisisfine);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        if (evaluteInput() && not isCommandMode) {
            evaluteTick();
        }
        else if (isCommandMode) {
            commandMode();
            // Call command mode
        }

    }
    userInput.stopReadInput();
}

bool Engine::evaluteInput() {
    InputType inputKey = userInput.getUserInput();
    Tile targetTile = Tile(0, 0, Grass);
    bool isMovementValid = false;
    Direction targetDirection;
    switch (inputKey) {
        case EscKey:
            isEngineRunning = false;
            break;
        case Up:
            if (player.getPos().getY() > 0) {
                targetTile = map.getTileAt(player.getPos().getX(), player.getPos().getY()-1);
                if (player.isMoveLocationValid(targetTile)) {
                    targetDirection = North;
                    isMovementValid = true;
                }
            }
            break;
        case Down:
            if (player.getPos().getY() < map.getSizeY() - 1) {
                targetTile = map.getTileAt(player.getPos().getX(), player.getPos().getY()+1);
                if (player.isMoveLocationValid(targetTile)) {
                    targetDirection = South;
                    isMovementValid = true;
                }
            }
            break;
        case Left:
            if (player.getPos().getX() > 0) {
                targetTile = map.getTileAt(player.getPos().getX()-1, player.getPos().getY());
                if (player.isMoveLocationValid(targetTile)) {
                    targetDirection = West;
                    isMovementValid = true;
                }
            }
            break;
        case Right:
            if (player.getPos().getX() < map.getSizeX() - 1) {
                targetTile = map.getTileAt(player.getPos().getX()+1, player.getPos().getY());
                if (player.isMoveLocationValid(targetTile)) {
                    targetDirection = East;
                    isMovementValid = true;
                }
            }
            break;
        case KeyboardE:
            isCommandMode = true;
            break;
    }

    if (isMovementValid) {
        map.moveEntity(player.getPos(), targetDirection);
        map.moveEntity(player.getCurrentEngimon()->getPos(), player.getLastDirection());
        player.getLastDirectionRef() = targetDirection;
        return true;
    }
    else if (targetTile.getEntity() != NULL) {
        Entity* targetEntity = targetTile.getEntity();
        if (targetEntity->getEntityID() == EntityEngimon) {
            Engimon *targetEngimon = (Engimon *) targetEntity;
            if (not targetEngimon->isWildEngimon()) {
                string interactionMessage = targetEngimon->getEngimonName();
                interactionMessage = interactionMessage + " : ";
                interactionMessage = interactionMessage + targetEngimon->getInteractString();
                messageList.addMessage(interactionMessage);
            }
            else {
                Battle doBattle = Battle(player.getCurrentEngimon(), targetEngimon);
                thisisfine.fillEmptyBuffer();
                ok.drawMessageBox(thisisfine);
                thisisfine.clearMessage();

                string wildEngimonName = "Species \xB3 ";
                wildEngimonName = wildEngimonName + targetEngimon->getName();
                thisisfine.addMessage(wildEngimonName);

                string wildEngimonLevel = "Lvl     \xB3 ";
                wildEngimonLevel = wildEngimonLevel + to_string(targetEngimon->getLevel());
                thisisfine.addMessage(wildEngimonLevel);

                set<ElementType> elements = targetEngimon->getElements();
                string typeMsg = "Type    \xB3 ";
                if (elements.find(Fire) != elements.end())
                    typeMsg = typeMsg + "Fire ";
                if (elements.find(Ice) != elements.end())
                    typeMsg = typeMsg + "Ice ";
                if (elements.find(Water) != elements.end())
                    typeMsg = typeMsg + "Water ";
                if (elements.find(Ground) != elements.end())
                    typeMsg = typeMsg + "Ground ";
                if (elements.find(Electric) != elements.end())
                    typeMsg = typeMsg + "Electric ";
                thisisfine.addMessage(typeMsg);


                userInput.toggleReadInput();
                // Temporary stop input thread from queueing movement input
                clearConsoleInputBuffer();
                // Clearing current input buffer (GetKeyState() does not clear buffer)
                thisisfine.addMessage("Power   \xB3 " + to_string(doBattle.getEngimon2Power()));
                thisisfine.addMessage("");
                thisisfine.addMessage("Your engimon stat");
                thisisfine.addMessage("Power   \xB3 " + to_string(doBattle.getEngimon1Power()));
                thisisfine.addMessage("Fight ? (yes/no)");
                ok.drawMessageBox(thisisfine);

                string commandBuffer;
                bool isPromptDone = false;
                while (not isPromptDone) {
                    renderer.clearCursorRestArea();
                    cout << ">>> ";
                    getline(cin, commandBuffer);
                    if (commandBuffer == "yes" || commandBuffer == "y") {
                        // TODO : Level up increase spawnLevelCap
                        bool isEnemyDied = false, isPlayerEngimonDied = false;
                        messageList.addMessage("");
                        switch (doBattle.getBattleWinner()) {
                            case 1:
                                messageList.addMessage(targetEngimon->getEngimonName() + " defeated");
                                // TODO : maybe remove
                                isEnemyDied = true;
                                break;
                            case 2:
                                messageList.addMessage("your engimon dies");
                                isPlayerEngimonDied = true;
                                break;
                            default:
                                messageList.addMessage("both dies");
                                isPlayerEngimonDied = true;
                                isEnemyDied = true;
                                break;
                        }
                        // TODO : Kill player engimon
                        // Branch if player engimon died
                        // TODO : Add
                        // TODO : Delete item

                        // Branch if enemy died
                        if (isEnemyDied && not isPlayerEngimonDied) {
                            // Level up checking
                            int levelGained = player.getCurrentEngimon()->xpGain(targetEngimon->getLevel()*xpMultiplier);
                            if (levelGained > 0) {
                                spawnLevelCap += levelGained;
                            }

                            // Random mastery level up
                            vector<Skill>& SkillReference = player.getCurrentEngimon()->getSkillListRef();
                            for (unsigned i = 0; i < SkillReference.size(); i++) {
                                if ((rand() % 100) < 40)
                                    SkillReference[i].levelUpMastery();
                            }

                            // Random skill drop
                            int dropRoll = rand() % 100;
                            if ((unsigned) dropRoll < wildEngimonDropProbability) {
                                SkillItem droppedSkill = 1; // Placeholder
                                string droppedSkillName = "";
                                bool isSkillDropValid = false;
                                set<ElementType> targetEngimonElements = targetEngimon->getElements();
                                while (not isSkillDropValid) {
                                    // Try catch block for random skill picking
                                    try {
                                        Skill randomSkill = skillDB.getSkill(rand() % maxSkillID);
                                        if (randomSkill.isElementCompatible(*(targetEngimonElements.begin()))) {
                                            isSkillDropValid = true;
                                        }
                                        else if (++(targetEngimonElements.begin()) != targetEngimonElements.end()) {
                                            // If multi element, check other one
                                            if (randomSkill.isElementCompatible(*(++(targetEngimonElements.begin()))))
                                                isSkillDropValid = true;
                                        }

                                        if (isSkillDropValid) {
                                            droppedSkill = randomSkill.getSkillID();
                                            droppedSkillName = randomSkill.getSkillName();
                                        }
                                    }
                                    catch (int e) {
                                        // Empty catch block
                                    }

                                }

                                player.addSkillItem(droppedSkill); // TODO : << Catch bool return, delete if full
                                messageList.addMessage(droppedSkillName + " dropped");

                            }

                            map.setTileEntity(targetEngimon->getPos(), NULL);
                            targetEngimon->tameEngimon();
                            // Catching prompt
                            bool validCatchCommand = false, catchEngimon = false;
                            while (not validCatchCommand) {
                                messageList.addMessage("Catch engimon? (y/n)");
                                renderer.drawMessageBox(messageList);
                                renderer.clearCursorRestArea();
                                cout << ">>> ";
                                getline(cin, commandBuffer);
                                if (commandBuffer == "y") {
                                    player.addEngimonItem(targetEngimon); // TODO : << Delete inventory
                                    messageList.addMessage(targetEngimon->getEngimonName() + " catched!");
                                    catchEngimon = true;
                                    validCatchCommand = true;
                                    // Remove from map and add to inventory
                                }
                                else if (commandBuffer == "n") {
                                    validCatchCommand = true;
                                }
                            }

                            if (not catchEngimon)
                                delete targetEngimon;

                            updateCurrentEngimonMessageStatus();
                        }

                        // Maximum cummulative XP check
                        if (player.getCurrentEngimon()->isMaxCXP()) {
                            // TODO : Kill
                        }

                        isPromptDone = true;
                    }
                    else if (commandBuffer == "no" || commandBuffer == "n")
                        isPromptDone = true;
                }
                thisisfine.fillEmptyBuffer();
                ok.drawMessageBox(thisisfine);
                thisisfine.clearMessage();

                userInput.toggleReadInput();
                renderer.clearCursorRestArea();
            }
        }
    }

    return false;
}

void Engine::evaluteTick() {
    // TODO : Add here
    map.wildEngimonRandomMove();
    unsigned int randomNumber = rand() % 100;
    if (Entity::getEntityCount() < entitySpawnLimit && randomNumber < wildEngimonSpawnProbability) {
        unsigned int randomSpeciesID = (rand() % (speciesDB.getSpeciesCount() - 1)) + 1;
        // TODO : Extra, fix mod operator
        Engimon *spawnedEngimon = map.spawnWildEngimon(speciesDB.getSpecies(randomSpeciesID), spawnLevelCap);

        // Random skill adder, 3x roll chance to get additional skill
        // Higher level cap also grant higher chance to get multiple skill,
        // up to 100% chance getting 4 skill
        set<ElementType> engimonElements = spawnedEngimon->getElements();
        for (int i = 0; i < 3; i++) {
            if ((rand() % 100) < 10 + spawnLevelCap) {
                // Try catch block random skill
                Skill generatedSkill = skillDB.getSkill(1); // Placeholder
                bool isSkillGeneratedValid = false;
                while (not isSkillGeneratedValid) {
                    try {
                        generatedSkill = skillDB.getSkill(rand() % maxSkillID);
                        if (generatedSkill.isElementCompatible(*engimonElements.begin())) {
                            isSkillGeneratedValid = true;
                        }
                        else if (++engimonElements.begin() != engimonElements.end()) {
                            if (generatedSkill.isElementCompatible(*(++engimonElements.begin())))
                                isSkillGeneratedValid = true;
                        }

                        if (isSkillGeneratedValid) {
                            int masteryLevelUp = (rand() % (1 + spawnLevelCap/5));
                            for (int j = 0; j < masteryLevelUp; j++)
                                generatedSkill.levelUpMastery();

                            spawnedEngimon->addSkill(generatedSkill);
                        }
                    }
                    catch (int e) {

                    }
                }
            }
        }
        engimonList.push_back(spawnedEngimon);
    }
}

void Engine::commandMode() {
    // TODO : Extra, super-duper-repetition :(
    userInput.toggleReadInput();
    // Temporary stop input thread from queueing movement input
    clearConsoleInputBuffer();
    // Clearing current input buffer (GetKeyState() does not clear buffer)

    messageList.fillEmptyBuffer();
    renderer.drawMessageBox(messageList);
    messageList.clearMessage();
    // Clearing message list window

    messageList.addMessage(" \xCD\xCD\xCD\xCD Command list \xCD\xCD\xCD\xCD ");
    messageList.addMessage("1. inventory   ");
    messageList.addMessage("2. engimon     ");
    messageList.addMessage("3. change      ");
    messageList.addMessage("4. item        ");
    messageList.addMessage("5. breed       ");
    // TODO : Delete

    renderer.drawMessageBox(messageList);

    string commandBuffer;
    cout << ">>> ";
    getline(cin, commandBuffer);

    messageList.fillEmptyBuffer();
    renderer.drawMessageBox(messageList);
    messageList.clearMessage();
    // Clearing message list window

    if (commandBuffer == "dbg") { // DEBUG
        player.addEngimonItem(new Engimon(speciesDB.getSpecies(3), false, Position(0, 0)));
        player.addEngimonItem(new Engimon(speciesDB.getSpecies(2), false, Position(0, 0)));
        player.addEngimonItem(new Engimon(speciesDB.getSpecies(rand()%10+1), false, Position(0, 0)));
        player.addSkillItem(4);
        player.addSkillItem(3);
        player.addSkillItem(rand()%10+1);
    }
    // TODO : Add
    // else if (commandBuffer == "breed")
    else if (commandBuffer == "engimon") {
        // TODO : Print parent
        list<EngimonItem> engimonInv = player.getEngimonInventory();
        int number = 1;
        for (auto it = engimonInv.begin(); it != engimonInv.end(); ++it) {
            Engimon *targetEngimon = *it;
            string speciesNameMsg = "Species \xB3 ";
            speciesNameMsg = speciesNameMsg + targetEngimon->getName();
            messageList.addMessage(speciesNameMsg);

            string nameMsg = "Name    \xB3 ";
            nameMsg = nameMsg + targetEngimon->getEngimonName();
            messageList.addMessage(nameMsg);

            string levelMsg = "Lvl     \xB3 ";
            levelMsg = levelMsg + to_string(targetEngimon->getLevel());
            messageList.addMessage(levelMsg);

            string xpMsg = "XP      \xB3 ";
            xpMsg = xpMsg + to_string(targetEngimon->getXP());
            messageList.addMessage(xpMsg);

            set<ElementType> elements = targetEngimon->getElements();
            string typeMsg = "Type    \xB3 ";
            if (elements.find(Fire) != elements.end())
                typeMsg = typeMsg + "Fire ";
            if (elements.find(Ice) != elements.end())
                typeMsg = typeMsg + "Ice ";
            if (elements.find(Water) != elements.end())
                typeMsg = typeMsg + "Water ";
            if (elements.find(Ground) != elements.end())
                typeMsg = typeMsg + "Ground ";
            if (elements.find(Electric) != elements.end())
                typeMsg = typeMsg + "Electric ";
            messageList.addMessage(typeMsg);

            messageList.addMessage(" \xCD\xCD\xCD\xCD Learned skill \xCD\xCD\xCD\xCD ");
            vector<Skill> skillList = targetEngimon->getSkillList();
            for (int i = 0; (unsigned) i < skillList.size(); i++) {
                string skillRow = skillList[i].getSkillName();
                skillRow = skillRow + " Lvl-" + to_string(skillList[i].getMasteryLevel());
                skillRow = skillRow + " Pow-" + to_string(skillList[i].getBasePower());
                messageList.addMessage(skillRow);
            }
            messageList.addMessage(" \xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD ");
            messageList.addMessage("");
            number++;
            if (number > 1) {
                messageList.addMessage("Press enter to print next");
                renderer.drawMessageBox(messageList);
                renderer.clearCursorRestArea();
                cout << ">>> ";
                getline(cin, commandBuffer);
                messageList.addMessage("");
            }
        }
        messageList.addMessage("End of inventory");
        renderer.drawMessageBox(messageList);
    }
    else if (commandBuffer == "inventory") {
        showItemInventory();
    }
    else if (commandBuffer == "change") {
        messageList.addMessage("Select Engimon Number");
        list<EngimonItem> engimonInv = player.getEngimonInventory();
        showEngimonInventory();
        bool doneChanging = false;
        messageList.addMessage("End of inventory list");
        messageList.addMessage("");
        messageList.addMessage("Input engimon number or exit");
        while (not doneChanging) {
            renderer.drawMessageBox(messageList);
            renderer.clearCursorRestArea();
            cout << ">>> ";
            getline(cin, commandBuffer);

            if (commandBuffer == "exit")
                break;

            // Trying to parsing to int
            int targetNumber;
            bool successParsing = false;
            try {
                targetNumber = stoi(commandBuffer);
                successParsing = true;
            }
            catch (invalid_argument e) {
                messageList.addMessage("Invalid input");
            }

            // If number are in valid range, then change
            if (successParsing && 0 < targetNumber && targetNumber <= (int) engimonInv.size()) {
                auto it = engimonInv.begin();
                int i = 0;
                while (i < targetNumber-1) {
                    i++;
                    ++it;
                }
                Engimon *targetEngimon = *it;
                string changingString = "Changed to ";
                changingString = changingString + targetEngimon->getEngimonName();
                messageList.addMessage("");
                messageList.addMessage(changingString);
                map.setTileEntity(player.getCurrentEngimon()->getPos(), targetEngimon);
                player.changeEngimon(targetEngimon);
                updateCurrentEngimonMessageStatus();
                doneChanging = true;
            }
            else if (successParsing) {
                messageList.addMessage("Number is out of range");
            }
        }
    }
    else if (commandBuffer == "item") {
        showItemInventory();
        std::map<SkillItem,int> skillInv = player.getSkillInventory();
        messageList.addMessage("");
        messageList.addMessage("Input item ID");

        renderer.drawMessageBox(messageList);
        renderer.clearCursorRestArea();
        cout << ">>> ";
        getline(cin, commandBuffer);

        // Trying to parsing to int
        int targetNumber;
        bool successParsing = false;
        try {
            targetNumber = stoi(commandBuffer);
            successParsing = true;
        }
        catch (invalid_argument e) {
            messageList.addMessage("Invalid input");
        }

        // If number are in valid range, then process
        if (successParsing && 0 < targetNumber && targetNumber <= (int) maxSkillID) {
            if (skillInv[targetNumber] > 0) {
                int skillIDTarget = targetNumber;
                list<EngimonItem> engimonInv = player.getEngimonInventory();
                showEngimonInventory();

                messageList.addMessage("Input engimon number");
                renderer.drawMessageBox(messageList);
                renderer.clearCursorRestArea();
                cout << ">>> ";
                getline(cin, commandBuffer);

                // Trying to parsing to int
                targetNumber = 0;
                successParsing = false;
                try {
                    targetNumber = stoi(commandBuffer);
                    successParsing = true;
                }
                catch (invalid_argument e) {
                    messageList.addMessage("Invalid input");
                }

                // If number are in valid range, then change
                if (successParsing && 0 < targetNumber && targetNumber <= (int) engimonInv.size()) {
                    auto it = engimonInv.begin();
                    int i = 0;
                    while (i < targetNumber-1) {
                        i++;
                        ++it;
                    }
                    Engimon *targetEngimon = *it;
                    if (skillDB.isCompatible(*targetEngimon, skillIDTarget)) {
                        Skill targetSkill = skillDB.getSkill(skillIDTarget);
                        string learningString = targetEngimon->getEngimonName();
                        learningString = learningString + " learned ";
                        learningString = learningString + targetSkill.getSkillName();

                        targetSkill.levelUpMastery();
                        if (targetEngimon->addSkill(targetSkill)) {
                            messageList.addMessage("");
                            messageList.addMessage(learningString);
                            player.delSkillItem(skillIDTarget);
                        }
                        else
                            messageList.addMessage("Skill already learned");
                        updateCurrentEngimonMessageStatus();
                        messageList.addMessage("");
                        messageList.addMessage("");
                        messageList.addMessage("");
                    }
                    else {
                        messageList.addMessage("Skill not compatible");
                    }
                }
                else if (successParsing) {
                    messageList.addMessage("Number is out of range");
                }

            }
            else
                messageList.addMessage("Item not found");
        }
        else if (successParsing) {
            messageList.addMessage("Number is out of range");
        }
    }


    userInput.toggleReadInput();
    renderer.clearCursorRestArea();
    isCommandMode = false;
}

void Engine::updateCurrentEngimonMessageStatus() {
    statMessage.clearMessage();
    string speciesNameMsg = "Species \xB3 ";
    speciesNameMsg = speciesNameMsg + player.getCurrentEngimon()->getName();
    statMessage.addMessage(speciesNameMsg);

    string nameMsg = "Name    \xB3 ";
    nameMsg = nameMsg + player.getCurrentEngimon()->getEngimonName();
    statMessage.addMessage(nameMsg);

    string levelMsg = "Lvl     \xB3 ";
    levelMsg = levelMsg + to_string(player.getCurrentEngimon()->getLevel());
    statMessage.addMessage(levelMsg);

    string xpMsg = "XP      \xB3 ";
    xpMsg = xpMsg + to_string(player.getCurrentEngimon()->getXP());
    statMessage.addMessage(xpMsg);

    set<ElementType> elements = player.getCurrentEngimon()->getElements();
    string typeMsg = "Type    \xB3 ";
    if (elements.find(Fire) != elements.end())
        typeMsg = typeMsg + "Fire ";
    if (elements.find(Ice) != elements.end())
        typeMsg = typeMsg + "Ice ";
    if (elements.find(Water) != elements.end())
        typeMsg = typeMsg + "Water ";
    if (elements.find(Ground) != elements.end())
        typeMsg = typeMsg + "Ground ";
    if (elements.find(Electric) != elements.end())
        typeMsg = typeMsg + "Electric ";
    statMessage.addMessage(typeMsg);

    statMessage.addMessage(" \xCD\xCD\xCD\xCD Learned skill \xCD\xCD\xCD\xCD ");
    vector<Skill> skillList = player.getCurrentEngimon()->getSkillList();
    for (int i = 0; (unsigned) i < skillList.size(); i++) {
        string skillRow = skillList[i].getSkillName();
        skillRow = skillRow + " Lvl-" + to_string(skillList[i].getMasteryLevel());
        skillRow = skillRow + " Pow-" + to_string(skillList[i].getBasePower());
        statMessage.addMessage(skillRow);
    }

    statRenderer.drawMessageBox(statMessage);
}

void Engine::showItemInventory() {
    // TODO : Extra, maybe need to enter to more ?
    messageList.addMessage("Inventory list");
    messageList.addMessage("ID Name       Count Type Power");
    std::map<SkillItem,int> skillInv = player.getSkillInventory();
    for (int i = 0; i < maxSkillID; i++) {
        if (skillInv[i] > 0) {
            string skillRow;
            Skill target = skillDB.getSkill(i);
            string paddedID = to_string(target.getSkillID());
            for (int i = paddedID.length(); i < 2; i++)
                paddedID = paddedID + " ";
            string paddedSkillName = target.getSkillName();
            for (int i = paddedSkillName.length(); i < 12; i++)
                paddedSkillName = paddedSkillName + " ";
            skillRow = paddedID + " " + paddedSkillName + " " + to_string(skillInv[i]) + " ";
            switch (target.getSkillElement()) {
                case Fire:
                    skillRow = skillRow + "Fire     ";
                    break;
                case Ice:
                    skillRow = skillRow + "Ice      ";
                    break;
                case Water:
                    skillRow = skillRow + "Water    ";
                    break;
                case Ground:
                    skillRow = skillRow + "Ground   ";
                    break;
                case Electric:
                    skillRow = skillRow + "Electric ";
                    break;
            }
            skillRow = skillRow + to_string(target.getBasePower());
            messageList.addMessage(skillRow);
        }
    }
}

void Engine::showEngimonInventory() {
    string commandBuffer;
    list<EngimonItem> engimonInv = player.getEngimonInventory();
    int number = 1;
    for (auto it = engimonInv.begin(); it != engimonInv.end(); ++it) {
        Engimon *targetEngimon = *it;
        string numberMsg = "\xCD\xCD\xCD\xCD\xCD\xCD\xCD";
        numberMsg = numberMsg + "  " + to_string(number) + "  " + numberMsg;
        messageList.addMessage(numberMsg);
        number++;

        string nameMsg = "Name    \xB3 ";
        nameMsg = nameMsg + targetEngimon->getEngimonName();
        messageList.addMessage(nameMsg);

        string levelMsg = "Lvl     \xB3 ";
        levelMsg = levelMsg + to_string(targetEngimon->getLevel());
        messageList.addMessage(levelMsg);

        set<ElementType> elements = targetEngimon->getElements();
        string typeMsg = "Type    \xB3 ";
        if (elements.find(Fire) != elements.end())
            typeMsg = typeMsg + "Fire ";
        if (elements.find(Ice) != elements.end())
            typeMsg = typeMsg + "Ice ";
        if (elements.find(Water) != elements.end())
            typeMsg = typeMsg + "Water ";
        if (elements.find(Ground) != elements.end())
            typeMsg = typeMsg + "Ground ";
        if (elements.find(Electric) != elements.end())
            typeMsg = typeMsg + "Electric ";
        messageList.addMessage(typeMsg);

        messageList.addMessage("");
        if ((number-1) % 3 == 0 && number > 1) {
            messageList.addMessage("Press enter to print next");
            renderer.drawMessageBox(messageList);
            renderer.clearCursorRestArea();
            cout << ">>> ";
            getline(cin, commandBuffer);
            messageList.addMessage("");
        }
    }
}

// void Engine::deleteInventory() {
//  // TODO : Add
// }
