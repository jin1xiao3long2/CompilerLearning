//
// Created by XM on 2021/3/24.
//

#include <CM_Lexer.hpp>

namespace cm {
    bool Lexer::is_space(char ch) noexcept {
        return ch == ' ';
    }

    bool Lexer::is_wide_space(char ch) noexcept {
        return ch == '\t';
    }

    bool Lexer::is_newline(char ch) noexcept {
        return ch == '\n';
    }

    bool Lexer::is_not_equal_start(char ch) noexcept {
        return ch == '~';
    }

    bool Lexer::is_not_equal_end(char ch) noexcept {
        return ch == '=';
    }

    bool Lexer::is_comment_start(char ch) noexcept {
        return ch == '/';
    }

    bool Lexer::is_comment_begin(char ch) noexcept {
        return ch == '*';
    }

    bool Lexer::is_comment_end(char ch) noexcept {
        return ch == '*';
    }

    bool Lexer::is_comment_finish(char ch) noexcept {
        return ch == '/';
    }

    bool Lexer::is_letter(char ch) noexcept {
        return isalpha(ch);
    }

    void Lexer::add_token_identifier(int line, int column, std::string token_value) {
        tokens.push_back(new token_identifier(line, column, token_value));
    }

    void Lexer::add_token_number(int line, int column, std::string token_value) {
        tokens.push_back(new token_number(line, column, token_value));
    }

    void Lexer::add_token_signal(int line, int column, std::string token_value) {
        signal_type signal = string_convert_signal(token_value);
        tokens.push_back(new token_signal(line, column, signal));
    }

    void Lexer::add_token_keyword(int line, int column, std::string token_value) {
        keyword_type keyword = string_convert_keyword(token_value);
        tokens.push_back(new token_keyword(line, column, keyword));
    }

    void Lexer::add_token_error(int line, int column, std::string token_value) {
        tokens.push_back(new token_error(line, column, token_value));
    }

    inline bool Lexer::is_signal_digit(char ch) const noexcept {
        return signal_map::signals.find(ch) != signal_map::signals.end();
    }

    inline bool Lexer::is_signal(std::string str) const noexcept {
        return signal_map::string2signal_map.find(str) != signal_map::string2signal_map.end();
    }

    inline bool Lexer::is_keyword(std::string str) const noexcept {
        return signal_map::string2keyword_map.find(str) != signal_map::string2keyword_map.end();
    }


