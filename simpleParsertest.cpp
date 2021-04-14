#include "lexer.hpp"
#include <iostream>
#include "simpleParser.cpp"
#include <vector>

int main() {
    std::string line;

//    while (true) {
//        std::cout << "> ";
//        std::cout.flush();
//        if (!std::getline(std::cin, line)) {
//            break;
//        }
//        if (line == ":q")
//            break;
//        Run(line);
//    }

    line = "1 + (cos(3.1415926) + 3) / 2 * (3 / 2)";
    std::string line1 = "1 + (cos(3.1415926) + 3) / 2 * (3 / 2)";
    lexer l;
    l.lex(line);
    std::deque<token_base *> tokens = l.getTokens();
    std::cout << "str is  " << line << std::endl;
    std::cout << "--------tokens--------" << std::endl;
    std::cout << "type\t\t" << "line\t" << "value" << std::endl;
    for (const auto &e : tokens) {
        e->show(std::cout);
        std::cout << std::endl;
    }
    try{
        Parser parser = Parser(tokens);
        Unit *unit = parser.ParseUnit();
        std::cout << unit->Eval(0) << std::endl;
    }catch (std::exception &e){
        std::cerr << e.what() << std::endl;
    }

    return 0;
}