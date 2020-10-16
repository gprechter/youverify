lexer: Main.c lex.l DoubleLink.h DoubleLink.c Queue.h Queue.c Token.h Token.c lex.yy.h
	lex lex.l
	gcc Main.c lex.yy.c lex.yy.h DoubleLink.h DoubleLink.c Queue.h Queue.c Token.h Token.c

queue: DoubleLink.h DoubleLink.c Queue.h Queue.c
	gcc DoubleLink.h DoubleLink.c Queue.h Queue.c

parser: lex2.l parse.y
	yacc -d parse.y
	flex lex2.l
	gcc lex.yy.c y.tab.c y.tab.h -ll
