#include "Controller.h"

Controller::Controller(std::string admin_filename, UserRepository *r) : admin_repo{AdminRepository(admin_filename)},
                                                                        user_repo{r} {}

AdminRepository Controller::get_admin_repo() {
    return this->admin_repo;
}

UserRepository *Controller::get_user_repo() {
    return this->user_repo;
}

void Controller::add_admin(const Movie &movie) {
    this->admin_repo.add_movie(movie);
}

void Controller::remove_admin(Movie movie) {
    std::vector<Movie>::iterator it = find(this->user_repo->get_watchlist().begin(),
                                           this->user_repo->get_watchlist().end(), movie);
    if (it != this->user_repo->get_watchlist().end()) {
        this->user_repo->remove_movie(movie);
    }
    this->admin_repo.remove_movie(movie);
}

void Controller::update_admin(Movie movie, Movie new_movie) {
    std::vector<Movie>::iterator it = find(this->user_repo->get_watchlist().begin(),
                                           this->user_repo->get_watchlist().end(), movie);
    if (it != this->user_repo->get_watchlist().end()) {
        this->user_repo->update_movie(movie, new_movie);
    }
    this->admin_repo.update_movie(movie, new_movie);
}

void Controller::add_user(Movie movie) {
    this->user_repo->add_movie(movie);
}

void Controller::remove_user(Movie movie) {
    this->user_repo->remove_movie(movie);
}
