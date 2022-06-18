#include "Task.h"

#include <utility>
#include <sstream>
#include <vector>

Task::Task(std::string description, int duration, int priority) : description(std::move(description)), duration(duration),
                                                                         priority(priority) {}

int Task::get_duration() {
    return this->duration;
}

int Task::get_priority() {
    return this->priority;
}

std::string Task::to_string() {
    std::string str = this->description + ", " + std::to_string(this->duration) + ", " + std::to_string(this->priority);
    return str;
}

std::vector<std::string> Task::tokenize(const std::string& str, char separator)
{
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string token;
    while (getline(ss, token, separator))
        result.push_back(token);
    return result;
}
std::istream& operator>>(std::istream& is, Task& t)
{
    if (is.eof())
        is.setstate(std::ios_base::failbit); // operator bool returns true for eof => enforce false to terminate the loop
    else
    {
        std::string line;
        getline(is, line);
        std::vector<std::string> tokens = t.tokenize(line, ',');
        if (tokens.size() != 3)
            return is;
        t.description = tokens.at(0);
        t.duration = stoi(tokens.at(1));
        t.priority = stoi(tokens.at(2));
    }
    return is;
}