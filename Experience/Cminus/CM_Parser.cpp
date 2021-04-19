//
// Created by XM on 2021/4/12.
//

#include <CM_Parser.hpp>

namespace cm {

    const std::string Parser::get_token_info() const {
        token_base *token = tokens.front();
        return std::string(
                "line: " + std::to_string(token->get_line()) + " column: " + std::to_string(token->get_column()) +
                token->get_show_info());
    }

    void Parser::add_message(const std::string &mes) {
        messages->push_back(mes);  //to be finished
    }

    void Parser::consume_error() {
        add_message("unexpected word " + get_token_info());
        consume_token();
    }

    bool Parser::Is_end() {
        return tokens.empty();
    }

    void Parser::Ensure() {
        if (Is_end()) {
            add_message("Unexpected EOF");
        }
    }

    token_type Parser::peek() {
        Ensure();
        return tokens.front()->get_type();
    }

    signal_type Parser::peek_signal() {
        Ensure();
        return reinterpret_cast<token_signal *>(tokens.front())->get_value();
    }

    keyword_type Parser::peek_keyword() {
        Ensure();
        return reinterpret_cast<token_keyword *>(tokens.front())->get_value();
    }

    token_base *Parser::consume_token() {
        Ensure();
        token_base *value = tokens.front();
        tokens.pop_front();
        return value;
    }

    bool Parser::match(token_type type) {
        Ensure();
        token_base *value = tokens.front();
        return value->get_type() == type;
    }

    token_base *Parser::consume_token(token_type type) {
        if (match(type)) {
            return consume_token();
        } else {
            add_message("unexpected type");
            return nullptr;
        }
    }

    bool Parser::match(signal_type signal) {
        match(token_type::signal_type);
        token_base *value = tokens.front();
        return reinterpret_cast<token_signal *>(value)->get_value() == signal;
    }

    token_base *Parser::consume_token(signal_type signal) {
        if (match(signal)) {
            return consume_token();
        } else {
            add_message("unexpected signal");
            return nullptr;
        }
    }

    bool Parser::match(keyword_type keyword) {
        match(token_type::keyword_type);
        token_base *value = tokens.front();
        return reinterpret_cast<token_keyword *>(value)->get_value() == keyword;
    }

    token_base *Parser::consume_token(keyword_type keyword) {
        if (match(keyword)) {
            return consume_token();
        } else {
            add_message("unexpected keyword");
            return nullptr;
        }
    }

    node_program *Parser::Parse_program() {
        node_program *program = new node_program;

        program->declaration_1 = Parse_declaration();
        //declaration
        while (!Is_end()) {
            program->declaration->push_back(Parse_declaration());
        }
        // (declaration)*

        return program;
    }

    node_declaration *Parser::Parse_declaration() {
        node_declaration *declaration = new node_declaration;

        declaration->type_specifier = Parse_type_speicifier();
        //type_specifier
        declaration->id = consume_token(token_type::identifier_type);
        //ID
        declaration->declaration_s = Parse_declaration_s();
        //declaration_s

        return declaration;
    }

    node_declaration_s *Parser::Parse_declaration_s() {
        node_declaration_s *declarationS = new node_declaration_s;

        switch (peek()) {
            case token_type::signal_type: {
                switch (peek_signal()) {
                    case signal_type::SEMICOLON: {
                        declarationS->SEMICOLON = consume_token();
                        //';'
                        break;
                    }
                    case signal_type::LEFT_S: {
                        declarationS->LEFT_S = consume_token();
                        //'['
                        declarationS->NUMBER = consume_token(token_type::number_type);
                        //'NUM'
                        declarationS->RIGHT_S = consume_token(signal_type::RIGHT_S);
                        //']'
                        break;
                    }
                    case signal_type::LEFT_P: {
                        declarationS->LEFT_P = consume_token();
                        //'('
                        declarationS->params = Parse_params();
                        //params
                        declarationS->RIGHT_P = consume_token(signal_type::RIGHT_P);
                        //')'
                        declarationS->compound_stmt = Parse_compound_stmt();
                        //compound_stmt
                        break;
                    }
                    default: {
                        consume_error();
                        break;
                    }
                }
                break;
            }
            default: {
                consume_error();
                break;
            }
        }
        return declarationS;
    }