    void Lexer::Lex() {
        token_type state = token_type::null_type;
        bool pre_comment = false;
        bool pre_end_comment = false;
        bool in_not_equal = false;
        line = 1;
        column = 1;
        std::string tmp_value = "";
        int tmp_column = 1;
        for (auto p = char_buff.begin(); p != char_buff.end();) {
            if (pre_comment) {
                if (is_comment_begin(*p)) {
                    state = token_type::multiline_comment_type;
                    pre_comment = false;
                    ++p;
                    column++;
                    continue;
                } else if (is_newline(*p)) {
                    pre_comment = false;
                    add_token_signal(line, column, "/");
                    pre_comment = false;
                    ++p;
                    column++;
                    continue;
                } else if (is_comment_start(*p)) {
                    ++p;
                    add_token_signal(line, column, "/");
                    column++;
                    continue;
                } else if (is_signal_digit(*p)) {
                    tmp_value += "/";
                    pre_comment = false;
                    state = token_type::signal_type;
                    continue;
                }
            }
            if (in_not_equal) {
                in_not_equal = false;
                ++p;
                column++;
                if (is_not_equal_end(*p)) {
                    add_token_signal(line, tmp_column, "~=");
                } else {
                    add_token_error(line, tmp_column, "~");
                }
                tmp_column = 0;
                continue;
            }
            switch (state) {
                case token_type::null_type: {
                    if (is_space(*p)) {
                        ++p;
                        column++;
                        continue;
                    } else if (is_wide_space(*p)) {
                        ++p;
                        column++; //需要修改
                        continue;
                    } else if (is_newline(*p)) {
                        ++p;
                        column = 1;
                        line++;
                        continue;
                    } else if (is_comment_start(*p)) {
                        ++p;
                        column++;
                        pre_comment = true;
                        continue;
                    } else if (is_not_equal_start(*p)) {
                        ++p;
                        tmp_column = column;
                        column++;
                        in_not_equal = true;
                        continue;
                    } else if (isdigit(*p)) {
                        state = token_type::number_type;
                        tmp_column = column;
                        continue;
                    } else if (is_signal_digit(*p)) {
                        state = token_type::signal_type;
                        tmp_column = column;
                        continue;
                    } else if (is_letter(*p)) {
                        state = token_type::identifier_type;
                        tmp_column = column;
                        continue;
                    } else {
                        std::string info = "";
                        info += *p;
                        add_token_error(line, column, info);
                        ++p;
                        column++;
                        continue;
                    }
                    break;
                }
                case token_type::multiline_comment_type: {
                    if (pre_end_comment) {
                        if (is_comment_finish(*p)) {
                            pre_end_comment = false;
                            state = token_type::null_type;
                        }
                    }
                    if (is_comment_end(*p)) {
                        pre_end_comment = true;
                    }
                    if (is_newline(*p)) {
                        line += 1;
                        column = 0;
                    }
                    ++p;
                    column++;
                    break;
                }
                case token_type::number_type: {
                    if (isdigit(*p)) {
                        tmp_value += *p;
                        ++p;
                        column++;
                        continue;
                    }
                    add_token_number(line, tmp_column, tmp_value);
                    state = token_type::null_type;
                    tmp_value.clear();
                    tmp_column = 0;
                    break;
                }
                case token_type::identifier_type: {
                    if (is_letter(*p)) {
                        tmp_value += *p;
                        ++p;
                        column++;
                        continue;
                    }
                    if (is_keyword(tmp_value)) {
                        add_token_keyword(line, tmp_column, tmp_value);
                    } else {
                        add_token_identifier(line, tmp_column, tmp_value);
                    }
                    state = token_type::null_type;
                    tmp_value.clear();
                    tmp_column = 0;
                    break;
                }
                case token_type::signal_type: {
                    if(is_signal_digit(*p)){
                        tmp_value += *p;
                        ++p;
                        column++;
                        continue;
                    }
                    std::string sig = "";
                    for(auto ch : tmp_value){
                        if(!is_signal(sig + ch)){
                            add_token_signal(line, tmp_column, sig);
                            sig = ch;
                        }else{
                            sig += ch;
                        }
                        tmp_column++;
                    }
                    if(!sig.empty()){
                        add_token_signal(line, tmp_column, sig);
                    }
                    state = token_type::null_type;;
                    tmp_value.clear();
                    tmp_column = 0;
                    break;
                }
            }
        }
        if (state == token_type::multiline_comment_type)
            add_token_error(line, column, "Lack of */");
        if (tmp_value.empty())
            return;
        switch (state) {
            case token_type::number_type: {
                add_token_number(line, tmp_column, tmp_value);
                break;
            }
            case token_type::identifier_type: {
                if (is_keyword(tmp_value)) {
                    add_token_keyword(line, tmp_column, tmp_value);
                } else {
                    add_token_identifier(line, tmp_column, tmp_value);
                }
                state = token_type::null_type;
                break;
            }
            case token_type::signal_type:{
                std::string sig;
                for(auto ch : sig){
                    if(!is_signal(sig + ch)){
                        add_token_signal(line, tmp_column, sig);
                        sig = ch;
                    }else{
                        sig += ch;
                    }
                    tmp_column++;
                }
                if(!sig.empty()){
                    add_token_signal(line, tmp_column, sig);
                }

                state = token_type::null_type;;
                tmp_value.clear();
                tmp_column = 0;
                break;
            }
        }
        tmp_value.clear();
    }

}