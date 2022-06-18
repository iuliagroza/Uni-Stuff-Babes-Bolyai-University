#ifndef A11_12_IULIAGROZA_CSVUSERREPOSITORY_H
#define A11_12_IULIAGROZA_CSVUSERREPOSITORY_H

#include "UserRepository.h"

class CSVUserRepository : public UserRepository {
public:
    /*
     * CONSTRUCTOR
     */
    explicit CSVUserRepository(const std::string &filename);

    /*
     * Overridden .write_from_file() function that writes a .csv file in order to store the instances (of Movie type) of
     * the repository.
     * return: vector of Movie objects
     */
    void write_to_file() override;

    /*
    * Overridden .display() function that displays in Notepad the contents of the .csv file associated to the
    * repository.
    * return: vector of Movie objects
    */
    void display() const override;
};


#endif
