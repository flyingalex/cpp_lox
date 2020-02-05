// Copyright 2020 <Copyright hulin>

#ifndef RUNTIMEERROR_HPP_
#define RUNTIMEERROR_HPP_

#include <string>
#include <exception>
#include "./Token.hpp"

using std::exception;
using std::string;

class RuntimeError: public exception  {
 public:
    Token token;
    string message;
    RuntimeError(Token token_, string message_):
    token(token_), message(message_) {}

    virtual const char* what() const throw() {
        return message.c_str();
    }
};

#endif  // RUNTIMEERROR_HPP_