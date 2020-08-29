/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "parser.y" /* yacc.c:339  */

#include <cstdio>
#include <iostream>
#include <map>
#include <vector>
#include <string>

#include "ast.hpp"
#include "lexer.hpp"


#line 78 "parser.cpp" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.hpp".  */
#ifndef YY_YY_PARSER_HPP_INCLUDED
# define YY_YY_PARSER_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 14 "parser.y" /* yacc.c:355  */
 
	#include "ast.hpp" 	
	#include <string>

#line 113 "parser.cpp" /* yacc.c:355  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    T_and = 258,
    T_end = 259,
    T_list = 260,
    T_ref = 261,
    T_bool = 262,
    T_exit = 263,
    T_mod = 264,
    T_return = 265,
    T_char = 266,
    T_false = 267,
    T_true = 268,
    T_new = 269,
    T_skip = 270,
    T_decl = 271,
    T_for = 272,
    T_nil = 273,
    T_tail = 274,
    T_head = 275,
    T_def = 276,
    T_nilq = 277,
    T_if = 278,
    T_else = 279,
    T_elsif = 280,
    T_not = 281,
    T_int = 282,
    T_or = 283,
    T_assign = 284,
    T_ge = 285,
    T_le = 286,
    T_neq = 287,
    T_constInt = 288,
    T_var = 289,
    T_constChar = 290,
    T_constString = 291,
    UPLUS = 292,
    UMINUS = 293
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 21 "parser.y" /* yacc.c:355  */

	FunctionDefinition 			*func_def;
	FunctionDeclaration 		*func_decl;
	DefinitionList 				*def_list;
	Header 						*header;
	Stmt 						*stmt;
	StmtList 					*stmt_list;
	Formal 						*formal;
	FormalList 					*formal_list;
	Expr 						*expr;
	ExprList 					* expr_list;
	Var 						*var;
	VarList 					*var_list;
	VarDefinition 				*var_definition;
	If 							*ifClass;
	For 						*forClass;
	CallObject 					*call_object;
	std::string 				*type;

	char 						chr;
	int 						num;
	const char 					*str;

#line 188 "parser.cpp" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_HPP_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 205 "parser.cpp" /* yacc.c:358  */

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
#else
typedef signed char yytype_int8;
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
# elif ! defined YYSIZE_T
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
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
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
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  11
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   571

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  54
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  23
/* YYNRULES -- Number of rules.  */
#define YYNRULES  77
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  156

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   293

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,    40,     2,     2,     2,     2,
      48,    49,    43,    41,    51,    42,     2,    44,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    47,    50,
      39,    37,    38,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    52,     2,    53,     2,     2,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    45,    46
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   118,   118,   122,   126,   130,   131,   132,   133,   137,
     138,   142,   143,   147,   148,   152,   153,   157,   158,   162,
     163,   167,   168,   169,   170,   171,   176,   181,   182,   183,
     184,   185,   189,   190,   194,   195,   199,   200,   201,   205,
     206,   210,   214,   215,   219,   220,   224,   225,   226,   227,
     231,   232,   233,   234,   235,   236,   237,   238,   239,   240,
     241,   242,   243,   244,   245,   246,   247,   248,   249,   250,
     251,   252,   253,   254,   255,   256,   257,   258
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "\"and\"", "\"end\"", "\"list\"",
  "\"ref\"", "\"bool\"", "\"exit\"", "\"mod\"", "\"return\"", "\"char\"",
  "\"false\"", "\"true\"", "\"new\"", "\"skip\"", "\"decl\"", "\"for\"",
  "\"nil\"", "\"tail\"", "\"head\"", "\"def\"", "\"nil?\"", "\"if\"",
  "\"else\"", "\"elsif\"", "\"not\"", "\"int\"", "\"or\"", "\":=\"",
  "\">=\"", "\"<=\"", "\"<>\"", "T_constInt", "T_var", "T_constChar",
  "T_constString", "'='", "'>'", "'<'", "'#'", "'+'", "'-'", "'*'", "'/'",
  "UPLUS", "UMINUS", "':'", "'('", "')'", "';'", "','", "'['", "']'",
  "$accept", "program", "func_def", "func_decl", "definition_list",
  "stmt_list", "header", "formal_list", "formal_head", "formal",
  "var_list", "type", "var_def", "stmt", "elsif_list", "else", "simple",
  "simple_list", "call", "expr_list", "expr_head", "atom", "expr", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,    61,    62,    60,
      35,    43,    45,    42,    47,   292,   293,    58,    40,    41,
      59,    44,    91,    93
};
# endif

