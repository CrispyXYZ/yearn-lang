
#include <iostream>
#include <string>

#include "interpreter.h"
#include "interpreter_error.h"

int main() {
    for(;;) {
        std::string str;
        std::cout << ">>> ";
        getline(std::cin, str);
        if(str.empty()) break;
        Interpreter interpreter{Lexer{str}};
        try {
            std::cout << interpreter.expr() << std::endl;
        } catch(const InterpreterError &e) {
            std::cout << "Error:" << e.what() << std::endl;
        }
    }
    return 0;
}