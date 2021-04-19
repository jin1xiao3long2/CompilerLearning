//
// Created by XM on 2021/4/12.
//

#include <CM_Nodes.hpp>


namespace cm {

    void add_tree_info(int l, const std::string &info, std::deque<std::string> *messages) {
        std::string mes = "";
        for (int i = 0; i < l; i++)
            mes.append("  ");
        mes.append(info);
        messages->push_back(mes);
    }

    void node_program::Eval(int i, std::deque<std::string> *messages) {
        int j = i + 1;

        declaration_1->Eval(j, messages);

        for(auto dec_iter = declaration->begin(); dec_iter != declaration->end(); dec_iter++){
            (*dec_iter)->Eval(j, messages);
        }
    }

    void node_program::Pull_back(std::deque<token_base *> &tokens) {

    }

    void node_declaration::Eval(int i, std::deque<std::string> *messages) {
        int j = i + 1;

        type_specifier->Eval(j, messages);
        //ID
        declaration_s->Eval(j, messages);
    }

    void node_declaration::Pull_back(std::deque<token_base *> &tokens) {

    }

    void node_declaration_s::Eval(int i, std::deque<std::string> *messages) {
        int j = i + 1;

        if(SEMICOLON){
            //semi
        }else if(NUMBER){
            //num
        }else{
            params->Eval(j, messages);
            compound_stmt->Eval(j, messages);
        }
    }

    void node_declaration_s::Pull_back(std::deque<token_base *> &tokens) {

    }

    void node_type_specifier::Eval(int i, std::deque<std::string> *messages) {
        //type
    }

    void node_type_specifier::Pull_back(std::deque<token_base *> &tokens) {

    }

    void node_params::Eval(int i, std::deque<std::string> *messages) {
        int j = i + 1;

        if(void_param_list){
            void_param_list->Eval(j , messages);
        }else{
            int_param_list->Eval(j, messages);
        }
    }

    void node_params::Pull_back(std::deque<token_base *> &tokens) {

    }

    void node_void_param_list::Eval(int i, std::deque<std::string> *messages) {
        int j = i + 1;
        //void

        for (auto param_iter = param->begin(); param_iter != param->end(); param_iter++){
            (*param_iter)->Eval(j, messages);
        }
    }

    void node_void_param_list::Pull_back(std::deque<token_base *> &tokens) {

    }

    void node_int_param_list::Eval(int i, std::deque<std::string> *messages) {
        int j = i + 1;

        //INT
        //ID

        for (auto param_iter = param->begin(); param_iter != param->end(); param_iter++){
            (*param_iter)->Eval(j, messages);
        }
    }

    void node_int_param_list::Pull_back(std::deque<token_base *> &tokens) {

    }

    void node_param::Eval(int i, std::deque<std::string> *messages) {
        int j = i + 1;

        type_specifier->Eval(j, messages);

        //ID
    }

    void node_param::Pull_back(std::deque<token_base *> &tokens) {

    }

    void node_compound_stmt::Eval(int i, std::deque<std::string> *messages) {
        int j = i + 1;

        for (auto var_iter = var_declaration->begin(); var_iter != var_declaration->end(); var_iter++) {
            (*var_iter)->Eval(j, messages);
        }
        for (auto stmt_iter = statement->begin(); stmt_iter != statement->end(); stmt_iter++) {
            (*stmt_iter)->Eval(j, messages);
        }
    }

    void node_compound_stmt::Pull_back(std::deque<token_base *> &tokens) {

    }

    void node_var_declaration::Eval(int i, std::deque<std::string> *messages) {
        int j = i + 1;

        type_specifier->Eval(j, messages);
        //ID
        if (NUMBER) {
            //num
        }
    }

    void node_var_declaration::Pull_back(std::deque<token_base *> &tokens) {

    }

