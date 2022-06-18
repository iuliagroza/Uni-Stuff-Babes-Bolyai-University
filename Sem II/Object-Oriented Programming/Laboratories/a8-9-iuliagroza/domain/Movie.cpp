#include "Movie.h"

Movie::Movie(std::string title, std::string genre, int year_of_release, int number_of_likes, std::string trailer)
        : title{title}, genre{genre}, year_of_release{year_of_release}, number_of_likes{number_of_likes},
          trailer{trailer} {}

Movie::Movie() : title(""), genre(""), year_of_release(0), number_of_likes(0), trailer("") {}

std::string Movie::get_title() const {
    return this->title;
}

std::string Movie::get_genre() const {
    return this->genre;
}

int Movie::get_year_of_release() const {
    return this->year_of_release;
}

int Movie::get_number_of_likes() const {
    return this->number_of_likes;
}

std::string Movie::get_trailer() const {
    return this->trailer;
}

std::string Movie::to_str() {
    std::ostringstream output;

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

std::vector<std::string> tokenize(const std::string &str, char delimiter) {
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string(token);
    while (getline(ss, token, delimiter))
        result.push_back(token);
    return result;
}

std::istream &operator>>(std::istream &is, Movie &movie) {
    std::string line;
    getline(is, line);

    std::vector<std::string> tokens = tokenize(line, ',');
    if (tokens.size() != 5)
        return is;

    movie.title = tokens[0];
    movie.genre = tokens[1];
    movie.year_of_release = stoi(tokens[2]);
    movie.number_of_likes = stoi(tokens[3]);
    movie.trailer = tokens[4];

    return is;
}

std::ostream &operator<<(std::ostream &os, const Movie &movie) {
    os << movie.title << "," << movie.genre << "," << movie.year_of_release << "," << movie.number_of_likes << ","
       << movie.trailer << "\n";
    return os;
}
