
#include <fstream>
#include <iostream>
#include <string>

#include "interpreter.h"
#include "interpreter_error.h"

int main() {
    Interpreter interpreter;
    for(;;) {
        std::string str;
        std::cout << "yearn>";
        getline(std::cin, str);
        if(str.empty()) break;

        if (str[0] == '@') {
            std::string filename = str.substr(1);
            std::ifstream file(filename);
            if (!file) {
                std::cout << "Error: File not found: " << filename << std::endl;
                continue;
            }
            std::string content((std::istreambuf_iterator(file)), std::istreambuf_iterator<char>());
            try {
                std::cout << interpreter.eval(content) << std::endl;
            } catch(InterpreterError const &e) {
                std::cout << "Error: " << e.what() << std::endl;
            }
        } else {
            try {
                std::cout << interpreter.eval(str) << std::endl;
            } catch(InterpreterError const &e) {
                std::cout << "Error: " << e.what() << std::endl;
            }
        }
    }
    return 0;
}