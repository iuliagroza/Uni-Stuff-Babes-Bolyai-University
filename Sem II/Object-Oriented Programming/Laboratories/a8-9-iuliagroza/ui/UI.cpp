#include "UI.h"

UI::UI(Controller controller) : controller { controller }{}

std::string UI::login_option() {
    std::string login_ipt;
    std::vector<std::string> options = {"admin", "user", "exit"};

    while (find(options.begin(), options.end(), login_ipt) == options.end()) {
        std::cout << "Welcome to \"Local Movie Database\"! Please choose your user type: (admin\\user\\exit)\n";
        std::cout << ">>> ";
        getline(std::cin, login_ipt);

        try {
            this->validator.validate_option(login_ipt, options);
        } catch (InputError &iie) {
            std::cout << iie.what() << "\n";
        }
    }

    return login_ipt;
}

void admin_menu() {
    std::cout << "Choose a command by typing its corresponding number:\n"
                 "1. Add a movie into the database.\n"
                 "2. Remove a movie from the database.\n"
                 "3. Update a movie from the database.\n"
                 "4. Display all the movies.\n"
                 "5. Exit\n";
}

void user_menu() {
    std::cout << "Choose a command by typing its corresponding number:\n"
                 "1. See the movie database.\n"
                 "2. Remove a movie from the database.\n"
                 "3. See the watchlist.\n"
                 "4. Exit\n";
}

std::string UI::menu_input(int number_of_commands) {
    std::string ipt;
    std::vector<std::string> options;

    for (int i = 1; i <= number_of_commands; i++) {
        options.push_back(std::to_string(i));
    }

    while (find(options.begin(), options.end(), ipt) == options.end()) {
        std::cout << ">>> ";
        getline(std::cin, ipt);

        try {
            this->validator.validate_option(ipt, options);
        } catch (InputError &iie) {
            std::cout << iie.what() << "\n";
        }
    }

    return ipt;
}

std::string get_title_input() {
    std::string title;
    std::cout << "Please type the title of the movie: ";
    getline(std::cin, title);

    return title;
}

std::string get_genre_input() {
    std::string genre;
    std::cout << "Please type the genre of the movie: ";
    getline(std::cin, genre);

    return genre;
}

std::string get_trailer_input() {
    std::string trailer;
    std::cout << "Please type the link of the trailer of the movie: ";
    getline(std::cin, trailer);

    return trailer;
}

int UI::get_year_of_release_input() {
    std::string year;
    int year_of_release;
    while (true) {
        std::cout << "Please type the year the movie has been released: ";
        getline(std::cin, year);

        try {
            if (!this->validator.is_number(year)) {
                throw InputError("Invalid input.");
            } else {
                year_of_release = stoi(year);
                time_t t = time(nullptr);
                tm *timePtr = localtime(&t);

                if (year_of_release < 1850 || year_of_release > 1900 + timePtr->tm_year) {
                    throw InputError("Invalid year.");
                } else {
                    break;
                }
            }
        } catch (InputError &iie) {
            std::cout << iie.what() << "\n";
        }
    }

    return year_of_release;
}

int UI::get_number_of_likes_input() {
    std::string likes;
    int number_of_likes;
    while (true) {
        std::cout << "Please type the number of likes the movie has received: ";
        getline(std::cin, likes);

        try {
            if (!this->validator.is_number(likes)) {
                throw InputError("Invalid input.");
            } else {
                number_of_likes = stoi(likes);
                if (number_of_likes < 0) {
                    throw InputError("Invalid number.\n");
                } else {
                    break;
                }
            }
        } catch (InputError &iie) {
            std::cout << iie.what() << "\n";
        }
    }

    return number_of_likes;
}

void UI::add_admin() {
    std::string title = get_title_input();
    std::string genre = get_genre_input();
    int year_of_release = get_year_of_release_input();
    int number_of_likes = get_number_of_likes_input();
    std::string trailer = get_trailer_input();

    try {
        this->controller.add_admin(Movie(title, genre, year_of_release, number_of_likes, trailer));
        std::cout << "Movie added successfully.\n";
    } catch (OperationError &ioe) {
        std::cout << ioe.what() << "\n";
    }
}

void UI::remove_admin() {
    std::string trailer = get_trailer_input();

    try {
        this->controller.remove_admin(Movie("a", "a", 0, 0, trailer));
        std::cout << "Movie removed successfully.\n";
    } catch (OperationError &ioe) {
        std::cout << ioe.what() << "\n";
    }
}

