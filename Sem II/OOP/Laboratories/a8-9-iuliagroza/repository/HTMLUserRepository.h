#ifndef A8_9_IULIAGROZA_HTMLUSERREPOSITORY_H
#define A8_9_IULIAGROZA_HTMLUSERREPOSITORY_H

#include "UserRepository.h"

class HTMLUserRepository : public UserRepository {
public:
    /*
     * CONSTRUCTOR
     */
    HTMLUserRepository(const std::string &filename);

    /*
     * Overridden .read_from_file() function that parses an HTML file and extracts the information of the objects
     * (of Movie type) that should be added  into the repository.
     * return: vector of Movie objects
     */
    std::vector<Movie> read_from_file() override;

    /*
     * Overridden .write_from_file() function that injects HTML in order to store the instances (of Movie type) of the
     * repository in the .html file associated to the repository.
     * return: vector of Movie objects
     */
    void write_to_file() override;

    /*
     * Overridden .display() function that displays in the browser the contents of the .html file associated to the
     * repository.
     * return: vector of Movie objects
     */
    void display() const override;
};


#endif
