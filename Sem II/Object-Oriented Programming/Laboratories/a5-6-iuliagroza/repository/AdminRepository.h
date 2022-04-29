#ifndef A5_6_IULIAGROZA_ADMINREPOSITORY_H
#define A5_6_IULIAGROZA_ADMINREPOSITORY_H

#include "../domain/Movie.h"
#include "../utils/DynamicArray.h"

class AdminRepository {
private:
    DynamicArray<Movie> movies;

public:
    /*
     * Getter for the size of the movies list (using .get_size() of the DynamicArray class).
     */
    int get_size();

    /*
     * Getter for the movies list.
     */
    DynamicArray<Movie> get_movies();

    /*
     * Function that adds a movie in the database. If the movie already exists in the database,
     * the function will return 0. Otherwise, it will perform the addition using the .add_admin() function
     * from the DynamicArray class and then return 1.
     * :movie: const pointer to a Movie object
     * return: bool
     */
    bool add_movie(Movie movie);

    /*
     * Function that removes a movie from the database. If the movie does not exist in the database,
     * the function will return 0. Otherwise, it will perform the removal using the .remove_admin() function
     * from the DynamicArray class and then return 1.
     * :movie: const pointer to a Movie object
     * return: bool
     */
    bool remove_movie(Movie movie);

    /*
     * Function that updates a movie from the database. If the movie does not exist in the database,
     * the function will return 0. Otherwise, it will perform the update_admin using the .update_admin() function
     * from the DynamicArray class and then return 1.
     * :movie: const pointer to a Movie object
     * return: bool
     */
    bool update_movie(Movie movie, Movie new_movie);

    /*
     * Function that finds a movie in the database. If the movie has been found, its position will be returned.
     * Otherwise, the function returns -1.
     * :movie: Movie object
     * return: integer (position or -1)
     */
    int find_movie(Movie movie);
};

#endif
