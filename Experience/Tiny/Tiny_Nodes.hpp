//
// Created by XM on 2021/3/27.
//
#pragma once

#include <Tiny_Signal.hpp>
#include <deque>


namespace tn{



    /*
     * 所有结点的基类,主要设计到
     */
    struct node_base{
//Eval 是否return 值得考究
        virtual node_base* Eval(int,std::deque<std::string>&) = 0;

        virtual ~node_base() = default;
    };

    struct node_Program final : public node_base{
        node_base* Stmt_sequence{};

        node_base * Eval(int,std::deque<std::string>&) override;

        ~node_Program(){
            delete Stmt_sequence;
        }
    };

    struct node_Stmt_sequence final : public node_base{
        node_base* Stmt_1{};
        token_base* Semicolon{};
        node_base* Stmt_2{};

        node_base * Eval(int,std::deque<std::string>&) override;

        ~node_Stmt_sequence(){
            delete Stmt_1;
            delete Semicolon;
            delete Stmt_2;
        }
    };

    struct node_Statement final: public node_base{
        node_base* If_stmt{};
        node_base* Repeat_stmt{};
        node_base* Assign_stmt{};
        node_base* Read_stmt{};
        node_base* Write_stmt{};

        node_base * Eval(int,std::deque<std::string>&) override;

        ~node_Statement(){
            delete If_stmt;
            delete Repeat_stmt;
            delete Assign_stmt;
            delete Read_stmt;
            delete Write_stmt;
        }
    };

    struct node_If_stmt final : public node_base{
        token_base* If{};
        node_base* Exp{};
        token_base* Then{};
        node_base* Stmt_sequence_1{};
        token_base* Else{};
        node_base* Stmt_sequence_2{};
        token_base* End{};

        node_base * Eval(int,std::deque<std::string>&) override;

        ~node_If_stmt(){
            delete If;
            delete Exp;
            delete Then;
            delete Stmt_sequence_1;
            delete Else;
            delete Stmt_sequence_2;
            delete End;
        }
    };

    struct node_Repeat_stmt final : public node_base{
        token_base* Repeat{};
        node_base* Stmt_sequence{};
        token_base* Until{};
        node_base* Exp{};

        node_base * Eval(int,std::deque<std::string>&) override;

        ~node_Repeat_stmt(){
            delete Repeat;
            delete Stmt_sequence;
            delete Until;
            delete Exp;
        }
    };

    struct node_Assign_stmt final : public node_base{
        token_base* Identifier{};
        token_base* Assign{};
        node_base* Exp{};

        node_base * Eval(int,std::deque<std::string>&) override;

        ~node_Assign_stmt(){
            delete Identifier;
            delete Assign;
            delete Exp;
        }
    };

    struct node_Read_stmt final : public node_base{
        token_base* Read{};
        token_base* Identifier{};

        node_base * Eval(int,std::deque<std::string>&) override;

        ~node_Read_stmt(){
            delete Read;
            delete Identifier;
        }
    };

    struct node_Write_stmt final : public node_base{
        token_base* Write{};
        node_base* Exp{};

        node_base * Eval(int,std::deque<std::string>&) override;

        ~node_Write_stmt(){
            delete Write;
            delete Exp;
        }
    };

    struct node_Exp final : public node_base{
        node_base* Simple_exp_1{};
        node_base* Comparison_op{};
        node_base* Simple_exp_2{};

        node_base * Eval(int,std::deque<std::string>&) override;

        ~node_Exp(){
            delete Simple_exp_1;
            delete Comparison_op;
            delete Simple_exp_2;
        }
    };

    struct node_Comparison_op final : public node_base{
        token_base* Comparison_op{};

        node_base * Eval(int,std::deque<std::string>&) override;

        ~node_Comparison_op(){
            delete Comparison_op;
        }
    };

    struct node_Simple_exp final : public node_base{
        node_base* Term_1{};
        node_base* AddOp{};
        node_base* Term_2{};

        node_base * Eval(int,std::deque<std::string>&) override;

        ~node_Simple_exp(){
            delete Term_1;
            delete AddOp;
            delete Term_2;
        }
    };

    struct node_AddOp final : public node_base{
        token_base* AddOp{};

        node_base * Eval(int,std::deque<std::string>&) override;

        ~node_AddOp(){
            delete AddOp;
        }
    };

    struct node_Term final : public node_base{
        node_base* Factor_1{};
        node_base* MulOp{};
        node_base* Factor_2{};

        node_base * Eval(int,std::deque<std::string>&) override;

        ~node_Term(){
            delete Factor_1;
            delete MulOp;
            delete Factor_2;
        }
    };

    struct node_MulOp final : public node_base{
        token_base* MulOp{};

        node_base * Eval(int,std::deque<std::string>&) override;

        ~node_MulOp(){
            delete MulOp;
        }
    };

    struct node_Factor final : public node_base{
        token_base* Left_B{};
        node_base* Exp{};
        token_base* Right_B{};
        token_base* Number{};
        token_base* Identifier{};

        node_base * Eval(int,std::deque<std::string>&) override;

        ~node_Factor(){
            delete Left_B;
            delete Exp;
            delete Right_B;
            delete Number;
            delete Identifier;
        }
    };

}
