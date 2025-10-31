#include "token.h"

#include <utility>

const std::unordered_map<TokenType, std::string> Token::typeNames = {
    {TokenType::Plus, "Plus"}, {TokenType::Minus, "Minus"},       {TokenType::Integer, "Integer"},
    {TokenType::Eof, "Eof"},   {TokenType::Multiply, "Multiply"}, {TokenType::Divide, "Divide"},
};

const TokenType &Token::getType() const noexcept {
    return type;
}

std::ostream &operator<<(std::ostream &strm, const Token &tok) {
    strm << "Token{type=" << Token::typeNames.at(tok.type) << ", value=";
    std::visit([&strm](const auto &v) { strm << v << "}"; }, tok.value);
    return strm;
}
