
#include <iostream>
#include <string>

#include "interpreter.h"
int main() {
    for (;;) {
        std::string str;
        std::cout << ">>> ";
        std::cin >> str;
        if (str.empty()) break;
        Interpreter interpreter{str};
        interpreter.process();
    }
    return 0;
}