#include <Tiny_Nodes.hpp>

namespace tn {
    void build_tree_version(int l, const std::string &info, std::deque<std::string> &Messages) {
        std::string mes = "";
        for (int i = 0; i < l; i++)
            mes.append("  ");
        mes.append(info);
        Messages.push_back(mes);
    }

    node_base *node_Program::Eval(int i, std::deque<std::string> &Messages) {
        if (Stmt_sequence) {
            Stmt_sequence->Eval(i, Messages);
        }

        return nullptr;
    }

    node_base *node_Stmt_sequence::Eval(int i, std::deque<std::string> &Messages) {
        if(Stmt_1)
            Stmt_1->Eval(i, Messages);
        if(Stmt_2)
            Stmt_2->Eval(i, Messages);
        return nullptr;
    }

    node_base *node_Statement::Eval(int i, std::deque<std::string> &Messages) {
        if (If_stmt) {
            If_stmt->Eval(i, Messages);
            return nullptr;
        } else if (Repeat_stmt) {
            Repeat_stmt->Eval(i, Messages);
            return nullptr;
        } else if (Assign_stmt) {
            Assign_stmt->Eval(i, Messages);
            return nullptr;
        } else if (Read_stmt) {
            Read_stmt->Eval(i, Messages);
            return nullptr;
        } else if (Write_stmt) {
            Write_stmt->Eval(i, Messages);
            return nullptr;
        }
        return nullptr;
    }

    node_base *node_If_stmt::Eval(int i, std::deque<std::string> &Messages) {
        int j = i + 1;
        build_tree_version(i, std::string("If"), Messages);
        Exp->Eval(j, Messages);
        Stmt_sequence_1->Eval(j, Messages);
        if (Else) {
            Stmt_sequence_2->Eval(j, Messages);
        }
        return nullptr;
    }

    node_base *node_Repeat_stmt::Eval(int i, std::deque<std::string> &Messages) {
        int j = i + 1;
        build_tree_version(i, std::string("Repeat"), Messages);;
        Stmt_sequence->Eval(j, Messages);
        Exp->Eval(j, Messages);
        return nullptr;
    }

    node_base *node_Assign_stmt::Eval(int i, std::deque<std::string> &Messages) {
        int j = i + 1;
        build_tree_version(i, std::string("Assign to: " + Identifier->get_string()), Messages);
        Exp->Eval(j, Messages);
        return nullptr;
    }

    node_base *node_Read_stmt::Eval(int i, std::deque<std::string> &Messages) {
        build_tree_version(i, std::string("Read: " + Identifier->get_string()), Messages);
        return nullptr;
    }

    node_base *node_Write_stmt::Eval(int i, std::deque<std::string> &Messages) {
        int j = i + 1;
        build_tree_version(i, std::string("Write"), Messages);
        Exp->Eval(j, Messages);
        return nullptr;
    }

    node_base *node_Exp::Eval(int i, std::deque<std::string> &Messages) {
        int j = i + 1;
        if (Comparison_op) {
            Comparison_op->Eval(i, Messages);
            Simple_exp_1->Eval(j, Messages);
            Simple_exp_2->Eval(j, Messages);
        } else {
            Simple_exp_1->Eval(i, Messages);
        }
        return nullptr;
    }

    node_base *node_Comparison_op::Eval(int i, std::deque<std::string> &Messages) {
        build_tree_version(i, std::string("Op: " + Comparison_op->get_string()), Messages);
        return nullptr;
    }

    node_base *node_Simple_exp::Eval(int i, std::deque<std::string> &Messages) {
        int j = i + 1;
        if (AddOp) {
            AddOp->Eval(i, Messages);
            Term_1->Eval(j, Messages);
            Term_2->Eval(j, Messages);
        } else {
            Term_1->Eval(i, Messages);
        }
        return nullptr;
    }

    node_base *node_AddOp::Eval(int i, std::deque<std::string> &Messages) {
        build_tree_version(i, std::string("Op: " + AddOp->get_string()), Messages);
        return nullptr;
    }

    node_base *node_Term::Eval(int i, std::deque<std::string> &Messages) {
        int j = i + 1;
        if (MulOp) {
            MulOp->Eval(i, Messages);
            if(Factor_1)
                Factor_1->Eval(j, Messages);
            if(Factor_2)
                Factor_2->Eval(j, Messages);
        } else {
            if(Factor_1)
                Factor_1->Eval(i, Messages);
        }
        return nullptr;
    }

    node_base *node_MulOp::Eval(int i, std::deque<std::string> &Messages) {
        build_tree_version(i, std::string("Op: " + MulOp->get_string()), Messages);
        return nullptr;
    }

    node_base *node_Factor::Eval(int i, std::deque<std::string> &Messages) {
        if (Left_B) {
            Exp->Eval(i, Messages);
            return nullptr;
        } else if (Number) {
            build_tree_version(i, std::string("Const: " + Number->get_string()), Messages);
            return nullptr;
        } else if (Identifier) {
            build_tree_version(i, std::string("Id: " + Identifier->get_string()), Messages);
            return nullptr;
        }
        return nullptr;
    }
}