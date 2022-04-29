#ifndef A5_6_IULIAGROZA_UI_H
#define A5_6_IULIAGROZA_UI_H

#include "../controller/Controller.h"

class UI {
private:
    Controller controller;
public:
    bool isNumber(const string &str);

    static string login_option();

    static void admin_menu();

    static void user_menu();

    static string admin_input();

    static string user_input();

    void add_admin();

    void remove_admin();

    void update_admin();

    void display_admin();

    string get_genre_input();

    string get_response_input();

    void tinder();

    void remove_user();

    void display_user();

    void start();
};


#endif
