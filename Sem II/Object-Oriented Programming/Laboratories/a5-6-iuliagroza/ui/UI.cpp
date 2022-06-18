#include "UI.h"

#include <iostream>
#include <cstring>
#include <ctime>

using namespace std;

bool UI::isNumber(const string &str) {
    for (char const &c: str) {
        if (std::isdigit(c) == 0) {
            return false;
        }
    }
    return true;
}

string UI::login_option() {
    string login_ipt;

    while (login_ipt != "admin" && login_ipt != "user" && login_ipt != "exit") {
        cout << "Welcome to \"Local Movie Database\"! Please choose your user type: (admin\\user\\exit)\n";
        cout << ">>> ";
        getline(cin, login_ipt);

        if (login_ipt != "admin" && login_ipt != "user" && login_ipt != "exit") {
            cout << "Invalid input.\n";
        }
    }

    return login_ipt;
}

void UI::admin_menu() {
    cout << "Choose a command by typing its corresponding number:\n"
            "1. Add a movie into the database.\n"
            "2. Remove a movie from the database.\n"
            "3. Update a movie from the database.\n"
            "4. Display all the movies.\n"
            "5. Exit\n";
}

void UI::user_menu() {
    cout << "Choose a command by typing its corresponding number:\n"
            "1. See the movie database.\n"
            "2. Remove a movie from the database.\n"
            "3. See the watchlist.\n"
            "4. Exit\n";
}

string UI::admin_input() {
    string ipt;

    while (ipt != "1" && ipt != "2" && ipt != "3" && ipt != "4" && ipt != "5") {
        cout << ">>> ";
        getline(cin, ipt);

        if (ipt != "1" && ipt != "2" && ipt != "3" && ipt != "4" && ipt != "5") {
            cout << "Invalid input.\n";
        }
    }

    return ipt;
}

string UI::user_input() {
    string ipt;

    while (ipt != "1" && ipt != "2" && ipt != "3" && ipt != "4") {
        cout << ">>> ";
        getline(cin, ipt);

        if (ipt != "1" && ipt != "2" && ipt != "3" && ipt != "4") {
            cout << "Invalid input.\n";
        }
    }

    return ipt;
}

void UI::add_admin() {
    string title;
    cout << "Please type the title of the movie: ";
    getline(cin, title);

    string genre;
    cout << "Please type the genre of the movie: ";
    getline(cin, genre);

    string year;
    int year_of_release;
    while (true) {
        cout << "Please type the year the movie has been released: ";
        getline(cin, year);

        if (!isNumber(year)) {
            cout << "Invalid input.\n";
        } else {
            year_of_release = stoi(year);
            time_t t = time(nullptr);
            tm *timePtr = localtime(&t);

            if (year_of_release < 1850 || year_of_release > 1900 + timePtr->tm_year) {
                cout << "Invalid year.\n";
            } else {
                break;
            }
        }
    }

    string likes;
    int number_of_likes;
    while (true) {
        cout << "Please type the number of likes the movie has received: ";
        getline(cin, likes);

        if (!isNumber(likes)) {
            cout << "Invalid input.\n";
        } else {
            number_of_likes = stoi(likes);
            if (number_of_likes < 0) {
                cout << "Invalid number.\n";
            } else {
                break;
            }
        }
    }

    string trailer;
    cout << "Please type the link of the trailer of the movie: ";
    getline(cin, trailer);

    bool result = this->controller.add_admin(Movie(title, genre, year_of_release, number_of_likes, trailer));

    if (result) {
        cout << "Movie added successfully.\n";
    } else {
        cout << "The movie already exists in the database.\n";
    }
}

void UI::remove_admin() {
    string trailer;
    cout << "Please type the link of the trailer of the movie: ";
    getline(cin, trailer);

    bool result = this->controller.remove_admin(Movie("a", "a", 0, 0, trailer));

    if (result) {
        cout << "Movie deleted successfully.\n";
    } else {
        cout << "The movie trailer you provided does not exist in the database.\n";
    }
}

void UI::update_admin() {
    string trailer;
    cout << "Please type the link of the trailer of the movie: ";
    getline(cin, trailer);

    string title;
    cout << "Please type the updated title of the movie: ";
    getline(cin, title);

    string genre;
    cout << "Please type the updated genre of the movie: ";
    getline(cin, genre);

    int year_of_release;
    while (true) {
        cout << "Please type the updated year the movie has been released: ";
        cin >> year_of_release;
        cin.get();

        time_t t = time(nullptr);
        tm *timePtr = localtime(&t);

        if (year_of_release < 1850 || year_of_release > 1900 + timePtr->tm_year) {
            cout << "Invalid year.\n";
        } else {
            break;
        }
    }

    int number_of_likes;
    while (true) {
        cout << "Please type the new number of likes the movie has received: ";
        cin >> number_of_likes;
        cin.get();

        if (number_of_likes < 0) {
            cout << "Invalid number.\n";
        } else {
            break;
        }
    }

    bool result = this->controller.update_admin(Movie("a", "a", 0, 0, trailer),
                                                Movie(title, genre, year_of_release, number_of_likes, trailer));

    if (result) {
        cout << "Movie updated successfully.\n";
    } else {
        cout << "The movie trailer you provided does not exist in the database.\n";
    }
}

