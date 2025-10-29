
#include <iostream>
#include <string>

#include "interpreter.h"
int main() {
    for(;;) {
        std::string str;
        std::cout << ">>> ";
        getline(std::cin, str);
        if(str.empty()) break;
        Interpreter interpreter{str};
        try {
            interpreter.process();
        } catch(const std::runtime_error& e) {
            std::cout << "Error:" << e.what() << std::endl;
        }
    }
    return 0;
}