// 13519214
#include "header/message.hpp"
#include <string>
#include <queue>

Message::Message(unsigned int maxBuf, unsigned int maxLength) : maxQueue(maxBuf), maxStringLength(maxLength) {

}

void Message::addMessage(std::string newMsg) {
    // Resize long string
    if (newMsg.length() > maxStringLength)
        newMsg.resize(maxStringLength);

    if (messageQueue.size() >= maxQueue)
        messageQueue.pop();

    messageQueue.push(newMsg);
}

std::queue<std::string> Message::showMessage() {
    return messageQueue;
}

int Message::getMaxMessage() {
    return (int) maxQueue;
}

int Message::getMaxStringLength() {
    return (int) maxStringLength;
}
