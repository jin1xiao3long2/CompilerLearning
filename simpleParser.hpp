//
// Created by XM on 2021/3/18.
//
#pragma once


#include <math.h>
#include "lexer.cpp"
#include <sstream>

/*
unit ::= expr ;

expr ::= term ('+' term)+
       | term ('-' term)+
       | term
       ;

term ::= factor ('*' factor)+
       | factor ('/' factor)+
       | factor ('%' factor)+
       | factor
       ;

factor ::= '(' expr ')'
         | identifier '(' expr ')'
         | Num
         ;

Num ::= Integer
      | Float
      ;

Integer ::= sign digit+
          | digit+
          ;

Float ::= sign digit+ '.' digit+
        | digit+ '.' digit+
        ;

digit ::= 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 ;

sign ::= + | -;
*/

int build_tree_version(int i, std::string info) {
    for (int v = 0; v < i; v++) {
        std::cout << '\t';
    }
    std::cout << info << std::endl;
    return i + 1;
}

class Num;

std::ostream &operator<<(std::ostream &out, const Num &num);

class Num final {

private:
    token_number number;

public:
    Num(token_number Num) : number(Num) {
        check_simplify();
    }

    Num(const Num &n) : number(n.number) {
        check_simplify();
    }

    Num() {
        check_simplify();
    }

    ~Num() = default;

    token_number get_number() const { return this->number; }

    void check_simplify(){
        std::ostringstream oss;
        std::string str = number.get_value();
        double n = std::stod(str);
        oss << n;
        number = token_number(number.get_Line(), oss.str());
    }

    Num operator+(const Num &rhs) const {
        return Num(token_number(0, std::to_string(std::stod(number.get_value()) + std::stod(rhs.number.get_value()))));
    }

    Num operator-(const Num &rhs) const {
        return Num(token_number(0, std::to_string(std::stod(number.get_value()) - std::stod(rhs.number.get_value()))));
    }

    Num operator*(const Num &rhs) const {
        return Num(token_number(0, std::to_string(std::stod(number.get_value()) * std::stod(rhs.number.get_value()))));
    }

    Num operator/(const Num &rhs) const {
        return Num(token_number(0, std::to_string(std::stod(number.get_value()) / std::stod(rhs.number.get_value()))));
    }

    Num operator%(const Num &rhs) const {  //有缺陷
        return Num(token_number(0, std::to_string(std::stoi(number.get_value()) % std::stoi(rhs.number.get_value()))));
    }

};

std::ostream &operator<<(std::ostream &out, const Num &num) {
    out << num.get_number().get_value();
    return out;
}

class ID final {

private:
    token_id id;
    Num num;

public:
    ID(token_id i) : id(i) {}

    void setNum(Num n) {
        num = n;
    }

    Num Eval(int i) {

        double d = std::stod(num.get_number().get_value());
        if (id.get_id() == "cos") {
            return Num(token_number(0, std::to_string(std::cos(d))));
        } else if (id.get_id() == "sin") {
            return Num(token_number(0, std::to_string(std::sin(d))));
        } else if (id.get_id() == "tan") {
            return Num(token_number(0, std::to_string(std::tan(d))));
        } else {
            throw std::runtime_error(
                    std::string("undefined function name at line " + std::to_string(id.get_Line()) + "."));
        }
    }

    const token_id &getId() const {
        return id;
    }

    const Num &getNum() const {
        return num;
    }
};


struct Node_base {

    virtual Num Eval(int i) = 0;

    virtual ~Node_base() = default;
};

struct Factor final : public Node_base {
    ID *id{};
    Node_base *expr{};
    Num num;

    Num Eval(int i) override {
        build_tree_version(i, "Factor");
        int j = ++i;
        if (!expr) {
            build_tree_version(j, "Num " + num.get_number().get_value());
            return num;
        } else {
            if (!id) {
                return expr->Eval(j);
            } else {
                build_tree_version(j, "ID " + id->getId().get_id());
                Num n = expr->Eval(j);
                id->setNum(n);
                return id->Eval(j);
            }
        }
    }

    ~Factor() {
        delete id;
        delete expr;
    }
};

struct Term final : public Node_base {
    Node_base *lhs{};
    Node_base *rhs{};
    signal_type op;

    Num Eval(int i) override {
        build_tree_version(i, "Term");
        int j = ++i;
        Num l = lhs->Eval(j);
        if (rhs) {
            std::string show_op = support_tool::signal2string_map.at(this->op);
            build_tree_version(j, "OP " + show_op);
            Num r = rhs->Eval(j);
            switch (op) {
                case signal_type::MUL:
                    return Num(l * r);
                case signal_type::DIV:
                    return Num(l / r);
                case signal_type::MOD:
                    return Num(l % r);
            }
            return r;
        }
        return l;
    }

    ~Term() {
        delete lhs;
        delete rhs;
    }
};

struct Expr final : public Node_base {
    Node_base *lhs{};
    Node_base *rhs{};
    signal_type op;

