// 13519214

#ifndef MESSAGEBOX_HPP
#define MESSAGEBOX_HPP

#include <queue>
#include <string>

class MessageBox {
    // TODO : Add
    private:
        std::queue<std::string> boxQueue;
        const int maxQueue;
    public:
        MessageBox();
        // MessageBox Constructor

        void addMessage(std::string newMsg);
        // Add message, erase older message if full
};

#endif