    node_type_specifier *Parser::Parse_type_speicifier() {
        node_type_specifier *typeSpecifier = nullptr;

        switch (peek()) {
            case token_type::signal_type: {
                switch (peek_keyword()) {
                    case keyword_type::INT:
                    case keyword_type::VOID: {
                        typeSpecifier = new node_type_specifier;
                        typeSpecifier->TYPE = consume_token();
                        //VOID | INT
                        return typeSpecifier;
                    }
                    default: {
                        consume_error();
                        break;
                    }
                }
                break;
            }
            default: {
                consume_error();
                break;
            }
        }
        return typeSpecifier;
    }

    node_params *Parser::Parse_params() {
        node_params *params = new node_params;

        switch (peek()) {
            case token_type::keyword_type: {
                switch (peek_keyword()) {
                    case keyword_type::VOID: {
                        params->void_param_list = Parse_void_param_list();
                        //void_param_list
                        break;
                    }
                    case keyword_type::INT: {
                        params->int_param_list = Parse_int_param_list();
                        //int_param_list
                        break;
                    }
                    default: {
                        consume_error();
                        break;
                    }
                }
                break;
            }
            default: {
                consume_error();
                break;
            }
        }
        return params;
    }


    node_void_param_list *Parser::Parse_void_param_list() {
        node_void_param_list *voidParamList = new node_void_param_list;

        voidParamList->VOID = consume_token();

        switch (peek()) {
            case token_type::identifier_type: {
                voidParamList->ID = consume_token();
                //ID

                switch (peek()) {
                    case token_type::signal_type: {
                        switch (peek_signal()) {
                            case signal_type::LEFT_S: {
                                voidParamList->LEFT_S = consume_token();
                                //'['
                                voidParamList->RIGHT_S = consume_token(signal_type::RIGHT_S);
                                //']'
                                break;
                            }
                            default: {
                                break;
                            }
                        }
                        break;
                    }
                    default: {
                        break;
                    }
                }
                //('[' ']')?

                while (!Is_end()) {
                    if (match(signal_type::COMMA)) {
                        voidParamList->COMMA->push_back(consume_token());
                        //','
                        voidParamList->param->push_back(Parse_param());
                        //param
                    } else {
                        break;
                    }

                }
                //(',' param)*
                break;
            }
            default: {
                break;
            }
        }
        //(ID ('[' ']')? (',' param)* )?
        return voidParamList;
    }

    node_int_param_list *Parser::Parse_int_param_list() {
        node_int_param_list *intParamList = new node_int_param_list;

        intParamList->INT = consume_token(keyword_type::INT);
        //INT
        intParamList->ID = consume_token(token_type::identifier_type);
        //ID

        switch (peek()) {
            case token_type::signal_type: {
                switch (peek_signal()) {
                    case signal_type::LEFT_S: {
                        intParamList->LEFT_S = consume_token();
                        //'['
                        intParamList->RIGHT_S = consume_token(signal_type::RIGHT_S);
                        //']'
                    }
                    default: {
                        break;
                    }
                }
                break;
            }
        }
        //('[' ']')?

        while (!Is_end()) {
            if (match(signal_type::COMMA)) {
                intParamList->COMMA->push_back(consume_token());
                //','
                intParamList->param->push_back(Parse_param());
                //param
            } else {
                break;
            }
        }
        //(',' param)?

        return intParamList;
    }

    node_param *Parser::Parse_param() {
        node_param *param = new node_param;

        param->type_specifier = Parse_type_speicifier();
        //type_specifier
        param->ID = consume_token(token_type::identifier_type);
        //ID
        switch (peek()) {
            case token_type::signal_type: {
                switch (peek_signal()) {
                    case signal_type::LEFT_S: {
                        param->LEFT_S = consume_token();
                        //'['
                        param->RIGHT_S = consume_token(signal_type::RIGHT_S);
                        //']'
                        break;
                    }
                    default: {
                        break;
                    }
                }
                break;
            }
            default: {
                break;
            }
        }
        //('[' ']')?

        return param;
    }

    node_compound_stmt *Parser::Parse_compound_stmt() {
        node_compound_stmt *compoundStmt = new node_compound_stmt;

        compoundStmt->LEFT_B = consume_token(signal_type::LEFT_B);
        //'{'
        while (!Is_end()) {
            if (match(keyword_type::INT) || match(keyword_type::VOID)) {
                compoundStmt->var_declaration->push_back(Parse_var_declaration());
            } else {
                break;
            }
        }
        //(var_declaration)*
        while (!Is_end()) {
            if (match(token_type::identifier_type) || match(signal_type::LEFT_P)
                || match(token_type::number_type) || match(signal_type::LEFT_B)
                || match(keyword_type::IF) || match(keyword_type::WHILE)
                || match(keyword_type::RETURN) || match(signal_type::SEMICOLON)) {
                compoundStmt->statement->push_back(Parse_statement());
            } else {
                break;
            }
            //(statement)*
        }
        compoundStmt->RIGHT_B = consume_token(signal_type::RIGHT_B);
        //'}'

        return compoundStmt;
    }

