// 13519214
#ifndef PLAYERINPUT_HPP
#define PLAYERINPUT_HPP

#include <queue>
#include <thread>

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
        std::queue<InputType> inputBuffer;
        const unsigned int maxInputBuffer;

    public:
        PlayerInput(unsigned int maxBuf);
        // User Constructor

        InputType getUserInput();
        // Get InputType from stdin
};

#endif
