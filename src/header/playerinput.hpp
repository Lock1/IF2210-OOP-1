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
    EmptyInput,
    KeyboardE
};

class PlayerInput {
    private:
        std::thread *inputThread;
        std::mutex inputLock;
        std::queue<InputType> inputBuffer;
        const unsigned int maxInputBuffer;
        const unsigned int inputDelayMillisecond;
        bool isRunning;
        bool isReading;

        void inputLoop();
        // Internal loop for reading input
    public:
        PlayerInput(unsigned int maxBuf, unsigned int inpDelay);
        // User Constructor
        ~PlayerInput();

        void startReadInput();
        // Start input reading
        void toggleReadInput();
        // Temporary disable reading input
        void stopReadInput();
        // Fully stop PlayerInput reading

        InputType getUserInput();
        // Get InputType from stdin
};

#endif