    void node_statement::Eval(int i, std::deque<std::string> *messages) {
        int j = i + 1;
        if (express_stmt) {
            express_stmt->Eval(j, messages);
        } else if (compound_stmt) {
            compound_stmt->Eval(j, messages);
        } else if (selection_stmt) {
            selection_stmt->Eval(j, messages);
        } else if (iteration_stmt) {
            iteration_stmt->Eval(j, messages);
        } else if (return_stmt) {
            return_stmt->Eval(j, messages);
        }
    }

    void node_statement::Pull_back(std::deque<token_base *> &tokens) {

    }

    void node_expression_stmt::Eval(int i, std::deque<std::string> *messages) {
        int j = i + 1;

        if (expression) {
            expression->Eval(j, messages);
        }
    }

    void node_expression_stmt::Pull_back(std::deque<token_base *> &tokens) {

    }

    void node_selection_stmt::Eval(int i, std::deque<std::string> *messages) {
        int j = i + 1;
        //if
        expression->Eval(j, messages);
        statement_1->Eval(j, messages);
        if (ELSE) {
            statement_2->Eval(j, messages);
        }
    }

    void node_selection_stmt::Pull_back(std::deque<token_base *> &tokens) {

    }

    void node_iteration_stmt::Eval(int i, std::deque<std::string> *messages) {
        int j = i + 1;
        //while
        expression->Eval(j, messages);
        statement->Eval(j, messages);
    }

    void node_iteration_stmt::Pull_back(std::deque<token_base *> &tokens) {

    }

    void node_return_stmt::Eval(int i, std::deque<std::string> *messages) {
        int j = i + 1;
        //return
        if (expression) {
            expression->Eval(j, messages);
        }
    }

    void node_return_stmt::Pull_back(std::deque<token_base *> &tokens) {

    }

    void node_expression::Eval(int i, std::deque<std::string> *messages) {
        int j = i + 1;
        if (var) {
            var->Eval(j, messages);
            expression->Eval(j, messages);
        } else {
            simple_expression->Eval(j, messages);
        }
    }

    void node_expression::Pull_back(std::deque<token_base *> &tokens) {
        if (var) {
            expression->Pull_back(tokens);
            tokens.push_front(this->EQ);
            var->Pull_back(tokens);
        } else {
            simple_expression->Pull_back(tokens);
        }
    }

    void node_var::Eval(int i, std::deque<std::string> *messages) {
        int j = i + 1;
        //ID
        this->expression->Eval(j, messages);
    }

    void node_var::Pull_back(std::deque<token_base *> &tokens) {
        if (LEFT_S) {
            tokens.push_front(this->RIGHT_S);
            this->expression->Pull_back(tokens);
            tokens.push_front(this->LEFT_S);
        }
        tokens.push_front(this->ID);
    }

    void node_simple_expression::Eval(int i, std::deque<std::string> *messages) {
        int j = i + 1;
        additive_expression_1->Eval(j, messages);
        if (relop) {
            additive_expression_2->Eval(j, messages);
        }
    }

    void node_simple_expression::Pull_back(std::deque<token_base *> &tokens) {
        if (relop) {
            this->additive_expression_2->Pull_back(tokens);
            this->relop->Pull_back(tokens);
        }

        this->additive_expression_1->Pull_back(tokens);
    }

    void node_relop::Eval(int i, std::deque<std::string> *messages) {
        //tree
    }

    void node_relop::Pull_back(std::deque<token_base *> &tokens) {
        tokens.push_front(this->RELOP);
    }

    void node_additive_expression::Eval(int i, std::deque<std::string> *messages) {
        int j = i + 1;

        term_1->Eval(j, messages);

        auto add_iter = addop->begin();
        auto term_iter = term->begin();

        for (add_iter, term_iter; add_iter != addop->end(); add_iter++, term_iter++) {
            (*add_iter)->Eval(j, messages);
            (*term_iter)->Eval(j, messages);
        }
    }

