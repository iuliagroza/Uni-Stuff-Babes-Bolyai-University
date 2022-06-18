#include "ChatSession.h"

void ChatSession::addMessage(std::string &user, std::string &message) {
    std::pair<std::string, std::string> mes;
    mes.first = user;
    mes.second = message;
    this->messages.push_back(&mes);
}

std::vector<std::pair<std::string, std::string>*> ChatSession::getMessages() {
    return this->messages;
}
