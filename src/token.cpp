#include "token.h"

std::ostream &operator<<(std::ostream &strm, TokenType const &tok) {
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
        case TokenType::Assign:
            strm << "Assign";
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
        case TokenType::LeftBrace:
            strm << "LeftBrace";
            break;
        case TokenType::RightBrace:
            strm << "RightBrace";
            break;
        case TokenType::Semicolon:
            strm << "Semicolon";
            break;
        case TokenType::Identifier:
            strm << "Identifier";
            break;
        case TokenType::Eof:
            strm << "Eof";
            break;
    }
    return strm;
}

TokenType const &Token::getType() const noexcept {
    return type;
}

std::ostream &operator<<(std::ostream &strm, Token const &tok) {
    strm << "Token{type=" << tok.type << ", value=";
    std::visit([&strm](auto const &v) { strm << v << "}"; }, tok.value);
    return strm;
}
