#ifndef E913_IULIAGROZA_SERVICE_H
#define E913_IULIAGROZA_SERVICE_H


#include "Observer.h"
#include "Question.h"
#include "Participant.h"
#include <fstream>

class Service : public Subject{
private:
    std::vector<Question> questions;
    std::vector<Participant> participants;

public:
    Service() { this->readFromFile(); };

    std::vector<Question>& getQuestions() { return this->questions; }
    std::vector<Participant>& getParticipants() { return this->participants; }

    void readFromFile();
    static bool cmp(Question &q1, Question &q2);
    void sort();
    void addQuestion(Question& q);
    void writeToFile();
};


#endif
