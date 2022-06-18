#ifndef P1_TASK_H
#define P1_TASK_H
#include <string>
#include <vector>

class Task {
private:
    std::string description;
    int duration;
    int priority;

public:
    Task()=default;

    Task(std::string description, int duration, int priority);

    int get_duration();

    int get_priority();

    std::string to_string();

    std::vector<std::string> tokenize(const std::string& str, char separator);

    friend std::istream &operator>>(std::istream &is, Task &t);
};


#endif
