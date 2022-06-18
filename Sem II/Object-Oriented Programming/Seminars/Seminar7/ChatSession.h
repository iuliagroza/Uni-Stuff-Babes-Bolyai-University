#ifndef SEMINAR7_CHATSESSION_H
#define SEMINAR7_CHATSESSION_H


#include <vector>
#include <string>

class ChatSession {
public:
    std::vector<std::pair<std::string, std::string>*> messages;
private:
    void addMessage(std::string &user, std::string &message);
    std::vector<std::pair<std::string, std::string>*> getMessages();
};


#endif
