#pragma once

#include <iostream>
#include <deque>
#include <map>
#include <set>
#include <list>


enum class signal_type {
    ADD,
    SUB,
    MUL,
    DIV,
    MOD,
    ADD_D,
    SUB_D,
    GT,
    LT,
    EQ,
    GE,
    LE,
    NE,
    AND,
    OR,
    NOT,
    AND_B,
    OR_B,
    NOT_B,
    XOR_B,
    LEFT_MOVE,
    RIGHT_MOVE,
    ASSIGN,
    ASSIGN_ADD,
    ASSIGN_SUB,
    ASSIGN_MUL,
    ASSIGN_DIV,
    ASSIGN_MOD,
    ASSIGN_AND_B,
    ASSIGN_OR_B,
    ASSIGN_XOR_B,
    ASSIGN_LEFT_MOVE,
    ASSIGN_RIGHT_MOVE,
    COMMA,
    SEMICOLON,
    LEFT_P,
    RIGHT_P,
    LEFT_B,
    RIGHT_B,
    LEFT_BR,
    RIGHT_BR,
    ARROW,
    POINT,
    COND_FRONT,
    COND_BACK,
};

enum class keyword_type {
    AUTO,
    BREAK,
    CASE,
    CHAR,
    CONST,
    CONTINUE,
    DEFAULT,
    DO,
    DOUBLE,
    ELSE,
    ENUM,
    EXTERN,
    FLOAT,
    FOR,
    GOTO,
    IF,
    INT,
    LONG,
    REGISTER,
    RETURN,
    SHORT,
    SIGNED,
    SIZEOF,
    STATIC,
    STRUCT,
    SWITCH,
    TYPEDEF,
    UNION,
    UNSIGNED,
    VOID,
    VOLATILE,
    WHILE,
    INLINE,
    RESTRICT,
};

enum class token_type {
    null,
    signal,
    keyword,
    id,
    number,
    string,
    character,
    multi_line_notes,
    single_line_notes,
};


class token_base {

protected:
    unsigned int line;

public:
    token_base() = default;

    token_base(unsigned int line) : line(line) {}

    virtual ~token_base() = default;

    virtual unsigned int get_Line() const final {
        return line;
    }

    virtual token_type get_type() const = 0;

    virtual void show(std::ostream &out) const {
        out << "< token_base >";
    }
};

class token_signal final : public token_base {

protected:
    signal_type signal;

public:
    token_signal() = delete;

    token_signal(unsigned int line, signal_type sig) : token_base(line), signal(sig) {}

    ~token_signal() = default;

    token_type get_type() const noexcept override {
        return token_type::signal;
    }

    signal_type get_signal() const noexcept {
        return signal;
    }

    void show(std::ostream &out) const override;
};

class token_keyword final : public token_base {

protected:
    keyword_type keyword;

public:
    token_keyword() = delete;

    token_keyword(int line, keyword_type kw) : token_base(line), keyword(kw) {}

    ~token_keyword() = default;

    token_type get_type() const noexcept override {
        return token_type::keyword;
    }

    keyword_type get_keyword() const noexcept {
        return keyword;
    }

    void show(std::ostream &out) const override {
        out << "< keyword,\t" << line << "\t>";
    }
};

class token_id final : public token_base {

protected:
    std::string id;

public:
    token_id() : id(""){}

    token_id(int line, std::string n) : token_base(line), id(n) {}

    ~token_id() = default;

    token_type get_type() const noexcept override {
        return token_type::id;
    }

    std::string get_id() const noexcept {
        return id;
    }

    void show(std::ostream &out) const override {
        out << "< id,\t\t" << line << ",\t" << id << "\t>";
    }
};

class token_number : public token_base {

protected:
    std::string value;

public:
    token_number() : value("0") {}

    token_number(int line, std::string v) : token_base(line), value(v) {}

    ~token_number() = default;

    token_type get_type() const noexcept override {
        return token_type::number;
    }

    std::string get_value() const noexcept {
        return value;
    }

    void show(std::ostream &out) const override {
        out << "< number,\t" << line << ",\t" << value << "\t>";
    }
};

class token_string final : public token_base {

protected:
    std::string data;

public:
    token_string() = default;

    token_string(int l, std::string d) : token_base(l), data(d) {}

    ~token_string() = default;

