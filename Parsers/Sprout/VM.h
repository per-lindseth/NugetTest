#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "Instruction.h"

class VM {
public:
    VM(const std::vector<Instruction>& code, const std::vector<std::string>& varnames)
        : code(code), pc(0), vars(varnames.size(), 0) {
    }

    void run() {
        while (pc < (int)code.size()) {
            const Instruction& ins = code[pc++];
            switch (ins.op) {
            case OP_CONST_INT: stack.push_back(ins.operand); break;
            case OP_LOAD_VAR: stack.push_back(vars.at(ins.operand)); break;
            case OP_STORE_VAR: {
                int val = pop();
                if (ins.operand >= (int)vars.size()) vars.resize(ins.operand + 1);
                vars[ins.operand] = val;
            } break;
            case OP_ADD: {
                int b = pop(); int a = pop(); stack.push_back(a + b);
            } break;
            case OP_SUB: {
                int b = pop(); int a = pop(); stack.push_back(a - b);
            } break;
            case OP_MUL: {
                int b = pop(); int a = pop(); stack.push_back(a * b);
            } break;
            case OP_DIV: {
                int b = pop(); int a = pop(); stack.push_back(a / b);
            } break;
            case OP_PRINT: {
                int v = pop(); std::cout << v << std::endl;
            } break;
            case OP_POP: pop(); break;
            case OP_HALT: return;
            }
        }
    }

private:
    std::vector<Instruction> code;
    int pc;
    std::vector<int> stack;
    std::vector<int> vars;

    int pop() {
        if (stack.empty()) throw std::runtime_error("stack underflow");
        int v = stack.back(); stack.pop_back(); return v;
    }
};

