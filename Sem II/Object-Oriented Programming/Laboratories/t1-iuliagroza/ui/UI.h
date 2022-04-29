#ifndef T1_IULIAGROZA_UI_H
#define T1_IULIAGROZA_UI_H
#include <string>
#include "../controller/Controller.h"

using namespace std;

class UI {
private:
    Controller ctrl;
public:
    void start_menu();
    void start();
    string input();
    void remove_UI();
    void display_bills();
    void display_sum_unpaid();
    void display_sort();
};


#endif