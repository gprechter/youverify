/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



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




/* Copy the first part of user declarations.  */
#line 1 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/src/parse.y"

    #include <stdio.h>
    #include <stdlib.h>
    #include <stdbool.h>
    #include <string.h>
    #include "parse.h"
    #include "Queue.h"
    #include "LinkedList.h"
    #include "DoubleLink.h"
    #include "AST/Identifier.h"
    #include "AST/Expression.h"
    #include "AST/Instruction.h"
    #include "AST/Expressions/AtomicExpression.h"
    #include "Analyze/HashMap.h"
    #include "Analyze/SymbolTable.h"
    #include "Analyze/Program.h"
    #include "Execution.h"
    #include "Analyze/Function.h"

    int yylex();
    int yyerror();

    PROGRAM *RESULT;

    QueuePtr instQueue;
    LinkedListPtr functions;
    QueuePtr funcInstQueue;
    LinkedListPtr labels;
    LinkedListPtr identifiers;
    int lineNumber = 0;
    int funcLineNumber = 0;
    extern FILE *yyin;
    SYMBOL_TABLE attributes;
    


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

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
/* Line 193 of yacc.c.  */
#line 282 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/cmake-build-debug/y.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 295 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/cmake-build-debug/y.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   230

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  73
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  18
/* YYNRULES -- Number of rules.  */
#define YYNRULES  94
/* YYNRULES -- Number of states.  */
#define YYNSTATES  202

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   324

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    72,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    71,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    70,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     7,    15,    16,    17,    21,    25,    26,
      30,    43,    47,    51,    54,    57,    59,    62,    64,    68,
      74,    76,    78,    82,    83,    85,    89,    92,    96,   101,
     103,   107,   114,   120,   125,   130,   133,   134,   136,   140,
     142,   145,   148,   151,   155,   159,   163,   167,   171,   175,
     179,   183,   187,   191,   195,   198,   201,   205,   209,   213,
     217,   221,   225,   229,   233,   237,   241,   244,   248,   253,
     256,   260,   264,   268,   272,   276,   279,   283,   287,   291,
     295,   298,   301,   304,   310,   315,   319,   324,   328,   333,
     336,   338,   340,   342,   344
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      74,     0,    -1,    75,    76,    85,    -1,    75,    33,     7,
      26,    77,    27,    68,    -1,    -1,    -1,    76,    78,    68,
      -1,    76,    79,    68,    -1,    -1,    77,    79,    68,    -1,
      32,     7,    21,    84,    22,    38,    82,    20,    68,    77,
      85,    37,    -1,    83,    20,    82,    -1,     7,    20,    82,
      -1,    69,    40,    -1,    81,    40,    -1,    69,    -1,    41,
       4,    -1,    81,    -1,    24,    69,    25,    -1,    24,    69,
      23,     4,    25,    -1,     7,    -1,     7,    -1,    83,    23,
       7,    -1,    -1,    80,    -1,    84,    23,    80,    -1,    86,
      68,    -1,    85,    86,    68,    -1,    31,     7,    20,    87,
      -1,    87,    -1,     7,    28,    89,    -1,     7,    24,    90,
      25,    28,    89,    -1,     7,    16,     7,    28,    89,    -1,
      40,     7,    28,    89,    -1,    29,    89,    30,     7,    -1,
      39,    89,    -1,    -1,    90,    -1,    88,    23,    90,    -1,
      90,    -1,     9,    90,    -1,    18,    90,    -1,    70,    90,
      -1,    90,    11,    90,    -1,    90,    12,    90,    -1,    90,
      13,    90,    -1,    90,    10,    90,    -1,    90,    17,    90,
      -1,    90,    18,    90,    -1,    90,    40,    90,    -1,    90,
      71,    90,    -1,    90,    72,    90,    -1,    90,    14,    90,
      -1,    90,    15,    90,    -1,    42,    90,    -1,    43,    90,
      -1,    90,    44,    90,    -1,    90,    58,    90,    -1,    90,
      57,    90,    -1,    90,    59,    90,    -1,    90,    60,    90,
      -1,    90,    61,    90,    -1,    90,    62,    90,    -1,    90,
      63,    90,    -1,    90,    64,    90,    -1,    90,    57,    90,
      -1,    57,    90,    -1,    90,    58,    90,    -1,    45,    90,
      90,    90,    -1,    46,    90,    -1,    90,    47,    90,    -1,
      90,    48,    90,    -1,    90,    54,    90,    -1,    90,    55,
      90,    -1,    90,    56,    90,    -1,    49,    90,    -1,    90,
      50,    90,    -1,    90,    51,    90,    -1,    90,    52,    90,
      -1,    90,    53,    90,    -1,    65,    90,    -1,    66,    90,
      -1,    67,    90,    -1,    90,    19,    90,    20,    90,    -1,
       7,    21,    88,    22,    -1,    24,    88,    25,    -1,     7,
      24,    90,    25,    -1,     7,    16,     7,    -1,    35,    21,
       4,    22,    -1,    40,     7,    -1,     3,    -1,     4,    -1,
       5,    -1,     6,    -1,     7,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    69,    69,    76,    93,    95,    98,   104,   111,   114,
     121,   125,   139,   143,   150,   158,   163,   169,   172,   180,
     188,   193,   200,   207,   210,   217,   225,   232,   240,   244,
     246,   249,   252,   255,   258,   261,   265,   268,   275,   283,
     286,   289,   292,   295,   298,   301,   304,   307,   310,   313,
     316,   319,   322,   325,   328,   331,   334,   337,   340,   343,
     346,   349,   352,   355,   358,   361,   364,   367,   370,   373,
     376,   379,   382,   385,   388,   391,   394,   397,   400,   403,
     406,   409,   412,   415,   418,   421,   424,   427,   430,   433,
     438,   439,   440,   441,   442
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "BOOL", "INTEGER", "BITVECTOR", "REAL",
  "IDENTIFIER", "NUMBER", "NOT", "IMPLIES", "AND", "OR", "XOR", "EQUALS",
  "DISTINCT", "DOT", "PLUS", "MINUS", "QMARK", "COLON", "OPAREN", "CPAREN",
  "COMMA", "OBRACKET", "CBRACKET", "OBRACE", "CBRACE", "ASSIGN", "IF",
  "GOTO", "LAB", "DEFINE", "STRUCT", "ENDSTRUCT", "MEMALLOC", "BEGIN_FUNC",
  "END_FUNC", "ARROW", "RETURN", "ASTERISK", "BITVEC", "BV2NAT", "NAT2BV",
  "BVCONCAT", "BVEXTRACT", "BVNOT", "BVAND", "BVOR", "BVNEG", "BVADD",
  "BVMUL", "BVUDIV", "BVUREM", "BVSHL", "BVLSHR", "BVULT", "RMINUS",
  "RADD", "RMUL", "RDIV", "RLEQ", "RLE", "RGEQ", "RGE", "RITOREAL",
  "RITOINT", "RIISINT", "EOL", "C_TYPE", "'|'", "'/'", "'%'", "$accept",
  "program", "TYPE_DECLARATIONS", "declarations_and_functions",
  "declarations", "function", "multiple_target_declaration", "declaration",
  "R_TYPE", "T_TYPE", "identifier_list", "commalist", "statements",
  "stmt_with_opt_label", "stmt", "exprlist", "expr", "term", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     124,    47,    37
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    73,    74,    75,    75,    76,    76,    76,    77,    77,
      78,    79,    80,    81,    81,    82,    82,    82,    82,    82,
      82,    83,    83,    84,    84,    84,    85,    85,    86,    86,
      87,    87,    87,    87,    87,    87,    88,    88,    88,    89,
      89,    89,    89,    89,    89,    89,    89,    89,    89,    89,
      89,    89,    89,    89,    89,    89,    89,    89,    89,    89,
      89,    89,    89,    89,    89,    89,    89,    89,    89,    89,
      89,    89,    89,    89,    89,    89,    89,    89,    89,    89,
      89,    89,    89,    89,    89,    89,    89,    89,    89,    89,
      90,    90,    90,    90,    90
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     3,     7,     0,     0,     3,     3,     0,     3,
      12,     3,     3,     2,     2,     1,     2,     1,     3,     5,
       1,     1,     3,     0,     1,     3,     2,     3,     4,     1,
       3,     6,     5,     4,     4,     2,     0,     1,     3,     1,
       2,     2,     2,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     2,     2,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     2,     3,     4,     2,
       3,     3,     3,     3,     3,     2,     3,     3,     3,     3,
       2,     2,     2,     5,     4,     3,     4,     3,     4,     2,
       1,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,     0,     5,     1,     0,     0,     0,    21,     0,     0,
       0,     0,     0,     0,     0,     0,     2,     0,    29,     8,
       0,     0,     0,    90,    91,    92,    93,    94,     0,     0,
      36,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    39,     0,     0,    35,     0,     6,
       7,     0,     0,     0,     0,    26,     0,     0,    94,     0,
      30,     0,    36,     0,    40,    41,     0,    37,     0,    89,
      54,    55,     0,    69,    75,    66,    80,    81,    82,    42,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    23,     0,    20,     0,     0,    15,    17,    11,
      22,    27,    21,     0,     0,     0,     0,    87,     0,     0,
       0,    85,     0,     0,    34,    46,    43,    44,    45,    52,
      53,    47,    48,     0,    49,    56,    70,    71,    76,    77,
      78,    79,    72,    73,    74,    58,    57,    59,    60,    61,
      62,    63,    64,    50,    51,    28,     0,    24,     0,    33,
       0,    16,    13,    14,     3,     9,    32,     0,    84,    86,
      38,    88,    68,     0,     0,     0,     0,     0,    18,    31,
      83,    12,     0,    25,     0,     0,    19,     0,     8,     0,
       0,    10
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     5,    56,    13,   124,   167,   118,   119,
      15,   168,    16,    17,    18,    66,    43,    44
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -180
static const yytype_int16 yypact[] =
{
    -180,     4,   -25,  -180,    34,    -4,     7,    14,    89,    43,
      47,    89,    90,   -23,    41,    38,    17,    42,  -180,  -180,
      95,   114,    89,  -180,  -180,  -180,  -180,    31,   114,   114,
     114,    84,    99,   114,   114,   114,   114,   114,   114,   114,
     114,   114,   114,    82,   158,   102,   104,  -180,   111,  -180,
    -180,    92,   116,    14,    59,  -180,    -1,   115,  -180,   117,
    -180,   137,   114,   114,  -180,  -180,     9,  -180,   141,  -180,
    -180,  -180,   114,  -180,  -180,  -180,  -180,  -180,  -180,  -180,
     140,   114,   114,   114,   114,   114,   114,   114,   114,   114,
     114,   114,   114,   114,   114,   114,   114,   114,   114,   114,
     114,   114,   114,   114,   114,   114,   114,   114,   114,   114,
     114,   101,   142,    89,  -180,    79,   146,   112,   113,  -180,
    -180,  -180,  -180,    83,    94,    89,   129,  -180,    37,   133,
     114,  -180,   138,   114,  -180,  -180,  -180,  -180,  -180,  -180,
    -180,  -180,  -180,   143,  -180,  -180,  -180,  -180,  -180,  -180,
    -180,  -180,  -180,  -180,  -180,  -180,  -180,  -180,  -180,  -180,
    -180,  -180,  -180,  -180,  -180,  -180,   145,  -180,    78,  -180,
      26,  -180,  -180,  -180,  -180,  -180,  -180,    89,  -180,  -180,
    -180,  -180,  -180,   114,    92,   128,   142,   170,  -180,  -180,
    -180,  -180,    92,  -180,   153,   159,  -180,   118,  -180,    97,
       0,  -180
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -180,  -180,  -180,  -180,   -18,  -180,   176,    -3,  -180,  -179,
    -180,  -180,   -17,   -16,    74,   125,   -10,   -19
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      54,    47,    59,     7,     3,   191,   122,    53,     4,    64,
      65,    67,    60,   195,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    53,     8,   123,     9,    10,     8,
      20,     9,   130,    19,   131,    11,    12,   201,    21,    11,
      12,     6,    22,    67,   129,    49,     8,    61,     9,   187,
      45,   188,    62,   133,    46,    63,    11,    12,    51,   178,
     130,    52,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   160,   161,   162,
     163,   164,    23,    24,    25,    26,    27,    48,    28,   114,
     185,   186,    57,   169,     7,    68,    69,    29,    53,    50,
      55,   180,    80,    30,   182,   176,   115,    23,    24,    25,
      26,    58,   111,   120,    31,   112,     8,   121,     9,    32,
       8,    33,    34,   116,    35,    36,    11,    12,    37,   113,
      11,    12,   126,   125,   127,   132,    38,   134,   170,   166,
     171,   174,   172,   173,    39,    40,    41,   177,   179,    42,
     181,   117,   175,   183,   190,   184,   192,   189,    81,    82,
      83,    84,    85,    86,   194,    87,    88,    89,   196,   197,
     199,    14,   200,   193,    54,   165,   198,   128,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    90,     0,
       0,     0,    91,     0,     0,    92,    93,     0,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,     0,     0,     0,     0,     0,     0,   109,
     110
};

