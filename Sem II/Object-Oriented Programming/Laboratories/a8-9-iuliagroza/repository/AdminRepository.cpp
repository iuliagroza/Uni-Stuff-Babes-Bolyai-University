#include "AdminRepository.h"
#include "../validators/Exceptions.h"

AdminRepository::AdminRepository(const std::string &filename) {
    this->filename = filename;
    this->movies = read_from_file();
}

std::vector<Movie> AdminRepository::get_movies() {
    return this->movies;
}

void AdminRepository::add_movie(Movie movie) {
    this->movies = read_from_file();

    std::vector<Movie>::iterator it = find(this->movies.begin(), this->movies.end(), movie);
    if (it != this->movies.end()) {
        throw OperationError("The movie you provided already exists in the database.");
    }
    this->movies.push_back(movie);

    write_to_file();
}

void AdminRepository::remove_movie(Movie movie) {
    this->movies = read_from_file();

    std::vector<Movie>::iterator it = find(this->movies.begin(), this->movies.end(), movie);
    if (it == this->movies.end()) {
        throw OperationError("The movie you provided does not exist in the database.");
    }

    this->movies.erase(it);

    write_to_file();
}

void AdminRepository::update_movie(Movie movie, Movie new_movie) {
    this->movies = read_from_file();

    std::vector<Movie>::iterator it = find(this->movies.begin(), this->movies.end(), movie);
    if (it == this->movies.end()) {
        throw OperationError("The movie you provided does not exist in the database.");
    }

    *it = new_movie;

    write_to_file();
}

std::vector<Movie> AdminRepository::read_from_file() {
    std::ifstream file(this->filename);

    if (!file.is_open()) {
        throw FileError("The file could not be open.");
    }

    std::vector<Movie> new_movies;
    Movie movie;
    while (file >> movie) {
        new_movies.push_back(movie);
    }

    file.close();
    return new_movies;
}

void AdminRepository::write_to_file() {
    std::ofstream file(this->filename);
    if (!file.is_open())
        throw FileError("The file could not be open.");
    for (auto movie: this->movies) {
        file << movie;
    }
    file.close();
}