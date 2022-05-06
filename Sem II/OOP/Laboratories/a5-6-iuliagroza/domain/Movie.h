#ifndef A5_6_IULIAGROZA_MOVIE_H
#define A5_6_IULIAGROZA_MOVIE_H

#include <string>

using namespace std;

class Movie {
public:
    Movie(string title, string genre, int year_of_release, int number_of_likes, string trailer);

    Movie();

private:
    string title;
    string genre;
    int year_of_release;
    int number_of_likes;
    string trailer;

public:
    /*
     * GETTERS
     */
    string get_title() const;

    string get_genre() const;

    int get_year_of_release() const;

    int get_number_of_likes() const;

    string get_trailer() const;

    /*
     * Function that returns the string representation of a Movie object.
     */
    string to_str();

    /*
     * Custom operator that facilitates the assignment of a Movie object to another Movie object by reference.
     */
    Movie &operator=(const Movie &movie);
};

/*
 * Inline operator that facilitates the comparison between two Movie objects.
 */
inline bool operator==(const Movie &a, const Movie &b) {
    return a.get_trailer() == b.get_trailer();
}

#endif
