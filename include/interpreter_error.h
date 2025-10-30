#ifndef YEARN_INTERPRETER_ERROR_H
#define YEARN_INTERPRETER_ERROR_H
#include <sstream>
#include <stdexcept>

class InterpreterError final : public std::runtime_error {
    template <typename... Args>
    static std::string make_string(Args &&...args) {
        std::stringstream ss;
        (ss << ... << std::forward<Args>(args));
        return ss.str();
    };

public:
    template <typename... Args>
    explicit InterpreterError(Args &&...args) :
        runtime_error(make_string(std::forward<Args>(args)...)){};
};

#endif  // YEARN_INTERPRETER_ERROR_H
