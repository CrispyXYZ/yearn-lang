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

char Lexer::peek() const {
    int const p = pos + 1;
    if(p >= expression.length()) {
        return '\0';
    }
    return expression[p];
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
        if(isalpha(currentChar)) {
            return getIdToken();
        }
        if(currentChar == ';') {
            advance();
            return Token{TokenType::Semicolon, nullptr};
        }
        if(currentChar == '=') {
            advance();
            return Token{TokenType::Assign, nullptr};
        }
        if(currentChar == '+') {
            advance();
            return Token{TokenType::Plus, nullptr};
        }
        if(currentChar == '-') {
            advance();
            return Token{TokenType::Minus, nullptr};
        }
        if(currentChar == '*') {
            advance();
            return Token{TokenType::Multiply, nullptr};
        }
        if(currentChar == '/') {
            advance();
            return Token{TokenType::Divide, nullptr};
        }
        if(currentChar == '(') {
            advance();
            return Token{TokenType::LeftParen, nullptr};
        }
        if(currentChar == ')') {
            advance();
            return Token{TokenType::RightParen, nullptr};
        }
        if(currentChar == '{') {
            advance();
            return Token{TokenType::LeftBrace, nullptr};
        }
        if(currentChar == '}') {
            advance();
            return Token{TokenType::RightBrace, nullptr};
        }
        throw InterpreterError("Unexpected character '", currentChar, "' while lexing");
    }
    return Token{TokenType::Eof, nullptr};
}

Token Lexer::getIdToken() {
    std::stringstream ss;
    while(currentChar != '\0' && isalnum(currentChar)) {
        ss << currentChar;
        advance();
    }
    return Token{TokenType::Identifier, ss.str()};
}