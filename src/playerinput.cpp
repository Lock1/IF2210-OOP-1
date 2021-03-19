// PlayerInput class
#include "header/playerinput.hpp"
#include <Windows.h>
#include <iostream>
#include <thread>

PlayerInput::PlayerInput(unsigned int maxBuf) : maxInputBuffer(maxBuf) {

}

InputType PlayerInput::getUserInput() {
    if (inputBuffer.size() < maxInputBuffer) {
        if ((GetKeyState(VK_UP) & 0x8000) || (GetKeyState('W') & 0x8000))
            inputBuffer.push(Up);
        if ((GetKeyState(VK_DOWN) & 0x8000) || (GetKeyState('S') & 0x8000))
            inputBuffer.push(Down);
        if ((GetKeyState(VK_LEFT) & 0x8000) || (GetKeyState('A') & 0x8000))
            inputBuffer.push(Left);
        if ((GetKeyState(VK_RIGHT) & 0x8000) || (GetKeyState('D') & 0x8000))
            inputBuffer.push(Right);
        if ((GetKeyState('1') & 0x8000))
            inputBuffer.push(Number1);
        if ((GetKeyState('2') & 0x8000))
            inputBuffer.push(Number2);
        if ((GetKeyState('3') & 0x8000))
            inputBuffer.push(Number3);
        if ((GetKeyState('4') & 0x8000))
            inputBuffer.push(Number4);
        if ((GetKeyState(VK_ESCAPE) & 0x8000))
            inputBuffer.push(EscKey);
    }

    if (!inputBuffer.empty()) {
        InputType frontQueueInput = inputBuffer.front();
        inputBuffer.pop();
        return frontQueueInput;
    }
    else
        return EmptyInput;
}