    token_type get_type() const noexcept override {
        return token_type::string;
    }

    std::string get_data() const noexcept {
        return data;
    }

    void show(std::ostream &out) const override {
        out << "< string,\t" << line << ",\t";
        for (auto const &e : data) {
            if (e == '\n') {
                out << "\\n";
            } else {
                out << e;
            }
        }
        out << ">";
    }
};

class token_character final : public token_base {

protected:
    char data;

public:
    token_character() = delete;

    token_character(int l, char d) : token_base(l), data(d) {}

    ~token_character() = default;

    token_type get_type() const noexcept override {
        return token_type::character;
    }

    char get_data() const noexcept {
        return data;
    }

    void show(std::ostream &out) const override {
        out << "< char,\t\t" << line << ",\t" << data << ">";
    }
};

class bracket final {

    char data;
    int line;
    int column;

public:
    bracket() = delete;

    bracket(char Data, int l, int c) : data(Data), line(l), column(c) {}

    ~bracket() = default;

    int get_line() const noexcept {
        return line;
    }

    int get_column() const noexcept {
        return column;
    }

    char get_char() const noexcept {
        return data;
    }

    char match_char() const noexcept {
        switch (data) {
            case ')':
                return '(';
            case ']':
                return '[';
            case '}':
                return '{';
            case '(':
                return ')';
            case '[':
                return ']';
            case '{':
                return '}';
            default:
                return '\0';
        }
    }

};

class error {

protected:
    int line;
    int column;
    std::string errorInfo;

public:
    error() = delete;

    error(int l, int c, std::string info) : line(l), column(c), errorInfo(info) {}

    virtual ~error() = default;

    virtual int get_Line() const final {
        return line;
    }

    virtual int get_Column() const final {
        return column;
    }

    virtual const std::string &get_ErrorInfo() const {
        return errorInfo;
    }
};

class identifier {

protected:
    int line;
    int addr;
    std::string name;

public:
    identifier() = delete;

    identifier(int l, int a, std::string n) : line(l), addr(a), name(n) {}

    virtual ~identifier() = default;

    virtual int get_Line() const final {
        return line;
    }

    virtual int get_Addr() const final {
        return addr;
    }

    virtual const std::string &get_Name() const {
        return name;
    }
};

class support_tool final {

public:
    static const std::map<std::string, signal_type> signal_map;
    static const std::map<std::string, keyword_type> keyword_map;
    static const std::map<signal_type, std::string> signal2string_map;
    static const std::map<char, char> escape_map;
    static const std::set<char> signals;
    static const std::set<char> support_digit;
};

const std::map<std::string, signal_type> support_tool::signal_map = {
        {"+",   signal_type::ADD},
        {"-",   signal_type::SUB},
        {"*",   signal_type::MUL},
        {"/",   signal_type::DIV},
        {"%",   signal_type::MOD},
        {"++",  signal_type::ADD_D},
        {"--",  signal_type::SUB_D},
        {">",   signal_type::GT},
        {"<",   signal_type::LT},
        {"==",  signal_type::EQ},
        {">=",  signal_type::GE},
        {"<=",  signal_type::LE},
        {"!=",  signal_type::NE},
        {"&&",  signal_type::AND},
        {"||",  signal_type::OR},
        {"!",   signal_type::NOT},
        {"&",   signal_type::AND_B},
        {"|",   signal_type::OR_B},
        {"~",   signal_type::NOT_B},
        {"^",   signal_type::XOR_B},
        {"<<",  signal_type::LEFT_MOVE},
        {">>",  signal_type::RIGHT_MOVE},
        {"=",   signal_type::ASSIGN},
        {"+=",  signal_type::ASSIGN_ADD},
        {"-=",  signal_type::ASSIGN_SUB},
        {"*=",  signal_type::ASSIGN_MUL},
        {"/=",  signal_type::ASSIGN_DIV},
        {"%=",  signal_type::ASSIGN_MOD},
        {"&=",  signal_type::ASSIGN_AND_B},
        {"|=",  signal_type::ASSIGN_OR_B},
        {"^=",  signal_type::ASSIGN_XOR_B},
        {"<<=", signal_type::ASSIGN_LEFT_MOVE},
        {">>=", signal_type::ASSIGN_RIGHT_MOVE},
        {",",   signal_type::COMMA},
        {";",   signal_type::SEMICOLON},
        {"(",   signal_type::LEFT_P},
        {")",   signal_type::RIGHT_P},
        {"[",   signal_type::LEFT_B},
        {"]",   signal_type::RIGHT_B},
        {"{",   signal_type::LEFT_BR},
        {"}",   signal_type::RIGHT_BR},
        {"->",  signal_type::ARROW},
        {".",   signal_type::POINT},
        {"?",   signal_type::COND_FRONT},
        {":",   signal_type::COND_BACK}
};


