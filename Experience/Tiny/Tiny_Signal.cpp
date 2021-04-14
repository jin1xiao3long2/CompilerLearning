//
// Created by XM on 2021/3/24.
//

#include <Tiny_Signal.hpp>

namespace tn {


    const std::unordered_map<std::string, signal_type> signal_map::string2signal_map = {
            {"+",  signal_type::ADD},
            {"-",  signal_type::SUB},
            {"*",  signal_type::MUL},
            {"/",  signal_type::DIV},
            {"=",  signal_type::EQ},
            {"<",  signal_type::LT},
            {"(",  signal_type::LEFT_B},
            {")",  signal_type::RIGHT_B},
            {";",  signal_type::SEMICOLON},
            {":=", signal_type::ASSIGN},
    };

    const std::unordered_map<signal_type, std::string> signal_map::signal2string_map = {
            {signal_type::ADD,       "+"},
            {signal_type::SUB,       "-"},
            {signal_type::MUL,       "*"},
            {signal_type::DIV,       "/"},
            {signal_type::EQ,        "="},
            {signal_type::LT,        "<"},
            {signal_type::LEFT_B,    "("},
            {signal_type::RIGHT_B,   ")"},
            {signal_type::SEMICOLON, ";"},
            {signal_type::ASSIGN,    ":="},
    };

    const std::unordered_map<std::string, keyword_type> signal_map::string2keyword_map = {
            {"if",     keyword_type::IF},
            {"then",   keyword_type::THEN},
            {"else",   keyword_type::ELSE},
            {"end",    keyword_type::END},
            {"repeat", keyword_type::REPEAT},
            {"until",  keyword_type::UNTIL},
            {"read",   keyword_type::READ},
            {"write",  keyword_type::WRITE},
    };

    const std::unordered_map<keyword_type, std::string> signal_map::keyword2string_map = {
            {keyword_type::IF,"if"},
            {keyword_type::THEN,"then"},
            {keyword_type::ELSE,"else"},
            {keyword_type::END,"end"},
            {keyword_type::REPEAT,"repeat"},
            {keyword_type::UNTIL,"until"},
            {keyword_type::READ,"read"},
            {keyword_type::WRITE,"write"},
    };

    const std::unordered_set<char> signal_map::signals = {
            '+', '-', '*', '/', '=', '<', '(', ')', ';',
    };//except assign begin ':'

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
