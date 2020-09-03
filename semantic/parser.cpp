/* A Bison parser, made by GNU Bison 3.4.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2019 Free Software Foundation,
   Inc.

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"

#include <cstdio>
#include <iostream>
#include <map>
#include <vector>
#include <string>

#include "ast.hpp"
#include "lexer.hpp"
#include "symbol.hpp"

// ST_SIZE must be a prime number
#define 	ST_SIZE 	257

#line 85 "parser.cpp"

# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
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
#line 17 "parser.y"
 
	#include "ast.hpp" 	
	#include <string>

#line 124 "parser.cpp"

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
#line 24 "parser.y"

	FunctionDefinition 			*func_def;
	FunctionDeclaration 		*func_decl;
	DefinitionList 				*def_list;
	Header 						*header;
	Stmt 						*stmt;
	StmtList 					*stmt_list;
	Formal 						*formal;
	FormalList 					*formal_list;
	Expr 						*expr;
	ExprList 					*expr_list;
	Var 						*var;
	VarList 					*var_list;
	VarDefinition 				*var_definition;
	If 							*ifClass;
	For 						*forClass;
	CallObject 					*call_object;
	Type 						type;

	char 						chr;
	int 						num;
	const char 					*str;

#line 198 "parser.cpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_HPP_INCLUDED  */



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
typedef unsigned short yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short yytype_int16;
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
#  define YYSIZE_T unsigned
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

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
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


#define YY_ASSERT(E) ((void) (0 && (E)))

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
#define YYLAST   579

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  54
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  24
/* YYNRULES -- Number of rules.  */
#define YYNRULES  79
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  165

#define YYUNDEFTOK  2
#define YYMAXUTOK   293

/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  ((unsigned) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
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
       0,   122,   122,   126,   130,   134,   135,   136,   137,   141,
     142,   146,   147,   151,   152,   156,   157,   161,   162,   166,
     167,   171,   172,   177,   178,   179,   180,   181,   186,   191,
     192,   193,   194,   195,   199,   200,   204,   205,   209,   210,
     211,   215,   216,   220,   224,   225,   229,   230,   234,   235,
     236,   237,   241,   242,   243,   244,   245,   246,   247,   248,
     249,   250,   251,   252,   253,   254,   255,   256,   257,   258,
     259,   260,   261,   262,   263,   264,   265,   266,   267,   268
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
  "stmt_list", "header_def", "header_decl", "formal_list", "formal_head",
  "formal", "var_list", "type", "var_def", "stmt", "elsif_list", "else",
  "simple", "simple_list", "call", "expr_list", "expr_head", "atom",
  "expr", YY_NULLPTR
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

#define YYPACT_NINF -83

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-83)))

#define YYTABLE_NINF -52

