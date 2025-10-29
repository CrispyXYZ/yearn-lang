#ifndef YEARN_INTERPRETER_H
#define YEARN_INTERPRETER_H
#include <string>

#include "token.h"

class Interpreter {
    std::string expression;
    int pos = 0;
    Token currentToken{};
    char currentChar;

    [[noreturn]] void throwError(const std::string &msg) const;
    Token getNextToken();
    void consume(const TokenType &type);
    void advance();
    void skipWhitespace();
    int parseInt();

public:
    explicit Interpreter(std::string expression);
    Interpreter() = delete;
    void process();
};

#endif  // YEARN_INTERPRETER_H
