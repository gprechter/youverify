lexer: Main.c lex.l DoubleLink.h DoubleLink.c Queue.h Queue.c Token.h Token.c lex.yy.h
	lex lex.l
	gcc Main.c lex.yy.c lex.yy.h DoubleLink.h DoubleLink.c Queue.h Queue.c Token.h Token.c

queue: DoubleLink.h DoubleLink.c Queue.h Queue.c
	gcc DoubleLink.h DoubleLink.c Queue.h Queue.c