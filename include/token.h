#ifndef YEARN_TOKEN_H
#define YEARN_TOKEN_H
#include <ostream>
#include <string>
#include <variant>

enum class TokenType : unsigned char {
    Null,
    Plus,
    Minus,
    Multiply,
    Divide,
    Assign,
    Integer,
    LeftParen,
    RightParen,
    LeftBrace,
    RightBrace,
    Semicolon,
    Identifier,
    Eof,
};

std::ostream &operator<<(std::ostream &strm, TokenType const &tok);

class Token {
public:
    using ValueType = std::variant<int, char, std::string, double, bool, void *>;

private:
    TokenType type = TokenType::Null;
    ValueType value = nullptr;

public:
    template <typename T>
    Token(TokenType const type, T &&value) noexcept : type(type), value(std::forward<T>(value)) {}

    Token() = default;

    [[nodiscard]] TokenType const &getType() const noexcept;

    template <typename T>
    T const &getValue() const noexcept {
        return std::get<T>(value);
    }

    friend std::ostream &operator<<(std::ostream &strm, Token const &tok);
};

#endif  // YEARN_TOKEN_H