#include "lexer.hpp"

void token_signal::show(std::ostream &out) const {
    std::string str = support_tool::signal2string_map.at(this->signal);
    out << "< signal,\t" << line << "\t" << str << "\t>";
}


void lexer::lex(const std::string &src) {
    std::string tmp_value;
    token_type type = token_type::null;
    bool inside_str = false;
    bool inside_char = false;
    bool escape = false;
    bool pre_comment = false;
    bool expected = false;
    std::string tmp;

//        std::cout << "begin" << std::endl;
    for (auto p = src.begin(); p != src.end();) {
        if (inside_char) {
            if (escape) {
                tmp += support_tool::escape_map.at(*p);
                escape = false;
            } else if (*p == '\\') {
                escape = true;
            } else if (*p == '\'') {
                if (tmp.empty()) {
                    add_error(line, column, "Char can't be empty");
                }
                if (tmp.size() > 1) {
                    add_error(line, column, "Char can't has multiple characters");
                }//字符问题尚未解决
                tokens.push_back(new token_character(line, (char) tmp[0]));
                tmp.clear();
                inside_char = false;
            } else {
                tmp += *p;
            }
            p++;
            column++;
            continue;
        }
        if (inside_str) {
            if (escape) {
                tmp += support_tool::escape_map.at(*p);
                escape = false;
            } else if (*p == '\\') {
                escape = true;
            } else if (*p == '\"') {
                tokens.push_back(new token_string(line, tmp));
                tmp.clear();
                inside_str = false;
            } else {
                tmp += *p;
            }
            p++;
            column++;
            continue;
        }
        if (pre_comment) {
            if (*p == '*') {
                type = token_type::multi_line_notes;
//                    std::cout << "/*this is comment start" << std::endl;
                expected = true;
            } else if (*p == '/') {
//                    std::cout << "//this is comment start" << std::endl;
                type = token_type::single_line_notes;
                expected = true;
            } else if (is_sign(*p)) {
                type = token_type::signal;
                tmp += '/';
                tmp += *p;
                p++;
                column++;
                continue;
            } else {
                add_token_signal(line, "/");
            }

            pre_comment = false;

            if (expected) {
                std::string sig;
                for (auto &ch : tmp) {
                    if (is_signal(sig + ch)) {
                        sig += ch;
                    } else {
                        add_token_signal(line, sig);
                        sig = ch;
                    }
                }
                if (!sig.empty()) {
                    add_token_signal(line, sig);
                }
                tmp.clear();
                p++;
                column++;
                expected = false;
                continue;
            }
        }
//            注释+符号

        switch (type) {
            case token_type::null:
                if (*p == '\"') {
                    inside_str = true;
                    p++;
                    column++;
//
                    continue;
                } else if (*p == '\'') {
                    inside_char = true;
                    p++;
                    column++;
//                        std::cout << "check state: char" << std::endl;
                    continue;
                } else if (*p == '/') {
                    pre_comment = true;
//                        std::cout << "pre_comment, line: " << line << " , column: " << column << std::endl;
                    p++;
                    column++;
                    continue;
                } else if (is_ws(*p)) {
                    p++;
                    column++;
                    continue;
                } else if (is_newline(*p)) {
                    p++;
                    column = 1;
                    line += 1;
//                        std::cout << "new line" << std::endl;
                    continue;
                } else if (*p != '/' && is_sign(*p)) { //验证符号
                    type = token_type::signal;
//                        std::cout << "check state: signal" << std::endl;
                    continue;
                } else if (is_identifier(*p)) {
                    type = token_type::id;
//                        std::cout << "check state: id" << std::endl;
                    continue;
                } else if (isdigit(*p)) {
                    type = token_type::number;
//                        std::cout << "check state: number" << std::endl;
                    continue;
                } else {
                    add_error(line, column, "Unknown character");
                }
                break;
            case token_type::id:
                if (is_identifier(*p) || isdigit(*p)) {
                    tmp += *p;
                    p++;
                    column++;
//                        std::cout << "id: tmp:" << tmp << std::endl;
                    continue;
                }
                type = token_type::null;
                if (is_keyword(tmp)) {
                    add_token_keyword(line, tmp);
                } else {
                    add_token_id(line, tmp);
                }
                tmp.clear();
                break;
            case token_type::signal: {
                if (is_sign(*p)) {
                    if(*p == '/'){
                        pre_comment = true;
                        continue;
                    }
                    tmp += *p;
                    p++;
                    column++;
                    continue;
                }
                std::string sig;
                for (auto &ch : tmp) {
                    if (is_signal(sig + ch)) {
                        sig += ch;
                    } else {
                        add_token_signal(line, sig);
                        sig = ch;
                    }
                }
                if (!sig.empty()) {
                    add_token_signal(line, sig);
                }
                type = token_type::null;
                tmp.clear();
                break;
            }
            case token_type::number: //待完善
                if (isdigit(*p) || *p == '.') {
                    tmp += *p;
                    p++;
                    column++;
                    continue;
                }
                type = token_type::null;
                add_token_number(line, tmp);
                tmp.clear();
                break;
            case token_type::multi_line_notes:
                if (expected) {
                    if (*p == '/') {
                        type = token_type::null;
                    }
                    expected = false;
                }
                if (*p == '*') {
                    expected = true;
                } else if (*p == '\n') {
                    line += 1;
                    column = 0;
                }
                p++;
                column++;
                break;
            case token_type::single_line_notes:
                if (*p == '\n') {
                    type = token_type::null;
                    line += 1;
                    column = 0;
                }
                p++;
                column++;
                break;
        }
    }
    if(inside_str){
        add_error(line, column, "lack \"");
    }
    if(inside_char){
        add_error(line, column, "lack \'");
    }
    if(type == token_type::multi_line_notes){
        add_error(line, column, "lack */");
    }
    if(tmp.empty())
        return ;
    switch (type) {
        case token_type::id:
            if (is_keyword(tmp)) {
                add_token_keyword(line, tmp);
            } else {
                add_token_id(line, tmp);
            }
            tmp.clear();
            break;
        case token_type::signal: {
            std::string sig;
            for (auto &ch : tmp) {
                if (is_signal(sig + ch)) {
                    sig += ch;
                } else {
                    add_token_idn_signal(line, sig);
                    sig = ch;
                }
            }
            if (!sig.empty()) {
                add_token_signal(line, sig);
            }
            tmp.clear();
            break;
        }
        case token_type::number:
            add_token_number(line, tmp);
            tmp.clear();
            break;
    }
}