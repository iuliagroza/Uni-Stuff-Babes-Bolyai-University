#ifndef E913_IULIAGROZA_REPOSITORY_H
#define E913_IULIAGROZA_REPOSITORY_H


#include "Question.h"
#include "Participant.h"
#include <fstream>

class Repository {
private:
    std::vector<Question> questions;
    std::vector<Participant> participants;

public:
    Repository() { this->readFromFile(); };

    std::vector<Question>& getQuestions() { return this->questions; }
    std::vector<Participant>& getParticipants() { return this->participants; }

    void readFromFile();
    void addQuestion(Question& q);
};


#endif
