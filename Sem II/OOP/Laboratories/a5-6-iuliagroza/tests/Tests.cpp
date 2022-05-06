#include <cassert>
#include <iostream>
#include "Tests.h"
#include "../controller/Controller.h"

using namespace std;

void Tests::test_add() {
    Controller ctrl;
    ctrl.add_admin(Movie("ad", "asd", 2020, 1232, "dsfd"));
    ctrl.add_user(Movie("ad", "asd", 2020, 1232, "dsfd"));
    assert(ctrl.get_admin_repo().get_size() == 1);
    assert(ctrl.get_user_repo().get_size() == 1);
    assert(ctrl.get_admin_repo().find_movie(Movie("ad", "asd", 2020, 1232, "dsfd")) == 0);
    bool result = ctrl.add_admin(Movie("ad", "asd", 2020, 1232, "dsfd"));
    assert(result == 0);
    cout << ".test_add() passed!\n";
}

void Tests::test_remove() {
    Controller ctrl;
    ctrl.add_admin(Movie("ad", "asd", 2020, 1232, "dsfd"));
    ctrl.add_user(Movie("ad", "asd", 2020, 1232, "dsfd"));
    ctrl.remove_user(Movie("ad", "asd", 2020, 1232, "dsfd"));
    ctrl.remove_admin(Movie("a", "a", 0, 0, "dsfd"));
    assert(ctrl.get_admin_repo().get_size() == 0);
    assert(ctrl.get_user_repo().get_size() == 0);
    bool result = ctrl.remove_admin(Movie("a", "a", 0, 0, "dsfd"));
    assert(ctrl.get_admin_repo().get_size() == 0);
    assert(result == 0);
    cout << ".test_remove() passed!\n";
}

void Tests::test_update() {
    Controller ctrl;
    ctrl.add_admin(Movie("ad", "asd", 2020, 1232, "dsfd"));
    ctrl.update_admin(Movie("a", "a", 0, 0, "dsfd"), Movie("a", "a", 0, 0, "dsfd"));
    assert(ctrl.get_admin_repo().get_movies().get_element(0).get_title() == "a");
    assert(ctrl.get_admin_repo().get_movies().get_element(0).get_genre() == "a");
    assert(ctrl.get_admin_repo().get_movies().get_element(0).get_year_of_release() == 0);
    assert(ctrl.get_admin_repo().get_movies().get_element(0).get_number_of_likes() == 0);
    bool result = ctrl.update_admin(Movie("a", "a", 0, 0, "a"), Movie("a", "a", 0, 0, "a"));
    assert(result == 0);
    cout << ".test_update() passed!\n";
}

void Tests::test_to_str() {
    Movie movie = Movie("a", "b", 2000, 10, "sad");
    assert(movie.to_str() == "Title: a; Genre: b; Year of release: 2000; Number of likes: 10; Trailer link: sad\n");
    cout << ".test_to_str() passed!\n";
}

void Tests::test_movie_operator() {
    Movie movie1 = Movie("a", "b", 2000, 10, "sad");
    movie1 = movie1;
    assert(movie1 == movie1);
    cout << ".test_movie_operator() passed!\n";
}

void Tests::test_dynamic_array() {
    DynamicArray<Movie> arr = DynamicArray<Movie>(2);
    arr.add(Movie("a", "b", 2000, 10, "c"));
    arr.add(Movie("d", "e", 2001, 11, "f"));
    arr.add(Movie("g", "h", 2002, 12, "i"));

    DynamicArray<Movie> new_arr = DynamicArray<Movie>(arr);
    new_arr = arr;
    arr = arr;
    assert(arr.get_size() == 3);
    assert(new_arr.get_size() == 3);

    arr.remove(0);
    assert(arr.get_size() == 2);

    cout << ".test_dynamic_array() passed!\n";
}

void Tests::test_user_repo() {
    UserRepository user_repo;
    user_repo.add_movie(Movie("a", "b", 1999, 2132, "c"));
    assert(user_repo.get_size() == 1);
    DynamicArray<Movie> da;
    da.add(Movie("a", "b", 1999, 2132, "c"));
    assert(user_repo.get_watchlist().get_size() == da.get_size());
    user_repo.update_movie(Movie("a", "b", 1999, 2132, "c"), Movie("s", "b", 1999, 2132, "c"));
    assert(user_repo.get_watchlist().get_element(0).get_title() == "s");
    user_repo.remove_movie(Movie("a", "b", 1999, 2132, "c"));
    assert(user_repo.get_size() == 0);
    cout << ".test_user_repo() passed!\n";
}

void Tests::test_all() {
    test_add();
    test_remove();
    test_update();
    test_to_str();
    test_movie_operator();
    test_dynamic_array();
    test_user_repo();

    cout << "All tests passed!\n";
}
