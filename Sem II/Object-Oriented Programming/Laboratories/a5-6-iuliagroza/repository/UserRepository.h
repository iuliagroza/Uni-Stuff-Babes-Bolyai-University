#ifndef A5_6_IULIAGROZA_USERREPOSITORY_H
#define A5_6_IULIAGROZA_USERREPOSITORY_H

#include "../domain/Movie.h"
#include "../utils/DynamicArray.h"

class UserRepository {
private:
    DynamicArray<Movie> watchlist;

public:
    /*
     * Getter for the size of watchlist (using .get_size() of the DynamicArray class).
     */
    int get_size();

    /*
     * Getter for the watchlist.
     */
    DynamicArray<Movie> get_watchlist();

    /*
     * Function that adds a movie in the watchlist. It performs the addition using the .add_admin() function
     * from the DynamicArray class.
     * :movie: const pointer to a Movie object
     */
    void add_movie(Movie movie);

    /*
     * Function that removes a movie from the watchlist. If the movie does not exist in the watchlist,
     * the function will return 0. Otherwise, it will perform the removal using the .remove_admin() function
     * from the DynamicArray class and then return 1.
     * :movie: const pointer to a Movie object
     * return: bool
     */
    bool remove_movie(Movie movie);

    /*
     * Function that updates a movie from the watchlist after being updated in the database. It performs the update_admin
     * using the .update_admin() function from the DynamicArray class.
     * :movie: const pointer to a Movie object
     */
    void update_movie(Movie movie, Movie new_movie);

    /*
     * Function that finds a movie in the watchlist. If the movie has been found, its position will be returned.
     * Otherwise, the function returns -1.
     * :movie: Movie object
     * return: integer (position or -1)
     */
    int find_movie(Movie movie);
};

#endif