const std::map<signal_type, std::string> support_tool::signal2string_map = {
        {signal_type::ADD,"+"},
        {signal_type::SUB,"-"},
        {signal_type::MUL,"*"},
        {signal_type::DIV,"/"},
        {signal_type::MOD,"%"},
        {signal_type::ADD_D,"++"},
        {signal_type::SUB_D,"--"},
        {signal_type::GT,">"},
        {signal_type::LT,"<"},
        {signal_type::EQ,"=="},
        {signal_type::GE,">="},
        {signal_type::LE,"<="},
        {signal_type::NE,"!="},
        {signal_type::AND,"&&"},
        {signal_type::OR,"||"},
        {signal_type::NOT,"!"},
        {signal_type::AND_B,"&"},
        {signal_type::OR_B,"|"},
        {signal_type::NOT_B,"~"},
        {signal_type::XOR_B,"^"},
        {signal_type::LEFT_MOVE,"<<"},
        {signal_type::RIGHT_MOVE,">>"},
        {signal_type::ASSIGN,"="},
        {signal_type::ASSIGN_ADD,"+="},
        {signal_type::ASSIGN_SUB,"-="},
        {signal_type::ASSIGN_MUL,"*="},
        {signal_type::ASSIGN_DIV,"/="},
        {signal_type::ASSIGN_MOD,"%="},
        {signal_type::ASSIGN_AND_B,"&="},
        {signal_type::ASSIGN_OR_B,"|="},
        {signal_type::ASSIGN_XOR_B,"^="},
        {signal_type::ASSIGN_LEFT_MOVE,"<<="},
        {signal_type::ASSIGN_RIGHT_MOVE,">>="},
        {signal_type::COMMA,","},
        {signal_type::SEMICOLON,";"},
        {signal_type::LEFT_P,"("},
        {signal_type::RIGHT_P,")"},
        {signal_type::LEFT_B,"["},
        {signal_type::RIGHT_B,"]"},
        {signal_type::LEFT_BR,"{"},
        {signal_type::RIGHT_BR,"}"},
        {signal_type::ARROW,"->"},
        {signal_type::POINT,"."},
        {signal_type::COND_FRONT,"?"},
        {signal_type::COND_BACK,":"},
};

const std::map<std::string, keyword_type> support_tool::keyword_map = {
        {"auto",     keyword_type::AUTO},
        {"break",    keyword_type::BREAK},
        {"case",     keyword_type::CASE},
        {"char",     keyword_type::CHAR},
        {"const",    keyword_type::CONST},
        {"continue", keyword_type::CONTINUE},
        {"default",  keyword_type::DEFAULT},
        {"do",       keyword_type::DO},
        {"double",   keyword_type::DOUBLE},
        {"else",     keyword_type::ELSE},
        {"enum",     keyword_type::ENUM},
        {"extern",   keyword_type::EXTERN},
        {"float",    keyword_type::FLOAT},
        {"for",      keyword_type::FOR},
        {"goto",     keyword_type::GOTO},
        {"if",       keyword_type::IF},
        {"int",      keyword_type::INT},
        {"long",     keyword_type::LONG},
        {"register", keyword_type::REGISTER},
        {"return",   keyword_type::RETURN},
        {"short",    keyword_type::SHORT},
        {"signed",   keyword_type::SIGNED},
        {"sizeof",   keyword_type::SIZEOF},
        {"static",   keyword_type::STATIC},
        {"struct",   keyword_type::STRUCT},
        {"switch",   keyword_type::SWITCH},
        {"typedef",  keyword_type::TYPEDEF},
        {"union",    keyword_type::UNION},
        {"unsigned", keyword_type::UNSIGNED},
        {"void",     keyword_type::VOID},
        {"volatile", keyword_type::VOLATILE},
        {"while",    keyword_type::WHILE},
        {"inline",   keyword_type::INLINE},
        {"restrict", keyword_type::RESTRICT}
};

