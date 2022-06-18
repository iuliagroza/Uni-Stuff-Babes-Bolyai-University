#ifndef E913_IULIAGROZA_QUESTION_H
#define E913_IULIAGROZA_QUESTION_H
#include <string>
#include <vector>
#include <sstream>

class Question {
private:
    int id;
    std::string text;
    std::string answer;
    int score;

public:
    Question();
    Question(int id, const std::string &text, const std::string &answer, int score) : id{id}, text{text}, answer{answer}, score{score} {}

    int getId() { return this->id; }
    std::string getText() { return this->text; }
    std::string getAnswer() { return this->answer; }
    int getScore() { return this->score; }

    std::vector<std::string> tokenize(const std::string& str, char separator);
    friend std::istream& operator>>(std::istream& is, Question& q);
};


#endif