    node_var_declaration *Parser::Parse_var_declaration() {
        node_var_declaration *varDeclaration = new node_var_declaration;

        varDeclaration->type_specifier = Parse_type_speicifier();
        //type_specifier
        varDeclaration->ID = consume_token(token_type::identifier_type);
        //ID
        switch (peek()) {
            case token_type::signal_type: {
                switch (peek_signal()) {
                    case signal_type::LEFT_S: {
                        varDeclaration->LEFT_S = consume_token();
                        //'['
                        varDeclaration->NUMBER = consume_token(token_type::number_type);
                        //NUM
                        varDeclaration->RIGHT_S = consume_token(signal_type::RIGHT_S);
                        //']'
                        break;
                    }
                    default: {
                        break;
                    }
                }
                break;
            }
            default: {
                break;
            }
        }
        //('[' NUM ']')?

        return varDeclaration;
    }

    node_statement *Parser::Parse_statement() {
        node_statement *statement = new node_statement;

        switch (peek()) {
            case token_type::signal_type: {
                switch (peek_signal()) {
                    case signal_type::LEFT_P: {
                        statement->express_stmt = Parse_expression_stmt();
                        break;
                    }
                        //expression_stmt
                    case signal_type::LEFT_B: {
                        statement->compound_stmt = Parse_compound_stmt();
                        break;
                    }
                        //compound_stmt
                    case signal_type::SEMICOLON: {
                        statement->express_stmt = Parse_expression_stmt();
                        break;
                    }
                        //expression_stmt
                    default: {
                        consume_error();
                        break;
                    }
                }
                break;
            }
            case token_type::keyword_type: {
                switch (peek_keyword()) {
                    case keyword_type::IF: {
                        statement->selection_stmt = Parse_selection_stmt();
                        break;
                    }
                        //selection_stmt
                    case keyword_type::WHILE: {
                        statement->iteration_stmt = Parse_iteration_stmt();
                        break;
                    }
                        //iteration_stmt
                    case keyword_type::RETURN: {
                        statement->return_stmt = Parse_return_stmt();
                        break;
                    }
                        //return_stmt
                    default: {
                        consume_error();
                        break;
                    }
                }
                break;
            }
            case token_type::number_type:
            case token_type::identifier_type: {
                statement->express_stmt = Parse_expression_stmt();
                break;
            }
                //expression_stmt
            default: {
                consume_error();
                break;
            }
        }
        return statement;
    }

    node_expression_stmt *Parser::Parse_expression_stmt() {
        node_expression_stmt *expressionStmt = new node_expression_stmt;

        bool need_semi = true;

        switch (peek()) {
            case token_type::signal_type: {
                switch (peek_signal()) {
                    case signal_type::LEFT_P: {
                        expressionStmt->expression = Parse_expression();
                        break;
                    }
                        //expression
                    case signal_type::SEMICOLON: {
                        expressionStmt->SEMICOLON = consume_token();
                        need_semi = false;
                        break;
                    }
                        //';'
                    default: {
                        consume_error();
                        need_semi = false;
                        break;
                    }
                }
                break;
            }
            case token_type::number_type:
            case token_type::identifier_type: {
                expressionStmt->expression = Parse_expression();
                break;
            }
                //expression
            default: {
                consume_error();
                need_semi = false;
                break;
            }
        }
        if (need_semi) {
            expressionStmt->SEMICOLON = consume_token(signal_type::SEMICOLON);
        }
        //';'

        return expressionStmt;
    }

    node_selection_stmt *Parser::Parse_selection_stmt() {
        node_selection_stmt *selectionStmt = new node_selection_stmt;

        selectionStmt->IF = consume_token();
        //IF
        selectionStmt->LEFT_P = consume_token(signal_type::LEFT_P);
        //'('
        selectionStmt->expression = Parse_expression();
        //expression
        selectionStmt->RIGHT_P = consume_token(signal_type::RIGHT_P);
        //')'
        selectionStmt->statement_1 = Parse_statement();
        //statement
        switch (peek()) {
            case token_type::keyword_type: {
                switch (peek_keyword()) {
                    case keyword_type::ELSE: {
                        selectionStmt->ELSE = consume_token();
                        //ELSE
                        selectionStmt->statement_2 = Parse_statement();
                        //statement
                        break;
                    }
                    default: {
                        break;
                    }
                }
                break;
            }
            default: {
                break;
            }
        }
        //(ELSE statement)?

        return selectionStmt;
    }

