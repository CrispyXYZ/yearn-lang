#include "interpreter.h"

#include <iostream>
#include <utility>

#include "interpreter_error.h"

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

int Interpreter::term() {
    Token const curr = currentToken;
    consume(TokenType::Integer);
    return curr.getValue<int>();
}

void Interpreter::process() {
    currentToken = lexer.getNextToken();
    int result = term();
    while(currentToken.getType() != TokenType::Eof) {
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
                throw InterpreterError("Unrecognized token type: ",
                                       Token::typeNames.at(currentToken.getType()));
        }
    }

    std::cout << result << std::endl;
}