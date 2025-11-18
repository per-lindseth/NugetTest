#pragma once

#include <stdexcept>
#include <vector>

#include "AST_nodes.h"
#include "Instruction.h"

class Compiler {
public:
    Compiler() {}

    std::vector<Instruction> compile(const std::vector<Stmt*>& stmts) {
        bytecode.clear();
        for (Stmt* s : stmts) compileStmt(s);
        bytecode.push_back({ OP_HALT, 0 });
        return bytecode;
    }

    const std::vector<std::string>& getConstants() const { return constants; }
    const std::vector<std::string>& getVarNames() const { return varnames; }

private:
    std::vector<Instruction> bytecode;
    std::vector<std::string> constants; // not heavily used here, but placeholder
    std::vector<std::string> varnames;

    int findVarIndex(const std::string& name) {
        for (size_t i = 0; i < varnames.size(); ++i) if (varnames[i] == name) return (int)i;
        varnames.push_back(name);
        return (int)(varnames.size() - 1);
    }

    void compileStmt(Stmt* s) {
        if (auto* ls = dynamic_cast<LetStmt*>(s)) {
            compileExpr(ls->expr);
            int idx = findVarIndex(ls->name);
            bytecode.push_back({ OP_STORE_VAR, idx });
        }
        else if (auto* ps = dynamic_cast<PrintStmt*>(s)) {
            compileExpr(ps->expr);
            bytecode.push_back({ OP_PRINT, 0 });
            bytecode.push_back({ OP_POP, 0 });
        }
        else if (auto* es = dynamic_cast<ExprStmt*>(s)) {
            compileExpr(es->expr);
            bytecode.push_back({ OP_POP, 0 });
        }
    }

    void compileExpr(Expr* e) {
        if (auto* n = dynamic_cast<NumberExpr*>(e)) {
            bytecode.push_back({ OP_CONST_INT, n->value });
            return;
        }
        if (auto* v = dynamic_cast<VariableExpr*>(e)) {
            int idx = findVarIndex(v->name);
            bytecode.push_back({ OP_LOAD_VAR, idx });
            return;
        }
        if (auto* b = dynamic_cast<BinaryExpr*>(e)) {
            compileExpr(b->left);
            compileExpr(b->right);
            switch (b->op) {
            case '+': bytecode.push_back({ OP_ADD, 0 }); break;
            case '-': bytecode.push_back({ OP_SUB, 0 }); break;
            case '*': bytecode.push_back({ OP_MUL, 0 }); break;
            case '/': bytecode.push_back({ OP_DIV, 0 }); break;
            }
            return;
        }
        throw std::runtime_error("Unknown expression in compiler");
    }
};
