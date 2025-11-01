#include "token.h"

std::ostream &operator<<(std::ostream &strm, const TokenType &tok) {
    switch(tok) {
        case TokenType::Null:
            strm << "Null";
            break;
        case TokenType::Plus:
            strm << "Plus";
            break;
        case TokenType::Minus:
            strm << "Minus";
            break;
        case TokenType::Multiply:
            strm << "Multiply";
            break;
        case TokenType::Divide:
            strm << "Divide";
            break;
        case TokenType::Integer:
            strm << "Integer";
            break;
        case TokenType::LeftParen:
            strm << "LeftParen";
            break;
        case TokenType::RightParen:
            strm << "RightParen";
            break;
        case TokenType::Eof:
            strm << "Eof";
            break;
    }
    return strm;
}

const TokenType &Token::getType() const noexcept {
    return type;
}

std::ostream &operator<<(std::ostream &strm, const Token &tok) {
    strm << "Token{type=" << tok.type << ", value=";
    std::visit([&strm](const auto &v) { strm << v << "}"; }, tok.value);
    return strm;
}
