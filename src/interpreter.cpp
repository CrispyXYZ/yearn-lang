#include "interpreter.h"

#include <iostream>
#include <sstream>
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
        std::stringstream ss;
        ss << "Unexpected character '" << currentChar << "'";
        throwError(ss.str());
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

int Interpreter::term() {
    Token const curr = currentToken;
    consume(TokenType::Integer);
    return curr.getValue<int>();
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
    int result = term();
    while(currentToken.getType()!=TokenType::Eof) {
        switch(currentToken.getType()) {
            case TokenType::Plus:
                consume(TokenType::Plus);
                result += term();
                break;
            case TokenType::Minus:
                consume(TokenType::Minus);
                result -= term();
                break;
            default:
                throwError("Unrecognized token type: " + Token::typeNames.at(currentToken.getType()));
        }
    }

    std::cout << result << std::endl;
}