#define YYPACT_NINF -71

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-71)))

#define YYTABLE_NINF -50

#define yytable_value_is_error(Yytable_value) \
  (!!((Yytable_value) == (-50)))

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -13,   369,     3,   -71,   -32,   -71,   -71,   -71,   -33,   -25,
     -24,   -71,   403,   -17,   -71,    -3,    24,   -28,    23,   439,
     517,   -17,   -71,   -71,   -71,   403,    30,    19,   -71,   429,
     -71,   369,   109,   429,    -1,   -71,   -71,   -71,   484,    19,
     -71,   -71,   -71,   -18,   -12,    35,    19,   -71,   -71,    34,
     -71,   -71,   403,   -71,    38,    39,    40,   429,   -71,   -71,
     429,   429,   429,   -71,    37,   381,   -71,   -71,     4,   299,
      41,   -71,   -71,    34,   429,   429,   -71,    34,    63,    46,
     429,   429,   429,    64,   -71,   -71,   211,   429,   429,   429,
     429,   429,   429,   429,   429,   429,   429,   429,   429,   429,
     429,   429,   109,   535,    50,   429,   381,   119,   -71,   353,
     231,   255,   275,   -71,    64,   -71,   396,   443,   443,   443,
     443,   443,   443,    -5,    -2,    -2,   -71,   -71,   185,   -71,
     531,   -71,   161,   -71,   143,   -71,   -71,   -71,   109,    53,
     429,   108,   -71,   -71,   -71,     1,   535,   317,   -71,   535,
     535,   535,   485,   531,   -71,   -71
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     2,     0,    22,    23,    21,     0,     0,
       0,     1,     0,    15,     5,     0,     0,     0,     0,     0,
       0,    15,    24,    25,    11,     0,    14,     0,    28,     0,
      36,     0,     0,     0,    46,    47,     6,     7,     0,     0,
       8,     9,    27,    38,     0,     0,     0,    16,    19,    17,
      68,    67,     0,    73,     0,     0,     0,     0,    51,    52,
       0,     0,     0,    49,    50,    29,     4,    39,     0,     0,
      44,     3,    10,    26,     0,     0,    12,    18,     0,     0,
       0,     0,     0,    69,    54,    55,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    37,     0,    20,     0,
       0,     0,     0,    53,    70,    60,    71,    66,    65,    64,
      61,    62,    63,    75,    56,    57,    58,    59,     0,    40,
      34,    41,    43,    48,     0,    77,    76,    74,     0,     0,
       0,     0,    32,    45,    72,     0,     0,     0,    30,     0,
      35,     0,     0,    34,    31,    33
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -71,   -71,    94,   -71,   -71,   -70,    86,    99,   -71,   -71,
     -23,    -6,   -71,   -37,   -30,   -71,   -27,    -4,   -20,   -71,
     -71,   -11,   -31
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,    37,    20,    38,     9,    18,    19,    26,
      49,    10,    40,    41,   141,   142,    42,    68,    63,   104,
     105,    64,    65
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      43,    72,    69,    11,    88,    67,    17,    88,     1,    44,
      15,   -49,    43,    27,    39,    13,    73,    74,    43,    46,
      12,    44,    14,    77,    16,    23,    83,    44,    16,    84,
      85,    86,   -13,   130,   -49,    96,    97,    98,    99,   100,
      75,    99,   100,   106,   107,    21,    79,    70,   149,   110,
     111,   112,   102,    48,   101,   102,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,    16,    24,    88,   132,   129,   150,    22,   134,   152,
      47,   153,    43,    43,    76,    78,    80,    81,    82,    75,
     -42,    44,    44,    72,    90,    91,    92,   108,   109,   131,
     146,    93,    94,    95,    96,    97,    98,    99,   100,   147,
      43,    67,   148,    72,    36,    72,    72,    66,    43,    44,
      45,     0,    87,   155,    30,     0,    43,    44,    88,    43,
      43,    43,    43,    43,   145,    44,     0,     0,    44,    44,
      44,    44,    44,    34,     0,    35,    87,    89,     0,    90,
      91,    92,    88,     0,     0,     0,    93,    94,    95,    96,
      97,    98,    99,   100,    87,     0,     0,     0,     0,     0,
      88,    89,   133,    90,    91,    92,     0,     0,     0,     0,
      93,    94,    95,    96,    97,    98,    99,   100,    87,    89,
       0,    90,    91,    92,    88,     0,   144,     0,    93,    94,
      95,    96,    97,    98,    99,   100,     0,     0,     0,     0,
       0,     0,   143,    89,    87,    90,    91,    92,     0,     0,
      88,     0,    93,    94,    95,    96,    97,    98,    99,   100,
       0,     0,     0,     0,    87,   138,     0,     0,     0,    89,
      88,    90,    91,    92,     0,     0,     0,     0,    93,    94,
      95,    96,    97,    98,    99,   100,     0,     0,    87,    89,
     113,    90,    91,    92,    88,     0,     0,     0,    93,    94,
      95,    96,    97,    98,    99,   100,     0,     0,    87,     0,
     135,     0,     0,    89,    88,    90,    91,    92,     0,     0,
       0,     0,    93,    94,    95,    96,    97,    98,    99,   100,
       0,     0,    87,    89,   136,    90,    91,    92,    88,     0,
       0,     0,    93,    94,    95,    96,    97,    98,    99,   100,
      87,     0,     0,     0,   137,     0,    88,    89,     0,    90,
      91,    92,     0,     0,     0,     0,    93,    94,    95,    96,
      97,    98,    99,   100,     0,    89,   103,    90,    91,    92,
       0,     0,     0,     0,    93,    94,    95,    96,    97,    98,
      99,   100,     0,     0,   151,    50,    51,    52,     0,     0,
       0,    53,    54,    55,     4,    56,     5,     0,     0,    57,
       6,     0,     0,     0,    87,     0,    58,    34,    59,    35,
      88,     0,     0,     0,    60,    61,     7,     0,     0,    87,
       0,    62,     0,     8,     0,    88,    22,     0,     4,    89,
       5,    90,    91,    92,     6,     0,     0,     0,    93,    94,
      95,    96,    97,    98,    99,   100,    90,    91,    92,     0,
       7,     0,     0,    93,    94,    95,    96,    97,    98,    99,
     100,    50,    51,    52,     4,    25,     5,    53,    54,    55,
       6,    56,    88,     0,     0,    57,     0,     0,     0,     0,
       0,     0,    58,    34,    59,    35,     7,     0,     0,     0,
      60,    61,     0,   -50,   -50,   -50,     0,    62,     0,     0,
     -50,   -50,   -50,    96,    97,    98,    99,   100,    71,   154,
       0,     0,    28,    28,    29,    29,     0,     0,     0,    30,
      30,    32,    32,     0,     0,     0,     0,    33,    33,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    34,    34,
      35,    35,     4,     0,     5,    28,     0,    29,     6,     0,
       0,     0,    30,    31,    32,     0,     0,     0,     1,    28,
      33,    29,     0,    28,     7,    29,    30,     0,    32,     0,
      30,    34,    32,    35,    33,   139,   140,     0,    33,     0,
       0,     0,     0,     0,     0,    34,     0,    35,     0,    34,
       0,    35
};

