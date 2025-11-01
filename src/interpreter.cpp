#include "interpreter.h"

#include <utility>

#include "interpreter_error.h"
#include "utils.h"

Interpreter::Interpreter(Lexer lexer) :
    lexer(std::move(lexer)), currentToken(this->lexer.getNextToken()) {}

void Interpreter::consume(const TokenType &type) {
    if(currentToken.getType() == type) {
        currentToken = lexer.getNextToken();
    } else {
        throw InterpreterError("Unexpected token type ", currentToken.getType(), ", expecting ",
                               type);
    }
}

int Interpreter::factor() {
    Token const curr = currentToken;
    if(curr.getType() == TokenType::Integer) {
        consume(TokenType::Integer);
        return curr.getValue<int>();
    }
    if(curr.getType() == TokenType::LeftParen) {
        consume(TokenType::LeftParen);
        int result = expr();
        consume(TokenType::RightParen);
        return result;
    }
    throw InterpreterError("Unexpected token type ", curr.getType(),
                           ", expecting Integer or LeftParen");
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
                throw InterpreterError("Unexpected token type: ", currentToken.getType(),
                                       ", expecting Multiply or Divide");
        }
    }
    return result;
}

int Interpreter::expr() {
    int result = term();
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
                throw InterpreterError("Unexpected token type: ", currentToken.getType(),
                                       ", expecting Plus or Minus");
        }
    }

    return result;
}
