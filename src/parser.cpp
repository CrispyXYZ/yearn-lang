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
    if(type == TokenType::Identifier) {
        return variable();
    }
    throw InterpreterError("Unexpected token type ", type, " while parsing factor");
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
                                       " while parsing term");
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
                                       " while parsing expr");
        }
        node = std::make_unique<BinOp>(token, std::move(node), term());
    }
    return node;
}

NodePtr Parser::variable() {
    NodePtr node = std::make_unique<Variable>(currentToken);
    consume(TokenType::Identifier);
    return node;
}

NodePtr Parser::assignment() {
    NodePtr left = variable();
    Token const token = currentToken;
    consume(TokenType::Assign);
    NodePtr right = expr();
    return std::make_unique<Assignment>(token, std::move(left), std::move(right));
}

NodePtr Parser::statement() {
    NodePtr node;
    if(currentToken.getType() == TokenType::LeftBrace) {
        node = compound_statement();
    } else if(currentToken.getType() == TokenType::Identifier) {
        node = assignment();
    } else {
        throw InterpreterError("Unexpected token type ", currentToken.getType(), " while parsing statement");
    }
    return node;
}

std::vector<NodePtr> Parser::statement_list() {
    std::vector<NodePtr> nodes;
    if(currentToken.getType() == TokenType::RightBrace) {
        return nodes;
    }

    nodes.push_back(statement());
    while(currentToken.getType() == TokenType::Semicolon) {
        consume(TokenType::Semicolon);
        if (currentToken.getType() == TokenType::RightBrace || currentToken.getType() == TokenType::Eof) {
            break;
        }
        nodes.push_back(statement());
    }

    return nodes;
}

NodePtr Parser::compound_statement() {
    consume(TokenType::LeftBrace);
    std::vector<NodePtr> nodes = statement_list();
    consume(TokenType::RightBrace);
    return std::make_unique<Compound>(std::move(nodes));
}

NodePtr Parser::parse() {
    return std::make_unique<Compound>(std::move(statement_list()));;
}