    Num Eval(int i) override {
        build_tree_version(i, "Expr");
        int j = ++i;
        Num l = lhs->Eval(j);
        if (rhs) {
            std::string show_op = support_tool::signal2string_map.at(this->op);
            build_tree_version(j, "OP " + show_op);
            Num r = rhs->Eval(j);
            switch (op) {
                case signal_type::ADD:
                    return Num(l + r);
                case signal_type::SUB:
                    return Num(l - r);
            }
        }
        return l;
    }

    ~Expr() {
        delete lhs;
        delete rhs;
    }
};

struct Unit final : public Node_base {
    Node_base *expr{};

    Num Eval(int i) override {
        build_tree_version(i, "Unit");
        int j = ++i;
        return expr->Eval(j);
    }

    ~Unit() {
        delete expr;
    }

};

class Parser final {

private:

    std::deque<token_base *> tokens;

    bool Finished() {
        return tokens.empty();
    }

    void Ensure() {
        if (Finished()) {
            throw std::runtime_error("Unexpected End");
        }
    }

    token_type peek() {
        Ensure();
        return tokens.front()->get_type();
    }

    signal_type peek_signal() {
        Ensure();
        return reinterpret_cast<token_signal *>(tokens.front())->get_signal();
    }

    void consume() {
        Ensure();
        tokens.pop_front();
    }

    void consume_signal_type(signal_type type) {
        if (peek_signal() != type) {
            throw std::runtime_error(std::string("unexpected token"));
        }
        consume();
    };

    signal_type consume_op() {
        Ensure();
        switch (reinterpret_cast<token_signal *>(tokens.front())->get_signal()) {
            case signal_type::ADD:
            case signal_type::SUB:
            case signal_type::MUL:
            case signal_type::DIV: {
                signal_type type = reinterpret_cast<token_signal *>(tokens.front())->get_signal();
                tokens.pop_front();
                return type;
            }
            default: {
                throw std::runtime_error("unexpected operator");
            }
        }
    }

    Num consume_num() {
        if (peek() != token_type::number) {
            throw std::runtime_error(std::string("expected Num"));
        }
        Num num = Num(*static_cast<token_number *>(tokens.front()));
        consume();
        return num;
    }

    ID *consume_id() {
        if (peek() != token_type::id) {
            throw std::runtime_error(std::string("expected functionName"));
        }
        ID *id = new ID(*static_cast<token_id *>(tokens.front()));
        consume();
        return id;
    }


    Factor *ParseFactor() {
        Factor *factor = new Factor;
        switch (peek()) {
            case token_type::signal: {
                switch (peek_signal()) {
                    case signal_type::LEFT_P:
                        consume();
                        factor->expr = ParseExpr();
                        consume_signal_type(signal_type::RIGHT_P);
                        break;
                    default:
                        throw std::runtime_error(std::string("wrong grammar"));
                }
                break;
            }
            case token_type::number: {
                factor->num = consume_num();
                break;
            }
            case token_type::id: {
                factor->id = consume_id();
                switch (peek_signal()) {
                    case signal_type::LEFT_P:
                        consume();
                        factor->expr = ParseExpr();
                        consume_signal_type(signal_type::RIGHT_P);
                        break;
                    default:
                        throw std::runtime_error(std::string("wrong grammar"));
                }
                break;
            }
            default: {
                throw std::runtime_error(std::string("expected '(' or Number."));
            }
        }
        return factor;
    }

    Term *ParseTerm() {
        Term *term = new Term;
        term->lhs = ParseFactor();
        bool bw = false;
        while (!Finished()) {
            switch (peek()) {
                case token_type::signal: {
                    switch (peek_signal()) {
                        case signal_type::MUL:
                        case signal_type::DIV:
                        case signal_type::MOD: {
                            term->op = consume_op();
                            term->rhs = ParseFactor();
                            Term *next = new Term;
                            next->lhs = term;
//                            next->rhs = nullptr;
                            term = next;
                            break;
                        }
                        default: {
                            bw = true;
                            break;
                        }
                    }
                    break;
                }
                default: {
                    bw = true;
                    break;
                }
            }
            if (bw)
                break;
        }
        return term;
    }


    Expr *ParseExpr() {
        Expr *expr = new Expr;
        expr->lhs = ParseTerm();
        bool bw = false;
        while (!Finished()) {
            switch (peek()) {
                case token_type::signal: {
                    switch (peek_signal()) {
                        case signal_type::ADD:
                        case signal_type::SUB: {
                            expr->op = consume_op();
                            expr->rhs = ParseTerm();
                            Expr *next = new Expr;
                            next->lhs = expr;
//                            next->rhs = nullptr;
                            expr = next;
                            break;
                        }
                        default: {
                            bw = true;
                            break;
                        }
                    }
                    break;
                }
                default: {
                    bw = true;
                    break;
                }
            }
            if (bw)
                break;
        }
        return expr;
    }

public:
    Unit *ParseUnit();

    explicit Parser(std::deque<token_base *> tokens) : tokens(std::move(tokens)) {}
};

