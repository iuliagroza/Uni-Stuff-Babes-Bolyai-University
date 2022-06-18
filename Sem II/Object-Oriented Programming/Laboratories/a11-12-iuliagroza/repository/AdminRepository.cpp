#include "AdminRepository.h"
#include "../validators/Exceptions.h"

AdminRepository::AdminRepository(const std::string &filename) {
    this->filename = filename;
    this->movies = read_from_file();
}

std::vector<Movie> AdminRepository::get_movies() {
    return this->movies;
}

int AdminRepository::find(const Movie& movie) {
    for(int i=0; i<this->movies.size(); i++) {
        if(movie == this->movies[i]) {
            return i;
        }
    }

    return -1;
}

void AdminRepository::add_movie(const Movie& movie) {
    this->movies = read_from_file();

    int it = this->find(movie);
    if (it != -1) {
        throw OperationError("The movie you provided already exists in the database.");
    }
    this->movies.push_back(movie);

    write_to_file();
}

void AdminRepository::remove_movie(const Movie& movie) {
    this->movies = read_from_file();

    int it = this->find(movie);
    if (it == -1) {
        throw OperationError("The movie you provided does not exist in the database.");
    }

    this->movies.erase(this->movies.begin() + it);

    write_to_file();
}

void AdminRepository::update_movie(const Movie& movie, const Movie& new_movie) {
    this->movies = read_from_file();

    int it = this->find(movie);
    if (it == -1) {
        throw OperationError("The movie you provided does not exist in the database.");
    }

    this->movies[it] = new_movie;

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
    for (const auto& movie: this->movies) {
        file << movie;
    }
    file.close();
}