void UI::display_admin() {
    for (int i = 0; i < this->controller.get_admin_repo().get_size(); i++) {
        cout << i + 1 << ". " << this->controller.get_admin_repo().get_movies().get_element(i).to_str();
    }
}

string UI::get_genre_input() {
    string genre;
    cout << "Please type your preferred genre: ";
    getline(cin, genre);

    return genre;
}

string UI::get_response_input() {
    string response;
    while (true) {
        cout << ">>> ";
        getline(cin, response);

        if (response != "yes" && response != "no") {
            cout << "Invalid input.\n";
        } else {
            break;
        }
    }

    return response;
}

void UI::tinder() {
    string genre = get_genre_input();

    int index = 0, seen = 0;
    while (index < this->controller.get_admin_repo().get_size()) {
        if (this->controller.get_user_repo().find_movie(this->controller.get_admin_repo().get_movies().get_element(
                index)) == -1 &&
            (this->controller.get_admin_repo().get_movies().get_element(index).get_genre() == genre || genre == "")) {
            seen++;
            cout << this->controller.get_admin_repo().get_movies().get_element(index).to_str();
            string start_str =
                    "start " + this->controller.get_admin_repo().get_movies().get_element(index).get_trailer();
            const char *start = start_str.c_str();
            system(start);
            cout << "Are you enjoying the trailer? (yes\\no)\n";
            string response = get_response_input();
            if (response == "yes") {
                this->controller.add_user(
                        this->controller.get_admin_repo().get_movies().get_element(index));
            }
            cout << "Do you want to continue? (yes\\no)\n";
            string sec_response = get_response_input();
            if (sec_response == "no") {
                break;
            }
        }
        index++;
        if (index == this->controller.get_admin_repo().get_size()) {
            index = 0;
            if (seen == 0) {
                cout << "There are no movies that match the provided genre.\n";
                break;
            }
            seen = 0;
        }
    }
}

void UI::remove_user() {
    string trailer;
    cout << "Please type the link of the trailer of the movie: ";
    getline(cin, trailer);

    bool result = this->controller.remove_user(Movie("a", "a", 0, 0, trailer));

    if (result) {
        cout << "Movie deleted successfully. Did you like the movie? (yes\\no)\n";
        string response = get_response_input();
        if (response == "yes") {
            int pos = this->controller.get_admin_repo().find_movie(Movie("a", "a", 0, 0, trailer));
            int number_of_likes =
                    this->controller.get_admin_repo().get_movies().get_element(pos).get_number_of_likes() + 1;
            string title = this->controller.get_admin_repo().get_movies().get_element(pos).get_title();
            string genre = this->controller.get_admin_repo().get_movies().get_element(pos).get_genre();
            int year_of_release = this->controller.get_admin_repo().get_movies().get_element(pos).get_year_of_release();
            this->controller.update_admin(Movie("a", "a", 0, 0, trailer),
                                          Movie(title, genre, year_of_release, number_of_likes, trailer));
        }
    } else {
        cout << "The movie trailer you provided does not exist in your watchlist.\n";
    }
}

void UI::display_user() {
    if (this->controller.get_user_repo().get_size() == 0) {
        cout << "There are no movies in your watchlist.\n";
    }

    for (int i = 0; i < this->controller.get_user_repo().get_size(); i++) {
        cout << i + 1 << ". " << this->controller.get_user_repo().get_watchlist().get_element(i).to_str();
    }
}

void UI::start() {
    this->controller.generate();
    while (true) {
        string option = login_option();

        if (option == "admin") {
            while (true) {
                admin_menu();

                string ipt = admin_input();

                if (ipt == "1") {
                    add_admin();
                } else if (ipt == "2") {
                    remove_admin();
                } else if (ipt == "3") {
                    update_admin();
                } else if (ipt == "4") {
                    display_admin();
                } else {
                    break;
                }
            }
        } else if (option == "user") {
            while (true) {
                user_menu();

                string ipt = user_input();

                if (ipt == "1") {
                    tinder();
                } else if (ipt == "2") {
                    remove_user();
                } else if (ipt == "3") {
                    display_user();
                } else {
                    break;
                }
            }
        } else {
            break;
        }
    }
}
