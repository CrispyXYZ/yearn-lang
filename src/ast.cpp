#include "ast.h"

#include <utility>

#include "interpreter.h"

UnaryOp::UnaryOp(Token op, NodePtr expr) : op(std::move(op)), expr(std::move(expr)) {}

int UnaryOp::accept(ASTVisitor const &visitor) const {
    return visitor.visitUnary(*this);
}

BinOp::BinOp(Token op, NodePtr left, NodePtr right) :
    op(std::move(op)), left(std::move(left)), right(std::move(right)) {}

int BinOp::accept(ASTVisitor const &visitor) const {
    return visitor.visitBinary(*this);
}

Num::Num(Token token) : token(std::move(token)), value(this->token.getValue<int>()) {}

int Num::accept(ASTVisitor const &visitor) const {
    return visitor.visitNumber(*this);
}