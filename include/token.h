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
    Integer,
    LeftParen,
    RightParen,
    Eof,
};

std::ostream &operator<<(std::ostream &strm, const TokenType &tok);

class Token {
public:
    using ValueType = std::variant<int, char, std::string, double, bool, void *>;

private:
    TokenType type = TokenType::Null;
    ValueType value = nullptr;

public:
    template <typename T>
    Token(const TokenType type, T &&value) noexcept : type(type), value(std::forward<T>(value)) {}

    Token() = default;

    [[nodiscard]] const TokenType &getType() const noexcept;

    template <typename T>
    const T &getValue() const noexcept {
        return std::get<T>(value);
    }

    friend std::ostream &operator<<(std::ostream &strm, const Token &tok);
};

#endif  // YEARN_TOKEN_H