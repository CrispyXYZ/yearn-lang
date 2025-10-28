#ifndef YEARN_INTERPRETER_H
#define YEARN_INTERPRETER_H
#include <string>

#include "token.h"

class Interpreter {
    std::string expression;
    int pos = 0;
    Token currentToken{};

public:
    explicit Interpreter(std::string expression) noexcept;
    Interpreter() = delete;
    [[noreturn]] void throwError() const;
    Token getNextToken();
    void expect(const TokenType &type);
    void process();

};

#endif  // YEARN_INTERPRETER_H
