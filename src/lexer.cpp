#include "lexer.h"

#include <iostream>
#include <sstream>
#include <utility>

#include "interpreter_error.h"

Lexer::Lexer(std::string expression) : expression(std::move(expression)) {
    currentChar = this->expression[pos];
}

void Lexer::advance() {
    pos++;
    if(pos >= expression.length()) {
        currentChar = '\0';
    } else {
        currentChar = expression[pos];
    }
}

void Lexer::skipWhitespace() {
    while(isspace(currentChar)) {
        advance();
    }
}

int Lexer::parseInt() {
    int sum = 0;
    while(isdigit(currentChar)) {
        sum = sum * 10 + currentChar - '0';
        advance();
    }
    return sum;
}

Token Lexer::getNextToken() {
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
        throw InterpreterError("Unexpected character '", currentChar, "'");
    }
    return Token{TokenType::Eof, nullptr};
}