const std::map<char, char> support_tool::escape_map = {
        {'0',  '\0'},//空字符
        {'n',  '\n'},//换行符
        {'r',  '\r'}, //回车符
        {'t',  '\t'},//水平制表符
        {'v',  '\v'}, //垂直制表符
        {'a',  '\a'},//响铃
        {'b',  '\b'},//退格
        {'f',  '\f'},//换页
        {'\'', '\''},//单引号
        {'\"', '\"'},//双引号
        {'\\', '\\'},//反斜杠
        {'?',  '\?'}//问号
};

const std::set<char> support_tool::signals = {
        '+', '-', '*', '/', '%', '=', '^', '|', '~', '&', '!', '<', '>', '(', ')', '[', ']', '{', '}',
        ':', '?', ';', ',', '.'
};

const std::set<char> support_tool::support_digit{

};

class lexer final {

private:
    std::deque<token_base *> tokens;
    std::deque<error *> errors;
    std::deque<identifier *> identifiers;
    std::list<bracket> brackets;
//    需要释放空间--

    int line = 1;
    int column = 1;
    int addr = 0;

    void add_error(int line, int column, const std::string &src) { //bool: can_recovery
        errors.push_back(new error(line, column, src));
    }

    void add_identifier(int line, const std::string &name) {
        int t_addr = 0;
        auto iter = identifiers.begin();
        for (; iter != identifiers.end(); iter++) {
            t_addr++;
            if ((*iter)->get_Name() == name)
                break;
        }
        if (iter == identifiers.end()) {
            addr++;
            t_addr = addr;
        }
        identifiers.push_back(new identifier(line, t_addr, name));
    }

    void add_token_id(int line, const std::string &id_name) {
        tokens.push_back(new token_id(line, id_name));
        add_identifier(line, id_name);
    }


    void add_token_keyword(int line, const std::string &key_word) {
        keyword_type keyword = support_tool::keyword_map.at(key_word);
        tokens.push_back(new token_keyword(line, keyword));
    }

    void add_token_signal(int line, const std::string &sig) { //检测吻合
        signal_type signal = support_tool::signal_map.at(sig);
        tokens.push_back(new token_signal(line, signal));
        if (sig == "{" || sig == "}" || sig == "(" || sig == ")" || sig == "[" || sig == "]")
            add_bracket(sig[0]);
    }

    void add_token_number(int line, const std::string &number) {
        tokens.push_back(new token_number(line, number));
    }

    bool is_keyword(std::string &src) {
        return support_tool::keyword_map.count(src) > 0;
    }

    bool is_identifier(char ch) {
        return (isalpha(ch) || ch == '_');
    }

    bool is_sign(char ch) {
        return (support_tool::signals.find(ch) != support_tool::signals.end());
    }

    bool is_signal(std::string sig) {
        return (support_tool::signal_map.find(sig) != support_tool::signal_map.end());
    }

    bool is_ws(char ch) {
        return (ch == ' ' || ch == '\t');
    }

    bool is_newline(char ch) {
        return ch == '\n';
    }

    void add_bracket(char ch) {
        switch (ch) {
            case '(':
            case '[':
            case '{':
                brackets.emplace_back(ch, line, column);
                break;
            case ')':
            case ']':
            case '}':
                auto iter = brackets.end();
                for (; iter != brackets.begin(); iter--) {
                    if (iter->match_char() == ch) {
                        brackets.erase(iter);
                        break;
                    }
                }
                if (iter == brackets.begin()) {
                    brackets.emplace_back(ch, line, column);
                }
                break;
        }
    }

    void check_brackets() {
        for (auto const &e : brackets) {
            add_error(e.get_line(), e.get_column(), std::string("lack of " + e.match_char()) + " for " + e.get_char());
        }
    }

public:
    lexer() = default;

    ~lexer() = default;

    void lex(const std::string &src);

    const std::deque<token_base *> &getTokens() const {
        return this->tokens;
    }

    const std::deque<error *> &getErrors() const {
        return this->errors;
    }

    const std::deque<identifier *> &getIdentifiers() const {
        return this->identifiers;
    }
};