static const yytype_int16 yycheck[] =
{
      16,    11,    21,     7,     0,   184,     7,     7,    33,    28,
      29,    30,    22,   192,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,     7,    29,    27,    31,    32,    29,
      16,    31,    23,    26,    25,    39,    40,    37,    24,    39,
      40,     7,    28,    62,    63,    68,    29,    16,    31,    23,
       7,    25,    21,    72,     7,    24,    39,    40,    20,    22,
      23,    23,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,     3,     4,     5,     6,     7,     7,     9,     7,
      22,    23,     7,   113,     7,    21,     7,    18,     7,    68,
      68,   130,    30,    24,   133,   125,    24,     3,     4,     5,
       6,     7,    20,     7,    35,    21,    29,    68,    31,    40,
      29,    42,    43,    41,    45,    46,    39,    40,    49,    28,
      39,    40,    25,    28,     7,     4,    57,     7,    69,     7,
       4,    68,    40,    40,    65,    66,    67,    28,    25,    70,
      22,    69,    68,    20,   183,    20,    38,   177,    10,    11,
      12,    13,    14,    15,     4,    17,    18,    19,    25,    20,
     198,     5,   199,   186,   200,   111,    68,    62,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    40,    -1,
      -1,    -1,    44,    -1,    -1,    47,    48,    -1,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    -1,    -1,    -1,    -1,    -1,    -1,    71,
      72
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    74,    75,     0,    33,    76,     7,     7,    29,    31,
      32,    39,    40,    78,    79,    83,    85,    86,    87,    26,
      16,    24,    28,     3,     4,     5,     6,     7,     9,    18,
      24,    35,    40,    42,    43,    45,    46,    49,    57,    65,
      66,    67,    70,    89,    90,     7,     7,    89,     7,    68,
      68,    20,    23,     7,    86,    68,    77,     7,     7,    90,
      89,    16,    21,    24,    90,    90,    88,    90,    21,     7,
      90,    90,    90,    90,    90,    90,    90,    90,    90,    90,
      30,    10,    11,    12,    13,    14,    15,    17,    18,    19,
      40,    44,    47,    48,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    71,
      72,    20,    21,    28,     7,    24,    41,    69,    81,    82,
       7,    68,     7,    27,    79,    28,    25,     7,    88,    90,
      23,    25,     4,    90,     7,    90,    90,    90,    90,    90,
      90,    90,    90,    90,    90,    90,    90,    90,    90,    90,
      90,    90,    90,    90,    90,    90,    90,    90,    90,    90,
      90,    90,    90,    90,    90,    87,     7,    80,    84,    89,
      69,     4,    40,    40,    68,    68,    89,    28,    22,    25,
      90,    22,    90,    20,    20,    22,    23,    23,    25,    89,
      90,    82,    38,    80,     4,    82,    25,    20,    68,    77,
      85,    37
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 69 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/src/parse.y"
    {
    PROGRAM *result = (PROGRAM *) malloc(sizeof(PROGRAM));
    result->declarations = (yyvsp[(2) - (3)].q);
    result->statements = (yyvsp[(3) - (3)].q);
    RESULT = result;
;}
    break;

  case 3:
#line 76 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/src/parse.y"
    {
  TYPE* newStructType = malloc(sizeof(TYPE));
  newStructType->id = getNextID();
  HashMap* fields = newHashMap();
  int totalSize = 0;
  while(!isEmpty((yyvsp[(5) - (7)].q))) {
    DECLARATION_INSTRUCTION decl = ((INSTRUCTION *) pop((yyvsp[(5) - (7)].q)))->contents.declarationInstruction;
    FIELDINFO* field = malloc(sizeof(FIELDINFO));
    field->type = decl.type;
    field->offset = totalSize;
    totalSize = totalSize + decl.type.bits;
    HM_put(fields, decl.identifier.id, (void*)field);
  }
  newStructType->metadata.fields = fields;
  newStructType->bits = totalSize;
  HM_put(idToType, (yyvsp[(3) - (7)].id).id, (void*)newStructType);
;}
    break;

  case 4:
#line 93 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/src/parse.y"
    {;}
    break;

  case 5:
#line 95 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/src/parse.y"
    {
   (yyval.q) = newQueue();
;}
    break;

  case 6:
#line 98 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/src/parse.y"
    {
    INSTRUCTION *iPtr = (INSTRUCTION *) malloc(sizeof(INSTRUCTION));
    *iPtr = (yyvsp[(2) - (3)].instr);
    push((yyvsp[(1) - (3)].q), iPtr);
    (yyval.q) = (yyvsp[(1) - (3)].q);
;}
    break;

  case 7:
#line 104 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/src/parse.y"
    {
    while(!isEmpty((yyvsp[(2) - (3)].q))) {
        push((yyvsp[(1) - (3)].q), pop((yyvsp[(2) - (3)].q)));
    }
    (yyval.q) = (yyvsp[(1) - (3)].q);
;}
    break;

  case 8:
#line 111 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/src/parse.y"
    {
   (yyval.q) = newQueue();
;}
    break;

  case 9:
#line 114 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/src/parse.y"
    {
    while(!isEmpty((yyvsp[(2) - (3)].q))) {
        push((yyvsp[(1) - (3)].q), pop((yyvsp[(2) - (3)].q)));
    }
    (yyval.q) = (yyvsp[(1) - (3)].q);
;}
    break;

  case 10:
#line 121 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/src/parse.y"
    {
    (yyval.instr) = newFUNCTION_DEFINE_INSTRUCTION((yyvsp[(2) - (12)].id), (yyvsp[(4) - (12)].q), (yyvsp[(7) - (12)].type), (yyvsp[(10) - (12)].q), (yyvsp[(11) - (12)].q));
;}
    break;

  case 11:
#line 125 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/src/parse.y"
    {
  QueuePtr queue = newQueue();
  while(!isEmpty((yyvsp[(1) - (3)].q))) {
      Identifier* idPtr = pop((yyvsp[(1) - (3)].q));
      INSTRUCTION* declarationInst = malloc(sizeof(INSTRUCTION));
      *declarationInst = newDECLARATION_INSTRUCTION(*idPtr, (yyvsp[(3) - (3)].type));
      free(idPtr);
      push(queue, (void *) declarationInst);
  }
  free((yyvsp[(1) - (3)].q));
  (yyval.q) = queue;
;}
    break;

  case 12:
#line 139 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/src/parse.y"
    {
    (yyval.instr) = newDECLARATION_INSTRUCTION((yyvsp[(1) - (3)].id), (yyvsp[(3) - (3)].type));
;}
    break;

  case 13:
#line 143 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/src/parse.y"
    {
    TYPE type = getType("REF");
    TYPE* referencedType;
    HM_get(idToType, (yyvsp[(1) - (2)].valueType), &referencedType);
    type.metadata.referencedType = referencedType;
    (yyval.type) = type;
;}
    break;

  case 14:
#line 150 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/src/parse.y"
    {
    TYPE type = getType("REF");
    TYPE* referencedType = malloc(sizeof(TYPE));
    *referencedType = (yyvsp[(1) - (2)].type);
    type.metadata.referencedType = referencedType;
    (yyval.type) = type;
;}
    break;

  case 15:
#line 158 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/src/parse.y"
    { // TODO; make it so that Structures can be the type in an array
    TYPE* type;
    HM_get(idToType, (yyvsp[(1) - (1)].valueType), &type);
    (yyval.type) = *type;
;}
    break;

  case 16:
#line 163 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/src/parse.y"
    {
    TYPE type;
    type.id = TID_bitvector;
    type.bits = (yyvsp[(2) - (2)].value).contents.INT;
    (yyval.type) = type;
;}
    break;

  case 17:
#line 169 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/src/parse.y"
    {
    (yyval.type) = (yyvsp[(1) - (1)].type);
;}
    break;

  case 18:
#line 172 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/src/parse.y"
    {
   TYPE type = getType("ARR");
       TYPE* elemType = malloc(sizeof(TYPE));
       HM_get(idToType, (yyvsp[(2) - (3)].valueType), &elemType);
       type.metadata.array_info.elementType = elemType;
       type.metadata.array_info.elements = 0;
       (yyval.type) = type;
;}
    break;

  case 19:
#line 180 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/src/parse.y"
    {
    TYPE type = getType("ARR");
    TYPE* elemType = malloc(sizeof(TYPE));
    HM_get(idToType, (yyvsp[(2) - (5)].valueType), &elemType);
    type.metadata.array_info.elementType = elemType;
    type.metadata.array_info.elements = (yyvsp[(4) - (5)].value).contents.INT;
    (yyval.type) = type;
;}
    break;

  case 20:
#line 188 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/src/parse.y"
    {
   TYPE type = getType((yyvsp[(1) - (1)].id).id);
   (yyval.type) = type;
;}
    break;

  case 21:
#line 193 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/src/parse.y"
    {
     QueuePtr new = newQueue();
     Identifier *iPtr = (Identifier *) malloc(sizeof(Identifier));
     *iPtr = (yyvsp[(1) - (1)].id);
     push(new, (void *) iPtr);
     (yyval.q) = new;
;}
    break;

  case 22:
#line 200 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/src/parse.y"
    {
  Identifier *iPtr = (Identifier *) malloc(sizeof(Identifier));
  *iPtr = (yyvsp[(3) - (3)].id);
  push((yyvsp[(1) - (3)].q), (void *) iPtr);
  (yyval.q) = (yyvsp[(1) - (3)].q);
;}
    break;

  case 23:
#line 207 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/src/parse.y"
    {
  (yyval.q) = newQueue();
;}
    break;

  case 24:
#line 210 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/src/parse.y"
    {
  QueuePtr new = newQueue();
  INSTRUCTION *iPtr = (INSTRUCTION *) malloc(sizeof(INSTRUCTION));
  *iPtr = (yyvsp[(1) - (1)].instr);
  push(new, iPtr);
  (yyval.q) = new;
;}
    break;

  case 25:
#line 217 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/src/parse.y"
    {
  INSTRUCTION *iPtr = (INSTRUCTION *) malloc(sizeof(INSTRUCTION));
  *iPtr = (yyvsp[(3) - (3)].instr);
  push((yyvsp[(1) - (3)].q), iPtr);
  (yyval.q) = (yyvsp[(1) - (3)].q);
;}
    break;

  case 26:
#line 225 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/src/parse.y"
    {
    QueuePtr queue = newQueue();
    INSTRUCTION *iPtr = (INSTRUCTION *) malloc(sizeof(INSTRUCTION));
    *iPtr = (yyvsp[(1) - (2)].instr);
    push(queue, iPtr);
    (yyval.q) = queue;
;}
    break;

  case 27:
#line 232 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/src/parse.y"
    {
    INSTRUCTION *iPtr = (INSTRUCTION *) malloc(sizeof(INSTRUCTION));
    *iPtr = (yyvsp[(2) - (3)].instr);
    push((yyvsp[(1) - (3)].q), iPtr);
    (yyval.q) = (yyvsp[(1) - (3)].q);
;}
    break;

  case 28:
#line 240 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/src/parse.y"
    {
    (yyvsp[(4) - (4)].instr).label = (yyvsp[(2) - (4)].id).id;
    (yyval.instr) = (yyvsp[(4) - (4)].instr);
;}
    break;

  case 30:
#line 246 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/src/parse.y"
    {
    (yyval.instr) = newASSIGNMENT_INSTRUCTION_TO_IDENTIFIER((yyvsp[(1) - (3)].id), (yyvsp[(3) - (3)].expression));
;}
    break;

  case 31:
#line 249 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/src/parse.y"
    {
    (yyval.instr) = newASSIGNMENT_INSTRUCTION_TO_ARRAY_ELEM(newArrayAccessExpression((yyvsp[(1) - (6)].id), (yyvsp[(3) - (6)].atom)).contents.arrayAccessExpression, (yyvsp[(6) - (6)].expression));
;}
    break;

  case 32:
#line 252 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/src/parse.y"
    {
    (yyval.instr) = newASSIGNMENT_INSTRUCTION_TO_FIELD(newFieldAccessExpression((yyvsp[(1) - (5)].id), (yyvsp[(3) - (5)].id)).contents.fieldAccessExpression, (yyvsp[(5) - (5)].expression));
;}
    break;

  case 33:
#line 255 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/src/parse.y"
    {
    (yyval.instr) = newASSIGNMENT_INSTRUCTION_TO_REFERENCE(newDereferenceExpression((yyvsp[(2) - (4)].id)).contents.dereferenceExpression, (yyvsp[(4) - (4)].expression));
;}
    break;

  case 34:
#line 258 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/src/parse.y"
    {
    (yyval.instr) = newGOTO_INSTRUCTION((yyvsp[(2) - (4)].expression), (yyvsp[(4) - (4)].id));
;}
    break;

  case 35:
#line 261 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/src/parse.y"
    {
    (yyval.instr) = newRETURN_INSTRUCTION((yyvsp[(2) - (2)].expression));
;}
    break;

  case 36:
#line 265 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/src/parse.y"
    {
  (yyval.q) = newQueue();
;}
    break;

  case 37:
#line 268 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/src/parse.y"
    {
  QueuePtr new = newQueue();
  EXPRESSION *ePtr = (EXPRESSION *) malloc(sizeof(EXPRESSION));
  *ePtr = newATOMIC_EXPRESSION((yyvsp[(1) - (1)].atom));
  push(new, ePtr);
  (yyval.q) = new;
;}
    break;

  case 38:
#line 275 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/src/parse.y"
    {
  EXPRESSION *ePtr = (EXPRESSION *) malloc(sizeof(EXPRESSION));
  *ePtr = newATOMIC_EXPRESSION((yyvsp[(3) - (3)].atom));
  push((yyvsp[(1) - (3)].q), ePtr);
  (yyval.q) = (yyvsp[(1) - (3)].q);
;}
    break;

  case 39:
#line 283 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/src/parse.y"
    {
    (yyval.expression) = newATOMIC_EXPRESSION((yyvsp[(1) - (1)].atom));
;}
    break;

  case 40:
#line 286 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/src/parse.y"
    {
    (yyval.expression) = newUNARY_EXPRESSION(U_OP_NOT, (yyvsp[(2) - (2)].atom));
;}
    break;

  case 41:
#line 289 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/src/parse.y"
    {
    (yyval.expression) = newUNARY_EXPRESSION(U_OP_MINUS, (yyvsp[(2) - (2)].atom));
;}
    break;

  case 42:
#line 292 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/src/parse.y"
    {
    (yyval.expression) = newUNARY_EXPRESSION(U_OP_ABS, (yyvsp[(2) - (2)].atom));
;}
    break;

  case 43:
#line 295 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/src/parse.y"
    {
    (yyval.expression) = newBINARY_EXPRESSION((yyvsp[(1) - (3)].atom), B_OP_AND, (yyvsp[(3) - (3)].atom));
;}
    break;

  case 44:
#line 298 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/src/parse.y"
    {
    (yyval.expression) = newBINARY_EXPRESSION((yyvsp[(1) - (3)].atom), B_OP_OR, (yyvsp[(3) - (3)].atom));
;}
    break;

  case 45:
#line 301 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/src/parse.y"
    {
    (yyval.expression) = newBINARY_EXPRESSION((yyvsp[(1) - (3)].atom), B_OP_XOR, (yyvsp[(3) - (3)].atom));
;}
    break;

  case 46:
#line 304 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/src/parse.y"
    {
    (yyval.expression) = newBINARY_EXPRESSION((yyvsp[(1) - (3)].atom), B_OP_IMPLIES, (yyvsp[(3) - (3)].atom));
;}
    break;

  case 47:
#line 307 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/src/parse.y"
    {
    (yyval.expression) = newBINARY_EXPRESSION((yyvsp[(1) - (3)].atom), B_OP_ADD, (yyvsp[(3) - (3)].atom));
;}
    break;

  case 48:
#line 310 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/src/parse.y"
    {
    (yyval.expression) = newBINARY_EXPRESSION((yyvsp[(1) - (3)].atom), B_OP_SUB, (yyvsp[(3) - (3)].atom));
;}
    break;

  case 49:
#line 313 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/src/parse.y"
    {
    (yyval.expression) = newBINARY_EXPRESSION((yyvsp[(1) - (3)].atom), B_OP_MUL, (yyvsp[(3) - (3)].atom));
;}
    break;

  case 50:
#line 316 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/src/parse.y"
    {
    (yyval.expression) = newBINARY_EXPRESSION((yyvsp[(1) - (3)].atom), B_OP_DIV, (yyvsp[(3) - (3)].atom));
;}
    break;

  case 51:
#line 319 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/src/parse.y"
    {
    (yyval.expression) = newBINARY_EXPRESSION((yyvsp[(1) - (3)].atom), B_OP_MOD, (yyvsp[(3) - (3)].atom));
;}
    break;

  case 52:
#line 322 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/src/parse.y"
    {
    (yyval.expression) = newBINARY_EXPRESSION((yyvsp[(1) - (3)].atom), B_OP_EQUALS, (yyvsp[(3) - (3)].atom));
;}
    break;

  case 53:
#line 325 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/src/parse.y"
    {
    (yyval.expression) = newBINARY_EXPRESSION((yyvsp[(1) - (3)].atom), B_OP_DISTINCT, (yyvsp[(3) - (3)].atom));
;}
    break;

  case 54:
#line 328 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/src/parse.y"
    {
    (yyval.expression) = newUNARY_EXPRESSION(U_BV2NAT, (yyvsp[(2) - (2)].atom));
;}
    break;

  case 55:
#line 331 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/src/parse.y"
    {
    (yyval.expression) = newUNARY_EXPRESSION(U_NAT2BV, (yyvsp[(2) - (2)].atom));
;}
    break;

  case 56:
#line 334 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/src/parse.y"
    {
    (yyval.expression) = newBINARY_EXPRESSION((yyvsp[(1) - (3)].atom), B_BVCONCAT, (yyvsp[(3) - (3)].atom));
;}
    break;

  case 57:
#line 337 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/src/parse.y"
    {
    (yyval.expression) = newBINARY_EXPRESSION((yyvsp[(1) - (3)].atom), B_OP_RADD, (yyvsp[(3) - (3)].atom));
;}
    break;

  case 58:
#line 340 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/src/parse.y"
    {
    (yyval.expression) = newBINARY_EXPRESSION((yyvsp[(1) - (3)].atom), B_OP_RSUB, (yyvsp[(3) - (3)].atom));
;}
    break;

  case 59:
#line 343 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/src/parse.y"
    {
    (yyval.expression) = newBINARY_EXPRESSION((yyvsp[(1) - (3)].atom), B_OP_RMUL, (yyvsp[(3) - (3)].atom));
;}
    break;

  case 60:
#line 346 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/src/parse.y"
    {
    (yyval.expression) = newBINARY_EXPRESSION((yyvsp[(1) - (3)].atom), B_OP_RDIV, (yyvsp[(3) - (3)].atom));
;}
    break;

  case 61:
#line 349 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/src/parse.y"
    {
    (yyval.expression) = newBINARY_EXPRESSION((yyvsp[(1) - (3)].atom), B_OP_RLEQ, (yyvsp[(3) - (3)].atom));
;}
    break;

  case 62:
#line 352 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/src/parse.y"
    {
    (yyval.expression) = newBINARY_EXPRESSION((yyvsp[(1) - (3)].atom), B_OP_RLE, (yyvsp[(3) - (3)].atom));
;}
    break;

  case 63:
#line 355 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/src/parse.y"
    {
    (yyval.expression) = newBINARY_EXPRESSION((yyvsp[(1) - (3)].atom), B_OP_RGEQ, (yyvsp[(3) - (3)].atom));
;}
    break;

  case 64:
#line 358 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/src/parse.y"
    {
    (yyval.expression) = newBINARY_EXPRESSION((yyvsp[(1) - (3)].atom), B_OP_RGE, (yyvsp[(3) - (3)].atom));
;}
    break;

  case 65:
#line 361 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/src/parse.y"
    {
    (yyval.expression) = newBINARY_EXPRESSION((yyvsp[(1) - (3)].atom), B_OP_RSUB, (yyvsp[(3) - (3)].atom));
;}
    break;

  case 66:
#line 364 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/src/parse.y"
    {
    (yyval.expression) = newUNARY_EXPRESSION(U_OP_RMINUS, (yyvsp[(2) - (2)].atom));
;}
    break;

  case 67:
#line 367 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/src/parse.y"
    {
    (yyval.expression) = newBINARY_EXPRESSION((yyvsp[(1) - (3)].atom), B_OP_RADD, (yyvsp[(3) - (3)].atom));
;}
    break;

  case 68:
#line 370 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/src/parse.y"
    {
    (yyval.expression) = newTERNARY_EXPRESSION(T_BVEXTRACT, (yyvsp[(2) - (4)].atom), (yyvsp[(3) - (4)].atom), (yyvsp[(4) - (4)].atom));
;}
    break;

  case 69:
#line 373 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/src/parse.y"
    {
    (yyval.expression) = newUNARY_EXPRESSION(U_BVNOT, (yyvsp[(2) - (2)].atom));
;}
    break;

  case 70:
#line 376 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/src/parse.y"
    {
    (yyval.expression) = newBINARY_EXPRESSION((yyvsp[(1) - (3)].atom), B_BVAND, (yyvsp[(3) - (3)].atom));
;}
    break;

  case 71:
#line 379 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/src/parse.y"
    {
    (yyval.expression) = newBINARY_EXPRESSION((yyvsp[(1) - (3)].atom), B_BVOR, (yyvsp[(3) - (3)].atom));
;}
    break;

  case 72:
#line 382 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/src/parse.y"
    {
    (yyval.expression) = newBINARY_EXPRESSION((yyvsp[(1) - (3)].atom), B_BVSHL, (yyvsp[(3) - (3)].atom));
;}
    break;

  case 73:
#line 385 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/src/parse.y"
    {
    (yyval.expression) = newBINARY_EXPRESSION((yyvsp[(1) - (3)].atom), B_BVLSHR, (yyvsp[(3) - (3)].atom));
;}
    break;

  case 74:
#line 388 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/src/parse.y"
    {
    (yyval.expression) = newBINARY_EXPRESSION((yyvsp[(1) - (3)].atom), B_BVULT, (yyvsp[(3) - (3)].atom));
;}
    break;

  case 75:
#line 391 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/src/parse.y"
    {
    (yyval.expression) = newUNARY_EXPRESSION(U_BVNEG, (yyvsp[(2) - (2)].atom));
;}
    break;

  case 76:
#line 394 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/src/parse.y"
    {
    (yyval.expression) = newBINARY_EXPRESSION((yyvsp[(1) - (3)].atom), B_BVADD, (yyvsp[(3) - (3)].atom));
;}
    break;

  case 77:
#line 397 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/src/parse.y"
    {
    (yyval.expression) = newBINARY_EXPRESSION((yyvsp[(1) - (3)].atom), B_BVMUL, (yyvsp[(3) - (3)].atom));
;}
    break;

  case 78:
#line 400 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/src/parse.y"
    {
    (yyval.expression) = newBINARY_EXPRESSION((yyvsp[(1) - (3)].atom), B_BVUDIV, (yyvsp[(3) - (3)].atom));
;}
    break;

  case 79:
#line 403 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/src/parse.y"
    {
    (yyval.expression) = newBINARY_EXPRESSION((yyvsp[(1) - (3)].atom), B_BVUREM, (yyvsp[(3) - (3)].atom));
;}
    break;

  case 80:
#line 406 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/src/parse.y"
    {
    (yyval.expression) = newUNARY_EXPRESSION(U_OP_ITR, (yyvsp[(2) - (2)].atom));
;}
    break;

  case 81:
#line 409 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/src/parse.y"
    {
    (yyval.expression) = newUNARY_EXPRESSION(U_OP_RTI, (yyvsp[(2) - (2)].atom));
;}
    break;

  case 82:
#line 412 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/src/parse.y"
    {
    (yyval.expression) = newUNARY_EXPRESSION(U_OP_ISINT, (yyvsp[(2) - (2)].atom));
;}
    break;

  case 83:
#line 415 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/src/parse.y"
    {
    (yyval.expression) = newTERNARY_EXPRESSION(T_ITE, (yyvsp[(1) - (5)].atom), (yyvsp[(3) - (5)].atom), (yyvsp[(5) - (5)].atom));
;}
    break;

  case 84:
#line 418 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/src/parse.y"
    {
    (yyval.expression) = newFunctionCallExpression((yyvsp[(1) - (4)].id), (yyvsp[(3) - (4)].q));
;}
    break;

  case 85:
#line 421 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/src/parse.y"
    {
    (yyval.expression) = newNewArrayExpression((yyvsp[(2) - (3)].q));
;}
    break;

  case 86:
#line 424 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/src/parse.y"
    {
    (yyval.expression) = newArrayAccessExpression((yyvsp[(1) - (4)].id), (yyvsp[(3) - (4)].atom));
;}
    break;

  case 87:
#line 427 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/src/parse.y"
    {
    (yyval.expression) = newFieldAccessExpression((yyvsp[(1) - (3)].id), (yyvsp[(3) - (3)].id));
;}
    break;

  case 88:
#line 430 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/src/parse.y"
    {
    (yyval.expression) = newMemoryAllocateExpression((yyvsp[(3) - (4)].value).contents.INT)
;}
    break;

  case 89:
#line 433 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/src/parse.y"
    {
    (yyval.expression) = newDereferenceExpression((yyvsp[(2) - (2)].id));
;}
    break;

  case 90:
#line 438 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/src/parse.y"
    { (yyval.atom) = newATOMIC_EXPRESSION_VALUE((yyvsp[(1) - (1)].value)); ;}
    break;

  case 91:
#line 439 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/src/parse.y"
    { (yyval.atom) = newATOMIC_EXPRESSION_VALUE((yyvsp[(1) - (1)].value)); ;}
    break;

  case 92:
#line 440 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/src/parse.y"
    { (yyval.atom) = newATOMIC_EXPRESSION_VALUE((yyvsp[(1) - (1)].value)); ;}
    break;

  case 93:
#line 441 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/src/parse.y"
    { (yyval.atom) = newATOMIC_EXPRESSION_VALUE((yyvsp[(1) - (1)].value)); ;}
    break;

  case 94:
#line 442 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/src/parse.y"
    { (yyval.atom) = newATOMIC_EXPRESSION_IDENTIFIER((yyvsp[(1) - (1)].id)); ;}
    break;


/* Line 1267 of yacc.c.  */
#line 2398 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/cmake-build-debug/y.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 444 "/Users/griffinprechter/Documents/School/Research/SE Research/youverify/src/parse.y"


yyerror(char *s) {
    fprintf(stderr, "error: %s\n", s);
}

FILE *readFile(char *filename) {
    FILE *fp;
    fp = fopen(filename,"r");
    return fp;
}

PROGRAM *parseProgram(char *filename) {
    yyin = readFile(filename);
    yyparse();
    return RESULT;
}
