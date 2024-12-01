#pragma once

#include <exception>
#include <source_location>
#include <string>

namespace x {

class Error : public std::exception {
public:
    explicit Error(std::source_location sl = std::source_location::current());
    explicit Error(std::string message, std::source_location sl = std::source_location::current());

    const char* what() const noexcept override;

private:
    std::string _message;
};

} // namespace x