#include "interpreter.h"

#include <utility>

#include "interpreter_error.h"

Interpreter::Interpreter(Parser parser) : parser(std::move(parser)) {}

int Interpreter::visit(ASTNode const &node) const {
    return node.accept(*this);
}

int Interpreter::visitNumber(Num const &node) const {
    return node.value;
}

int Interpreter::visitBinary(BinOp const &node) const {
    switch(node.op.getType()) {
        case TokenType::Plus:
            return visit(*node.left) + visit(*node.right);
        case TokenType::Minus:
            return visit(*node.left) - visit(*node.right);
        case TokenType::Multiply:
            return visit(*node.left) * visit(*node.right);
        case TokenType::Divide:
            return visit(*node.left) / visit(*node.right);
        default:
            throw InterpreterError("Unsupported node type ", node.op.getType());
    }
}

int Interpreter::interpret() {
    return visit(*parser.parse());
}