#ifndef E913_IULIAGROZA_PARTICIPANT_H
#define E913_IULIAGROZA_PARTICIPANT_H
#include <string>
#include <vector>
#include <sstream>

class Participant {
private:
    std::string name;
    int score;
    std::vector<int> answered;

public:
    Participant();
    Participant(const std::string &name) : name{name} {
        this->score = 0;
    }

    std::string getName() { return this->name; }
    int getScore() { return this->score; }
    void setScore(int newScore) { this->score = newScore; }

    std::vector<int>& getAnswered() { return this->answered; }

    std::vector<std::string> tokenize(const std::string& str, char separator);
    friend std::istream& operator>>(std::istream& is, Participant& p);
};


#endif
