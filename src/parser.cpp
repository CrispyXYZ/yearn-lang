#include "parser.h"

#include "interpreter_error.h"
#include "utils.h"

void Parser::consume(TokenType const &type) {
    if(currentToken.getType() == type) {
        currentToken = lexer.getNextToken();
    } else {
        throw InterpreterError("Unexpected token type ", currentToken.getType(), ", expecting ",
                               type);
    }
}

Parser::Parser(Lexer lexer) : lexer(std::move(lexer)), currentToken(this->lexer.getNextToken()) {}

NodePtr Parser::factor() {
    Token const token = currentToken;
    TokenType const type = token.getType();
    if(type == TokenType::Plus || type == TokenType::Minus) {
        consume(type);
        return std::make_unique<UnaryOp>(token, factor());
    }
    if(type == TokenType::Integer) {
        consume(TokenType::Integer);
        return std::make_unique<Num>(token);
    }
    if(type == TokenType::LeftParen) {
        consume(TokenType::LeftParen);
        NodePtr node = expr();
        consume(TokenType::RightParen);
        return node;
    }
    throw InterpreterError("Unexpected token type ", type, ", expecting Integer or LeftParen");
}

NodePtr Parser::term() {
    NodePtr node = factor();
    while(is_in(currentToken.getType(), TokenType::Multiply, TokenType::Divide)) {
        Token const token = currentToken;
        switch(currentToken.getType()) {
            case TokenType::Multiply:
                consume(TokenType::Multiply);
                break;
            case TokenType::Divide:
                consume(TokenType::Divide);
                break;
            default:
                throw InterpreterError("Unexpected token type: ", currentToken.getType(),
                                       ", expecting Multiply or Divide");
        }
        node = std::make_unique<BinOp>(token, std::move(node), factor());
    }
    return node;
}

NodePtr Parser::expr() {
    NodePtr node = term();
    while(is_in(currentToken.getType(), TokenType::Plus, TokenType::Minus)) {
        Token const token = currentToken;
        switch(currentToken.getType()) {
            case TokenType::Plus:
                consume(TokenType::Plus);
                break;
            case TokenType::Minus:
                consume(TokenType::Minus);
                break;
            default:
                throw InterpreterError("Unexpected token type: ", currentToken.getType(),
                                       ", expecting Plus or Minus");
        }
        node = std::make_unique<BinOp>(token, std::move(node), term());
    }
    return node;
}

NodePtr Parser::parse() {
    return expr();
}