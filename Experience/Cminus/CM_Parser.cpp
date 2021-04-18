//
// Created by XM on 2021/4/12.
//

#include <CM_Parser.hpp>

namespace cm {

    const std::string Parser::get_token_info() const{
        token_base* token = tokens.front();
        return std::string("line: " + std::to_string(token->get_line()) + " column: " + std::to_string(token->get_column()) + token->get_show_info());
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

    bool Parser::match_type(token_type type) {
        Ensure();
        token_base *value = tokens.front();
        return value->get_type() == type;
    }

    token_base *Parser::consume_token(token_type type) {
        if (match_type(type)) {
            return consume_token();
        } else {
            add_message("unexpected type");
            return nullptr;
        }
    }

    bool Parser::match_signal(signal_type signal) {
        match_type(token_type::signal_type);
        token_base *value = tokens.front();
        return reinterpret_cast<token_signal *>(value)->get_value() == signal;
    }

    token_base *Parser::consume_token(signal_type signal) {
        if (match_signal(signal)) {
            return consume_token();
        } else {
            add_message("unexpected signal");
            return nullptr;
        }
    }

    bool Parser::match_keyword(keyword_type keyword) {
        match_type(token_type::keyword_type);
        token_base *value = tokens.front();
        return reinterpret_cast<token_keyword *>(value)->get_value() == keyword;
    }

    token_base *Parser::consume_token(keyword_type keyword) {
        if (match_keyword(keyword)) {
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
            case token_type::signal_type:{
                switch (peek_signal()) {
                    case signal_type::SEMICOLON:{
                        declarationS->SEMICOLON = consume_token();
                        //';'
                        break;
                    }
                    case signal_type::LEFT_S:{
                        declarationS->LEFT_S = consume_token();
                        //'['
                        declarationS->NUMBER = consume_token(token_type::number_type);
                        //'NUM'
                        declarationS->RIGHT_S = consume_token(signal_type::RIGHT_S);
                        //']'
                        break;
                    }
                    case signal_type::LEFT_P:{
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
                    default:{
                        consume_error();
                        break;
                    }
                }
            }
            default:{
                consume_error();
                break;
            }
        }
        return declarationS;
    }

    node_type_specifier *Parser::Parse_type_speicifier() {
        node_type_specifier *typeSpecifier = nullptr;

        switch (peek()) {
            case token_type::signal_type:{
                switch (peek_keyword()) {
                    case keyword_type::INT:
                    case keyword_type::VOID:{
                        typeSpecifier = new node_type_specifier;
                        typeSpecifier->TYPE = consume_token();
                        //VOID | INT
                        return typeSpecifier;
                    }

                    default:{
                        consume_error();
                        break;
                    }
                }
            }
            default:{
                consume_error();
                break;
            }
        }
    }

    node_params *Parser::Parse_params() {
        node_params *params = new node_params;

        switch (peek()) {
            case token_type::keyword_type:{
                switch (peek_keyword()) {
                    case keyword_type::VOID:{
                        params->void_param_list = Parse_void_param_list();
                        //void_param_list
                        break;
                    }
                    case keyword_type::INT:{
                        params->int_param_list = Parse_int_param_list();
                        //int_param_list
                        break;
                    }
                    default:{
                        consume_error();
                        break;
                    }
                }
            }
            default:{
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
            case token_type::identifier_type:{
                voidParamList->ID = consume_token();
                //ID

                switch (peek()) {
                    case token_type::signal_type:{
                        switch (peek_signal()) {
                            case signal_type::LEFT_S:{
                                voidParamList->LEFT_S = consume_token();
                                //'['
                                voidParamList->RIGHT_S = consume_token(signal_type::RIGHT_S);
                                //']'
                                break;
                            }
                            case signal_type::COMMA:{
                                break;
                            }
                            default:{
                                break;
                            }
                        }
                    }
                    default:{
                        break;
                    }
                }
                bool break_while = false;
                while(!Is_end()){
                    if(match_signal(signal_type::COMMA)){
                        voidParamList->COMMA->push_back(consume_token());
                        //','
                        voidParamList->param->push_back(Parse_param());
                        //param
                    }else{
                        break_while = true;
                    }
                    if(break_while)
                        break;;
                }
            }
        }
    }

    node_int_param_list *Parser::Parse_int_param_list() {

    }

    node_param *Parser::Parse_param() {

    }

    node_compound_stmt *Parser::Parse_compound_stmt() {

    }

    node_statement *Parser::Parse_statement() {

    }

    node_expression_stmt *Parser::Parse_expression_stmt() {

    }

    node_selection_stmt *Parser::Parse_selection_stmt() {

    }

    node_iteration_stmt *Parser::Parse_iteration_stmt() {

    }

    node_return_stmt *Parser::Parse_return_stmt() {

    }

    node_expression *Parser::Parse_expression() {

    }

    node_var *Parser::Parse_var() {

    }

    node_simple_expression *Parser::Parse_simple_expression() {

    }

    node_relop *Parser::Parse_relop() {

    }

    node_additive_expression *Parser::Parse_additive_expression() {

    }

    node_addop *Parser::Parse_addop() {

    }

    node_term *Parser::Parse_term() {

    }

    node_mulop *Parser::Parse_mulop() {

    }

    node_factor *Parser::Parse_factor() {

    }

    node_factor_s *Parser::Parse_factor_s() {

    }

    node_base *Parser::Parse_args() {

    }

    std::deque<std::string> *Parser::getMessages() const {
        return messages;
    }


}