#define yytable_value_is_error(Yytable_value) \
  (!!((Yytable_value) == (-52)))

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -11,   110,    21,   -83,   -29,   -83,   -83,   -83,    34,    43,
      -1,   -83,    86,     6,   -83,    41,    -8,    -9,    52,     8,
     525,     6,   -83,   -83,   -83,    86,    54,    22,   -83,   437,
     -83,   377,    14,   437,    71,   -83,   -83,   -83,   492,    22,
     -83,   -83,   -83,   -28,   -18,    73,    22,   -83,   -83,    72,
     -83,   -83,    86,   -83,    81,    83,    84,   437,   -83,   -83,
     437,   437,   437,   -83,    93,   389,    85,   -83,    51,   -83,
       7,   307,   102,   -83,   -83,    72,   437,   437,   -83,    72,
     118,   101,   437,   437,   437,    68,   -83,   -83,   219,   437,
     437,   437,   437,   437,   437,   437,   437,   437,   437,   437,
     437,   437,   437,     6,   108,   437,    14,   543,   112,   437,
     389,   127,   -83,   361,   239,   263,   283,   -83,    68,   -83,
     404,   451,   451,   451,   451,   451,   451,    -4,    -2,    -2,
     -83,   -83,   113,     6,   193,   -83,   539,   -83,   169,   -83,
     151,   -83,   -83,   -83,   -83,   114,    14,   126,   437,   170,
     -83,   -83,   -83,   -83,    45,   543,   325,   -83,   543,   543,
     543,   493,   539,   -83,   -83
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     2,     0,    24,    25,    23,     0,     0,
       0,     1,     0,    17,     5,     0,     0,     0,     0,     0,
       0,    17,    26,    27,    11,     0,    16,     0,    30,     0,
      38,     0,     0,     0,    48,    49,     6,     7,     0,     0,
       8,     9,    29,    40,     0,     0,     0,    18,    21,    19,
      70,    69,     0,    75,     0,     0,     0,     0,    53,    54,
       0,     0,     0,    51,    52,    31,     0,     4,     0,    41,
       0,     0,    46,     3,    10,    28,     0,     0,    12,    20,
       0,     0,     0,     0,     0,    71,    56,    57,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    17,     0,     0,     0,     0,     0,     0,
      39,     0,    22,     0,     0,     0,     0,    55,    72,    62,
      73,    68,    67,    66,    63,    64,    65,    77,    58,    59,
      60,    61,     0,    17,     0,    42,    36,    43,    45,    50,
       0,    79,    78,    76,    13,     0,     0,     0,     0,     0,
      34,    47,    74,    14,     0,     0,     0,    32,     0,    37,
       0,     0,    36,    33,    35
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -83,   -83,   155,   -83,   -83,   -82,   -83,   -83,   -19,   -83,
     -83,    42,    -3,   -83,   -34,    15,   -83,   -26,    30,   -20,
     -83,   -83,   -12,   -30
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,    37,    20,    38,     9,    67,    18,    19,
      26,    49,    10,    40,    41,   149,   150,    42,    70,    63,
     108,   109,    64,    65
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      43,   -51,    45,    71,    74,    90,    69,    90,    44,    17,
       1,    76,    43,     4,    25,     5,    27,    39,    43,     6,
      44,    11,    46,    12,   -51,   136,    44,    85,    68,    30,
      86,    87,    88,    15,    77,     7,    98,    99,   100,   101,
     102,   101,   102,    16,    23,    22,   110,   111,    34,    81,
      35,    16,   114,   115,   116,   -15,    48,   105,   106,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   159,    16,   134,   161,    90,   162,   138,
     135,    75,    13,   140,   132,   104,    43,    43,    79,    21,
      14,     4,   158,     5,    44,    44,   106,     6,    92,    93,
      94,    24,    74,    16,    47,    95,    96,    97,    98,    99,
     100,   101,   102,     7,   145,     4,    43,     5,   156,    72,
      69,     6,    78,    80,    44,    74,    43,    74,    74,    82,
      89,    83,    84,   103,    44,    43,    90,     7,    43,    43,
      43,    43,    43,    44,     8,    77,    44,    44,    44,    44,
      44,   -44,   112,   113,    89,    91,   133,    92,    93,    94,
      90,   137,   144,   153,    95,    96,    97,    98,    99,   100,
     101,   102,    89,   155,   157,    36,   154,   164,    90,    91,
     139,    92,    93,    94,     0,     0,     0,     0,    95,    96,
      97,    98,    99,   100,   101,   102,    89,    91,     0,    92,
      93,    94,    90,     0,   152,     0,    95,    96,    97,    98,
      99,   100,   101,   102,     0,     0,     0,     0,     0,     0,
     151,    91,    89,    92,    93,    94,     0,     0,    90,     0,
      95,    96,    97,    98,    99,   100,   101,   102,     0,     0,
       0,     0,    89,   146,     0,     0,     0,    91,    90,    92,
      93,    94,     0,     0,     0,     0,    95,    96,    97,    98,
      99,   100,   101,   102,     0,     0,    89,    91,   117,    92,
      93,    94,    90,     0,     0,     0,    95,    96,    97,    98,
      99,   100,   101,   102,     0,     0,    89,     0,   141,     0,
       0,    91,    90,    92,    93,    94,     0,     0,     0,     0,
      95,    96,    97,    98,    99,   100,   101,   102,     0,     0,
      89,    91,   142,    92,    93,    94,    90,     0,     0,     0,
      95,    96,    97,    98,    99,   100,   101,   102,    89,     0,
       0,     0,   143,     0,    90,    91,     0,    92,    93,    94,
       0,     0,     0,     0,    95,    96,    97,    98,    99,   100,
     101,   102,     0,    91,   107,    92,    93,    94,     0,     0,
       0,     0,    95,    96,    97,    98,    99,   100,   101,   102,
       0,     0,   160,    50,    51,    52,     0,     0,     0,    53,
      54,    55,     4,    56,     5,     0,     0,    57,     6,     0,
       0,     0,    89,     0,    58,    34,    59,    35,    90,     0,
       0,     0,    60,    61,     7,     0,     0,    89,     0,    62,
       0,    66,     0,    90,    22,     0,     0,    91,     0,    92,
      93,    94,     0,     0,     0,     0,    95,    96,    97,    98,
      99,   100,   101,   102,    92,    93,    94,     0,     0,     0,
       0,    95,    96,    97,    98,    99,   100,   101,   102,    50,
      51,    52,     0,     0,     0,    53,    54,    55,     0,    56,
      90,     0,     0,    57,     0,     0,     0,     0,     0,     0,
      58,    34,    59,    35,     0,     0,     0,     0,    60,    61,
       0,   -52,   -52,   -52,     0,    62,     0,     0,   -52,   -52,
     -52,    98,    99,   100,   101,   102,    73,   163,     0,     0,
      28,    28,    29,    29,     0,     0,     0,    30,    30,    32,
      32,     0,     0,     0,     0,    33,    33,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    34,    34,    35,    35,
       4,     0,     5,    28,     0,    29,     6,     0,     0,     0,
      30,    31,    32,     0,     0,     0,     1,    28,    33,    29,
       0,    28,     7,    29,    30,     0,    32,     0,    30,    34,
      32,    35,    33,   147,   148,     0,    33,     0,     0,     0,
       0,     0,     0,    34,     0,    35,     0,    34,     0,    35
};

