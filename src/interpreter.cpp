#include "interpreter.h"

#include <iostream>
#include <utility>

Interpreter::Interpreter(std::string expression) : expression(std::move(expression)) {
    currentChar = this->expression[pos];
}

[[noreturn]] void Interpreter::throwError(const std::string &msg) const {
    throw std::runtime_error("Interpreter error at " + std::to_string(pos) + " with \"" +
                             expression + "\": " + msg);
}

Token Interpreter::getNextToken() {
    while(currentChar != '\0') {
        if(isspace(currentChar)) {
            skipWhitespace();
            continue;
        }
        if(isdigit(currentChar)) {
            return Token{TokenType::Integer, parseInt()};
        }
        if(currentChar == '+') {
            advance();
            return Token{TokenType::Plus, nullptr};
        }
        if(currentChar == '-') {
            advance();
            return Token{TokenType::Minus, nullptr};
        }
        throwError("Unexpected character '" + std::string{1, currentChar} + "'");
    }
    return Token{TokenType::Eof, nullptr};
}

void Interpreter::consume(const TokenType &type) {
    if(currentToken.getType() == type) {
        currentToken = getNextToken();
    } else {
        throwError("Unexpected token type " + Token::typeNames.at(currentToken.getType()) +
                   ", expecting " + Token::typeNames.at(type));
    }
}

void Interpreter::advance() {
    pos++;
    if(pos >= expression.length()) {
        currentChar = '\0';
    } else {
        currentChar = expression[pos];
    }
}

void Interpreter::skipWhitespace() {
    while(isspace(currentChar)) {
        advance();
    }
}

int Interpreter::parseInt() {
    int sum = 0;
    while(isdigit(currentChar)) {
        sum = sum * 10 + currentChar - '0';
        advance();
    }
    return sum;
}

void Interpreter::process() {
    currentToken = getNextToken();
    Token left = currentToken;
    consume(TokenType::Integer);

    Token op = currentToken;
    if(op.getType() == TokenType::Plus) {
        consume(TokenType::Plus);
    } else /*if(op.getType() == TokenType::Minus)*/ {
        consume(TokenType::Minus);
    }

    Token right = currentToken;
    consume(TokenType::Integer);

    int result;
    if(op.getType() == TokenType::Plus) {
        result = left.getValue<int>() + right.getValue<int>();
    } else if(op.getType() == TokenType::Minus) {
        result = left.getValue<int>() - right.getValue<int>();
    } else {
        throwError("Unexpected operator type " + Token::typeNames.at(op.getType()));
    }

    std::cout << result << std::endl;
}