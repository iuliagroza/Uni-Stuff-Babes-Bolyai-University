#pragma once

#include <string>
#include "Spaceship.h"

namespace Lecture_7_exceptions {
    class ValidationException {
    private:
        std::string message;

    public:
        ValidationException(std::string _message);

        std::string getMessage() const;
    };

    class ValidationExceptionInherited : public std::exception {
    private:
        std::string message;

    public:
        ValidationExceptionInherited(std::string _message);

        const char *what() const noexcept override;
    };

    class SpaceshipValidator {
    public:
        static void validate(const Spaceship &s);
    };
}