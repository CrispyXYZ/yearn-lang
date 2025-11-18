#include "ast.h"

#include <utility>

#include "interpreter.h"

UnaryOp::UnaryOp(Token op, NodePtr expr) : op(std::move(op)), expr(std::move(expr)) {}

int UnaryOp::accept(ASTVisitor &visitor) {
    return visitor.visitUnary(*this);
}

BinOp::BinOp(Token op, NodePtr left, NodePtr right) :
    op(std::move(op)), left(std::move(left)), right(std::move(right)) {}

int BinOp::accept(ASTVisitor &visitor) {
    return visitor.visitBinary(*this);
}

Num::Num(Token token) : token(std::move(token)), value(this->token.getValue<int>()) {}

int Num::accept(ASTVisitor &visitor) {
    return visitor.visitNumber(*this);
}

Compound::Compound(std::vector<NodePtr> nodes) : children(std::move(nodes)) {}

int Compound::accept(ASTVisitor &visitor) {
    return visitor.visitCompound(*this);
}

Variable::Variable(Token token) :
    token(std::move(token)), name(this->token.getValue<std::string>()) {}

int Variable::accept(ASTVisitor &visitor) {
    return visitor.visitVariable(*this);
}

Assignment::Assignment(Token op, NodePtr left, NodePtr right) :
    op(std::move(op)), left(std::move(left)), right(std::move(right)) {}

int Assignment::accept(ASTVisitor &visitor) {
    return visitor.visitAssignment(*this);
}
