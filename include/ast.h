#ifndef YEARN_AST_H
#define YEARN_AST_H
#include <memory>

#include "token.h"
class ASTVisitor;

class ASTNode {
public:
    virtual ~ASTNode() = default;
    [[nodiscard]] virtual int accept(ASTVisitor const &visitor) const = 0;
};

using NodePtr = std::unique_ptr<ASTNode>;

class UnaryOp final : public ASTNode {
public:
    Token op;
    NodePtr expr;
    UnaryOp(Token op, NodePtr expr);
    [[nodiscard]] int accept(ASTVisitor const &visitor) const override;
};

class BinOp final : public ASTNode {
public:
    Token op;
    NodePtr left;
    NodePtr right;
    BinOp(Token op, NodePtr left, NodePtr right);
    [[nodiscard]] int accept(ASTVisitor const &visitor) const override;
};

class Num final : public ASTNode {
public:
    Token token;
    int value;
    explicit Num(Token token);
    [[nodiscard]] int accept(ASTVisitor const &visitor) const override;
};

class ASTVisitor {
public:
    virtual ~ASTVisitor() = default;
    [[nodiscard]] virtual int visit(ASTNode const &node) const = 0;
    [[nodiscard]] virtual int visitNumber(Num const &node) const = 0;
    [[nodiscard]] virtual int visitBinary(BinOp const &node) const = 0;
    [[nodiscard]] virtual int visitUnary(UnaryOp const &node) const = 0;
};

#endif  // YEARN_AST_H
