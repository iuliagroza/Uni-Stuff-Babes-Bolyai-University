#include "Issue.h"

Issue::Issue(const std::string &description,const std::string &status,const std::string &reporter,const std::string &solver) {
    this->description = description;
    this->status = status;
    this->reporter = reporter;
    this->solver = solver;
}

std::string Issue::get_description() {
    return this->description;
}

std::string Issue::get_status() {
    return this->status;
}

std::string Issue::get_reporter() {
    return this->reporter;
}

std::string Issue::get_solver() {
    return this->solver;
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
        is.setstate(std::ios_base::failbit);
    else
    {
        std::string line;
        getline(is, line);
        std::vector<std::string> tokens = i.tokenize(line, ',');
        if (tokens.size() != 5)
            return is;
        i.description = tokens.at(0);
        i.status = tokens.at(1);
        i.reporter = tokens.at(2);
        i.solver = tokens.at(3);
    }
    return is;
}