    node_iteration_stmt *Parser::Parse_iteration_stmt() {
        node_iteration_stmt *iterationStmt = new node_iteration_stmt;

        iterationStmt->WHILE = consume_token();
        //WHILE
        iterationStmt->LEFT_P = consume_token(signal_type::LEFT_P);
        //'('
        iterationStmt->expression = Parse_expression();
        //expression
        iterationStmt->RIGHT_P = consume_token(signal_type::RIGHT_P);
        //')'
        iterationStmt->statement = Parse_statement();
        //statement
        return iterationStmt;
    }

    node_return_stmt *Parser::Parse_return_stmt() {
        node_return_stmt *returnStmt = new node_return_stmt;

        returnStmt->RETURN = consume_token();
        //RETURN
        switch (peek()) {
            case token_type::signal_type: {
                switch (peek_signal()) {
                    case signal_type::RIGHT_P: {
                        returnStmt->expression = Parse_statement();
                        break;
                    }
                        //statement
                    default: {
                        break;
                    }
                }
                break;
            }
            case token_type::number_type:
            case token_type::identifier_type: {
                returnStmt->expression = Parse_expression();
                break;
            }
                //expression
            default: {
                break;
            }
        }
        //(expression)?

        return returnStmt;
    }

    node_expression *Parser::Parse_expression() {
        node_expression *expression = new node_expression;
        //look back, we may have to use a stack
        node_var *tmp_node = nullptr;
        bool check_var = false;
        //for look back, will be nullptr in the end
        switch (peek()) {
            case token_type::signal_type: {
                switch (peek_signal()) {
                    case signal_type::LEFT_P: {
                        expression->simple_expression = Parse_simple_expression();
                        break;
                    }
                        //simple_expression
                    default: {//actually it is invalid code
                        consume_error();
                        break;
                    }
                }
                break;
            }
            case token_type::number_type: {
                expression->simple_expression = Parse_simple_expression();
                break;
            }
                //simple_expression
            case token_type::identifier_type: {
                tmp_node = Parse_var();
                check_var = true;
                break;
            }
            default: {//actually it is invalid code
                consume_error();
                break;
            }
        }

        if (check_var) {
            if (match(signal_type::EQ)) {
                expression->var = tmp_node;
                //var
                tmp_node = nullptr;
                expression->EQ = consume_token();
                //'='
                expression->expression = Parse_expression();
                //expression
            } else {
                if (tmp_node->LEFT_S) {
                    //look back
                    tmp_node = nullptr;
                    expression->Pull_back(tokens);
                    expression->simple_expression = Parse_simple_expression();
                    //simple_expression
                }
            }
        }
        return expression;
    }

    node_var *Parser::Parse_var() {
        node_var *var = new node_var;

        var->ID = consume_token();
        //ID
        if (match(signal_type::LEFT_S)) {
            var->LEFT_S = consume_token();
            //'['
            var->expression = Parse_expression();
            //expression
            var->RIGHT_S = consume_token(signal_type::RIGHT_S);
            //']'
        }

        return var;
    }

    node_simple_expression *Parser::Parse_simple_expression() {
        node_simple_expression *simpleExpression = new node_simple_expression;

        simpleExpression->additive_expression_1 = Parse_additive_expression();

        switch (peek()) {
            case token_type::signal_type: {
                switch (peek_signal()) {
                    case signal_type::LE:
                    case signal_type::LT:
                    case signal_type::GT:
                    case signal_type::GE:
                    case signal_type::EQ:
                    case signal_type::NEQ: {
                        simpleExpression->relop = Parse_relop();
                        //relop
                        simpleExpression->additive_expression_2 = Parse_additive_expression();
                        //additive_expression
                        break;
                    }
                    default: {
                        break;
                    }
                }
                break;
            }
            default: {
                break;
            }
        }
        //(relop additive_expression)?

        return simpleExpression;
    }

    node_relop *Parser::Parse_relop() {
        node_relop *relop = new node_relop;

        relop->RELOP = consume_token();
        //sign
        return relop;
    }

