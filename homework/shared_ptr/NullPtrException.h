#pragma once

#include <stdexcept>
#include <iostream>

struct NullPtrException : public std::runtime_error{
public:
    NullPtrException(std::string msg = "nullptr exception\n") : std::runtime_error(msg){}

    std::string what(){ return msg_; }
private:
    std::string msg_;
};