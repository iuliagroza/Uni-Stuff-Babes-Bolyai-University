#include "UserRepository.h"
#include "../validators/Exceptions.h"

UserRepository::UserRepository(const std::string &filename)  {
    this->filename = filename;
}

std::vector<Movie> UserRepository::get_watchlist() {
    return this->watchlist;
}

void UserRepository::set_watchlist(std::vector<Movie> new_watchlist) {
    this->watchlist = new_watchlist;
}

void UserRepository::add_movie(Movie movie) {
    this->watchlist = read_from_file();

    this->watchlist.push_back(movie);

    write_to_file();
}

void UserRepository::remove_movie(Movie movie) {
    this->watchlist = read_from_file();

    std::vector<Movie>::iterator it = find(this->watchlist.begin(), this->watchlist.end(), movie);
    if (it == this->watchlist.end()) {
        throw OperationError("The movie you provided is not in your watchlist.");
    }

    this->watchlist.erase(it);

    write_to_file();
}

void UserRepository::update_movie(Movie movie, Movie new_movie) {
    this->watchlist = read_from_file();

    std::vector<Movie>::iterator it = find(this->watchlist.begin(), this->watchlist.end(), movie);
    if (it != this->watchlist.end()) {
        *it = new_movie;
    }

    write_to_file();
}

std::vector<Movie> UserRepository::read_from_file() {
    std::ifstream file(this->filename);
    if (!file.is_open()) {
        throw FileError("The file could not be open.");
    }
    std::vector<Movie> new_watchlist;

    Movie movie;
    while (file >> movie) {
        new_watchlist.push_back(movie);
    }

    file.close();
    return new_watchlist;
}

void UserRepository::write_to_file() {
    std::ofstream file(this->filename);
    if (!file.is_open())
        throw FileError("The file could not be open.");
    for (auto movie : this->watchlist)
    {
        file << movie;
    }
    file.close();
}
