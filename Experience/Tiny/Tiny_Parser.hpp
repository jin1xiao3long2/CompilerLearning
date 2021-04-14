/*
 * program ::= stmt-sequence ;
 *
 * stmt-sequence ::= statement ( ';' statement)* ;
 *
 * statement ::= if-stmt
 *             | repeat-stmt
 *             | assign-stmt
 *             | read-stmt
 *             | write-stmt
 *             ;
 *
 * if-stmt ::= 'if' exp 'then' stmt-sequence end
 *           | 'if' exp 'then' stmt-sequence else stmt-sequence end
 *
 * repeat-stmt ::= 'repeat' stmt-sequence 'until' exp ;
 *
 * assign-stmt ::= 'identifier' ':=' exp
 *
 * read-stmt ::= 'read' 'identifier'
 *
 * write-stmt ::= 'write' exp
 *
 * exp ::= simple-exp
 *       | simple-exp comparison-op simple-exp
 *       ;
 *
 * comparison-op ::= '<'
 *                 | '='
 *                 ;
 * simple-exp ::= term
 *              | term (addop term)*
 *              ;
 *
 * addop ::= '+'
 *         | '-'
 *         ;
 *
 * term ::= factor
 *        | factor (mulop factor)*
 *        ;
 *
 * mulop ::= '*'
 *         | '/'
 *         ;
 *
 * factor ::= '(' exp ')'
 *          | 'number'
 *          | 'identifier'
 *          ;
 */

#pragma once


#include <Tiny_Nodes.hpp>
#include <deque>

namespace tn {

    class Parser final {

    private:
        std::deque<token_base *> tokens;
        node_base *start;
        int lineNum = 0;
        std::deque<std::string> messages;


//        Message Function
        void addMessage(const std::string &info);

        void addInfo(const std::string &info);

//        Support Function
        bool IsEnd(); //check if tokens.empty

        void Ensure(); //check if empty

        token_type peek(); //check tokens.front.type

        int get_line(); //get tokens.front.line

        signal_type peek_signal(); //check signal.value

        keyword_type peek_keyword(); //check keyword.value

        token_base *consume_token(); //pop and get tokens.front

        bool match_type(token_type type);

        token_base *consume_type(token_type type);

        bool match_keyword(keyword_type keyword);

        token_base *consume_token(keyword_type keyword);

        bool match_signal(signal_type signal);

        token_base *consume_token(signal_type signal);
//        Parse Function

        node_Program *Parse_Program();

        node_Stmt_sequence *Parse_Stmt_sequence();

        node_Statement *Parse_Statement();

        node_If_stmt *Parse_If_stmt();

        node_Repeat_stmt *Parse_Repeat_stmt();

        node_Assign_stmt *Parse_Assign_stmt();

        node_Read_stmt *Parse_Read_stmt();

        node_Write_stmt *Parse_Write_stmt();

        node_Exp *Parse_Exp();

        node_Comparison_op *Parse_Comparison_op();

        node_Simple_exp *Parse_Simple_exp();

        node_AddOp *Parse_AddOp();

        node_Term *Parse_Term();

        node_MulOp *Parse_MulOp();

        node_Factor *Parse_Factor();

        void show_info() {
            for (auto iter = messages.begin(); iter != messages.end(); iter++) {
                std::cout << iter->data() << std::endl;
            }
            std::cout << "\nSyntax tree: " << std::endl;
//            start->Eval(1, messages);
        }

    public:
        explicit Parser(const std::deque<token_base *> Tokens) : tokens(std::move(Tokens)) {};

        void parse() {
            messages.push_back("TINY PARSING:");
            start = Parse_Program();

            messages.push_back("\nSyntax tree:");
            start->Eval(1, this->messages);
        }

        const std::deque<std::string> &getMessages() const {
            return messages;
        }


    };

}

