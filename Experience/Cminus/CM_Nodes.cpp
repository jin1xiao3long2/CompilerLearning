//
// Created by XM on 2021/4/12.
//

#include <CM_Nodes.hpp>


namespace cm{

    void node_program::Eval(int, std::deque<std::string> *) {

    }

    void node_program::Pull_back(std::deque<token_base *> &) {

    }

    void node_declaration::Eval(int, std::deque<std::string> *) {

    }

    void node_declaration::Pull_back(std::deque<token_base *> &) {

    }

    void node_declaration_s::Eval(int, std::deque<std::string> *) {

    }

    void node_declaration_s::Pull_back(std::deque<token_base *> &) {

    }

    void node_type_specifier::Eval(int, std::deque<std::string> *) {

    }

    void node_type_specifier::Pull_back(std::deque<token_base *> &) {

    }

    void node_params::Eval(int, std::deque<std::string> *) {

    }

    void node_params::Pull_back(std::deque<token_base *> &) {

    }

    void node_void_param_list::Eval(int, std::deque<std::string> *) {

    }

    void node_void_param_list::Pull_back(std::deque<token_base *> &) {

    }

    void node_int_param_list::Eval(int, std::deque<std::string> *) {

    }

    void node_int_param_list::Pull_back(std::deque<token_base *> &) {

    }

    void node_param::Eval(int, std::deque<std::string> *) {

    }

    void node_param::Pull_back(std::deque<token_base *> &) {

    }

    void node_compound_stmt::Eval(int, std::deque<std::string> *) {

    }

    void node_compound_stmt::Pull_back(std::deque<token_base *> &) {

    }

    void node_var_declaration::Eval(int, std::deque<std::string> *) {

    }

    void node_var_declaration::Pull_back(std::deque<token_base *> &) {

    }

    void node_statement::Eval(int, std::deque<std::string> *) {

    }

    void node_statement::Pull_back(std::deque<token_base *> &) {

    }

    void node_expression_stmt::Eval(int, std::deque<std::string> *) {

    }

    void node_expression_stmt::Pull_back(std::deque<token_base *> &) {

    }

    void node_selection_stmt::Eval(int, std::deque<std::string> *) {

    }

    void node_selection_stmt::Pull_back(std::deque<token_base *> &) {

    }

    void node_iteration_stmt::Eval(int, std::deque<std::string> *) {

    }

    void node_iteration_stmt::Pull_back(std::deque<token_base *> &) {

    }

    void node_return_stmt::Eval(int, std::deque<std::string> *) {

    }

    void node_return_stmt::Pull_back(std::deque<token_base *> &) {

    }

    void node_expression::Eval(int, std::deque<std::string> *) {

    }

    void node_expression::Pull_back(std::deque<token_base *> &) {

    }

    void node_var::Eval(int, std::deque<std::string> *) {

    }

    void node_var::Pull_back(std::deque<token_base *> &) {

    }

    void node_simple_expression::Eval(int, std::deque<std::string> *) {

    }

    void node_simple_expression::Pull_back(std::deque<token_base *> &) {

    }

    void node_relop::Eval(int, std::deque<std::string> *) {

    }

    void node_relop::Pull_back(std::deque<token_base *> &) {

    }

    void node_additive_expression::Eval(int, std::deque<std::string> *) {

    }

    void node_additive_expression::Pull_back(std::deque<token_base *> &) {

    }

    void node_addop::Eval(int, std::deque<std::string> *) {

    }

    void node_addop::Pull_back(std::deque<token_base *> &) {

    }

    void node_term::Eval(int, std::deque<std::string> *) {

    }

    void node_term::Pull_back(std::deque<token_base *> &) {

    }

    void node_mulop::Eval(int, std::deque<std::string> *) {

    }

    void node_mulop::Pull_back(std::deque<token_base *> &) {

    }

    void node_factor::Eval(int, std::deque<std::string> *) {

    }

    void node_factor::Pull_back(std::deque<token_base *> &) {

    }

    void node_factor_s::Eval(int, std::deque<std::string> *) {

    }

    void node_factor_s::Pull_back(std::deque<token_base *> &) {

    }

    void node_args::Eval(int, std::deque<std::string> *) {

    }

    void node_args::Pull_back(std::deque<token_base *> &) {
        while(!expression->empty()){
            expression->end()
        }
    }


}
