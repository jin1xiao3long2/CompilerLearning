//
// Created by XM on 2021/3/18.
//


#include <iostream>
#include <string>
#include "simpleParser.hpp"

Unit * Parser::ParseUnit() {
Unit *unit = new Unit;
unit->expr = ParseExpr();
return unit;
}

//void Run(const std::string &line) {
//    try {
//        lexer l = lexer();
//        l.lex(line);
//
//        Parser parser(l.getTokens());
//        Unit *unit = parser.ParseUnit();
//        std::cout << unit->Eval() << std::endl;
//        delete unit;
//    } catch (std::exception &e) {
//        std::cout << e.what() << std::endl;
//    }
//}

