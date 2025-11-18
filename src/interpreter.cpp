#include "interpreter.h"

#include <utility>

#include "interpreter_error.h"

Interpreter::Interpreter() {}

int Interpreter::visit(ASTNode &node) {
    return node.accept(*this);
}

int Interpreter::visitNumber(Num &node) {
    return node.value;
}

int Interpreter::visitBinary(BinOp &node) {
    int const left_val = visit(*node.left);
    int const right_val = visit(*node.right);

    switch(node.op.getType()) {
        case TokenType::Plus:
            return left_val + right_val;
        case TokenType::Minus:
            return left_val - right_val;
        case TokenType::Multiply:
            return left_val * right_val;
        case TokenType::Divide:
            if (right_val == 0) {
                throw InterpreterError("Division by zero");
            }
            return left_val / right_val;
        default:
            throw InterpreterError("Unsupported binary operator: ", node.op.getType());
    }
}

int Interpreter::visitUnary(UnaryOp &node) {
    int const expr_val = visit(*node.expr);

    switch(node.op.getType()) {
        case TokenType::Plus:
            return expr_val;
        case TokenType::Minus:
            return -expr_val;
        default:
            throw InterpreterError("Unsupported unary operator: ", node.op.getType());
    }
}

int Interpreter::visitCompound(Compound &node) {
    int result = 0;
    for(auto &&each: node.children) {
        result = visit(*each);
    }
    return result;
}

int Interpreter::visitAssignment(Assignment &node) {
    auto const *var = dynamic_cast<Variable*>(node.left.get());
    if (!var) {
        throw InterpreterError("Left side of assignment must be a variable");
    }

    int const value = visit(*node.right);

    symbols[var->name] = value;

    return value;
}

int Interpreter::visitVariable(Variable &node) {
    auto const it = symbols.find(node.name);
    if (it == symbols.end()) {
        throw InterpreterError("Undefined variable: ", node.name);
    }
    return it->second;
}

int Interpreter::eval(std::string &code) {
    Parser parser{Lexer{code}};
    return visit(*parser.parse());
}

void Interpreter::reset() {
    symbols.clear();
}

std::unordered_map<std::string, int> Interpreter::getSymbols() const {
    return symbols;
}
