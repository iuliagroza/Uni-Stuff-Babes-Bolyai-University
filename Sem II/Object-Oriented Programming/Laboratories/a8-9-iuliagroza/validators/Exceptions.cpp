#include "Exceptions.h"

OperationError::OperationError(const char *message) {
    this->message = message;
}

const char *OperationError::what() const noexcept {
    return this->message;
}

InputError::InputError(const char *message) {
    this->message = message;
}

const char *InputError::what() const noexcept {
    return this->message;
}

FileError::FileError(const char *message) {
    this->message = message;
}

const char *FileError::what() const noexcept {
    return this->message;
}
