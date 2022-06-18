#ifndef A11_12_IULIAGROZA_UI_H
#define A11_12_IULIAGROZA_UI_H

#include "../controller/Controller.h"
#include "../validators/Validators.h"
#include <ctime>

class UI {
private:
    Controller controller;
    Validators validator;

public:
    UI(Controller ctrl);

    std::string login_option();

    std::string menu_input(int number_of_commands);

    int get_year_of_release_input();

    int get_number_of_likes_input();

    void add_admin();

    void remove_admin();

    void update_admin();

    void display_admin();

    std::string get_response_input();

    void tinder();

    void remove_user();

    void display_user();

    void start();
};


#endif
