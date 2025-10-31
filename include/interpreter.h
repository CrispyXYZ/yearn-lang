#ifndef YEARN_INTERPRETER_H
#define YEARN_INTERPRETER_H

#include "lexer.h"
#include "token.h"

class Interpreter {
    Lexer lexer;
    Token currentToken{};

    void consume(const TokenType &type);

public:
    explicit Interpreter(Lexer lexer);
    Interpreter() = delete;
    int factor();
    int term();
    void expr();
};

#endif  // YEARN_INTERPRETER_H