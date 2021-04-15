//
// Created by XM on 2021/4/12.
//
#pragma once

#include <CM_Lexer.hpp>

namespace cm {

    //
    struct node_base {
        virtual void Eval(int) = 0;

        virtual ~node_base() = default;
    };

    struct node_program final : node_base {

        node_base *declaration_1{};
        std::deque<node_base *> *declaration{};

        void Eval(int) override;

        ~node_program() override {
            delete declaration_1;
            declaration->clear();
            delete declaration;
        }
    };

    struct node_declaration final : node_base {
        node_base *type_specifier{};
        token_base *id{};
        node_base *declaration_s;


        void Eval(int) override;

        ~node_declaration() override {
            delete type_specifier;
            delete id;
            delete declaration_s;
        }
    };

    struct node_declaration_s final : node_base {
        token_base *SEMICOLON{};
        token_base *LEFT_P{};
        token_base *RIGHT_P{};
        token_base *NUMBER{};
        token_base *LEFT_S{};
        token_base *RIGHT_S{};
        node_base *params{};
        node_base *compound_stmt{};

        void Eval(int) override;

        ~node_declaration_s() override {
            delete SEMICOLON;
            delete LEFT_P;
            delete RIGHT_P;
            delete NUMBER;
            delete LEFT_S;
            delete RIGHT_S;
            delete params;
            delete compound_stmt;
        }
    };

    struct node_type_specifier final : node_base {
        token_base *INT{};
        token_base *VOID{};

        void Eval(int) override;

        ~node_type_specifier() override {
            delete INT;
            delete VOID;
        }
    };

    struct node_params final : node_base {
        node_base *void_param_list{};
        node_base *int_param_list{};

        void Eval(int) override;

        ~node_params() override {
            delete void_param_list;
            delete int_param_list;
        }
    };

    struct node_void_param_list final : node_base {
        token_base *VOID{};
        token_base *ID{};
        token_base *LEFT_S{};
        token_base *RIGHT_S{};
        token_base *SEMICOLON{};
        std::deque<node_base *> *param{};

        void Eval(int) override;

        ~node_void_param_list() override {
            delete VOID;
            delete ID;
            delete LEFT_S;
            delete RIGHT_S;
            delete SEMICOLON;
            param->clear();
            delete param;
        }
    };

    struct node_int_param_list final : node_base {
        token_base *INT{};
        token_base *ID{};
        token_base *LEFT_S{};
        token_base *RIGHT_S{};
        token_base *SEMICOLON{};
        std::deque<node_base *> *param{};

        void Eval(int) override;

        ~node_int_param_list() override {
            delete INT;
            delete ID;
            delete LEFT_S;
            delete RIGHT_S;
            delete SEMICOLON;
            param->clear();
            delete param;
        }
    };

    struct node_param final : node_base {
        node_base *type_specifier{};
        token_base *ID{};
        token_base *LEFT_S{};
        token_base *RIGHT_S{};

        void Eval(int) override;

        ~node_param() override {
            delete type_specifier;
            delete ID;
            delete LEFT_S;
            delete RIGHT_S;
        }
    };

    struct node_compound_stmt final : node_base {
        token_base *LEFT_B{};
        std::deque<node_base *> *var_declaration{};
        std::deque<node_base *> *statement{};
        token_base *RIGHT_B{};

        void Eval(int) override;

        ~node_compound_stmt() override {
            delete LEFT_B;
            delete RIGHT_B;
            var_declaration->clear();
            delete var_declaration;
            statement->clear();
            delete statement;
        }
    };

    struct node_statement final : node_base {
        node_base *express_stmt{};
        node_base *compound_stmt{};
        node_base *selection_stmt{};
        node_base *iteration_stmt{};
        node_base *return_stmt{};

        void Eval(int) override;

        ~node_statement() override {
            delete express_stmt;
            delete compound_stmt;
            delete selection_stmt;
            delete iteration_stmt;
            delete return_stmt;
        }
    };

    struct node_expression_stmt final : node_base {
        node_base *expression{};
        token_base *SEMICOLON{};

        void Eval(int) override;

        ~node_expression_stmt() override {
            delete expression;
            delete SEMICOLON;
        }
    };

