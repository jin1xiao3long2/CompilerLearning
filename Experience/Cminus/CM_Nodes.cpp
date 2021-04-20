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
        std::cerr << mes << std::endl;
        if(messages)
            messages->push_back(mes);
    }

    void support_recur_term(node_base* node, std::deque<node_base *> *ops, std::deque<node_base*> *nodes , int i, std::deque<std::string>* message){
        int j = i + 1;
        if(ops->empty()){
            node->Eval(i, message);
            return ;
        }
        node_base* op_back = ops->back();
        node_base* node_back = nodes->back();
        ops->pop_back();
        nodes->pop_back();
        op_back->Eval(i, message);

        support_recur_term(node, ops, nodes, j, message);
        node_back->Eval(j, message);
        nodes->push_back(node_back);
        ops->push_back(op_back);
        return ;
    }

    void node_program::Eval(int i, std::deque<std::string> *messages) {

        declaration_1->Eval(i, messages);

        for (auto dec_iter = declaration->begin(); dec_iter != declaration->end(); dec_iter++) {
            (*dec_iter)->Eval(i, messages);
        }
    }

    void node_program::Pull_back(std::deque<token_base *> &tokens) {
//
    }

    void node_declaration::Eval(int i, std::deque<std::string> *messages) {
        int j = i + 1;

        if (reinterpret_cast<node_declaration_s *>(declaration_s)->params) {
            add_tree_info(i, "FuncK", messages);
            type_specifier->Eval(j, messages);
            add_tree_info(j, std::string("IdK: " + id->get_string()), messages);
            declaration_s->Eval(j, messages);
        } else if (reinterpret_cast<node_declaration_s *>(declaration_s)->NUMBER) {
            add_tree_info(i, "ConstK", messages);
            type_specifier->Eval(j, messages);
            add_tree_info(j, std::string("IdK: " + id->get_string()), messages);
            declaration_s->Eval(j, messages);
        } else {
            type_specifier->Eval(j, messages);
            add_tree_info(j, std::string("IdK: " + id->get_string()), messages);
            declaration_s->Eval(j, messages);
        }


    }

    void node_declaration::Pull_back(std::deque<token_base *> &tokens) {
//
    }

    void node_declaration_s::Eval(int i, std::deque<std::string> *messages) {
        int j = i + 1;

        if (SEMICOLON) {

        } else if (NUMBER) {
            add_tree_info(i, NUMBER->get_string(), messages);
        } else {
            add_tree_info(i, "ParamsK", messages);
            params->Eval(i, messages);
            compound_stmt->Eval(i, messages);
        }
    }

    void node_declaration_s::Pull_back(std::deque<token_base *> &tokens) {
//
    }

    void node_type_specifier::Eval(int i, std::deque<std::string> *messages) {
        std::string str = "";
        if (this->TYPE->get_string() == "int") {
            str = "IntK";
        } else {
            str = "VoidK";
        }
        add_tree_info(i, str, messages);
    }

    void node_type_specifier::Pull_back(std::deque<token_base *> &tokens) {
//
    }

    void node_params::Eval(int i, std::deque<std::string> *messages) {
        int j = i + 1;
        if (void_param_list) {
            void_param_list->Eval(j, messages);
        } else {
            int_param_list->Eval(j, messages);
        }
    }

    void node_params::Pull_back(std::deque<token_base *> &tokens) {
//
    }

    void node_void_param_list::Eval(int i, std::deque<std::string> *messages) {
        int j = i + 1;
        //void
        add_tree_info(j, "VoidK", messages);
        if (ID){
            add_tree_info(j, "Idk" + ID->get_string(), messages);
        }
        for (auto param_iter = param->begin(); param_iter != param->end(); param_iter++) {
           (*param_iter)->Eval(j, messages);
        }
    }

    void node_void_param_list::Pull_back(std::deque<token_base *> &tokens) {
//
    }

    void node_int_param_list::Eval(int i, std::deque<std::string> *messages) {
        int j = i + 1;
        add_tree_info(i, "ParamK", messages);
        add_tree_info(j, "IntK", messages);
        //INT
        add_tree_info(j, "Idk: " + ID->get_string(), messages);
        //ID
        if(LEFT_S)
            add_tree_info(j, "Idk:", messages);

        for (auto param_iter = param->begin(); param_iter != param->end(); param_iter++) {
            (*param_iter)->Eval(i, messages);
        }
    }

    void node_int_param_list::Pull_back(std::deque<token_base *> &tokens) {
//
    }

    void node_param::Eval(int i, std::deque<std::string> *messages) {
        int j = i + 1;

        add_tree_info(i, "ParamK", messages);

        type_specifier->Eval(j, messages);
        //ID
        add_tree_info(j, "IdK: " + ID->get_string(), messages);
    }

    void node_param::Pull_back(std::deque<token_base *> &tokens) {
//
    }

    void node_compound_stmt::Eval(int i, std::deque<std::string> *messages) {
        int j = i + 1;
        add_tree_info(i, "CompK", messages);
        for (auto var_iter = var_declaration->begin(); var_iter != var_declaration->end(); var_iter++) {
            (*var_iter)->Eval(j, messages);
        }
        for (auto stmt_iter = statement->begin(); stmt_iter != statement->end(); stmt_iter++) {
            (*stmt_iter)->Eval(j, messages);
        }
    }

    void node_compound_stmt::Pull_back(std::deque<token_base *> &tokens) {
//
    }

    void node_var_declaration::Eval(int i, std::deque<std::string> *messages) {
        int j = i + 1;
        add_tree_info(i, "Var_DeclK", messages);
        type_specifier->Eval(j, messages);
        //ID

        if (NUMBER) {
            //num
            add_tree_info(j, "Array_DeclK", messages);
            add_tree_info(j + 1, "IdK: " + ID->get_string(), messages);
            add_tree_info(j + 1, "ConstK: " + NUMBER->get_string(), messages);
        }else{
            add_tree_info(j, "IdK: " + ID->get_string(), messages);
        }
    }

    void node_var_declaration::Pull_back(std::deque<token_base *> &tokens) {
//
    }

    void node_statement::Eval(int i, std::deque<std::string> *messages) {
        if (express_stmt) {
            express_stmt->Eval(i, messages);
        } else if (compound_stmt) {
            compound_stmt->Eval(i, messages);
        } else if (selection_stmt) {
            selection_stmt->Eval(i, messages);
        } else if (iteration_stmt) {
            iteration_stmt->Eval(i, messages);
        } else if (return_stmt) {
            return_stmt->Eval(i, messages);
        }
    }

    void node_statement::Pull_back(std::deque<token_base *> &tokens) {
//
    }

    void node_expression_stmt::Eval(int i, std::deque<std::string> *messages) {
        if (expression) {
            expression->Eval(i, messages);
        }
    }

    void node_expression_stmt::Pull_back(std::deque<token_base *> &tokens) {
//
    }

    void node_selection_stmt::Eval(int i, std::deque<std::string> *messages) {
        int j = i + 1;
        //if
        add_tree_info(i, "If", messages);
        expression->Eval(j, messages);

        statement_1->Eval(j, messages);
        if (ELSE) {
            statement_2->Eval(j, messages);
        }
    }

    void node_selection_stmt::Pull_back(std::deque<token_base *> &tokens) {
//
    }

    void node_iteration_stmt::Eval(int i, std::deque<std::string> *messages) {
        int j = i + 1;
        //while
        add_tree_info(i, "While", messages);
        expression->Eval(j, messages);
        statement->Eval(j, messages);
    }

    void node_iteration_stmt::Pull_back(std::deque<token_base *> &tokens) {
//
    }

    void node_return_stmt::Eval(int i, std::deque<std::string> *messages) {
        int j = i + 1;
        //return
        add_tree_info(i, "Return", messages);
        if (expression) {
            expression->Eval(j, messages);
        }
    }

    void node_return_stmt::Pull_back(std::deque<token_base *> &tokens) {
//
    }

    void node_expression::Eval(int i, std::deque<std::string> *messages) {
        int j = i + 1;
        if (var) {
            add_tree_info(i, "Assign", messages);
            var->Eval(j, messages);
            expression->Eval(j, messages);
        } else {
            simple_expression->Eval(i, messages);
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
        add_tree_info(i, "IdK: " + ID->get_string(), messages);
        if(expression)
            this->expression->Eval(j, messages);
    }

    void node_var::Pull_back(std::deque<token_base *> &tokens) {
        this->Eval(10, nullptr);
        if (LEFT_S) {
            tokens.push_front(this->RIGHT_S);
            this->expression->Pull_back(tokens);
            tokens.push_front(this->LEFT_S);
        }
        tokens.push_front(this->ID);
    }

    void node_simple_expression::Eval(int i, std::deque<std::string> *messages) {
        int j = i + 1;

        if (relop) {
            relop->Eval(i, messages);
            additive_expression_1->Eval(j, messages);
            additive_expression_2->Eval(j, messages);
        } else {
            additive_expression_1->Eval(i, messages);
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
        add_tree_info(i, "Op: " + RELOP->get_string(), messages);
    }

    void node_relop::Pull_back(std::deque<token_base *> &tokens) {
        tokens.push_front(this->RELOP);
    }

    void node_additive_expression::Eval(int i, std::deque<std::string> *messages) {
        int j = i + 1;

        if (!addop->empty()) {
            support_recur_term(term_1, addop, term, i, messages);
        } else {
            term_1->Eval(i, messages);
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
        add_tree_info(i, "Op: " + op->get_string(), messages);
    }

    void node_addop::Pull_back(std::deque<token_base *> &tokens) {
        tokens.push_front(this->op);
    }

    void node_term::Eval(int i, std::deque<std::string> *messages) {
        int j = i + 1;

        if(!mulop->empty()) {
            support_recur_term(factor_1, mulop, factor, i, messages);
        }else{
            factor_1->Eval(i, messages);
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
        add_tree_info(i, "Op: " + op->get_string(), messages);
    }

    void node_mulop::Pull_back(std::deque<token_base *> &tokens) {
        tokens.push_front(this->op);
    }

    void node_factor::Eval(int i, std::deque<std::string> *messages) {

        int j = i + 1;
        if (expression) {
            expression->Eval(j, messages);
        } else if (ID) {
            if(factor_s) {
                if(reinterpret_cast<node_factor_s*>(factor_s)->LEFT_P)
                {
                    add_tree_info(i, "CallK", messages);
                    add_tree_info(j, "IdK: " + ID->get_string(), messages);
                    factor_s->Eval(j, messages);
                }else if(reinterpret_cast<node_factor_s*>(factor_s)->expression){
                    add_tree_info(i, "Arry_ElemK", messages);
                    add_tree_info(j, "IdK: " + ID->get_string(), messages);
                    factor_s->Eval(j, messages);
                }

            }else{
                add_tree_info(i, "IdK: " + ID->get_string(), messages);
            }
        } else {
            add_tree_info(i, "ConstK: " + NUM->get_string(), messages);
        }
    }

    void node_factor::Pull_back(std::deque<token_base *> &tokens) {
        if (this->LEFT_P) {
            tokens.push_front(this->RIGHT_P);
            expression->Pull_back(tokens);
            tokens.push_front(this->LEFT_P);
        } else if (this->ID) {
            if(factor_s)
                this->factor_s->Pull_back(tokens);
            tokens.push_front(this->ID);
        } else {
            tokens.push_front(this->NUM);
        }
    }

    void node_factor_s::Eval(int i, std::deque<std::string> *messages) {
        int j = i + 1;
        if (expression) {
            expression->Eval(i, messages);
        } else if (args) {
            args->Eval(i, messages);
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
        int j = i + 1;
        add_tree_info(i, "ArgsK", messages);
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
