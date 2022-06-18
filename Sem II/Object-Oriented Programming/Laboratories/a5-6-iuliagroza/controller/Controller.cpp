#include "Controller.h"

AdminRepository Controller::get_admin_repo() {
    return this->admin_repo;
}

UserRepository Controller::get_user_repo() {
    return this->user_repo;
}

bool Controller::add_admin(const Movie &movie) {
    return this->admin_repo.add_movie(movie);
}

bool Controller::remove_admin(Movie movie) {
    this->user_repo.remove_movie(movie);
    return this->admin_repo.remove_movie(movie);
}

bool Controller::update_admin(Movie movie, Movie new_movie) {
    this->user_repo.update_movie(movie, new_movie);
    return this->admin_repo.update_movie(movie, new_movie);
}

void Controller::add_user(Movie movie) {
    this->user_repo.add_movie(movie);
}

bool Controller::remove_user(Movie movie) {
    return this->user_repo.remove_movie(movie);
}

void Controller::generate() {
    this->admin_repo.add_movie(Movie("Once upon a time in Hollywood", "Comedy", 2019, 1234445, "https://www.youtube.com/watch?v=ELeMaP8EPAA"));
    this->admin_repo.add_movie(Movie("Carrie", "Horror", 1979, 6000, "https://www.youtube.com/watch?v=YuO26oJQLVs"));
    this->admin_repo.add_movie(Movie("Jaws", "Horror", 1976, 4445, "https://www.youtube.com/watch?v=U1fu_sA7XhE"));
    this->admin_repo.add_movie(Movie("Taxi driver", "Action", 1983, 3243, "https://www.youtube.com/watch?v=oCjiNBiEUaQ"));
    this->admin_repo.add_movie(Movie("Indiana Jones", "Action", 1999, 100000, "https://www.youtube.com/watch?v=WAdJf4wTC5Y"));
    this->admin_repo.add_movie(Movie("Hangover", "Comedy", 2009, 6969696, "https://www.youtube.com/watch?v=tcdUhdOlz9M"));
    this->admin_repo.add_movie(Movie("The Dark Knight", "Thriller", 2008, 23494244, "https://www.youtube.com/watch?v=EXeTwQWrcwY"));
    this->admin_repo.add_movie(Movie("American Pie", "Comedy", 2002, 123, "https://www.youtube.com/watch?v=iUZ3Yxok6N8"));
    this->admin_repo.add_movie(Movie("Breakfast at Tiffany's", "Classic", 1961, 120001, "https://www.youtube.com/watch?v=OPQkbvo99Ug"));
    this->admin_repo.add_movie(Movie("Due Date", "Comedy", 2011, 1234445, "https://www.youtube.com/watch?v=1p3NnJ_oiE0"));
}
