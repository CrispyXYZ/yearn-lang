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
    NodePtr variable();
    NodePtr assignment();
    NodePtr statement();
    std::vector<NodePtr> statement_list();
    NodePtr compound_statement();
    NodePtr parse();
};

#endif  // YEARN_PARSER_H
