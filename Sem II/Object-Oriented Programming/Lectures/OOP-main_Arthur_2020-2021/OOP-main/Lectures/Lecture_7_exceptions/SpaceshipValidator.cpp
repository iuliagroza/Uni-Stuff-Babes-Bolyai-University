#include "SpaceshipValidator.h"

using namespace std;
namespace Lecture_7_exceptions {
    ValidationException::ValidationException(std::string _message) : message{_message} {
    }

    std::string ValidationException::getMessage() const {
        return this->message;
    }


    ValidationExceptionInherited::ValidationExceptionInherited(std::string _message) : message{_message} {
    }

    const char *ValidationExceptionInherited::what() const noexcept {
        return message.c_str();
    }


    void SpaceshipValidator::validate(const Spaceship &s) {
        string errors;
        if (s.getName().size() < 3)
            errors += string("The spaceship name cannot be less than 2 characters!\n");
        if (!isupper(s.getCaptain()[0]))
            errors += string("The captain's name must start with a capital letter!\n");
        if (s.getType().size() < 3)
            errors += string("The spaceship type cannot be less than 2 characters!\n");

        if (errors.size() > 0)
            throw ValidationException(errors);

        /*if (errors.size() > 0)
            throw ValidationExceptionInherited(errors);*/
    }
}