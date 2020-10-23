lexer: Main.c lex.l DoubleLink.h DoubleLink.c Queue.h Queue.c Token.h Token.c lex.yy.h
	lex lex.l
	gcc Main.c lex.yy.c lex.yy.h DoubleLink.h DoubleLink.c Queue.h Queue.c Token.h Token.c

queue: DoubleLink.h DoubleLink.c Queue.h Queue.c
	gcc DoubleLink.h DoubleLink.c Queue.h Queue.c

parser: AST.c lex2.l parse.y AST.h DoubleLink.h DoubleLink.c Queue.h Queue.c Execution.h Execution.c
	yacc -d parse.y
	flex lex2.l
	gcc AST.h AST.c lex.yy.c y.tab.c y.tab.h DoubleLink.h DoubleLink.c Queue.h Queue.c Execution.h Execution.c -ll