    void node_additive_expression::Pull_back(std::deque<token_base *> &tokens) {
        auto add_iter = addop->rbegin();
        auto term_iter = term->rbegin();

        for (term_iter, add_iter; term_iter != term->rend(); add_iter++, term_iter++) {
            (*term_iter)->Pull_back(tokens);
            (*add_iter)->Pull_back(tokens);
        }

        term_1->Pull_back(tokens);
    }

    void node_addop::Eval(int i, std::deque<std::string> *messages) {
        //tree
    }

    void node_addop::Pull_back(std::deque<token_base *> &tokens) {
        tokens.push_front(this->op);
    }

    void node_term::Eval(int i, std::deque<std::string> *messages) {
        int j = i + 1;

        this->factor_1->Eval(j, messages);

        auto mul_iter = mulop->begin();
        auto fac_iter = factor->begin();

        for (mul_iter, fac_iter; mul_iter != mulop->end(); mul_iter++, fac_iter++) {
            (*mul_iter)->Eval(j, messages);
            (*fac_iter)->Eval(j, messages);
        }
    }

    void node_term::Pull_back(std::deque<token_base *> &tokens) {

        auto fac_iter = this->factor->rbegin();
        auto mul_iter = this->mulop->rbegin();

        for (fac_iter, mul_iter; fac_iter != factor->rend(); fac_iter++, mul_iter++) {
            (*fac_iter)->Pull_back(tokens);
            (*mul_iter)->Pull_back(tokens);
        }

        factor_1->Pull_back(tokens);
    }

    void node_mulop::Eval(int i, std::deque<std::string> *messages) {
        //build tree
    }

    void node_mulop::Pull_back(std::deque<token_base *> &tokens) {
        tokens.push_front(this->op);
    }

    void node_factor::Eval(int i, std::deque<std::string> *messages) {
        int j = i + 1;
        if (expression) {
            expression->Eval(j, messages);
        } else if (factor_s) {
            factor_s->Eval(j, messages);
        } else {
            //tree
        }
    }

    void node_factor::Pull_back(std::deque<token_base *> &tokens) {
        if (this->LEFT_P) {
            tokens.push_front(this->RIGHT_P);
            expression->Pull_back(tokens);
            tokens.push_front(this->LEFT_P);
        } else if (this->ID) {
            this->factor_s->Pull_back(tokens);
            tokens.push_front(this->ID);
        } else {
            tokens.push_front(this->NUM);
        }
    }

    void node_factor_s::Eval(int i, std::deque<std::string> *messages) {
        int j = i + 1;
        if (expression) {
            expression->Eval(j, messages);
        } else if (args) {
            args->Eval(j, messages);
        }

    }

    void node_factor_s::Pull_back(std::deque<token_base *> &tokens) {

        if (this->LEFT_S) {
            tokens.push_front(this->RIGHT_S);
            this->expression->Pull_back(tokens);
            tokens.push_front(this->LEFT_S);
        } else if (LEFT_P) {
            tokens.push_front(this->RIGHT_P);
            this->args->Pull_back(tokens);
            tokens.push_front(this->LEFT_P);
        }

    }

    void node_args::Eval(int i, std::deque<std::string> *messages) {
        int j = i + i;

        if (expression_1) {
            expression_1->Eval(j, messages);
            for (auto iter = expression->begin(); iter != expression->end(); iter++) {
                (*iter)->Eval(j, messages);
            }
        }
    }

    void node_args::Pull_back(std::deque<token_base *> &tokens) {
        if (expression_1) {
            auto exp_iter = this->expression->rbegin();
            auto comma_iter = this->COMMA->rbegin();
            for (exp_iter, comma_iter; exp_iter != this->expression->rend(); exp_iter++, comma_iter++) {
                (*exp_iter)->Pull_back(tokens);
                tokens.push_front(*comma_iter);
            }
            expression_1->Pull_back(tokens);
        }
    }

}
