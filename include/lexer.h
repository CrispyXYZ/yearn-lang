#ifndef YEARN_LEXER_H
#define YEARN_LEXER_H

#include <string>

#include "token.h"

class Lexer {
    std::string expression;
    int pos = 0;
    char currentChar;

    void advance();
    void skipWhitespace();
    int parseInt();

public:
    explicit Lexer(std::string expression);
    Lexer() = delete;
    Token getNextToken();
};

#endif  // YEARN_LEXER_H