#pragma once

#include <stdexcept>
#include <string>

class StudioException : public std::runtime_error {
public:
    explicit StudioException(const std::string& message)
        : std::runtime_error(message) {}
};

class InputValidationException : public StudioException {
public:
    explicit InputValidationException(const std::string& message)
        : StudioException(message) {}
};

class BusinessRuleException : public StudioException {
public:
    explicit BusinessRuleException(const std::string& message)
        : StudioException(message) {}
};

class RepositoryException : public StudioException {
public:
    explicit RepositoryException(const std::string& message)
        : StudioException(message) {}
};

