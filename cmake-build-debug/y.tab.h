/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     BOOL = 258,
     INTEGER = 259,
     BITVECTOR = 260,
     REAL = 261,
     IDENTIFIER = 262,
     NUMBER = 263,
     NOT = 264,
     IMPLIES = 265,
     AND = 266,
     OR = 267,
     XOR = 268,
     EQUALS = 269,
     DISTINCT = 270,
     DOT = 271,
     PLUS = 272,
     MINUS = 273,
     QMARK = 274,
     COLON = 275,
     OPAREN = 276,
     CPAREN = 277,
     COMMA = 278,
     OBRACKET = 279,
     CBRACKET = 280,
     OBRACE = 281,
     CBRACE = 282,
     ASSIGN = 283,
     IF = 284,
     GOTO = 285,
     LAB = 286,
     DEFINE = 287,
     STRUCT = 288,
     ENDSTRUCT = 289,
     MEMALLOC = 290,
     BEGIN_FUNC = 291,
     END_FUNC = 292,
     ARROW = 293,
     RETURN = 294,
     ASTERISK = 295,
     BITVEC = 296,
     BV2NAT = 297,
     NAT2BV = 298,
     BVCONCAT = 299,
     BVEXTRACT = 300,
     BVNOT = 301,
     BVAND = 302,
     BVOR = 303,
     BVNEG = 304,
     BVADD = 305,
     BVMUL = 306,
     BVUDIV = 307,
     BVUREM = 308,
     BVSHL = 309,
     BVLSHR = 310,
     BVULT = 311,
     RMINUS = 312,
     RADD = 313,
     RMUL = 314,
     RDIV = 315,
     RLEQ = 316,
     RLE = 317,
     RGEQ = 318,
     RGE = 319,
     RITOREAL = 320,
     RITOINT = 321,
     RIISINT = 322,
     EOL = 323,
     C_TYPE = 324
   };
#endif
/* Tokens.  */
#define BOOL 258
#define INTEGER 259
#define BITVECTOR 260
#define REAL 261
#define IDENTIFIER 262
#define NUMBER 263
#define NOT 264
#define IMPLIES 265
#define AND 266
#define OR 267
#define XOR 268
#define EQUALS 269
#define DISTINCT 270
#define DOT 271
#define PLUS 272
#define MINUS 273
#define QMARK 274
#define COLON 275
#define OPAREN 276
#define CPAREN 277
#define COMMA 278
#define OBRACKET 279
#define CBRACKET 280
#define OBRACE 281
#define CBRACE 282
#define ASSIGN 283
#define IF 284
#define GOTO 285
#define LAB 286
#define DEFINE 287
#define STRUCT 288
#define ENDSTRUCT 289
#define MEMALLOC 290
#define BEGIN_FUNC 291
#define END_FUNC 292
#define ARROW 293
#define RETURN 294
#define ASTERISK 295
#define BITVEC 296
#define BV2NAT 297
#define NAT2BV 298
#define BVCONCAT 299
#define BVEXTRACT 300
#define BVNOT 301
#define BVAND 302
#define BVOR 303
#define BVNEG 304
#define BVADD 305
#define BVMUL 306
#define BVUDIV 307
#define BVUREM 308
#define BVSHL 309
#define BVLSHR 310
#define BVULT 311
#define RMINUS 312
#define RADD 313
#define RMUL 314
#define RDIV 315
#define RLEQ 316
#define RLE 317
#define RGEQ 318
#define RGE 319
#define RITOREAL 320
#define RITOINT 321
#define RIISINT 322
#define EOL 323
#define C_TYPE 324




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 36 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/src/parse.y"
{
    VALUE value;
    Identifier id;
    ATOMIC_EXPRESSION atom;
    EXPRESSION expression;
    INSTRUCTION instr;
    TYPE type;
    char* valueType;
    int num;
    QueuePtr q;
}
/* Line 1529 of yacc.c.  */
#line 199 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/cmake-build-debug/y.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

