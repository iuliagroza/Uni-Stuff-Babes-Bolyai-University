#include "UserRepository.h"

int UserRepository::get_size() {
    return this->watchlist.get_size();
}

DynamicArray<Movie> UserRepository::get_watchlist() {
    return this->watchlist;
}

void UserRepository::add_movie(Movie movie) {
    this->watchlist.add(movie);
}

bool UserRepository::remove_movie(Movie movie) {
    int position = find_movie(movie);
    if (position == -1) {
        return false;
    }

    this->watchlist.remove(position);
    return true;
}

void UserRepository::update_movie(Movie movie, Movie new_movie) {
    int position = find_movie(movie);
    if (position != -1) {
        this->watchlist.update(position, new_movie);
    }
}

int UserRepository::find_movie(Movie movie) {
    for (int i = 0; i < this->watchlist.get_size(); i++) {
        if (this->watchlist.get_element(i) == movie) {
            return i;
        }
    }
    return -1;
}
