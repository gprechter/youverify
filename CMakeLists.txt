cmake_minimum_required(VERSION 3.17)
project(youverify C)
find_package(BISON)
find_package(FLEX)

set(CMAKE_C_STANDARD 11)
BISON_TARGET(MyParser src/parse.y ${CMAKE_CURRENT_BINARY_DIR}/y.tab.c)
FLEX_TARGET(MyLexer src/lexer.l ${CMAKE_CURRENT_BINARY_DIR}/lex.yy.c)
ADD_FLEX_BISON_DEPENDENCY(MyLexer MyParser)

include_directories(src)
include_directories(${CMAKE_CURRENT_BINARY_DIR})



add_executable(youverify
        src/DoubleLink.c
        src/DoubleLink.h
        src/Execution.c
        src/Execution.h
        src/LinkedList.c
        src/LinkedList.h
        src/Queue.c
        src/Queue.h
        src/AST/Instruction.c src/AST/Instruction.h src/AST/Value.c src/AST/Value.h src/AST/Identifier.c src/AST/Identifier.h src/AST/Expression.c src/AST/Expression.h src/AST/Expressions/BinaryExpression.h src/AST/Expressions/AtomicExpression.c src/AST/Expressions/AtomicExpression.h src/AST/Expressions/UnaryExpression.h src/AST/Expressions/TernaryExpression.h src/AST/Instructions/GotoInstruction.h src/AST/Instructions/AssignmentInstruction.h src/AST/Instructions/DeclarationInstruction.h src/AST/Instructions/FunctionDefineInstruction.h src/Analyze/SymbolTable.c src/Analyze/SymbolTable.h src/Analyze/HashMap.c src/Analyze/HashMap.h src/Analyze/Program.c src/Analyze/Program.h src/Analyze/Function.c src/Analyze/Function.h src/Main.c src/Main.h src/AST/Expressions/FunctionCallExpression.h src/AST/Instructions/ReturnInstruction.h src/Memory.c src/Memory.h src/Runtime/RT_Variable.c src/Runtime/RT_Variable.h src/Runtime/RT_Value.c src/Runtime/RT_Value.h src/Runtime/Instructions/RT_AssignmentInstruction.h src/Runtime/RT_Expression.c src/Runtime/RT_Expression.h src/Runtime/Instructions/RT_GotoInstruction.h src/Runtime/Instructions/RT_ReturnInstruction.h src/Runtime/RT_Instruction.c src/Runtime/RT_Instruction.h src/Runtime/Expressions/RT_NewArrayExpression.h src/Runtime/Expressions/RT_ArrayAccessExpression.h src/AST/Expressions/ArrayAccessExpression.h src/AST/Expressions/NewArrayExpression.h src/Operators/Operator.c src/Operators/Operator.h src/AST/Expressions/NewStructExpression.h src/AST/Expressions/FieldAccessExpression.h src/Runtime/Expressions/RT_FieldAccessExpression.h src/AST/Expressions/MemoryAllocateExpression.h src/Runtime/Expressions/RT_MemoryAllocateExpression.h src/AST/Expressions/DereferenceExpression.h src/Runtime/Expressions/RT_DerefernceExpression.h src/Operators/CoreOperators.c src/Operators/CoreOperators.h src/Operators/ConsumeValue.c src/Operators/ConsumeValue.h src/Operators/IntegerOperators.c src/Operators/IntegerOperators.h src/Utilities.c src/Utilities.h src/Operators/BitVectorOperators.c src/Operators/BitVectorOperators.h src/Operators/RealOperators.c src/Operators/RealOperators.h src/Operators/RealsIntsOperators.c src/Operators/RealsIntsOperators.h src/Operators/FloatingPointOperators.c src/Operators/FloatingPointOperators.h src/List.c src/List.h src/parse.h src/Runtime/RT_Environment.c src/Runtime/RT_Environment.h
        ${BISON_MyParser_OUTPUTS}
        ${FLEX_MyLexer_OUTPUTS})
target_link_libraries(${PROJECT_NAME} m)