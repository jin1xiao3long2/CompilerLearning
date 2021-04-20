/*
 *  program ::= declaration  (declaration)* ;
 *
 *  declaration ::= type_specifier ID declaration_s;
 *
 *  declaration_s ::= ';'
 *                        | '[' NUM ']' ';'
 *                        | '(' params ')' compound_stmt
 *                        ;
 *
 * type_specifier ::= INT
 *                            | VOID
 *                            ;
 *
 *  params ::= void_param_list
 *                 | int_param_list
 *                 ;
 *
 * void_param_list ::= VOID ( ID  ('[' ']')?  ( ',' param)* )? ;
 *
 *  int_param_list ::= INT ID ( '[' ']' )? ( ',' param )* ;
 *
 * param ::= type_specifier ID ( '[' ']' )? ;
 *
 * compound_stmt ::= '{' (var_declaration)* (statement)* '}' ;
 *
 * statement ::= expression_stmt
 *                     | compound_stmt
 *                     | selection_stmt
 *                     | iteration_stmt
 *                     | return_stmt
 *                     ;
 *
 * expression_stmt ::= expression ';'
 *                                | ';'
 *                                ;
 *
 *  selection_stmt ::= IF '(' expression ')' statement ( ELSE statement)? ;
 *
 *  iteration_stmt ::= WHILE '(' expression ')' statement ;
 *
 *  return_stmt ::= RETURN (expression)?
 *
 *  expression ::= var '=' expression
 *                       | simple_expression
 *                       ;
 *
 * var ::= ID ( '[' expression ']' )? ;
 *
 * simple_expression ::= additive_expression (relop additive_expression)? ;
 *
 * relop ::= '<=' | '<' | '>' | '>=' | '==' | '~=' ;
 *
 * additive_expression ::= term (addop term)* ;
 *
 * addop ::= '+' | '-' ;
 *
 * term ::= factor (mulop factor)*
 *
 * mulop ::= '*' | '/' ;
 *
 * factor ::= '(' expression ')'
 *               | ID factor_s
 *               | NUM
 *               ;
 *
 * factor_s ::= '[' expression ']'
 *                | '(' args ')'
 *                | NULL
 *                ;
 *
 * args ::= expression ( ',' expression)*
 *            | NULL
 *            ;
 */


#pragma once

#include <CM_Nodes.hpp>


namespace cm {


    class Parser final {

    private:

        std::deque<token_base *> tokens;
        std::deque<std::string> *messages;
        node_base *start = nullptr;

        const std::string get_token_info() const;

        void add_message(const std::string &);

        void consume_error();

        bool Is_end();

        void Ensure();

        token_type peek();

        signal_type peek_signal();

        keyword_type peek_keyword();

        token_base * consume_token();

        bool match(token_type);

        token_base *consume_token(token_type);

        bool match(signal_type);

        token_base * consume_token(signal_type);

        bool match(keyword_type);

        token_base * consume_token(keyword_type);

        node_program *Parse_program();

        node_declaration *Parse_declaration();

        node_declaration_s *Parse_declaration_s();

        node_type_specifier *Parse_type_speicifier();

        node_params *Parse_params();

        node_void_param_list *Parse_void_param_list();

        node_int_param_list *Parse_int_param_list();

        node_param *Parse_param();

        node_compound_stmt *Parse_compound_stmt();

        node_var_declaration *Parse_var_declaration();

        node_statement *Parse_statement();

        node_expression_stmt *Parse_expression_stmt();

        node_selection_stmt *Parse_selection_stmt();

        node_iteration_stmt *Parse_iteration_stmt();

        node_return_stmt *Parse_return_stmt();

        node_expression *Parse_expression();

        node_var *Parse_var();

        node_simple_expression *Parse_simple_expression();

        node_relop *Parse_relop();

        node_additive_expression *Parse_additive_expression();

        node_addop *Parse_addop();

        node_term *Parse_term();

        node_mulop *Parse_mulop();

        node_factor *Parse_factor();

        node_factor_s *Parse_factor_s();

        node_base * Parse_args();

    public:

        Parser(const std::deque<token_base *> &Tokens) : tokens(std::move(Tokens)) {}

        ~Parser(){
        }

        void parse(){
            start = Parse_program();
            start->Eval(0, messages);
        }

        std::deque<std::string> *getMessages() const;
    };


}