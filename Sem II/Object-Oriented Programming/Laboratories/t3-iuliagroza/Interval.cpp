#include "Interval.h"

Interval::Interval(std::string description, int start_time, int end_time, int temp, int precipitation) : description(std::move(description)), start_time(start_time),
                                                                  end_time(end_time), temp(temp), precipitation(precipitation) {}

std::string Interval::get_description() {
    return this->description;
}

int Interval::get_start_time() const {
    return this->start_time;
}

int Interval::get_end_time() const {
    return this->end_time;
}

int Interval::get_precipitation() const {
    return this->precipitation;
}


std::string Interval::to_string() {
    std::string str =  "Time interval: " + std::to_string(this->start_time) + "-" + std::to_string(this->end_time) + "; Temperature: " + std::to_string(this->temp) + "; Precipitation probability: " + std::to_string(this->precipitation) + "; Weather:  " + this->description;
    return str;
}

std::vector<std::string> Interval::tokenize(const std::string& str, char separator)
{
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string token;
    while (getline(ss, token, separator))
        result.push_back(token);
    return result;
}
std::istream& operator>>(std::istream& is, Interval& i)
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
        i.start_time = stoi(tokens.at(0));
        i.end_time = stoi(tokens.at(1));
        i.temp = stoi(tokens.at(2));
        i.precipitation = stoi(tokens.at(3));
        i.description = tokens.at(4);
    }
    return is;
}