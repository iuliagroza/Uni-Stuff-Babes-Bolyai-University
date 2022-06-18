#include <cassert>
#include <iostream>
#include "Tests.h"
#include "../controller/Controller.h"
/*
void Tests::test_add() {
    Controller ctrl = Controller("test.txt", );
    ctrl.add_admin(Movie("ad", "asd", 2020, 1232, "dsfd"));
    ctrl.add_user(Movie("ad", "asd", 2020, 1232, "dsfd"));
    assert(ctrl.get_admin_repo().get_movies().size() == 1);
    assert(ctrl.get_user_repo().get_watchlist().size() == 1);
    std::vector<Movie>::iterator it = find(ctrl.get_admin_repo().get_movies().begin(),
                                           ctrl.get_admin_repo().get_movies().end(),
                                           Movie("ad", "asd", 2020, 1232, "dsfd"));
    assert(*it == ctrl.get_admin_repo().get_movies()[0]);
    std::cout << ".test_add() passed!\n";
}

void Tests::test_remove() {
    Controller ctrl = Controller("test.txt", "test.txt");
    ctrl.remove_user(Movie("ad", "asd", 2020, 1232, "dsfd"));
    ctrl.remove_admin(Movie("a", "a", 0, 0, "dsfd"));
    assert(ctrl.get_admin_repo().get_movies().size() == 0);
    assert(ctrl.get_user_repo().get_watchlist().size() == 0);
    std::cout << ".test_remove() passed!\n";
}

void Tests::test_update() {
    Controller ctrl = Controller("test.txt", "test.txt");
    ctrl.add_admin(Movie("ad", "asd", 2020, 1232, "dsfd"));
    ctrl.update_admin(Movie("a", "a", 0, 0, "dsfd"), Movie("a", "a", 0, 0, "dsfd"));
    assert(ctrl.get_admin_repo().get_movies()[0].get_title() == "a");
    assert(ctrl.get_admin_repo().get_movies()[0].get_genre() == "a");
    assert(ctrl.get_admin_repo().get_movies()[0].get_year_of_release() == 0);
    assert(ctrl.get_admin_repo().get_movies()[0].get_number_of_likes() == 0);
    std::cout << ".test_update() passed!\n";
}

void Tests::test_to_str() {
    Movie movie = Movie("a", "b", 2000, 10, "sad");
    assert(movie.to_str() == "Title: a; Genre: b; Year of release: 2000; Number of likes: 10; Trailer link: sad\n");
    std::cout << ".test_to_str() passed!\n";
}

void Tests::test_movie_operator() {
    Movie movie1 = Movie("a", "b", 2000, 10, "sad");
    movie1 = movie1;
    assert(movie1 == movie1);
    std::cout << ".test_movie_operator() passed!\n";
}

void Tests::test_user_repo() {
    UserRepository user_repo = UserRepository("test.txt");
    user_repo.add_movie(Movie("a", "b", 1999, 2132, "c"));
    assert(user_repo.get_watchlist().size() == 1);
    std::vector<Movie> da;
    da.push_back(Movie("a", "b", 1999, 2132, "c"));
    assert(user_repo.get_watchlist().size() == da.size());
    user_repo.update_movie(Movie("a", "b", 1999, 2132, "c"), Movie("s", "b", 1999, 2132, "c"));
    assert(user_repo.get_watchlist()[0].get_title() == "s");
    user_repo.remove_movie(Movie("a", "b", 1999, 2132, "c"));
    assert(user_repo.get_watchlist().size() == 0);
    std::cout << ".test_user_repo() passed!\n";
}

void Tests::test_all() {
    test_add();
    test_remove();
    test_update();
    test_to_str();
    test_movie_operator();
    test_user_repo();

    std::cout << "All tests passed!\n";
}
*/