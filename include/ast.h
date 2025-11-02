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
    [[nodiscard]] virtual int visit(const ASTNode &node) const = 0;
    [[nodiscard]] virtual int visitNumber(const Num &node) const = 0;
    [[nodiscard]] virtual int visitBinary(const BinOp &node) const = 0;
};

#endif  // YEARN_AST_H
