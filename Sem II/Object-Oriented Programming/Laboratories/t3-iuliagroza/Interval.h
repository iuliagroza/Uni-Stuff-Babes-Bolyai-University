#ifndef T3_IULIAGROZA_INTERVAL_H
#define T3_IULIAGROZA_INTERVAL_H
#include <string>
#include <vector>
#include <sstream>

class Interval {
private:
    std::string description;
    int start_time;
    int end_time;
    int temp;
    int precipitation;

public:
    Interval()=default;

    Interval(std::string description, int start_time, int end_time, int temp, int precipitation);

    std::string get_description();

    int get_start_time() const;

    int get_end_time() const;

    int get_precipitation() const;

    std::string to_string();

    static std::vector<std::string> tokenize(const std::string& str, char separator);

    friend std::istream &operator>>(std::istream &is, Interval &i);
};


#endif