    node_additive_expression *Parser::Parse_additive_expression() {
        node_additive_expression *additiveExpression = new node_additive_expression;

        additiveExpression->term_1 = Parse_term();
        //term

        bool break_while = false;
        while (!Is_end()) {
            switch (peek()) {
                case token_type::signal_type: {
                    switch (peek_signal()) {
                        case signal_type::ADD:
                        case signal_type::SUB: {
                            additiveExpression->addop->push_back(Parse_addop());
                            //addop
                            additiveExpression->term->push_back(Parse_term());
                            //term
                            break;
                        }
                        default: {
                            break_while = true;
                            break;
                        }
                    }
                    break;
                }
                default: {
                    break_while = true;
                    break;
                }
            }
            if (break_while) {
                break;
            }
        }
        //(addop term)*

        return additiveExpression;
    }


    node_addop *Parser::Parse_addop() {
        node_addop *addop = new node_addop;

        addop->op = consume_token();
        //op

        return addop;
    }

    node_term *Parser::Parse_term() {
        node_term *term = new node_term;

        term->factor_1 = Parse_factor();
        //factor
        bool break_while = false;
        while (!Is_end()) {
            switch (peek()) {
                case token_type::signal_type: {
                    switch (peek_signal()) {
                        case signal_type::MUL:
                        case signal_type::DIV: {
                            term->mulop->push_back(Parse_mulop());
                            //mulop
                            term->factor->push_back(Parse_factor());
                            //factor
                            break;
                        }
                        default: {
                            break_while = true;
                            break;
                        }
                    }
                    break;
                }
                default: {
                    break_while = true;
                    break;
                }
            }
            if (break_while) {
                break;
            }
        }
        //(mulop factor)*

        return term;
    }

    node_mulop *Parser::Parse_mulop() {
        node_mulop *mulop = new node_mulop;

        mulop->op = consume_token();
        //op
        return mulop;
    }

    node_factor *Parser::Parse_factor() {
        node_factor *factor = new node_factor;

        switch (peek()) {
            case token_type::signal_type: {
                switch (peek_signal()) {
                    case signal_type::LEFT_P: {
                        factor->LEFT_P = consume_token();
                        factor->expression = Parse_expression();
                        factor->RIGHT_P = consume_token(signal_type::RIGHT_P);
                        break;
                    }
                    default: {
                        consume_error();
                        break;
                    }
                }
                break;
            }
            case token_type::identifier_type: {
                factor->ID = consume_token();
                factor->factor_s = Parse_factor_s();
                break;
            }
            case token_type::number_type: {
                factor->NUM = consume_token();
                break;
            }
            default: {
                consume_error();
                break;
            }
        }

        return factor;
    }

    node_factor_s *Parser::Parse_factor_s() {
        node_factor_s *factorS = new node_factor_s;
        switch (peek()) {
            case token_type::signal_type: {
                switch (peek_signal()) {
                    case signal_type::LEFT_S: {
                        factorS->LEFT_S = consume_token();
                        //'['
                        factorS->expression = Parse_expression();
                        //expression
                        factorS->RIGHT_S = consume_token(signal_type::RIGHT_S);
                        //']'
                        break;
                    }
                    case signal_type::LEFT_P: {
                        factorS->LEFT_P = consume_token();
                        //'('
                        factorS->args = Parse_args();
                        //args
                        factorS->RIGHT_P = consume_token(signal_type::RIGHT_P);
                        //')'
                    }
                    default: {
                        return nullptr;
                    }
                }
                break;
            }
            default: {
                return nullptr;
            }
        }

        return factorS;
    }

    node_base *Parser::Parse_args() {
        node_args *args = new node_args;

        switch (peek()) {
            case token_type::signal_type: {
                switch (peek_signal()) {
                    case signal_type::LEFT_P: {
                        args->expression_1 = Parse_expression();
                        break;
                    }
                    default: {
                        return nullptr;
                    }
                }
                break;
            }
            case token_type::identifier_type:
            case token_type::number_type: {
                args->expression_1 = Parse_expression();
                break;
            }
            default: {
                return nullptr;
            }
        }

        while (!Is_end()) {
            if (match(signal_type::COMMA)) {
                args->COMMA->push_back(consume_token());
                args->expression->push_back(Parse_expression());
            } else {
                break;
            }
        }

        return args;
    }

    std::deque<std::string> *Parser::getMessages() const {
        return messages;
    }

}