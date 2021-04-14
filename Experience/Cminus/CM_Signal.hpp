#pragma once

//
// Created by XM on 2021/3/24.
//

#pragma once
#include <unordered_map>
#include <unordered_set>
#include <iostream>


namespace cm{

    enum class token_type {
        signal_type,
        keyword_type,
        number_type,
        identifier_type,
        null_type,
        multiline_comment_type,
        error_type,
    };

    enum class signal_type {
        ADD, SUB, MUL, DIV,
        LT, LE, GT, GE,
        EQ, NEQ,
        ASSIGN,
        LEFT_P, RIGHT_P,
        LEFT_S, RIGHT_S,
        LEFT_B, RIGHT_B,
        COMMA,SEMICOLON,
    };

    enum class keyword_type {
        IF,
        ELSE,
        INT,
        RETURN,
        VOID,
        WHILE
    };

    struct signal_map final{
        const static std::unordered_map<std::string, signal_type> string2signal_map;
        const static std::unordered_map<signal_type, std::string> signal2string_map;
        const static std::unordered_map<std::string, keyword_type> string2keyword_map;
        const static std::unordered_map<keyword_type, std::string> keyword2string_map;
        const static std::unordered_set<char> signals;

    };

    signal_type string_convert_signal(std::string) noexcept;

    std::string signal_convert_string(signal_type) noexcept;

    keyword_type string_convert_keyword(std::string) noexcept;

    std::string keyword_convert_string(keyword_type) noexcept;


    class token_base {

    protected:
        unsigned int line;
        unsigned int column;

    public:
        token_base() = default;

        token_base(int l, int c) : line(l), column(c) {}

        virtual token_type get_type() const = 0;

        virtual ~token_base() = default;

        virtual std::string get_string() const = 0;

        virtual std::string get_show_info() const {
            return std::string(this->get_string());
        }

        int get_line() const { return line; }

        int get_column() const { return column; }
    };

    class token_signal final : public token_base {

    protected:
        signal_type signal;

    public:
        token_signal(int l, int c, signal_type s) : token_base(l, c), signal(s) {}

        token_signal(signal_type s) : signal(s) {}

        token_type get_type() const override {
            return token_type::signal_type;
        }

        ~token_signal() = default;

        std::string get_string() const override{
            return signal_convert_string(signal);
        }

        signal_type get_value() const{
            return signal;
        }

    };

    class token_keyword final : public token_base{

    protected:
        keyword_type keyword;

    public:
        token_keyword(int l, int c, keyword_type k) : token_base(l, c), keyword(k) {}

        token_keyword(keyword_type k) : keyword(k) {}

        token_type get_type() const override {
            return token_type::keyword_type;
        }

        ~token_keyword() = default;

        std::string get_string() const override{
            return keyword_convert_string(keyword);
        }

        keyword_type get_value() const{
            return keyword;
        }

        std::string  get_show_info() const override{
            return std::string("reserved word:" + this->get_string());
        }
    };

    class token_number final: public token_base{

    protected:
        std::string number;

    public:
        token_number(int l, int c, std::string n): token_base(l, c), number(n) {}

        token_number(std::string n): number(n) {}

        token_type get_type() const override{
            return token_type::number_type;
        }

        std::string get_string() const override{
            return number;
        }

        std::string get_value(){
            return number;
        }

        ~token_number() = default;

        std::string  get_show_info() const override{
            return std::string("Num, val= " + this->get_string());
        }
    };

    class token_identifier final : public token_base{

    protected:
        std::string name;

    public:
        token_identifier(int l, int c, std::string n): token_base(l, c), name(n) {}

        token_type get_type() const override{
            return token_type::identifier_type;
        }

        ~token_identifier() = default;

        std::string get_string() const override{
            return name;
        }

        std::string get_value() const{
            return name;
        }

        std::string  get_show_info() const override{
            return std::string("ID,name= " + this->get_string());
        }
    };

    class token_error final: public token_base{

    protected:
        std::string info;

    public:
        token_error(int l, int c, std::string n): token_base(l, c), info(n) {}

        token_type get_type() const override{
            return token_type::error_type;
        }

        std::string get_string() const override{
            return info;
        }

        std::string get_value(){
            return info;
        }

        ~token_error() = default;

//        id
        std::string  get_show_info() const override{
            return std::string("ERROR:" + this->get_string() + "2018141461179");
        }
    };
}