    struct node_selection_stmt final : node_base {
        token_base *IF{};
        token_base *LEFT_P{};
        node_base *expression{};
        token_base *RIGHT_P{};
        node_base *statement_1{};
        token_base *ELSE{};
        node_base *statement_2{};

        void Eval(int) override;

        ~node_selection_stmt() override {
            delete IF;
            delete LEFT_P;
            delete expression;
            delete RIGHT_P;
            delete statement_1;
            delete ELSE;
            delete statement_2;
        }
    };

    struct node_iteration_stmt final : node_base {
        token_base *WHILE{};
        token_base *LEFT_P{};
        node_base *expression{};
        token_base *RIGHT_P{};
        node_base *statement{};

        void Eval(int) override;

        ~node_iteration_stmt() override {
            delete WHILE;
            delete LEFT_P;
            delete expression;
            delete RIGHT_P;
            delete statement;
        }
    };

    struct node_return_stmt final : node_base {
        token_base *RETURN{};
        node_base *expression{};

        void Eval(int) override;

        ~node_return_stmt() override {
            delete RETURN;
            delete expression;
        }
    };

    struct node_expression final : node_base {
        node_base *var{};
        token_base *EQ{};
        node_base *expression{};
        node_base *simple_expression{};

        void Eval(int) override;

        ~node_expression() override {
            delete var;
            delete EQ;
            delete expression;
            delete simple_expression;
        }
    };

    struct node_var final : node_base {
        token_base *ID{};
        token_base *LEFT_S{};
        node_base *expression{};
        token_base *RIGHT_S{};

        void Eval(int) override;

        ~node_var() override {
            delete ID;
            delete LEFT_S;
            delete expression;
            delete RIGHT_S;
        }
    };

    struct node_simple_expression final : node_base {
        node_base *additive_expression_1{};
        node_base *relop{};
        node_base *additive_expression_2{};

        void Eval(int) override;

        ~node_simple_expression() override {
            delete additive_expression_1;
            delete relop;
            delete additive_expression_2;
        }
    };

    struct node_relop final : node_base {
        token_base *RELOP{};

        void Eval(int) override;

        ~node_relop() override {
            delete RELOP;
        }
    };

    struct node_additive_expression final : node_base{
        node_base *term_1{};
        std::deque<node_base *> *addop{};
        std::deque<node_base *> *term{};

        void Eval(int) override;

        ~node_additive_expression() override{
            delete term_1;
            addop->clear();
            delete addop;
            term->clear();
            delete term;
        }
    };

    struct node_term final : node_base{
        node_base *factor_1{};
        std::deque<node_base *> *mulop{};
        std::deque<node_base *> *factor{};

        void Eval(int) override;

        ~node_term() override{
            delete factor_1;
            mulop->clear();
            delete mulop;
            factor->clear();
            delete factor;
        }
    };

    struct node_factor final : node_base{
        token_base *LEFT_P{};
        node_base *expression{};
        token_base *RIGHT_P{};
        token_base *ID{};
        node_base *factor_s{};
        token_base *NUM{};

        void Eval(int) override;

        ~node_factor() override{
            delete LEFT_P;
            delete expression;
            delete RIGHT_P;
            delete ID;
            delete factor_s;
            delete NUM;
        }
    };

    struct node_factor_s final : node_base{
        token_base *LEFT_S{};
        node_base *expression{};
        token_base *RIGHT_S{};
        token_base *LEFT_P{};
        node_base *args{};
        token_base *RIGHT_P{};
        node_base *empty{};

        void Eval(int) override;

        ~node_factor_s() override{
            delete LEFT_S;
            delete expression;
            delete RIGHT_S;
            delete LEFT_P;
            delete args;
            delete RIGHT_P;
            delete empty;
        }
    };

    struct node_args final : node_base{
        node_base *expression_1{};
        std::deque<token_base *> *SEMICOLON{};
        std::deque<node_base *> *expression{};
        node_base *empty{};

        void Eval(int) override;

        ~node_args() override{
            delete expression_1;
            SEMICOLON->clear();
            delete SEMICOLON;
            expression->clear();
            delete expression;
            delete empty;
        }
    };



}