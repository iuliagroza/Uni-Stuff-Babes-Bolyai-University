#ifndef A11_12_IULIAGROZA_ADMINREPOSITORY_H
#define A11_12_IULIAGROZA_ADMINREPOSITORY_H

#include "../domain/Movie.h"
#include <algorithm>
#include <fstream>

class AdminRepository {
private:
    std::vector<Movie> movies;
    std::string filename;

public:
    /*
     * Constructor
     */
    explicit AdminRepository(const std::string &filename);

    /*
     * Getter for the movies list.
     */
    std::vector<Movie> get_movies();

    /*
     * Function that returns the position of the element from the movie list that equals movie. If movie is not found,
     * -1 is returned.
     * :movie: Movie object
     * return: integer (the position of movie in this->movie or -1)
     */
    int find(const Movie& movie);

    /*
     * Function that adds a movie in the database. If the movie already exists in the database,
     * the function will return 0. Otherwise, it will perform the addition and then return 1.
     * :movie: Movie object
     * return: bool
     */
    void add_movie(const Movie& movie);

    /*
     * Function that removes a movie from the database. If the movie does not exist in the database,
     * the function will return 0. Otherwise, it will perform the removal and then return 1.
     * :movie: Movie object
     * return: bool
     */
    void remove_movie(const Movie& movie);

    /*
     * Function that updates a movie from the database. If the movie does not exist in the database,
     * the function will return 0. Otherwise, it will perform the update_admin and then return 1.
     * :movie: Movie object
     * :new_movie: Movie object
     * return: bool
     */
    void update_movie(const Movie& movie, const Movie& new_movie);

private:
    /*
     * Function that reads the content of the repo from a .txt file. Used before every operation from the repository.
     * return: vector of Movie objects
     */
    std::vector<Movie> read_from_file();

    /*
     * Function that writes the content of the repo in a .txt file. Used after every operation from the repository.
     */
    void write_to_file();
};

#endif
