#include "interpreter.h"

#include <iostream>
#include <utility>

Interpreter::Interpreter(std::string expression) noexcept : expression(std::move(expression)) {}

[[noreturn]] void Interpreter::throwError() const {
    throw std::runtime_error("Interpreter error at "+std::to_string(pos)+": "+expression);
}

Token Interpreter::getNextToken() {
    if (pos >= expression.size()) {
        return Token{TokenType::Eof, ""};
    }

    char currentChar = expression[pos];

    while (isspace(currentChar)) {
        pos++;
        currentChar = expression[pos];
    }

    if (isdigit(currentChar)) {
        int sum=0;
        while (isdigit(currentChar)) {
            sum = sum * 10 + currentChar - '0';
            currentChar = expression[++pos];
        }
        return {TokenType::Integer, sum};
    }
    if (currentChar == '+') {
        pos++;
        return {TokenType::Plus, nullptr};
    }
    if (currentChar == '-') {
        pos++;
        return {TokenType::Minus, nullptr};
    }
    throwError();
}

void Interpreter::consume(const TokenType &type) {
    if (currentToken.getType() == type) {
        currentToken = getNextToken();
    } else {
        throwError();
    }
}

void Interpreter::process() {
    currentToken = getNextToken();
    auto left = currentToken;
    consume(TokenType::Integer);

    auto op = currentToken;
    if (op.getType() == TokenType::Plus) {
        consume(TokenType::Plus);
    } else if (op.getType() == TokenType::Minus) {
        consume(TokenType::Minus);
    }

    auto right = currentToken;
    consume(TokenType::Integer);

    int result;
    if (op.getType() == TokenType::Plus) {
        result = left.getValue<int>() + right.getValue<int>();
    } else if (op.getType() == TokenType::Minus) {
        result = left.getValue<int>() - right.getValue<int>();
    } else {
        throwError();
    }

    std::cout << result << std::endl;
}