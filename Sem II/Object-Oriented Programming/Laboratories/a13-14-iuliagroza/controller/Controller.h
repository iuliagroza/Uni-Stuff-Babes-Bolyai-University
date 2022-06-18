#ifndef A11_12_IULIAGROZA_CONTROLLER_H
#define A11_12_IULIAGROZA_CONTROLLER_H

#include "../domain/Movie.h"
#include "../repository/AdminRepository.h"
#include "../repository/UserRepository.h"

class Controller {
private:
    AdminRepository admin_repo;
    UserRepository *user_repo;
public:
    /*
     * CONSTRUCTOR
     */
    Controller(const std::string& admin_filename, UserRepository *r);

    /*
     * Getter for the admin_repo filed.
     */
    AdminRepository get_admin_repo();

    /*
     * Getter for the user_repo field.
     */
    UserRepository *get_user_repo();

    /*
     * Function that adds a movie in the database. If the movie already exists in the database,
     * the function will return 0. Otherwise, it will perform the addition using the .add_movie() function
     * from the AdminRepository class and then return 1.
     * :movie: Movie object
     * return: bool
     */
    void add_admin(const Movie &movie);

    /*
     * Function that removes a movie from the database. If the movie does not exist in the database,
     * the function will return 0. Otherwise, it will perform the removal using the .remove_movie() function
     * from the AdminRepository class and then return 1.
     * :movie: Movie object
     * return: bool
     */
    void remove_admin(const Movie& movie);

    /*
     * Function that updates a movie from the database. If the movie does not exist in the database,
     * the function will return 0. Otherwise, it will perform the update_admin using the .update_movie() function
     * from the AdminRepository class and then return 1.
     * :movie: Movie object
     * return: bool
     */
    void update_admin(const Movie& movie, const Movie& new_movie);

    /*
     * Function that adds a movie to the watchlist of the user. No validation is required as the user will be presented
     * only films that are not in the watchlist already.
     * :movie: Movie object
     */
    void add_user(const Movie& movie);

    /*
     * Function that removes a movie from the watchlist. If the movie does not exist in the watchlist,
     * the function will return 0. Otherwise, it will perform the removal using the .remove_movie() function
     * from the UserRepository class and then return 1.
     * :movie: Movie object
     * return: bool
     */
    void remove_user(const Movie& movie);
};


#endif
