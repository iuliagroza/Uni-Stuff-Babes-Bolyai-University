#include "HTMLUserRepository.h"
#include "../validators/Exceptions.h"

HTMLUserRepository::HTMLUserRepository(const std::string &filename) : UserRepository(filename) {
    this->filename = filename;
}

void strip(std::string &string) {
    while (!string.empty() && (string.back() == ' ' || string.back() == '\t' || string.back() == '\n'))
        string.pop_back();
    reverse(string.begin(), string.end());
    while (!string.empty() && (string.back() == ' ' || string.back() == '\t' || string.back() == '\n'))
        string.pop_back();
    reverse(string.begin(), string.end());
}

void html_strip(std::string &string) {
    strip(string);
    string = string.substr(0, string.size() - 5);
    reverse(string.begin(), string.end());
    string = string.substr(0, string.size() - 4);
    reverse(string.begin(), string.end());
    strip(string);
}

void link_strip(std::string &string) {
    string = string.substr(0, string.size() - 4);
    reverse(string.begin(), string.end());
    string = string.substr(0, string.size() - 9);
    reverse(string.begin(), string.end());
    int length = (string.size() - 2) / 2;
    string = string.substr(0, string.size() - length - 2);
}

std::vector<Movie> HTMLUserRepository::read_from_file() {
    std::ifstream file(this->filename);

    if (!file.is_open()) {
        throw FileError("The file could not be opened!");
    }

    std::vector<Movie> new_watchlist;
    std::string line;
    for (int i = 1; i <= 7; i++) {
        std::getline(file, line);
    }

    do {
        std::getline(file, line);
        strip(line);
        if (line != "<tr>")
            break;

        std::string title, genre, year_of_release, number_of_likes, trailer;

        std::getline(file, title);
        html_strip(title);

        std::getline(file, genre);
        html_strip(genre);

        std::getline(file, year_of_release);
        html_strip(year_of_release);

        std::getline(file, number_of_likes);
        html_strip(number_of_likes);

        std::getline(file, trailer);
        html_strip(trailer);
        link_strip(trailer);

        std::getline(file, line);
        new_watchlist.push_back(Movie(title, genre, stoi(year_of_release), stoi(number_of_likes), trailer));
    } while (true);

    file.close();
    return new_watchlist;
}

void HTMLUserRepository::write_to_file() {
    std::ofstream file(this->filename);

    if (!file.is_open()) {
        throw FileError("The file could not be opened!");
    }

    file << "<!DOCTYPE html>\n<html>\n<head>\n<title>Watchlist</title>\n</head>\n<body>\n<table border=1>\n";
    for (auto movie: this->watchlist) {
        file << "<tr>\n" << "<td>" << movie.get_title() << "</td>\n" << "<td>" << movie.get_genre() << "</td>\n"
             << "<td>" << movie.get_year_of_release() << "</td>\n" << "<td>" << movie.get_number_of_likes() << "</td>\n"
             << "<td><a href=\"" << movie.get_trailer() << "\">" << movie.get_trailer() << "</a></td>\n" << "</tr>\n";
    }
    file << "</table>\n</body>\n</html>";
    file.close();
}

void HTMLUserRepository::display() const {
    std::string aux = "start \"\" \"" + this->filename + "\"";
    system(aux.c_str());
}
