#include "Participant.h"

Participant::Participant() {
    this->score = 0;
}

std::vector<std::string> Participant::tokenize(const std::string& str, char separator)
{
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string token;
    while (getline(ss, token, separator))
        result.push_back(token);
    return result;
}

std::istream& operator>>(std::istream& is, Participant& p)
{
    if (is.eof())
        is.setstate(std::ios_base::failbit);
    else
    {
        std::string line;
        getline(is, line);
        std::vector<std::string> tokens = p.tokenize(line, ',');
        if (tokens.size() != 2)
            return is;
        p.name = tokens[0];
        p.score = stoi(tokens[1]);
    }
    return is;
}
