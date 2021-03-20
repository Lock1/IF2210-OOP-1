// 13519214
// Multi-threading player input
#ifndef PLAYERINPUT_HPP
#define PLAYERINPUT_HPP

#include <queue>
#include <thread>
#include <mutex>

enum InputType {
    Up,
    Down,
    Left,
    Right,
    Number1,
    Number2,
    Number3,
    Number4,
    EscKey,
    EmptyInput
};

class PlayerInput {
    private:
        std::thread *inputThread;
        std::mutex inputLock;
        std::queue<InputType> inputBuffer;
        const unsigned int maxInputBuffer;
        bool isRunning;

        void inputLoop();
        // Internal loop for reading input
    public:
        PlayerInput(unsigned int maxBuf);
        // User Constructor
        ~PlayerInput();

        void startReadInput();
        // Start input reading
        void stopReadInput();
        // Stop input reading

        InputType getUserInput();
        // Get InputType from stdin
};

#endif
