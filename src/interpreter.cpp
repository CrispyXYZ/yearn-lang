#include "interpreter.h"

#include <iostream>
#include <utility>

#include "interpreter_error.h"
#include "utils.h"

Interpreter::Interpreter(Lexer lexer) : lexer(std::move(lexer)) {}

void Interpreter::consume(const TokenType &type) {
    if(currentToken.getType() == type) {
        currentToken = lexer.getNextToken();
    } else {
        throw InterpreterError("Unexpected token type ",
                               Token::typeNames.at(currentToken.getType()), ", expecting ",
                               Token::typeNames.at(type));
    }
}

int Interpreter::factor() {
    Token const curr = currentToken;
    consume(TokenType::Integer);
    return curr.getValue<int>();
}

int Interpreter::term() {
    int result = factor();
    while(is_in(currentToken.getType(), TokenType::Multiply, TokenType::Divide)) {
        switch(currentToken.getType()) {
            case TokenType::Multiply:
                consume(TokenType::Multiply);
                result *= factor();
                break;
            case TokenType::Divide:
                consume(TokenType::Divide);
                result /= factor();
                break;
            default:
                throw InterpreterError(
                    "Unexpected token type: ", Token::typeNames.at(currentToken.getType()),
                    ", expecting Multiply or Divide");
        }
        return result;
    }
}

void Interpreter::expr() {
    currentToken = lexer.getNextToken();
    int result = factor();
    while(is_in(currentToken.getType(), TokenType::Plus, TokenType::Minus)) {
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
                throw InterpreterError(
                    "Unexpected token type: ", Token::typeNames.at(currentToken.getType()),
                    ", expecting Plus or Minus");
        }
    }

    std::cout << result << std::endl;
}