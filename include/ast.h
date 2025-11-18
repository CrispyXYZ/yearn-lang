#ifndef YEARN_AST_H
#define YEARN_AST_H
#include <memory>
#include <unordered_map>
#include <vector>

#include "token.h"
class ASTVisitor;

class ASTNode {
public:
    virtual ~ASTNode() = default;
    virtual int accept(ASTVisitor &visitor) = 0; // 移除了 [[nodiscard]] 和 const
};

using NodePtr = std::unique_ptr<ASTNode>;

class UnaryOp final : public ASTNode {
public:
    Token op;
    NodePtr expr;
    UnaryOp(Token op, NodePtr expr);
    int accept(ASTVisitor &visitor) override;
};

class BinOp final : public ASTNode {
public:
    Token op;
    NodePtr left;
    NodePtr right;
    BinOp(Token op, NodePtr left, NodePtr right);
    int accept(ASTVisitor &visitor) override;
};

class Num final : public ASTNode {
public:
    Token token;
    int value;
    explicit Num(Token token);
    int accept(ASTVisitor &visitor) override;
};

class Compound final : public ASTNode {
public:
    std::vector<NodePtr> children;
    explicit Compound(std::vector<NodePtr> nodes);
    int accept(ASTVisitor &visitor) override;
};

class Variable final : public ASTNode {
public:
    Token token;
    std::string name;
    explicit Variable(Token token);
    int accept(ASTVisitor &visitor) override;
};

class Assignment final : public ASTNode {
public:
    Token op;
    NodePtr left;
    NodePtr right;
    Assignment(Token op, NodePtr left, NodePtr right);
    int accept(ASTVisitor &visitor) override;
};

class ASTVisitor {
protected:
    std::unordered_map<std::string, int> symbols;
public:
    virtual ~ASTVisitor() = default;
    virtual int visit(ASTNode &node) = 0;
    virtual int visitNumber(Num &node) = 0;
    virtual int visitBinary(BinOp &node) = 0;
    virtual int visitUnary(UnaryOp &node) = 0;
    virtual int visitCompound(Compound &node) = 0;
    virtual int visitAssignment(Assignment &node) = 0;
    virtual int visitVariable(Variable &node) = 0;
};

#endif  // YEARN_AST_H