void UI::update_admin() {
    std::string trailer = get_trailer_input();
    std::string title = get_title_input();
    std::string genre = get_genre_input();
    int year_of_release;
    int number_of_likes;
    try {
        year_of_release = get_year_of_release_input();
        number_of_likes = get_number_of_likes_input();
    } catch (InputError &iie) {
        std::cout << iie.what() << "\n";
    }

    try {
        this->controller.update_admin(Movie("a", "a", 0, 0, trailer),
                                      Movie(title, genre, year_of_release, number_of_likes, trailer));
        std::cout << "Movie updated successfully.\n";
    } catch (OperationError &ioe) {
        std::cout << ioe.what() << "\n";
    }
}

void UI::display_admin() {
    for (int i = 0; i < this->controller.get_admin_repo().get_movies().size(); i++) {
        std::cout << i + 1 << ". " << this->controller.get_admin_repo().get_movies()[i].to_str();
    }
}

std::string UI::get_response_input() {
    std::string response;
    std::vector<std::string> options = {"yes", "no"};

    while (find(options.begin(), options.end(), response) == options.end()) {
        std::cout << ">>> ";
        getline(std::cin, response);

        try {
            this->validator.validate_option(response, options);
        } catch (InputError &iie) {
            std::cout << iie.what() << "\n";
        }
    }

    return response;
}

int find(std::vector<Movie> m, Movie obj) {
    for(int i=0; i<m.size(); i++) {
        if(obj == m[i]) {
            return i;
        }
    }

    return -1;
}

void UI::tinder() {
    std::string genre = get_genre_input();

    int index = 0, seen = 0;
    while (index < this->controller.get_admin_repo().get_movies().size()) {
        int pos = find(this->controller.get_user_repo()->get_watchlist(), this->controller.get_admin_repo().get_movies()[index]);
        /*std::vector<Movie>::iterator it = find(this->controller.get_user_repo().get_watchlist().begin(),
                                               this->controller.get_user_repo().get_watchlist().end(),
                                               this->controller.get_admin_repo().get_movies()[index]);*/
        if (pos == -1 &&
            (this->controller.get_admin_repo().get_movies()[index].get_genre() == genre || genre == "")) {
            seen++;

            std::cout << this->controller.get_admin_repo().get_movies()[index].to_str();

            std::string start_str =
                    "start " + this->controller.get_admin_repo().get_movies()[index].get_trailer();
            const char *start = start_str.c_str();
            system(start);

            std::cout << "Are you enjoying the trailer? (yes\\no)\n";
            std::string response = get_response_input();
            if (response == "yes") {
                this->controller.add_user(
                        this->controller.get_admin_repo().get_movies()[index]);
            }

            std::cout << "Do you want to continue? (yes\\no)\n";
            std::string sec_response = get_response_input();
            if (sec_response == "no") {
                break;
            }
        }

        index++;
        if (index == this->controller.get_admin_repo().get_movies().size()) {
            index = 0;
            if (seen == 0) {
                std::cout << "There are no movies that match the provided genre.\n";
                break;
            }
            seen = 0;
        }
    }
}

void UI::remove_user() {
    std::string trailer = get_trailer_input();

    try {
        this->controller.remove_user(Movie("a", "a", 0, 0, trailer));
        std::cout << "Movie deleted successfully. Did you like the movie? (yes\\no)\n";
        std::string response = get_response_input();
        if (response == "yes") {
            int pos = find(this->controller.get_admin_repo().get_movies(), Movie("a", "a", 0, 0, trailer));
            /*std::vector<Movie>::iterator it = find(this->controller.get_admin_repo().get_movies().begin(),
                                                   this->controller.get_admin_repo().get_movies().end(),
                                                   Movie("a", "a", 0, 0, trailer));*/

            int number_of_likes = this->controller.get_admin_repo().get_movies()[pos].get_number_of_likes() + 1;
            std::string title = this->controller.get_admin_repo().get_movies()[pos].get_title();
            std::string genre = this->controller.get_admin_repo().get_movies()[pos].get_genre();
            int year_of_release = this->controller.get_admin_repo().get_movies()[pos].get_year_of_release();
            this->controller.update_admin(Movie("a", "a", 0, 0, trailer),
                                          Movie(title, genre, year_of_release, number_of_likes, trailer));
        }
    } catch (OperationError &ioe) {
        std::cout << ioe.what() << "\n";
    }
}

void UI::display_user() {
    if (this->controller.get_user_repo()->get_watchlist().size() == 0) {
        std::cout << "There are no movies in your watchlist.\n";
    }

    for (int i = 0; i < this->controller.get_user_repo()->get_watchlist().size(); i++) {
        std::cout << i + 1 << ". " << this->controller.get_user_repo()->get_watchlist()[i].to_str();
    }

    this->controller.get_user_repo()->display();
}

void UI::start() {
    this->controller.get_user_repo()->set_watchlist(this->controller.get_user_repo()->read_from_file());
    while (true) {
        std::string option = login_option();

        if (option == "admin") {
            while (true) {
                admin_menu();

                std::string ipt = menu_input(5);

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

                std::string ipt = menu_input(4);

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