static const yytype_int16 yycheck[] =
{
      20,    38,    33,     0,     9,    32,    12,     9,    21,    20,
      34,    29,    32,    19,    20,    48,    39,    29,    38,    25,
      52,    32,    47,    46,    52,    53,    57,    38,    52,    60,
      61,    62,    49,   103,    52,    40,    41,    42,    43,    44,
      52,    43,    44,    74,    75,    48,    52,    48,    47,    80,
      81,    82,    51,    34,    50,    51,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,    52,    49,     9,   105,   102,   146,    53,   109,   149,
      50,   151,   102,   103,    49,    51,    48,    48,    48,    52,
      49,   102,   103,   130,    30,    31,    32,    34,    52,    49,
      47,    37,    38,    39,    40,    41,    42,    43,    44,   140,
     130,   138,     4,   150,    20,   152,   153,    31,   138,   130,
      21,    -1,     3,   153,    15,    -1,   146,   138,     9,   149,
     150,   151,   152,   153,   138,   146,    -1,    -1,   149,   150,
     151,   152,   153,    34,    -1,    36,     3,    28,    -1,    30,
      31,    32,     9,    -1,    -1,    -1,    37,    38,    39,    40,
      41,    42,    43,    44,     3,    -1,    -1,    -1,    -1,    -1,
       9,    28,    53,    30,    31,    32,    -1,    -1,    -1,    -1,
      37,    38,    39,    40,    41,    42,    43,    44,     3,    28,
      -1,    30,    31,    32,     9,    -1,    53,    -1,    37,    38,
      39,    40,    41,    42,    43,    44,    -1,    -1,    -1,    -1,
      -1,    -1,    51,    28,     3,    30,    31,    32,    -1,    -1,
       9,    -1,    37,    38,    39,    40,    41,    42,    43,    44,
      -1,    -1,    -1,    -1,     3,    50,    -1,    -1,    -1,    28,
       9,    30,    31,    32,    -1,    -1,    -1,    -1,    37,    38,
      39,    40,    41,    42,    43,    44,    -1,    -1,     3,    28,
      49,    30,    31,    32,     9,    -1,    -1,    -1,    37,    38,
      39,    40,    41,    42,    43,    44,    -1,    -1,     3,    -1,
      49,    -1,    -1,    28,     9,    30,    31,    32,    -1,    -1,
      -1,    -1,    37,    38,    39,    40,    41,    42,    43,    44,
      -1,    -1,     3,    28,    49,    30,    31,    32,     9,    -1,
      -1,    -1,    37,    38,    39,    40,    41,    42,    43,    44,
       3,    -1,    -1,    -1,    49,    -1,     9,    28,    -1,    30,
      31,    32,    -1,    -1,    -1,    -1,    37,    38,    39,    40,
      41,    42,    43,    44,    -1,    28,    47,    30,    31,    32,
      -1,    -1,    -1,    -1,    37,    38,    39,    40,    41,    42,
      43,    44,    -1,    -1,    47,    12,    13,    14,    -1,    -1,
      -1,    18,    19,    20,     5,    22,     7,    -1,    -1,    26,
      11,    -1,    -1,    -1,     3,    -1,    33,    34,    35,    36,
       9,    -1,    -1,    -1,    41,    42,    27,    -1,    -1,     3,
      -1,    48,    -1,    34,    -1,     9,    53,    -1,     5,    28,
       7,    30,    31,    32,    11,    -1,    -1,    -1,    37,    38,
      39,    40,    41,    42,    43,    44,    30,    31,    32,    -1,
      27,    -1,    -1,    37,    38,    39,    40,    41,    42,    43,
      44,    12,    13,    14,     5,     6,     7,    18,    19,    20,
      11,    22,     9,    -1,    -1,    26,    -1,    -1,    -1,    -1,
      -1,    -1,    33,    34,    35,    36,    27,    -1,    -1,    -1,
      41,    42,    -1,    30,    31,    32,    -1,    48,    -1,    -1,
      37,    38,    39,    40,    41,    42,    43,    44,     4,     4,
      -1,    -1,     8,     8,    10,    10,    -1,    -1,    -1,    15,
      15,    17,    17,    -1,    -1,    -1,    -1,    23,    23,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    34,    34,
      36,    36,     5,    -1,     7,     8,    -1,    10,    11,    -1,
      -1,    -1,    15,    16,    17,    -1,    -1,    -1,    21,     8,
      23,    10,    -1,     8,    27,    10,    15,    -1,    17,    -1,
      15,    34,    17,    36,    23,    24,    25,    -1,    23,    -1,
      -1,    -1,    -1,    -1,    -1,    34,    -1,    36,    -1,    34,
      -1,    36
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    21,    55,    56,     5,     7,    11,    27,    34,    60,
      65,     0,    52,    48,    47,    34,    52,    65,    61,    62,
      58,    48,    53,    53,    49,     6,    63,    65,     8,    10,
      15,    16,    17,    23,    34,    36,    56,    57,    59,    65,
      66,    67,    70,    72,    75,    61,    65,    50,    34,    64,
      12,    13,    14,    18,    19,    20,    22,    26,    33,    35,
      41,    42,    48,    72,    75,    76,    60,    70,    71,    76,
      48,     4,    67,    64,    29,    52,    49,    64,    51,    65,
      48,    48,    48,    76,    76,    76,    76,     3,     9,    28,
      30,    31,    32,    37,    38,    39,    40,    41,    42,    43,
      44,    50,    51,    47,    73,    74,    76,    76,    34,    52,
      76,    76,    76,    49,    76,    76,    76,    76,    76,    76,
      76,    76,    76,    76,    76,    76,    76,    76,    76,    70,
      59,    49,    76,    53,    76,    49,    49,    49,    50,    24,
      25,    68,    69,    51,    53,    71,    47,    76,     4,    47,
      59,    47,    59,    59,     4,    68
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    54,    55,    56,    57,    58,    58,    58,    58,    59,
      59,    60,    60,    61,    61,    62,    62,    63,    63,    64,
      64,    65,    65,    65,    65,    65,    66,    67,    67,    67,
      67,    67,    68,    68,    69,    69,    70,    70,    70,    71,
      71,    72,    73,    73,    74,    74,    75,    75,    75,    75,
      76,    76,    76,    76,    76,    76,    76,    76,    76,    76,
      76,    76,    76,    76,    76,    76,    76,    76,    76,    76,
      76,    76,    76,    76,    76,    76,    76,    76
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     6,     2,     0,     2,     2,     2,     1,
       2,     4,     5,     0,     2,     0,     3,     2,     3,     1,
       3,     1,     1,     1,     3,     4,     2,     1,     1,     2,
       6,     9,     1,     5,     0,     3,     1,     3,     1,     1,
       3,     4,     0,     2,     0,     3,     1,     1,     4,     1,
       1,     1,     1,     3,     2,     2,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     1,     1,     2,
       3,     3,     5,     1,     4,     3,     4,     4
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

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
#ifndef YYINITDEPTH
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
static YYSIZE_T
yystrlen (const char *yystr)
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
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
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
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

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
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
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 3:
#line 122 "parser.y" /* yacc.c:1646  */
    { (yyval.func_def) = new FunctionDefinition((yyvsp[-4].header),(yyvsp[-2].def_list),(yyvsp[-1].stmt_list)); }
#line 1473 "parser.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 126 "parser.y" /* yacc.c:1646  */
    { (yyval.func_decl) = new FunctionDeclaration((yyvsp[0].header)); }
#line 1479 "parser.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 130 "parser.y" /* yacc.c:1646  */
    { (yyval.def_list) = new DefinitionList(); }
#line 1485 "parser.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 131 "parser.y" /* yacc.c:1646  */
    { (yyvsp[-1].def_list)->append((yyvsp[0].func_def)); (yyval.def_list)=(yyvsp[-1].def_list); }
#line 1491 "parser.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 132 "parser.y" /* yacc.c:1646  */
    { (yyvsp[-1].def_list)->append((yyvsp[0].func_decl)); (yyval.def_list)=(yyvsp[-1].def_list); }
#line 1497 "parser.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 133 "parser.y" /* yacc.c:1646  */
    { (yyvsp[-1].def_list)->append((yyvsp[0].var_definition)); (yyval.def_list)=(yyvsp[-1].def_list); }
#line 1503 "parser.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 137 "parser.y" /* yacc.c:1646  */
    { (yyval.stmt_list) = new StmtList((yyvsp[0].stmt)); }
#line 1509 "parser.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 138 "parser.y" /* yacc.c:1646  */
    { (yyvsp[-1].stmt_list)->append((yyvsp[0].stmt)); (yyval.stmt_list)=(yyvsp[-1].stmt_list); }
#line 1515 "parser.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 142 "parser.y" /* yacc.c:1646  */
    { (yyval.header) = new Header((yyvsp[-3].var),(yyvsp[-1].formal_list)); }
#line 1521 "parser.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 143 "parser.y" /* yacc.c:1646  */
    { (yyval.header) = new Header((yyvsp[-3].var),(yyvsp[-1].formal_list),(yyvsp[-4].type)); }
#line 1527 "parser.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 147 "parser.y" /* yacc.c:1646  */
    { (yyval.formal_list) = new FormalList(); }
#line 1533 "parser.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 148 "parser.y" /* yacc.c:1646  */
    { (yyvsp[-1].formal_list)->append((yyvsp[0].formal)) ; (yyval.formal_list) = (yyvsp[-1].formal_list); }
#line 1539 "parser.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 152 "parser.y" /* yacc.c:1646  */
    { (yyval.formal_list) = new FormalList(); }
#line 1545 "parser.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 153 "parser.y" /* yacc.c:1646  */
    { (yyvsp[-2].formal_list)->append((yyvsp[-1].formal)); (yyval.formal_list) = (yyvsp[-2].formal_list); }
#line 1551 "parser.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 157 "parser.y" /* yacc.c:1646  */
    { (yyval.formal) = new Formal((yyvsp[-1].type),(yyvsp[0].var_list)); }
#line 1557 "parser.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 158 "parser.y" /* yacc.c:1646  */
    { (yyval.formal) = new Formal((yyvsp[-1].type),(yyvsp[0].var_list),true); }
#line 1563 "parser.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 162 "parser.y" /* yacc.c:1646  */
    { (yyval.var_list) = new VarList((yyvsp[0].var)); }
#line 1569 "parser.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 163 "parser.y" /* yacc.c:1646  */
    { (yyvsp[-2].var_list)->append((yyvsp[0].var)); (yyval.var_list) = (yyvsp[-2].var_list); }
#line 1575 "parser.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 167 "parser.y" /* yacc.c:1646  */
    { (yyval.type) = new std::string("int"); }
#line 1581 "parser.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 168 "parser.y" /* yacc.c:1646  */
    { (yyval.type) = new std::string("bool"); }
#line 1587 "parser.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 169 "parser.y" /* yacc.c:1646  */
    { (yyval.type) = new std::string("char"); }
#line 1593 "parser.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 170 "parser.y" /* yacc.c:1646  */
    { (yyvsp[-2].type)->append("[]"); (yyval.type)=(yyvsp[-2].type); }
#line 1599 "parser.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 171 "parser.y" /* yacc.c:1646  */
    { (yyval.type) = new std::string("list ["); (yyval.type)->append((yyvsp[-1].type)->c_str()) ; (yyval.type)->append("]"); }
#line 1605 "parser.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 176 "parser.y" /* yacc.c:1646  */
    { (yyval.var_definition) = new VarDefinition((yyvsp[-1].type),(yyvsp[0].var_list)); }
#line 1611 "parser.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 181 "parser.y" /* yacc.c:1646  */
    { (yyval.stmt) = (yyvsp[0].stmt); }
#line 1617 "parser.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 182 "parser.y" /* yacc.c:1646  */
    { (yyval.stmt) = new ExitStmt(); }
#line 1623 "parser.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 183 "parser.y" /* yacc.c:1646  */
    { (yyval.stmt) = new ReturnStmt((yyvsp[0].expr)); }
#line 1629 "parser.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 184 "parser.y" /* yacc.c:1646  */
    { (yyval.stmt) = new If((yyvsp[-4].expr),(yyvsp[-2].stmt_list),(yyvsp[-1].ifClass)); }
#line 1635 "parser.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 185 "parser.y" /* yacc.c:1646  */
    { (yyval.stmt) = new For((yyvsp[-7].stmt_list),(yyvsp[-5].expr),(yyvsp[-3].stmt_list),(yyvsp[-1].stmt_list)); }
#line 1641 "parser.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 189 "parser.y" /* yacc.c:1646  */
    { (yyval.ifClass) = (yyvsp[0].ifClass); }
#line 1647 "parser.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 190 "parser.y" /* yacc.c:1646  */
    { (yyval.ifClass) = new If((yyvsp[-3].expr),(yyvsp[-1].stmt_list),(yyvsp[0].ifClass)); }
#line 1653 "parser.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 194 "parser.y" /* yacc.c:1646  */
    { (yyval.ifClass) = NULL; }
#line 1659 "parser.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 195 "parser.y" /* yacc.c:1646  */
    { (yyval.ifClass) = new If(NULL,(yyvsp[0].stmt_list),NULL); }
#line 1665 "parser.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 199 "parser.y" /* yacc.c:1646  */
    {  }
#line 1671 "parser.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 200 "parser.y" /* yacc.c:1646  */
    { (yyval.stmt) = new AssignStmt((yyvsp[-2].expr),(yyvsp[0].expr)); }
#line 1677 "parser.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 201 "parser.y" /* yacc.c:1646  */
    { (yyval.stmt) = (yyvsp[0].call_object); }
#line 1683 "parser.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 205 "parser.y" /* yacc.c:1646  */
    { (yyval.stmt_list) = new StmtList((yyvsp[0].stmt)); }
#line 1689 "parser.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 206 "parser.y" /* yacc.c:1646  */
    { (yyvsp[-2].stmt_list)->append((yyvsp[0].stmt)); (yyval.stmt_list) = (yyvsp[-2].stmt_list); }
#line 1695 "parser.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 210 "parser.y" /* yacc.c:1646  */
    { (yyval.call_object) = new CallObject((yyvsp[-3].var),(yyvsp[-1].expr_list)); }
#line 1701 "parser.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 214 "parser.y" /* yacc.c:1646  */
    { (yyval.expr_list) = new ExprList(); }
#line 1707 "parser.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 215 "parser.y" /* yacc.c:1646  */
    { (yyvsp[-1].expr_list)->append((yyvsp[0].expr)); (yyval.expr_list) = (yyvsp[-1].expr_list); }
#line 1713 "parser.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 219 "parser.y" /* yacc.c:1646  */
    { (yyval.expr_list) = new ExprList(); }
#line 1719 "parser.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 220 "parser.y" /* yacc.c:1646  */
    { (yyvsp[-2].expr_list)->append((yyvsp[-1].expr)); (yyval.expr_list) = (yyvsp[-2].expr_list); }
#line 1725 "parser.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 224 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].var); }
#line 1731 "parser.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 225 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new ConstString((yyvsp[0].str)); }
#line 1737 "parser.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 226 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new ArrayIndexing((yyvsp[-3].expr),(yyvsp[-1].expr)); }
#line 1743 "parser.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 227 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].call_object); }
#line 1749 "parser.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 231 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 1755 "parser.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 232 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new ConstInt((yyvsp[0].num)); }
#line 1761 "parser.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 233 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new ConstInt((yyvsp[0].num)); }
#line 1767 "parser.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 234 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[-1].expr); }
#line 1773 "parser.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 235 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new BinOp(NULL,'+',(yyvsp[0].expr)); }
#line 1779 "parser.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 236 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new BinOp(NULL,'-',(yyvsp[0].expr)); }
#line 1785 "parser.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 237 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new BinOp((yyvsp[-2].expr),'+',(yyvsp[0].expr)); }
#line 1791 "parser.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 238 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new BinOp((yyvsp[-2].expr),'-',(yyvsp[0].expr)); }
#line 1797 "parser.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 239 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new BinOp((yyvsp[-2].expr),'*',(yyvsp[0].expr)); }
#line 1803 "parser.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 240 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new BinOp((yyvsp[-2].expr),'/',(yyvsp[0].expr)); }
#line 1809 "parser.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 241 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new BinOp((yyvsp[-2].expr),'%',(yyvsp[0].expr)); }
#line 1815 "parser.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 242 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new RelOp((yyvsp[-2].expr),eq,(yyvsp[0].expr)); }
#line 1821 "parser.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 243 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new RelOp((yyvsp[-2].expr),gt,(yyvsp[0].expr)); }
#line 1827 "parser.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 244 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new RelOp((yyvsp[-2].expr),lt,(yyvsp[0].expr)); }
#line 1833 "parser.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 245 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new RelOp((yyvsp[-2].expr),neq,(yyvsp[0].expr)); }
#line 1839 "parser.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 246 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new RelOp((yyvsp[-2].expr),le,(yyvsp[0].expr)); }
#line 1845 "parser.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 247 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new RelOp((yyvsp[-2].expr),ge,(yyvsp[0].expr)); }
#line 1851 "parser.cpp" /* yacc.c:1646  */
    break;

  case 67:
#line 248 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new LogOp(TRUE); }
#line 1857 "parser.cpp" /* yacc.c:1646  */
    break;

  case 68:
#line 249 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new LogOp(FALSE); }
#line 1863 "parser.cpp" /* yacc.c:1646  */
    break;

  case 69:
#line 250 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new LogOp(NOT,NULL,(yyvsp[0].expr)); }
#line 1869 "parser.cpp" /* yacc.c:1646  */
    break;

  case 70:
#line 251 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new LogOp(AND,(yyvsp[-2].expr),(yyvsp[0].expr)); }
#line 1875 "parser.cpp" /* yacc.c:1646  */
    break;

  case 71:
#line 252 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new LogOp(OR,(yyvsp[-2].expr),(yyvsp[0].expr)); }
#line 1881 "parser.cpp" /* yacc.c:1646  */
    break;

  case 72:
#line 253 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new ArrayInit((yyvsp[-3].type),(yyvsp[-1].expr)); }
#line 1887 "parser.cpp" /* yacc.c:1646  */
    break;

  case 73:
#line 254 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new ListOp(nil,NULL,NULL); }
#line 1893 "parser.cpp" /* yacc.c:1646  */
    break;

  case 74:
#line 255 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new ListOp(nilq,NULL,(yyvsp[-1].expr)); }
#line 1899 "parser.cpp" /* yacc.c:1646  */
    break;

  case 75:
#line 256 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new ListOp(append,(yyvsp[-2].expr),(yyvsp[0].expr)); }
#line 1905 "parser.cpp" /* yacc.c:1646  */
    break;

  case 76:
#line 257 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new ListOp(head,NULL,(yyvsp[-1].expr)); }
#line 1911 "parser.cpp" /* yacc.c:1646  */
    break;

  case 77:
#line 258 "parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new ListOp(tail,NULL,(yyvsp[-1].expr)); }
#line 1917 "parser.cpp" /* yacc.c:1646  */
    break;


#line 1921 "parser.cpp" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
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

  /* Else will try to reuse lookahead token after shifting the error
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

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
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

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
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
  return yyresult;
}
#line 261 "parser.y" /* yacc.c:1906  */


int main(){
	return yyparse();
}