static const yytype_int16 yycheck[] =
{
      20,    29,    21,    33,    38,     9,    32,     9,    20,    12,
      21,    29,    32,     5,     6,     7,    19,    20,    38,    11,
      32,     0,    25,    52,    52,   107,    38,    57,    31,    15,
      60,    61,    62,    34,    52,    27,    40,    41,    42,    43,
      44,    43,    44,    52,    53,    53,    76,    77,    34,    52,
      36,    52,    82,    83,    84,    49,    34,    50,    51,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   155,    52,   105,   158,     9,   160,   109,
     106,    39,    48,   113,   103,    34,   106,   107,    46,    48,
      47,     5,    47,     7,   106,   107,    51,    11,    30,    31,
      32,    49,   136,    52,    50,    37,    38,    39,    40,    41,
      42,    43,    44,    27,   133,     5,   136,     7,   148,    48,
     146,    11,    49,    51,   136,   159,   146,   161,   162,    48,
       3,    48,    48,    48,   146,   155,     9,    27,   158,   159,
     160,   161,   162,   155,    34,    52,   158,   159,   160,   161,
     162,    49,    34,    52,     3,    28,    48,    30,    31,    32,
       9,    49,    49,    49,    37,    38,    39,    40,    41,    42,
      43,    44,     3,    47,     4,    20,   146,   162,     9,    28,
      53,    30,    31,    32,    -1,    -1,    -1,    -1,    37,    38,
      39,    40,    41,    42,    43,    44,     3,    28,    -1,    30,
      31,    32,     9,    -1,    53,    -1,    37,    38,    39,    40,
      41,    42,    43,    44,    -1,    -1,    -1,    -1,    -1,    -1,
      51,    28,     3,    30,    31,    32,    -1,    -1,     9,    -1,
      37,    38,    39,    40,    41,    42,    43,    44,    -1,    -1,
      -1,    -1,     3,    50,    -1,    -1,    -1,    28,     9,    30,
      31,    32,    -1,    -1,    -1,    -1,    37,    38,    39,    40,
      41,    42,    43,    44,    -1,    -1,     3,    28,    49,    30,
      31,    32,     9,    -1,    -1,    -1,    37,    38,    39,    40,
      41,    42,    43,    44,    -1,    -1,     3,    -1,    49,    -1,
      -1,    28,     9,    30,    31,    32,    -1,    -1,    -1,    -1,
      37,    38,    39,    40,    41,    42,    43,    44,    -1,    -1,
       3,    28,    49,    30,    31,    32,     9,    -1,    -1,    -1,
      37,    38,    39,    40,    41,    42,    43,    44,     3,    -1,
      -1,    -1,    49,    -1,     9,    28,    -1,    30,    31,    32,
      -1,    -1,    -1,    -1,    37,    38,    39,    40,    41,    42,
      43,    44,    -1,    28,    47,    30,    31,    32,    -1,    -1,
      -1,    -1,    37,    38,    39,    40,    41,    42,    43,    44,
      -1,    -1,    47,    12,    13,    14,    -1,    -1,    -1,    18,
      19,    20,     5,    22,     7,    -1,    -1,    26,    11,    -1,
      -1,    -1,     3,    -1,    33,    34,    35,    36,     9,    -1,
      -1,    -1,    41,    42,    27,    -1,    -1,     3,    -1,    48,
      -1,    34,    -1,     9,    53,    -1,    -1,    28,    -1,    30,
      31,    32,    -1,    -1,    -1,    -1,    37,    38,    39,    40,
      41,    42,    43,    44,    30,    31,    32,    -1,    -1,    -1,
      -1,    37,    38,    39,    40,    41,    42,    43,    44,    12,
      13,    14,    -1,    -1,    -1,    18,    19,    20,    -1,    22,
       9,    -1,    -1,    26,    -1,    -1,    -1,    -1,    -1,    -1,
      33,    34,    35,    36,    -1,    -1,    -1,    -1,    41,    42,
      -1,    30,    31,    32,    -1,    48,    -1,    -1,    37,    38,
      39,    40,    41,    42,    43,    44,     4,     4,    -1,    -1,
       8,     8,    10,    10,    -1,    -1,    -1,    15,    15,    17,
      17,    -1,    -1,    -1,    -1,    23,    23,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    34,    34,    36,    36,
       5,    -1,     7,     8,    -1,    10,    11,    -1,    -1,    -1,
      15,    16,    17,    -1,    -1,    -1,    21,     8,    23,    10,
      -1,     8,    27,    10,    15,    -1,    17,    -1,    15,    34,
      17,    36,    23,    24,    25,    -1,    23,    -1,    -1,    -1,
      -1,    -1,    -1,    34,    -1,    36,    -1,    34,    -1,    36
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    21,    55,    56,     5,     7,    11,    27,    34,    60,
      66,     0,    52,    48,    47,    34,    52,    66,    62,    63,
      58,    48,    53,    53,    49,     6,    64,    66,     8,    10,
      15,    16,    17,    23,    34,    36,    56,    57,    59,    66,
      67,    68,    71,    73,    76,    62,    66,    50,    34,    65,
      12,    13,    14,    18,    19,    20,    22,    26,    33,    35,
      41,    42,    48,    73,    76,    77,    34,    61,    66,    71,
      72,    77,    48,     4,    68,    65,    29,    52,    49,    65,
      51,    66,    48,    48,    48,    77,    77,    77,    77,     3,
       9,    28,    30,    31,    32,    37,    38,    39,    40,    41,
      42,    43,    44,    48,    34,    50,    51,    47,    74,    75,
      77,    77,    34,    52,    77,    77,    77,    49,    77,    77,
      77,    77,    77,    77,    77,    77,    77,    77,    77,    77,
      77,    77,    62,    48,    77,    71,    59,    49,    77,    53,
      77,    49,    49,    49,    49,    62,    50,    24,    25,    69,
      70,    51,    53,    49,    72,    47,    77,     4,    47,    59,
      47,    59,    59,     4,    69
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    54,    55,    56,    57,    58,    58,    58,    58,    59,
      59,    60,    60,    61,    61,    62,    62,    63,    63,    64,
      64,    65,    65,    66,    66,    66,    66,    66,    67,    68,
      68,    68,    68,    68,    69,    69,    70,    70,    71,    71,
      71,    72,    72,    73,    74,    74,    75,    75,    76,    76,
      76,    76,    77,    77,    77,    77,    77,    77,    77,    77,
      77,    77,    77,    77,    77,    77,    77,    77,    77,    77,
      77,    77,    77,    77,    77,    77,    77,    77,    77,    77
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     6,     2,     0,     2,     2,     2,     1,
       2,     4,     5,     4,     5,     0,     2,     0,     3,     2,
       3,     1,     3,     1,     1,     1,     3,     4,     2,     1,
       1,     2,     6,     9,     1,     5,     0,     3,     1,     3,
       1,     1,     3,     4,     0,     2,     0,     3,     1,     1,
       4,     1,     1,     1,     1,     3,     2,     2,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     1,
       1,     2,     3,     3,     5,     1,     4,     3,     4,     4
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
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
  unsigned long yylno = yyrline[yyrule];
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
                       &yyvsp[(yyi + 1) - (yynrhs)]
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
            else
              goto append;

          append:
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

  return (YYSIZE_T) (yystpcpy (yyres, yystr) - yyres);
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
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
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
    default: /* Avoid compiler warnings. */
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
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
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
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yynewstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  *yyssp = (yytype_int16) yystate;

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = (YYSIZE_T) (yyssp - yyss + 1);

# if defined yyoverflow
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
# else /* defined YYSTACK_RELOCATE */
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
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

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
| yyreduce -- do a reduction.  |
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
  case 2:
#line 122 "parser.y"
    { (yyvsp[0].func_def)->sem(); }
#line 1486 "parser.cpp"
    break;

  case 3:
#line 126 "parser.y"
    { (yyval.func_def) = new FunctionDefinition((yyvsp[-4].header),(yyvsp[-2].def_list),(yyvsp[-1].stmt_list)); }
#line 1492 "parser.cpp"
    break;

  case 4:
#line 130 "parser.y"
    { (yyval.func_decl) = new FunctionDeclaration((yyvsp[0].header)); }
#line 1498 "parser.cpp"
    break;

  case 5:
#line 134 "parser.y"
    { (yyval.def_list) = new DefinitionList(); }
#line 1504 "parser.cpp"
    break;

  case 6:
#line 135 "parser.y"
    { (yyvsp[-1].def_list)->append((yyvsp[0].func_def)); (yyval.def_list)=(yyvsp[-1].def_list); }
#line 1510 "parser.cpp"
    break;

  case 7:
#line 136 "parser.y"
    { (yyvsp[-1].def_list)->append((yyvsp[0].func_decl)); (yyval.def_list)=(yyvsp[-1].def_list); }
#line 1516 "parser.cpp"
    break;

  case 8:
#line 137 "parser.y"
    { (yyvsp[-1].def_list)->append((yyvsp[0].var_definition)); (yyval.def_list)=(yyvsp[-1].def_list); }
#line 1522 "parser.cpp"
    break;

  case 9:
#line 141 "parser.y"
    { (yyval.stmt_list) = new StmtList((yyvsp[0].stmt)); }
#line 1528 "parser.cpp"
    break;

  case 10:
#line 142 "parser.y"
    { (yyvsp[-1].stmt_list)->append((yyvsp[0].stmt)); (yyval.stmt_list)=(yyvsp[-1].stmt_list); }
#line 1534 "parser.cpp"
    break;

  case 11:
#line 146 "parser.y"
    { (yyval.header) = new Header((yyvsp[-3].str), (yyvsp[-1].formal_list), typeVoid, Func_Def); }
#line 1540 "parser.cpp"
    break;

  case 12:
#line 147 "parser.y"
    { (yyval.header) = new Header((yyvsp[-3].str), (yyvsp[-1].formal_list), (yyvsp[-4].type), Func_Def); }
#line 1546 "parser.cpp"
    break;

  case 13:
#line 151 "parser.y"
    { (yyval.header) = new Header((yyvsp[-3].str), (yyvsp[-1].formal_list), typeVoid, Func_Decl); }
#line 1552 "parser.cpp"
    break;

  case 14:
#line 152 "parser.y"
    { (yyval.header) = new Header((yyvsp[-3].str), (yyvsp[-1].formal_list), (yyvsp[-4].type), Func_Decl); }
#line 1558 "parser.cpp"
    break;

  case 15:
#line 156 "parser.y"
    { (yyval.formal_list) = new FormalList(); }
#line 1564 "parser.cpp"
    break;

  case 16:
#line 157 "parser.y"
    { (yyvsp[-1].formal_list)->append((yyvsp[0].formal)) ; (yyval.formal_list) = (yyvsp[-1].formal_list); }
#line 1570 "parser.cpp"
    break;

  case 17:
#line 161 "parser.y"
    { (yyval.formal_list) = new FormalList(); }
#line 1576 "parser.cpp"
    break;

  case 18:
#line 162 "parser.y"
    { (yyvsp[-2].formal_list)->append((yyvsp[-1].formal)); (yyval.formal_list) = (yyvsp[-2].formal_list); }
#line 1582 "parser.cpp"
    break;

  case 19:
#line 166 "parser.y"
    { (yyval.formal) = new Formal((yyvsp[-1].type),(yyvsp[0].var_list)); }
#line 1588 "parser.cpp"
    break;

  case 20:
#line 167 "parser.y"
    { (yyval.formal) = new Formal((yyvsp[-1].type),(yyvsp[0].var_list),true); }
#line 1594 "parser.cpp"
    break;

  case 21:
#line 171 "parser.y"
    { (yyval.var_list) = new VarList((yyvsp[0].str)); }
#line 1600 "parser.cpp"
    break;

  case 22:
#line 172 "parser.y"
    { (yyvsp[-2].var_list)->append((yyvsp[0].str)); (yyval.var_list) = (yyvsp[-2].var_list); }
#line 1606 "parser.cpp"
    break;

  case 23:
#line 177 "parser.y"
    { (yyval.type) = typeInteger; }
#line 1612 "parser.cpp"
    break;

  case 24:
#line 178 "parser.y"
    { (yyval.type) = typeBoolean; }
#line 1618 "parser.cpp"
    break;

  case 25:
#line 179 "parser.y"
    { (yyval.type) = typeChar; }
#line 1624 "parser.cpp"
    break;

  case 26:
#line 180 "parser.y"
    { (yyval.type) = typeIArray((yyvsp[-2].type)); }
#line 1630 "parser.cpp"
    break;

  case 27:
#line 181 "parser.y"
    { (yyval.type) = typeList((yyvsp[-1].type)); }
#line 1636 "parser.cpp"
    break;

  case 28:
#line 186 "parser.y"
    { (yyval.var_definition) = new VarDefinition((yyvsp[-1].type),(yyvsp[0].var_list)); }
#line 1642 "parser.cpp"
    break;

  case 29:
#line 191 "parser.y"
    { (yyval.stmt) = (yyvsp[0].stmt); }
#line 1648 "parser.cpp"
    break;

  case 30:
#line 192 "parser.y"
    { (yyval.stmt) = new ExitStmt(); }
#line 1654 "parser.cpp"
    break;

  case 31:
#line 193 "parser.y"
    { (yyval.stmt) = new ReturnStmt((yyvsp[0].expr)); }
#line 1660 "parser.cpp"
    break;

  case 32:
#line 194 "parser.y"
    { (yyval.stmt) = new If((yyvsp[-4].expr),(yyvsp[-2].stmt_list),(yyvsp[-1].ifClass)); }
#line 1666 "parser.cpp"
    break;

  case 33:
#line 195 "parser.y"
    { (yyval.stmt) = new For((yyvsp[-7].stmt_list),(yyvsp[-5].expr),(yyvsp[-3].stmt_list),(yyvsp[-1].stmt_list)); }
#line 1672 "parser.cpp"
    break;

  case 34:
#line 199 "parser.y"
    { (yyval.ifClass) = (yyvsp[0].ifClass); }
#line 1678 "parser.cpp"
    break;

  case 35:
#line 200 "parser.y"
    { (yyval.ifClass) = new If((yyvsp[-3].expr),(yyvsp[-1].stmt_list),(yyvsp[0].ifClass)); }
#line 1684 "parser.cpp"
    break;

  case 36:
#line 204 "parser.y"
    { (yyval.ifClass) = NULL; }
#line 1690 "parser.cpp"
    break;

  case 37:
#line 205 "parser.y"
    { (yyval.ifClass) = new If(NULL,(yyvsp[0].stmt_list),NULL); }
#line 1696 "parser.cpp"
    break;

  case 38:
#line 209 "parser.y"
    { (yyval.stmt) = new SkipStmt(); }
#line 1702 "parser.cpp"
    break;

  case 39:
#line 210 "parser.y"
    { (yyval.stmt) = new AssignStmt((yyvsp[-2].expr),(yyvsp[0].expr)); }
#line 1708 "parser.cpp"
    break;

  case 40:
#line 211 "parser.y"
    { (yyval.stmt) = (yyvsp[0].call_object); }
#line 1714 "parser.cpp"
    break;

  case 41:
#line 215 "parser.y"
    { (yyval.stmt_list) = new StmtList((yyvsp[0].stmt)); }
#line 1720 "parser.cpp"
    break;

  case 42:
#line 216 "parser.y"
    { (yyvsp[-2].stmt_list)->append((yyvsp[0].stmt)); (yyval.stmt_list) = (yyvsp[-2].stmt_list); }
#line 1726 "parser.cpp"
    break;

  case 43:
#line 220 "parser.y"
    { (yyval.call_object) = new CallObject((yyvsp[-3].str),(yyvsp[-1].expr_list)); }
#line 1732 "parser.cpp"
    break;

  case 44:
#line 224 "parser.y"
    { (yyval.expr_list) = new ExprList(); }
#line 1738 "parser.cpp"
    break;

  case 45:
#line 225 "parser.y"
    { (yyvsp[-1].expr_list)->append((yyvsp[0].expr)); (yyval.expr_list) = (yyvsp[-1].expr_list); }
#line 1744 "parser.cpp"
    break;

  case 46:
#line 229 "parser.y"
    { (yyval.expr_list) = new ExprList(); }
#line 1750 "parser.cpp"
    break;

  case 47:
#line 230 "parser.y"
    { (yyvsp[-2].expr_list)->append((yyvsp[-1].expr)); (yyval.expr_list) = (yyvsp[-2].expr_list); }
#line 1756 "parser.cpp"
    break;

  case 48:
#line 234 "parser.y"
    { (yyval.expr) = new Var((yyvsp[0].str)); }
#line 1762 "parser.cpp"
    break;

  case 49:
#line 235 "parser.y"
    { (yyval.expr) = new ConstString((yyvsp[0].str)); }
#line 1768 "parser.cpp"
    break;

  case 50:
#line 236 "parser.y"
    { (yyval.expr) = new ArrayIndexing((yyvsp[-3].expr),(yyvsp[-1].expr)); }
#line 1774 "parser.cpp"
    break;

  case 51:
#line 237 "parser.y"
    { (yyval.expr) = (yyvsp[0].call_object); }
#line 1780 "parser.cpp"
    break;

  case 52:
#line 241 "parser.y"
    { (yyval.expr) = (yyvsp[0].expr); }
#line 1786 "parser.cpp"
    break;

  case 53:
#line 242 "parser.y"
    { (yyval.expr) = new ConstInt((yyvsp[0].num)); }
#line 1792 "parser.cpp"
    break;

  case 54:
#line 243 "parser.y"
    { (yyval.expr) = new ConstChar((yyvsp[0].num)); }
#line 1798 "parser.cpp"
    break;

  case 55:
#line 244 "parser.y"
    { (yyval.expr) = (yyvsp[-1].expr); }
#line 1804 "parser.cpp"
    break;

  case 56:
#line 245 "parser.y"
    { (yyval.expr) = new BinOp(NULL,'+',(yyvsp[0].expr)); }
#line 1810 "parser.cpp"
    break;

  case 57:
#line 246 "parser.y"
    { (yyval.expr) = new BinOp(NULL,'-',(yyvsp[0].expr)); }
#line 1816 "parser.cpp"
    break;

  case 58:
#line 247 "parser.y"
    { (yyval.expr) = new BinOp((yyvsp[-2].expr),'+',(yyvsp[0].expr)); }
#line 1822 "parser.cpp"
    break;

  case 59:
#line 248 "parser.y"
    { (yyval.expr) = new BinOp((yyvsp[-2].expr),'-',(yyvsp[0].expr)); }
#line 1828 "parser.cpp"
    break;

  case 60:
#line 249 "parser.y"
    { (yyval.expr) = new BinOp((yyvsp[-2].expr),'*',(yyvsp[0].expr)); }
#line 1834 "parser.cpp"
    break;

  case 61:
#line 250 "parser.y"
    { (yyval.expr) = new BinOp((yyvsp[-2].expr),'/',(yyvsp[0].expr)); }
#line 1840 "parser.cpp"
    break;

  case 62:
#line 251 "parser.y"
    { (yyval.expr) = new BinOp((yyvsp[-2].expr),'%',(yyvsp[0].expr)); }
#line 1846 "parser.cpp"
    break;

  case 63:
#line 252 "parser.y"
    { (yyval.expr) = new RelOp((yyvsp[-2].expr),eq,(yyvsp[0].expr)); }
#line 1852 "parser.cpp"
    break;

  case 64:
#line 253 "parser.y"
    { (yyval.expr) = new RelOp((yyvsp[-2].expr),gt,(yyvsp[0].expr)); }
#line 1858 "parser.cpp"
    break;

  case 65:
#line 254 "parser.y"
    { (yyval.expr) = new RelOp((yyvsp[-2].expr),lt,(yyvsp[0].expr)); }
#line 1864 "parser.cpp"
    break;

  case 66:
#line 255 "parser.y"
    { (yyval.expr) = new RelOp((yyvsp[-2].expr),neq,(yyvsp[0].expr)); }
#line 1870 "parser.cpp"
    break;

  case 67:
#line 256 "parser.y"
    { (yyval.expr) = new RelOp((yyvsp[-2].expr),le,(yyvsp[0].expr)); }
#line 1876 "parser.cpp"
    break;

  case 68:
#line 257 "parser.y"
    { (yyval.expr) = new RelOp((yyvsp[-2].expr),ge,(yyvsp[0].expr)); }
#line 1882 "parser.cpp"
    break;

  case 69:
#line 258 "parser.y"
    { (yyval.expr) = new LogOp(TRUE); }
#line 1888 "parser.cpp"
    break;

  case 70:
#line 259 "parser.y"
    { (yyval.expr) = new LogOp(FALSE); }
#line 1894 "parser.cpp"
    break;

  case 71:
#line 260 "parser.y"
    { (yyval.expr) = new LogOp(NOT,NULL,(yyvsp[0].expr)); }
#line 1900 "parser.cpp"
    break;

  case 72:
#line 261 "parser.y"
    { (yyval.expr) = new LogOp(AND,(yyvsp[-2].expr),(yyvsp[0].expr)); }
#line 1906 "parser.cpp"
    break;

  case 73:
#line 262 "parser.y"
    { (yyval.expr) = new LogOp(OR,(yyvsp[-2].expr),(yyvsp[0].expr)); }
#line 1912 "parser.cpp"
    break;

  case 74:
#line 263 "parser.y"
    { (yyval.expr) = new ArrayInit((yyvsp[-3].type),(yyvsp[-1].expr)); }
#line 1918 "parser.cpp"
    break;

  case 75:
#line 264 "parser.y"
    { (yyval.expr) = new ListOp(nil,NULL,NULL); }
#line 1924 "parser.cpp"
    break;

  case 76:
#line 265 "parser.y"
    { (yyval.expr) = new ListOp(nilq,NULL,(yyvsp[-1].expr)); }
#line 1930 "parser.cpp"
    break;

  case 77:
#line 266 "parser.y"
    { (yyval.expr) = new ListOp(append,(yyvsp[-2].expr),(yyvsp[0].expr)); }
#line 1936 "parser.cpp"
    break;

  case 78:
#line 267 "parser.y"
    { (yyval.expr) = new ListOp(head,NULL,(yyvsp[-1].expr)); }
#line 1942 "parser.cpp"
    break;

  case 79:
#line 268 "parser.y"
    { (yyval.expr) = new ListOp(tail,NULL,(yyvsp[-1].expr)); }
#line 1948 "parser.cpp"
    break;


#line 1952 "parser.cpp"

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
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

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


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
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
#line 271 "parser.y"


int main()
{
	initSymbolTable(ST_SIZE);
	openScope();
	int result = yyparse();
	destroySymbolTable();
	return result;
}
