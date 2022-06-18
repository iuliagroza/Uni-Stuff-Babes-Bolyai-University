#include "AdminRepository.h"

int AdminRepository::get_size() {
    return this->movies.get_size();
}

DynamicArray<Movie> AdminRepository::get_movies() {
    return this->movies;
}

bool AdminRepository::add_movie(Movie movie) {
    if (find_movie(movie) != -1) {
        return false;
    }
    this->movies.add(movie);
    return true;
}

bool AdminRepository::remove_movie(Movie movie) {
    int position = find_movie(movie);
    if (position == -1) {
        return false;
    }

    this->movies.remove(position);
    return true;
}

bool AdminRepository::update_movie(Movie movie, Movie new_movie) {
    int position = find_movie(movie);
    if (position == -1) {
        return false;
    }

    this->movies.update(position, new_movie);
    return true;
}

int AdminRepository::find_movie(Movie movie) {
    for (int i = 0; i < this->movies.get_size(); i++) {
        if (this->movies.get_element(i) == movie) {
            return i;
        }
    }
    return -1;
}

