#include "Demo.h"

#include <string>
#include "Lexer.h"
#include "Parser.h"
#include "Compiler.h"
#include "VM.h"


// --- Demo main: parse, compile, run ---
void Demo()
{
    std::string code = "let x = 10; let y = x * 2 + 3; print y;";
    Lexer lexer(code);
    Parser parser(lexer);
    auto stmts = parser.parseProgram();

    Compiler compiler;
    auto bytecode = compiler.compile(stmts);

    // For demo: print bytecode
    std::cout << "Bytecode (op, operand):\n";
    for (size_t i = 0; i < bytecode.size(); ++i) {
        std::cout << i << ": " << (int)bytecode[i].op
            << ", " << bytecode[i].operand << "\n";
    }

    VM vm(bytecode, compiler.getVarNames());
    vm.run();
}
