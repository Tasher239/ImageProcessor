#include "../../include/utils/exceptions.h"

const char *WrongAmountOfArguments::what() const noexcept {
    return message_.c_str();
}

const char *TransformError::what() const noexcept {
    return message_.c_str();
}

const char *WrongFilterName::what() const noexcept {
    return message_.c_str();
}

const char *FileReadError::what() const noexcept {
    return message_.c_str();
}

const char *FileWriteError::what() const noexcept {
    return message_.c_str();
}

const char *NotBMPError::what() const noexcept {
    return message_.c_str();
}

const char *WrongAmountOfFilterArguments::what() const noexcept {
    return message_.c_str();
}
