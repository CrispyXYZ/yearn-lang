#ifndef YEARN_INTERPRETER_H
#define YEARN_INTERPRETER_H

#include "ast.h"
#include "parser.h"

class Interpreter final : public ASTVisitor {
    Parser parser;

public:
    explicit Interpreter(Parser parser);
    Interpreter() = delete;
    [[nodiscard]] int visit(ASTNode const &node) const override;
    [[nodiscard]] int visitNumber(Num const &node) const override;
    [[nodiscard]] int visitBinary(BinOp const &node) const override;
    int interpret();
};

#endif  // YEARN_INTERPRETER_H