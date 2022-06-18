#include "Issue.h"

Issue::Issue()
{
}

std::vector<std::string> Issue::tokenize(const std::string& str, char separator)
{
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string token;
    while (getline(ss, token, separator))
        result.push_back(token);
    return result;
}

std::istream& operator>>(std::istream& is, Issue& i)
{
    if (is.eof())
        is.setstate(std::ios_base::failbit); // operator bool returns true for eof => enforce false to terminate the loop
    else
    {
        std::string line;
        getline(is, line);
        std::vector<std::string> tokens = i.tokenize(line, ',');
        if (tokens.size() != 4)
            return is;
        i.description = tokens[0];
        i.status = tokens[1];
        i.reporter = tokens[2];
        i.solver = tokens[3];
    }
    return is;
}

