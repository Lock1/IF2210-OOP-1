// 13519214
#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <queue>
#include <string>

class Message {
    private:
        std::queue<std::string> messageQueue; // TODO : Extra, scrollable
        const unsigned int maxQueue;
        const unsigned int maxStringLength;

    public:
        Message(unsigned int maxBuf, unsigned int maxLength);
        // Message Constructor

        void addMessage(std::string newMsg);
        // Add message, erase older message if full

        std::queue<std::string> showMessage();
        // Return copy queue of messages

        void clearMessage();
        // Pop all queue

        void fillEmptyBuffer();
        // Fill queue with empty string

        int getMaxMessage();
        // Get max message contained

        int getMaxStringLength();
        // Get max string length in one entry
};

#endif
