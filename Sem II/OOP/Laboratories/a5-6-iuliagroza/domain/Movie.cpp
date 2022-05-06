#include "Movie.h"

#include <string>
#include <sstream>

Movie::Movie(string title, string genre, int year_of_release, int number_of_likes, string trailer) {
    this->title = title;
    this->genre = genre;
    this->year_of_release = year_of_release;
    this->number_of_likes = number_of_likes;
    this->trailer = trailer;


}

Movie::Movie() {
    this->title = "";
    this->genre = "";
    this->year_of_release = 0;
    this->trailer = "";
}

string Movie::get_title() const {
    return this->title;
}

string Movie::get_genre() const {
    return this->genre;
}

int Movie::get_year_of_release() const {
    return this->year_of_release;
}

int Movie::get_number_of_likes() const {
    return this->number_of_likes;
}

string Movie::get_trailer() const {
    return this->trailer;
}

string Movie::to_str() {
    ostringstream output;

    output << "Title: " << this->title << "; ";
    output << "Genre: " << this->genre << "; ";
    output << "Year of release: " << this->year_of_release << "; ";
    output << "Number of likes: " << this->number_of_likes << "; ";
    output << "Trailer link: " << this->trailer << "\n";

    return output.str();
}

Movie &Movie::operator=(const Movie &movie) {
    if (this == &movie)
        return *this;

    this->title = movie.title;
    this->genre = movie.genre;
    this->year_of_release = movie.year_of_release;
    this->number_of_likes = movie.number_of_likes;
    this->trailer = movie.trailer;

    return *this;
}
