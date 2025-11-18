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
    [[nodiscard]] char peek() const;

public:
    explicit Lexer(std::string expression);
    Lexer() = delete;
    Token getNextToken();
    Token getIdToken();
};

#endif  // YEARN_LEXER_H