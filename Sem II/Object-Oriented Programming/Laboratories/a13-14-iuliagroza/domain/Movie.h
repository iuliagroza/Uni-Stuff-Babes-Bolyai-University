#ifndef A11_12_IULIAGROZA_MOVIE_H
#define A11_12_IULIAGROZA_MOVIE_H

#include <string>
#include <sstream>
#include <iostream>
#include <vector>

class Movie {
protected:
    std::string title;
    std::string genre;
    int year_of_release;
    int number_of_likes;
    std::string trailer;

public:
    /*
     * CONSTRUCTORS
     */
    Movie(std::string title, std::string genre, int year_of_release, int number_of_likes, std::string trailer);

    Movie();

    /*
     * GETTERS
     */
    std::string get_title() const;

    std::string get_genre() const;

    int get_year_of_release() const;

    int get_number_of_likes() const;

    std::string get_trailer() const;

    /*
     * Function that returns the string representation of a Movie object.
     */
    std::string to_str();

    /*
     * Custom operator that facilitates the assignment of a Movie object to another Movie object by reference.
     */
    Movie &operator=(const Movie &movie);

    /*
     * Custom operators that override the functionality of the stream operators using <iostream>. Facilitates the
     * read-a-movie and write-a-movie operations.
     */
    friend std::istream &operator>>(std::istream &is, Movie &movie);

    friend std::ostream &operator<<(std::ostream &os, const Movie &movie);
};

/*
 * Inline operator that facilitates the comparison between two Movie objects.
 */
inline bool operator==(const Movie &a, const Movie &b) {
    return a.get_trailer() == b.get_trailer();
}

#endif
