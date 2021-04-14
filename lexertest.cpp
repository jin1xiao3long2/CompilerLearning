#include <iostream>
#include <set>
#include "lexer.cpp"
#include <fstream>
#include <string>

int main() {
//    test :
    std::string filename = "C:/CPP/2020_5/test.txt";
    std::fstream fs;
    fs.open(filename, std::ios::in);
    std::string sp;
    bool newline = false;
    while (!fs.eof()) {
        std::string s;
        std::getline(fs, s);
        if (newline)
            s = '\n' + s;
        newline = true;
        sp += s;
    }
    std::cout << sp << std::endl;
    lexer lexer;
    lexer.lex(sp);
    std::deque<token_base *> tokens = lexer.getTokens();
    std::deque<error *> errors = lexer.getErrors();
    std::deque<identifier *> identifiers = lexer.getIdentifiers();
    std::cout << "--------tokens--------" << std::endl;
    std::cout << "type\t\t" << "line\t" << "value" << std::endl;
    for (const auto &e : tokens) {
        e->show(std::cout);
        std::cout << std::endl;
    }
    std::cout << "--------errors--------" << std::endl;
    std::cout << "line\tcolumn\tinfo\t" << std::endl;
    for (const auto &e : errors) {
        std::cout << e->get_Line() << "\t" << e->get_Column() << "\t" << e->get_ErrorInfo() << "\t" << std::endl;
    }
    std::cout << "------identifiers------" << std::endl;
    std::cout << "line\t" << "name\t" << "address" << std::endl;
    for (const auto &e : identifiers) {
        std::cout << e->get_Line() << "\t" << e->get_Name() << "\t" << e->get_Addr() << std::endl;
    }
    return 0;
}