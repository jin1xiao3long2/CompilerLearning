//
// Created by XM on 2021/3/24.
//

#pragma once

#include <string>
#include <Tiny_Signal.hpp>
#include <deque>

namespace tn {

    class Lexer final {

    private:
        std::deque<token_base *> tokens;
        std::string char_buff;
        int line;
        int column;

        bool is_space(char ch) noexcept;

        bool is_wide_space(char ch) noexcept;

        bool is_newline(char ch) noexcept;

        bool is_letter(char ch) noexcept;

        bool is_comment_start(char ch) noexcept;

        bool is_comment_end(char ch) noexcept;

        bool is_assign_start(char ch) noexcept;

        bool is_assign_end(char ch) noexcept;

        void add_token_signal(int line, int column, std::string token_value);

        void add_token_identifier(int line, int column, std::string token_value);

        void add_token_number(int line, int column, std::string token_value);

        void add_token_keyword(int line, int column, std::string token_value);

        void add_token_error(int line, int column, std::string token_value);

        bool is_signal_digit(char) const noexcept;

        bool is_keyword(std::string) const noexcept;

        bool is_signal(std::string) const noexcept;


    public:
        Lexer() = delete;

        Lexer(std::string str) : char_buff(str) {}

        Lexer(const Lexer &) = delete;

        ~Lexer() = default;

        void Lex();

        const std::deque<token_base *> &getTokens() const {
            return tokens;
        }
    };

}


