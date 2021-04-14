//
// Created by XM on 2021/3/24.
//

#include <CM_Signal.hpp>

namespace cm {

    /*
     ADD, SUB, MUL, DIV,
        LT, LE, GT, GE,
        EQ, NEQ,
        ASSIGN,
        LEFT_P, RIGHT_P,
        LEFT_S, RIGHT_S,
        LEFT_B, RIGHT_B,
     */

    const std::unordered_map<std::string, signal_type> signal_map::string2signal_map = {
            {"+",signal_type::ADD},
            {"-",signal_type::SUB},
            {"*",signal_type::MUL},
            {"/",signal_type::DIV},
            {"<",signal_type::LT},
            {"<=",signal_type::LE},
            {">",signal_type::GT},
            {">=",signal_type::GE},
            {"==",signal_type::EQ},
            {"~=",signal_type::NEQ},
            {"=",signal_type::ASSIGN},
            {"(",signal_type::LEFT_P},
            {")",signal_type::RIGHT_P},
            {"[",signal_type::LEFT_S},
            {"]",signal_type::RIGHT_S},
            {"{",signal_type::LEFT_B},
            {"}",signal_type::RIGHT_B},
            {",", signal_type::COMMA},
            {";",signal_type::SEMICOLON},
    };

    const std::unordered_map<signal_type, std::string> signal_map::signal2string_map = {
            {signal_type::ADD,"+"},
            {signal_type::SUB,"-"},
            {signal_type::MUL,"*"},
            {signal_type::DIV,"/"},
            {signal_type::LT,"<"},
            {signal_type::LE,"<="},
            {signal_type::GT,">"},
            {signal_type::GE,">="},
            {signal_type::EQ,"=="},
            {signal_type::NEQ,"~="},
            {signal_type::ASSIGN,"="},
            {signal_type::LEFT_P,"("},
            {signal_type::RIGHT_P,")"},
            {signal_type::LEFT_S,"["},
            {signal_type::RIGHT_S,"]"},
            {signal_type::LEFT_B,"{"},
            {signal_type::RIGHT_B,"}"},
            {signal_type::COMMA,","},
            {signal_type::SEMICOLON, ";"},
    };

    /*
        IF,
        ELSE,
        INT,
        RETURN,
        VOID,
        WHILE
     */
    const std::unordered_map<std::string, keyword_type> signal_map::string2keyword_map = {
            {"if",keyword_type::IF},
            {"else",keyword_type::ELSE},
            {"int",keyword_type::INT},
            {"return",keyword_type::RETURN},
            {"void",keyword_type::VOID},
            {"while",keyword_type::WHILE},
    };

    const std::unordered_map<keyword_type, std::string> signal_map::keyword2string_map = {
            {keyword_type::IF,"if"},
            {keyword_type::ELSE,"else"},
            {keyword_type::INT,"int"},
            {keyword_type::RETURN,"return"},
            {keyword_type::VOID,"void"},
            {keyword_type::WHILE,"while"},
    };

    const std::unordered_set<char> signal_map::signals = {
            '+','-','*','/','<','=','>','~','(',')','[',']','{','}',',',';',
    };//except not_eq begin '~'

    signal_type string_convert_signal(std::string str) noexcept{
        return signal_map::string2signal_map.at(str);
    }

    std::string signal_convert_string(signal_type sig) noexcept{
        return signal_map::signal2string_map.at(sig);
    }

    keyword_type string_convert_keyword(std::string str) noexcept{
        return signal_map::string2keyword_map.at(str);
    }

    std::string keyword_convert_string(keyword_type key) noexcept{
        return signal_map::keyword2string_map.at(key);
    }
}
