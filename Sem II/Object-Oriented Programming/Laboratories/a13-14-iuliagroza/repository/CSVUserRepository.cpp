#include "CSVUserRepository.h"
#include "../validators/Exceptions.h"

CSVUserRepository::CSVUserRepository(const std::string &filename) : UserRepository(filename) {
    this->filename = filename;
}

void CSVUserRepository::write_to_file() {
    std::ofstream file(this->filename);

    if (!file.is_open()) {
        throw FileError("The file could not be opened!");
    }

    for (const auto& movie: this->watchlist) {
        file << movie;
    }

    file.close();
}

void CSVUserRepository::display() const {
    std::string aux = "notepad \"" + this->filename + "\"";
    system(aux.c_str());
}
