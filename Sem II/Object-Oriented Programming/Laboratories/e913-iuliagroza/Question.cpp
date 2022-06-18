#include "Question.h"

Question::Question() {

}

std::vector<std::string> Question::tokenize(const std::string& str, char separator)
{
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string token;
    while (getline(ss, token, separator))
        result.push_back(token);
    return result;
}

std::istream& operator>>(std::istream& is, Question& q)
{
    if (is.eof())
        is.setstate(std::ios_base::failbit);
    else
    {
        std::string line;
        getline(is, line);
        std::vector<std::string> tokens = q.tokenize(line, ',');
        if (tokens.size() != 4)
            return is;
        q.id = stoi(tokens[0]);
        q.text = tokens[1];
        q.answer = tokens[2];
        q.score = stoi(tokens[3]);
    }
    return is;
}


