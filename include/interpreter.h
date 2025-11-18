#ifndef YEARN_INTERPRETER_H
#define YEARN_INTERPRETER_H

#include "ast.h"
#include "parser.h"

class Interpreter final : public ASTVisitor {
public:
    Interpreter();
    [[nodiscard]] int visit(ASTNode &node) override;
    [[nodiscard]] int visitNumber(Num &node) override;
    [[nodiscard]] int visitBinary(BinOp &node) override;
    [[nodiscard]] int visitUnary(UnaryOp &node) override;
    [[nodiscard]] int visitCompound(Compound &node) override;
    [[nodiscard]] int visitAssignment(Assignment &node) override;
    [[nodiscard]] int visitVariable(Variable &node) override;
    int eval(std::string &code);
    void reset();
    std::unordered_map<std::string, int> getSymbols() const;

};

#endif  // YEARN_INTERPRETER_H