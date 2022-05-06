#ifndef A5_6_IULIAGROZA_USERREPOSITORY_H
#define A5_6_IULIAGROZA_USERREPOSITORY_H

#include "../domain/Movie.h"
#include <algorithm>
#include <fstream>

class UserRepository {
protected:
    std::vector<Movie> watchlist;
    std::string filename;

public:
    /*
     * Constructor
     */
    UserRepository(const std::string &filename);

    /*
     * Destructor
     */
    virtual ~UserRepository() {}

    /*
     * Getter for the watchlist.
     */
    std::vector<Movie> get_watchlist();

    void set_watchlist(std::vector<Movie> new_watchlist);

    /*
     * Function that adds a movie in the watchlist. It performs the addition.
     * :movie: const pointer to a Movie object
     */
    void add_movie(Movie movie);

    /*
     * Function that removes a movie from the watchlist. If the movie does not exist in the watchlist,
     * the function will return 0. Otherwise, it will perform the removal and then return 1.
     * :movie: const pointer to a Movie object
     * return: bool
     */
    void remove_movie(Movie movie);

    /*
     * Function that updates a movie from the watchlist after being updated in the database. It performs the update_admin.
     * :movie: const pointer to a Movie object
     */
    void update_movie(Movie movie, Movie new_movie);

    /*
     * Function that reads the content of the repo from a .txt file. Used before every operation from the repo. It is
     * virtual, so it can be inherited by CSVUserRepository and HTMLUserRepository.
     * return: vector of Movie objects
     */
    virtual std::vector<Movie> read_from_file();

    /*
     * Function that writes the content of the repo in a .txt file. Used after every operation from the repository. It is
     * virtual, so it can be inherited by CSVUserRepository and HTMLUserRepository.
     */
    virtual void write_to_file();

    /*
     * Function that displays in Notepad the contents of the .txt file associated to the repository.
     */
    virtual void display() const = 0;
};

#endif
