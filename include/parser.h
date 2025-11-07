#ifndef YEARN_PARSER_H
#define YEARN_PARSER_H
#include "ast.h"
#include "lexer.h"

class Parser {
    Lexer lexer;
    Token currentToken;

    void consume(TokenType const &type);

public:
    explicit Parser(Lexer lexer);
    NodePtr factor();
    NodePtr term();
    NodePtr expr();
    NodePtr parse();
};

#endif  // YEARN_PARSER_H
