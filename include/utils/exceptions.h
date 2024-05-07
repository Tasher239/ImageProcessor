#pragma once

#include <iostream>
#include <fstream>
#include <string>

class WrongAmountOfArguments : public std::exception {
public:
    WrongAmountOfArguments(const std::string &required_args, const int &required_amount)
        : message_("Need at least " + std::to_string(required_amount) + " required arguments: " + required_args){};

    const char *what() const noexcept override;

private:
    std::string message_;
};

class WrongAmountOfFilterArguments : public std::exception {
public:
    WrongAmountOfFilterArguments(const std::string &filter_name, const int &required_amount)
        : message_("Filter " + filter_name + " need " + std::to_string(required_amount) + " arguments"){};

    const char *what() const noexcept override;

private:
    std::string message_;
};

class TransformError : public std::exception {
public:
    explicit TransformError(const std::string &filter_name)
        : message_("Filter " + filter_name + "can't be applied. Error while Transform() pixel."){};

    const char *what() const noexcept override;

private:
    std::string message_;
};

class WrongFilterName : public std::exception {
public:
    explicit WrongFilterName(const std::string &filter_name)
        : message_("Filter " + filter_name + "doesn't exist. Try another name."){};

    const char *what() const noexcept override;

private:
    std::string message_;
};

class FileReadError : public std::exception {
public:
    explicit FileReadError() : message_("Sorry, file couldn't be read. Try again."){};

    const char *what() const noexcept override;

private:
    std::string message_;
};

class FileWriteError : public std::exception {
public:
    explicit FileWriteError() : message_("Sorry, file couldn't be written. Try again."){};

    const char *what() const noexcept override;

private:
    std::string message_;
};

class NotBMPError : public std::exception {
public:
    explicit NotBMPError() : message_("It's not .bmp file. Load please another file with .bmp extension."){};

    const char *what() const noexcept override;

private:
    std::string message_;
};