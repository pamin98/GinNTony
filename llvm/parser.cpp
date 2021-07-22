/* A Bison parser, made by GNU Bison 3.7.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30704

/* Bison version string.  */
#define YYBISON_VERSION "3.7.4"

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

// #define YYDEBUG 1

extern FILE *yyin;

bool optimize = false;


// ST_SIZE must be a prime number
#define 	ST_SIZE 	257

#line 93 "parser.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
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

#include "parser.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_T_and = 3,                      /* "and"  */
  YYSYMBOL_T_end = 4,                      /* "end"  */
  YYSYMBOL_T_list = 5,                     /* "list"  */
  YYSYMBOL_T_ref = 6,                      /* "ref"  */
  YYSYMBOL_T_bool = 7,                     /* "bool"  */
  YYSYMBOL_T_exit = 8,                     /* "exit"  */
  YYSYMBOL_T_mod = 9,                      /* "mod"  */
  YYSYMBOL_T_return = 10,                  /* "return"  */
  YYSYMBOL_T_char = 11,                    /* "char"  */
  YYSYMBOL_T_false = 12,                   /* "false"  */
  YYSYMBOL_T_true = 13,                    /* "true"  */
  YYSYMBOL_T_new = 14,                     /* "new"  */
  YYSYMBOL_T_skip = 15,                    /* "skip"  */
  YYSYMBOL_T_decl = 16,                    /* "decl"  */
  YYSYMBOL_T_for = 17,                     /* "for"  */
  YYSYMBOL_T_nil = 18,                     /* "nil"  */
  YYSYMBOL_T_tail = 19,                    /* "tail"  */
  YYSYMBOL_T_head = 20,                    /* "head"  */
  YYSYMBOL_T_def = 21,                     /* "def"  */
  YYSYMBOL_T_nilq = 22,                    /* "nil?"  */
  YYSYMBOL_T_if = 23,                      /* "if"  */
  YYSYMBOL_T_else = 24,                    /* "else"  */
  YYSYMBOL_T_elsif = 25,                   /* "elsif"  */
  YYSYMBOL_T_not = 26,                     /* "not"  */
  YYSYMBOL_T_int = 27,                     /* "int"  */
  YYSYMBOL_T_or = 28,                      /* "or"  */
  YYSYMBOL_T_assign = 29,                  /* ":="  */
  YYSYMBOL_T_ge = 30,                      /* ">="  */
  YYSYMBOL_T_le = 31,                      /* "<="  */
  YYSYMBOL_T_neq = 32,                     /* "<>"  */
  YYSYMBOL_T_constInt = 33,                /* T_constInt  */
  YYSYMBOL_T_var = 34,                     /* T_var  */
  YYSYMBOL_T_constChar = 35,               /* T_constChar  */
  YYSYMBOL_T_constString = 36,             /* T_constString  */
  YYSYMBOL_37_ = 37,                       /* '='  */
  YYSYMBOL_38_ = 38,                       /* '>'  */
  YYSYMBOL_39_ = 39,                       /* '<'  */
  YYSYMBOL_40_ = 40,                       /* '#'  */
  YYSYMBOL_41_ = 41,                       /* '+'  */
  YYSYMBOL_42_ = 42,                       /* '-'  */
  YYSYMBOL_43_ = 43,                       /* '*'  */
  YYSYMBOL_44_ = 44,                       /* '/'  */
  YYSYMBOL_UPLUS = 45,                     /* UPLUS  */
  YYSYMBOL_UMINUS = 46,                    /* UMINUS  */
  YYSYMBOL_47_ = 47,                       /* ':'  */
  YYSYMBOL_48_ = 48,                       /* '('  */
  YYSYMBOL_49_ = 49,                       /* ')'  */
  YYSYMBOL_50_ = 50,                       /* ';'  */
  YYSYMBOL_51_ = 51,                       /* ','  */
  YYSYMBOL_52_ = 52,                       /* '['  */
  YYSYMBOL_53_ = 53,                       /* ']'  */
  YYSYMBOL_YYACCEPT = 54,                  /* $accept  */
  YYSYMBOL_program = 55,                   /* program  */
  YYSYMBOL_func_def = 56,                  /* func_def  */
  YYSYMBOL_func_decl = 57,                 /* func_decl  */
  YYSYMBOL_definition_list = 58,           /* definition_list  */
  YYSYMBOL_stmt_list = 59,                 /* stmt_list  */
  YYSYMBOL_header_def = 60,                /* header_def  */
  YYSYMBOL_header_decl = 61,               /* header_decl  */
  YYSYMBOL_formal_list = 62,               /* formal_list  */
  YYSYMBOL_formal_head = 63,               /* formal_head  */
  YYSYMBOL_formal = 64,                    /* formal  */
  YYSYMBOL_var_list = 65,                  /* var_list  */
  YYSYMBOL_type = 66,                      /* type  */
  YYSYMBOL_var_def = 67,                   /* var_def  */
  YYSYMBOL_stmt = 68,                      /* stmt  */
  YYSYMBOL_elsif_list = 69,                /* elsif_list  */
  YYSYMBOL_else = 70,                      /* else  */
  YYSYMBOL_simple = 71,                    /* simple  */
  YYSYMBOL_simple_list = 72,               /* simple_list  */
  YYSYMBOL_call = 73,                      /* call  */
  YYSYMBOL_expr_list = 74,                 /* expr_list  */
  YYSYMBOL_expr_head = 75,                 /* expr_head  */
  YYSYMBOL_atom = 76,                      /* atom  */
  YYSYMBOL_expr = 77                       /* expr  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

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
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
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
#define YYLAST   617

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  54
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  24
/* YYNRULES -- Number of rules.  */
#define YYNRULES  80
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  168

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   293


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
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
static const yytype_int16 yyrline[] =
{
       0,   133,   133,   137,   141,   145,   146,   147,   148,   152,
     153,   157,   158,   162,   163,   167,   168,   172,   173,   177,
     178,   182,   183,   187,   188,   189,   190,   191,   196,   201,
     202,   203,   204,   205,   209,   210,   214,   215,   219,   220,
     221,   222,   226,   227,   231,   235,   236,   240,   241,   245,
     246,   247,   248,   249,   253,   254,   255,   256,   257,   258,
     259,   260,   261,   262,   263,   264,   265,   266,   267,   268,
     269,   270,   271,   272,   273,   274,   276,   277,   278,   279,
     280
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "\"and\"", "\"end\"",
  "\"list\"", "\"ref\"", "\"bool\"", "\"exit\"", "\"mod\"", "\"return\"",
  "\"char\"", "\"false\"", "\"true\"", "\"new\"", "\"skip\"", "\"decl\"",
  "\"for\"", "\"nil\"", "\"tail\"", "\"head\"", "\"def\"", "\"nil?\"",
  "\"if\"", "\"else\"", "\"elsif\"", "\"not\"", "\"int\"", "\"or\"",
  "\":=\"", "\">=\"", "\"<=\"", "\"<>\"", "T_constInt", "T_var",
  "T_constChar", "T_constString", "'='", "'>'", "'<'", "'#'", "'+'", "'-'",
  "'*'", "'/'", "UPLUS", "UMINUS", "':'", "'('", "')'", "';'", "','",
  "'['", "']'", "$accept", "program", "func_def", "func_decl",
  "definition_list", "stmt_list", "header_def", "header_decl",
  "formal_list", "formal_head", "formal", "var_list", "type", "var_def",
  "stmt", "elsif_list", "else", "simple", "simple_list", "call",
  "expr_list", "expr_head", "atom", "expr", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,    61,    62,    60,
      35,    43,    45,    42,    47,   292,   293,    58,    40,    41,
      59,    44,    91,    93
};
#endif

#define YYPACT_NINF (-74)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-54)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      -7,     4,    16,   -74,   -30,   -74,   -74,   -74,   -12,    -8,
     -29,   -74,   427,    -3,   -74,     6,    18,    45,     3,   549,
     567,    -3,   -74,   -74,   -74,   427,    25,   -17,   -74,   478,
     -74,   119,    19,   478,   -42,    36,   -74,   -74,   534,   -17,
     -74,   -74,   -74,    70,    80,    61,   -17,   -74,   -74,    60,
     -74,   -74,   -74,    65,    66,    72,   478,   -74,   -74,   478,
     478,   478,   -74,   -74,   405,    74,   -74,    -4,   -74,    40,
     326,    69,   478,   478,   -74,   -74,    60,   453,   -74,    60,
      98,   478,   478,   478,    64,   -74,   -74,   238,   478,   478,
     478,   478,   478,   478,   478,   478,   478,   478,   478,   478,
     478,   478,    -3,    85,   478,    19,   581,    86,   478,   128,
     152,   427,   405,   -74,   258,   282,   302,   -74,    64,   -74,
     420,   493,   493,   493,   493,   493,   493,    38,    -1,    -1,
     -74,   -74,    89,    -3,   212,   -74,   392,   -74,   194,   -74,
     -74,    87,   -74,   -74,   -74,   -74,   101,    19,   107,   478,
     153,   -74,   -74,   377,   -74,    23,   581,   344,   -74,   170,
     581,   581,   581,   -74,   535,   392,   -74,   -74
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     2,     0,    24,    25,    23,     0,     0,
       0,     1,     0,    17,     5,     0,     0,     0,     0,     0,
       0,    17,    26,    27,    11,     0,    16,     0,    30,     0,
      38,     0,     0,     0,    49,    50,     6,     7,     0,     0,
       8,     9,    29,    41,     0,     0,     0,    18,    21,    19,
      72,    71,    76,     0,     0,     0,     0,    55,    56,     0,
       0,     0,    53,    54,    31,     0,     4,     0,    42,     0,
       0,    47,     0,     0,     3,    10,    28,     0,    12,    20,
       0,     0,     0,     0,    73,    58,    59,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    17,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    39,    22,     0,     0,     0,    57,    74,    64,
      75,    70,    69,    68,    65,    66,    67,    78,    60,    61,
      62,    63,     0,    17,     0,    43,    36,    44,    46,    52,
      51,     0,    80,    79,    77,    13,     0,     0,     0,     0,
       0,    34,    48,     0,    14,     0,     0,     0,    32,     0,
       0,    37,     0,    40,     0,    36,    33,    35
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -74,   -74,   142,   -74,   -74,   -73,   -74,   -74,   -18,   -74,
     -74,    -2,     1,   -74,   -36,     9,   -74,   -28,    17,   -20,
     -74,   -74,   -13,   -32
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,    37,    20,    38,     9,    66,    18,    19,
      26,    49,    10,    40,    41,   150,   151,    42,    69,    62,
     107,   108,    63,    64
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      43,    70,    75,    45,    68,    15,    71,    44,    89,     4,
      72,     5,    43,    17,     1,     6,    11,    48,    43,    44,
      27,    39,    12,    16,    84,    44,    46,    85,    86,    87,
     103,     7,    67,   136,    30,    16,    13,    76,     8,    14,
     109,   110,   100,   101,    79,   112,   -15,    89,    16,   114,
     115,   116,    24,    34,    21,    35,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     160,    22,   134,    89,   105,    47,   138,   135,    97,    98,
      99,   100,   101,   161,   132,    43,    43,   164,    73,   165,
     104,   105,    44,    44,    91,    92,    93,    16,    23,   -53,
      75,    94,    95,    96,    97,    98,    99,   100,   101,    77,
      78,    80,   141,    81,    82,   146,    43,   157,   -45,    68,
      83,   159,   102,    44,     4,    75,     5,    43,    75,    75,
       6,    88,   113,   133,    44,   137,    43,    89,   145,   153,
      43,    43,    43,    44,    43,    43,     7,    44,    44,    44,
     154,    44,    44,    65,   156,    88,    90,   158,    91,    92,
      93,    89,    36,     0,   155,    94,    95,    96,    97,    98,
      99,   100,   101,    88,   167,     0,     0,     0,     0,    89,
      90,   139,    91,    92,    93,     0,     0,     0,     0,    94,
      95,    96,    97,    98,    99,   100,   101,    88,    90,     0,
      91,    92,    93,    89,     0,   140,     0,    94,    95,    96,
      97,    98,    99,   100,   101,    88,     0,     0,     0,     0,
       0,    89,    90,   163,    91,    92,    93,     0,     0,     0,
       0,    94,    95,    96,    97,    98,    99,   100,   101,     0,
      90,    88,    91,    92,    93,   152,     0,    89,     0,    94,
      95,    96,    97,    98,    99,   100,   101,     0,     0,     0,
       0,    88,   147,     0,     0,     0,    90,    89,    91,    92,
      93,     0,     0,     0,     0,    94,    95,    96,    97,    98,
      99,   100,   101,     0,     0,    88,    90,   117,    91,    92,
      93,    89,     0,     0,     0,    94,    95,    96,    97,    98,
      99,   100,   101,     0,     0,    88,     0,   142,     0,     0,
      90,    89,    91,    92,    93,     0,     0,     0,     0,    94,
      95,    96,    97,    98,    99,   100,   101,     0,     0,    88,
      90,   143,    91,    92,    93,    89,     0,     0,     0,    94,
      95,    96,    97,    98,    99,   100,   101,    88,     0,     0,
       0,   144,     0,    89,    90,     0,    91,    92,    93,     0,
       0,     0,     0,    94,    95,    96,    97,    98,    99,   100,
     101,     0,    90,   106,    91,    92,    93,     0,     0,     0,
       0,    94,    95,    96,    97,    98,    99,   100,   101,    50,
      51,   162,     0,     0,     0,    52,    53,    54,     0,    55,
      28,     0,    29,    56,     0,     0,     0,    30,    88,    32,
      57,    34,    58,    35,    89,    33,   148,   149,    59,    60,
       0,     0,     0,    88,     0,    61,    34,     0,    35,    89,
      22,     0,     4,    90,     5,    91,    92,    93,     6,     0,
       0,     0,    94,    95,    96,    97,    98,    99,   100,   101,
      91,    92,    93,     0,     7,     0,     0,    94,    95,    96,
      97,    98,    99,   100,   101,    50,    51,   111,     0,     0,
       0,    52,    53,    54,     0,    55,     0,     0,     0,    56,
       0,     0,     0,     0,     0,     0,    57,    34,    58,    35,
      50,    51,     0,     0,    59,    60,    52,    53,    54,     0,
      55,    61,    89,     0,    56,     0,     0,     0,     0,     0,
       0,    57,    34,    58,    35,     0,     0,     0,     0,    59,
      60,     0,     0,   -54,   -54,   -54,    61,     0,     0,     0,
     -54,   -54,   -54,    97,    98,    99,   100,   101,    74,   166,
       0,     0,    28,    28,    29,    29,     0,     0,     0,    30,
      30,    32,    32,     0,     4,    25,     5,    33,    33,     0,
       6,     0,     0,     0,     0,     0,     0,     0,    34,    34,
      35,    35,     4,     0,     5,    28,     7,    29,     6,     0,
       0,     0,    30,    31,    32,     0,     0,     0,     1,    28,
      33,    29,     0,     0,     7,     0,    30,     0,    32,     0,
       0,    34,     0,    35,    33,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    34,     0,    35
};

static const yytype_int16 yycheck[] =
{
      20,    33,    38,    21,    32,    34,    48,    20,     9,     5,
      52,     7,    32,    12,    21,    11,     0,    34,    38,    32,
      19,    20,    52,    52,    56,    38,    25,    59,    60,    61,
      34,    27,    31,   106,    15,    52,    48,    39,    34,    47,
      72,    73,    43,    44,    46,    77,    49,     9,    52,    81,
      82,    83,    49,    34,    48,    36,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
      47,    53,   104,     9,    51,    50,   108,   105,    40,    41,
      42,    43,    44,   156,   102,   105,   106,   160,    52,   162,
      50,    51,   105,   106,    30,    31,    32,    52,    53,    29,
     136,    37,    38,    39,    40,    41,    42,    43,    44,    29,
      49,    51,   111,    48,    48,   133,   136,   149,    49,   147,
      48,   153,    48,   136,     5,   161,     7,   147,   164,   165,
      11,     3,    34,    48,   147,    49,   156,     9,    49,    52,
     160,   161,   162,   156,   164,   165,    27,   160,   161,   162,
      49,   164,   165,    34,    47,     3,    28,     4,    30,    31,
      32,     9,    20,    -1,   147,    37,    38,    39,    40,    41,
      42,    43,    44,     3,   165,    -1,    -1,    -1,    -1,     9,
      28,    53,    30,    31,    32,    -1,    -1,    -1,    -1,    37,
      38,    39,    40,    41,    42,    43,    44,     3,    28,    -1,
      30,    31,    32,     9,    -1,    53,    -1,    37,    38,    39,
      40,    41,    42,    43,    44,     3,    -1,    -1,    -1,    -1,
      -1,     9,    28,    53,    30,    31,    32,    -1,    -1,    -1,
      -1,    37,    38,    39,    40,    41,    42,    43,    44,    -1,
      28,     3,    30,    31,    32,    51,    -1,     9,    -1,    37,
      38,    39,    40,    41,    42,    43,    44,    -1,    -1,    -1,
      -1,     3,    50,    -1,    -1,    -1,    28,     9,    30,    31,
      32,    -1,    -1,    -1,    -1,    37,    38,    39,    40,    41,
      42,    43,    44,    -1,    -1,     3,    28,    49,    30,    31,
      32,     9,    -1,    -1,    -1,    37,    38,    39,    40,    41,
      42,    43,    44,    -1,    -1,     3,    -1,    49,    -1,    -1,
      28,     9,    30,    31,    32,    -1,    -1,    -1,    -1,    37,
      38,    39,    40,    41,    42,    43,    44,    -1,    -1,     3,
      28,    49,    30,    31,    32,     9,    -1,    -1,    -1,    37,
      38,    39,    40,    41,    42,    43,    44,     3,    -1,    -1,
      -1,    49,    -1,     9,    28,    -1,    30,    31,    32,    -1,
      -1,    -1,    -1,    37,    38,    39,    40,    41,    42,    43,
      44,    -1,    28,    47,    30,    31,    32,    -1,    -1,    -1,
      -1,    37,    38,    39,    40,    41,    42,    43,    44,    12,
      13,    47,    -1,    -1,    -1,    18,    19,    20,    -1,    22,
       8,    -1,    10,    26,    -1,    -1,    -1,    15,     3,    17,
      33,    34,    35,    36,     9,    23,    24,    25,    41,    42,
      -1,    -1,    -1,     3,    -1,    48,    34,    -1,    36,     9,
      53,    -1,     5,    28,     7,    30,    31,    32,    11,    -1,
      -1,    -1,    37,    38,    39,    40,    41,    42,    43,    44,
      30,    31,    32,    -1,    27,    -1,    -1,    37,    38,    39,
      40,    41,    42,    43,    44,    12,    13,    14,    -1,    -1,
      -1,    18,    19,    20,    -1,    22,    -1,    -1,    -1,    26,
      -1,    -1,    -1,    -1,    -1,    -1,    33,    34,    35,    36,
      12,    13,    -1,    -1,    41,    42,    18,    19,    20,    -1,
      22,    48,     9,    -1,    26,    -1,    -1,    -1,    -1,    -1,
      -1,    33,    34,    35,    36,    -1,    -1,    -1,    -1,    41,
      42,    -1,    -1,    30,    31,    32,    48,    -1,    -1,    -1,
      37,    38,    39,    40,    41,    42,    43,    44,     4,     4,
      -1,    -1,     8,     8,    10,    10,    -1,    -1,    -1,    15,
      15,    17,    17,    -1,     5,     6,     7,    23,    23,    -1,
      11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    34,    34,
      36,    36,     5,    -1,     7,     8,    27,    10,    11,    -1,
      -1,    -1,    15,    16,    17,    -1,    -1,    -1,    21,     8,
      23,    10,    -1,    -1,    27,    -1,    15,    -1,    17,    -1,
      -1,    34,    -1,    36,    23,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    34,    -1,    36
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    21,    55,    56,     5,     7,    11,    27,    34,    60,
      66,     0,    52,    48,    47,    34,    52,    66,    62,    63,
      58,    48,    53,    53,    49,     6,    64,    66,     8,    10,
      15,    16,    17,    23,    34,    36,    56,    57,    59,    66,
      67,    68,    71,    73,    76,    62,    66,    50,    34,    65,
      12,    13,    18,    19,    20,    22,    26,    33,    35,    41,
      42,    48,    73,    76,    77,    34,    61,    66,    71,    72,
      77,    48,    52,    52,     4,    68,    65,    29,    49,    65,
      51,    48,    48,    48,    77,    77,    77,    77,     3,     9,
      28,    30,    31,    32,    37,    38,    39,    40,    41,    42,
      43,    44,    48,    34,    50,    51,    47,    74,    75,    77,
      77,    14,    77,    34,    77,    77,    77,    49,    77,    77,
      77,    77,    77,    77,    77,    77,    77,    77,    77,    77,
      77,    77,    62,    48,    77,    71,    59,    49,    77,    53,
      53,    66,    49,    49,    49,    49,    62,    50,    24,    25,
      69,    70,    51,    52,    49,    72,    47,    77,     4,    77,
      47,    59,    47,    53,    59,    59,     4,    69
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    54,    55,    56,    57,    58,    58,    58,    58,    59,
      59,    60,    60,    61,    61,    62,    62,    63,    63,    64,
      64,    65,    65,    66,    66,    66,    66,    66,    67,    68,
      68,    68,    68,    68,    69,    69,    70,    70,    71,    71,
      71,    71,    72,    72,    73,    74,    74,    75,    75,    76,
      76,    76,    76,    76,    77,    77,    77,    77,    77,    77,
      77,    77,    77,    77,    77,    77,    77,    77,    77,    77,
      77,    77,    77,    77,    77,    77,    77,    77,    77,    77,
      77
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     6,     2,     0,     2,     2,     2,     1,
       2,     4,     5,     4,     5,     0,     2,     0,     3,     2,
       3,     1,     3,     1,     1,     1,     3,     4,     2,     1,
       1,     2,     6,     9,     1,     5,     0,     3,     1,     3,
       7,     1,     1,     3,     4,     0,     2,     0,     3,     1,
       1,     4,     4,     1,     1,     1,     1,     3,     2,     2,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     1,     1,     2,     3,     3,     1,     4,     3,     4,
       4
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


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


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YY_LOCATION_PRINT
#  if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#   define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

#  else
#   define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#  endif
# endif /* !defined YY_LOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  YYUSE (yylocationp);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yykind < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yykind], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YY_LOCATION_PRINT (yyo, *yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]));
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
  YYLTYPE *yylloc;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
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
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
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
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
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
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
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
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
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
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      yyerror_range[1] = yylloc;
      goto yyerrlab1;
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: func_def  */
#line 133 "parser.y"
                                                                        { (yyvsp[0].func_def)->sem(); (yyvsp[0].func_def)->llvm_compile_and_dump(optimize); }
#line 1725 "parser.cpp"
    break;

  case 3: /* func_def: "def" header_def ':' definition_list stmt_list "end"  */
#line 137 "parser.y"
                                                                        { (yyval.func_def) = new FunctionDefinition((yyvsp[-4].header),(yyvsp[-2].def_list),(yyvsp[-1].stmt_list)); (yyval.func_def)->set_line(yylineno); }
#line 1731 "parser.cpp"
    break;

  case 4: /* func_decl: "decl" header_decl  */
#line 141 "parser.y"
                                                                { (yyval.func_decl) = new FunctionDeclaration((yyvsp[0].header)); (yyval.func_decl)->set_line(yylineno); }
#line 1737 "parser.cpp"
    break;

  case 5: /* definition_list: %empty  */
#line 145 "parser.y"
                                                                                { (yyval.def_list) = new DefinitionList(); (yyval.def_list)->set_line(yylineno);}
#line 1743 "parser.cpp"
    break;

  case 6: /* definition_list: definition_list func_def  */
#line 146 "parser.y"
                                                        { (yyvsp[-1].def_list)->append((yyvsp[0].func_def)); (yyval.def_list)=(yyvsp[-1].def_list); }
#line 1749 "parser.cpp"
    break;

  case 7: /* definition_list: definition_list func_decl  */
#line 147 "parser.y"
                                                { (yyvsp[-1].def_list)->append((yyvsp[0].func_decl)); (yyval.def_list)=(yyvsp[-1].def_list); }
#line 1755 "parser.cpp"
    break;

  case 8: /* definition_list: definition_list var_def  */
#line 148 "parser.y"
                                                        { (yyvsp[-1].def_list)->append((yyvsp[0].var_definition)); (yyval.def_list)=(yyvsp[-1].def_list); }
#line 1761 "parser.cpp"
    break;

  case 9: /* stmt_list: stmt  */
#line 152 "parser.y"
                                                                        { (yyval.stmt_list) = new StmtList((yyvsp[0].stmt)); (yyval.stmt_list)->set_line(yylineno);}
#line 1767 "parser.cpp"
    break;

  case 10: /* stmt_list: stmt_list stmt  */
#line 153 "parser.y"
                                                                { (yyvsp[-1].stmt_list)->append((yyvsp[0].stmt)); (yyval.stmt_list)=(yyvsp[-1].stmt_list); }
#line 1773 "parser.cpp"
    break;

  case 11: /* header_def: T_var '(' formal_list ')'  */
#line 157 "parser.y"
                                                                { (yyval.header) = new Header((yyvsp[-3].str), (yyvsp[-1].formal_list), typeVoid, Func_Def); (yyval.header)->set_line(yylineno);}
#line 1779 "parser.cpp"
    break;

  case 12: /* header_def: type T_var '(' formal_list ')'  */
#line 158 "parser.y"
                                                        { (yyval.header) = new Header((yyvsp[-3].str), (yyvsp[-1].formal_list), (yyvsp[-4].type), Func_Def); (yyval.header)->set_line(yylineno);}
#line 1785 "parser.cpp"
    break;

  case 13: /* header_decl: T_var '(' formal_list ')'  */
#line 162 "parser.y"
                                                                { (yyval.header) = new Header((yyvsp[-3].str), (yyvsp[-1].formal_list), typeVoid, Func_Decl); (yyval.header)->set_line(yylineno);}
#line 1791 "parser.cpp"
    break;

  case 14: /* header_decl: type T_var '(' formal_list ')'  */
#line 163 "parser.y"
                                                        { (yyval.header) = new Header((yyvsp[-3].str), (yyvsp[-1].formal_list), (yyvsp[-4].type), Func_Decl); (yyval.header)->set_line(yylineno);}
#line 1797 "parser.cpp"
    break;

  case 15: /* formal_list: %empty  */
#line 167 "parser.y"
                                                                                { (yyval.formal_list) = new FormalList(); (yyval.formal_list)->set_line(yylineno);}
#line 1803 "parser.cpp"
    break;

  case 16: /* formal_list: formal_head formal  */
#line 168 "parser.y"
                                                                { (yyvsp[-1].formal_list)->append((yyvsp[0].formal)) ; (yyval.formal_list) = (yyvsp[-1].formal_list); }
#line 1809 "parser.cpp"
    break;

  case 17: /* formal_head: %empty  */
#line 172 "parser.y"
                                                                                { (yyval.formal_list) = new FormalList(); (yyval.formal_list)->set_line(yylineno);}
#line 1815 "parser.cpp"
    break;

  case 18: /* formal_head: formal_head formal ';'  */
#line 173 "parser.y"
                                                        { (yyvsp[-2].formal_list)->append((yyvsp[-1].formal)); (yyval.formal_list) = (yyvsp[-2].formal_list); }
#line 1821 "parser.cpp"
    break;

  case 19: /* formal: type var_list  */
#line 177 "parser.y"
                                                                { (yyval.formal) = new Formal((yyvsp[-1].type),(yyvsp[0].var_list)); (yyval.formal)->set_line(yylineno);}
#line 1827 "parser.cpp"
    break;

  case 20: /* formal: "ref" type var_list  */
#line 178 "parser.y"
                                                        { (yyval.formal) = new Formal((yyvsp[-1].type),(yyvsp[0].var_list),true); (yyval.formal)->set_line(yylineno);}
#line 1833 "parser.cpp"
    break;

  case 21: /* var_list: T_var  */
#line 182 "parser.y"
                                                                        { (yyval.var_list) = new VarList((yyvsp[0].str)); (yyval.var_list)->set_line(yylineno);}
#line 1839 "parser.cpp"
    break;

  case 22: /* var_list: var_list ',' T_var  */
#line 183 "parser.y"
                                                                { (yyvsp[-2].var_list)->append((yyvsp[0].str)); (yyval.var_list) = (yyvsp[-2].var_list); }
#line 1845 "parser.cpp"
    break;

  case 23: /* type: "int"  */
#line 187 "parser.y"
                                                                        { (yyval.type) = typeInteger; }
#line 1851 "parser.cpp"
    break;

  case 24: /* type: "bool"  */
#line 188 "parser.y"
                                                                        { (yyval.type) = typeBoolean; }
#line 1857 "parser.cpp"
    break;

  case 25: /* type: "char"  */
#line 189 "parser.y"
                                                                        { (yyval.type) = typeChar; }
#line 1863 "parser.cpp"
    break;

  case 26: /* type: type '[' ']'  */
#line 190 "parser.y"
                                                                { (yyval.type) = typeIArray((yyvsp[-2].type)); }
#line 1869 "parser.cpp"
    break;

  case 27: /* type: "list" '[' type ']'  */
#line 191 "parser.y"
                                                        { (yyval.type) = typeList((yyvsp[-1].type)); }
#line 1875 "parser.cpp"
    break;

  case 28: /* var_def: type var_list  */
#line 196 "parser.y"
                                                                { (yyval.var_definition) = new VarDefinition((yyvsp[-1].type),(yyvsp[0].var_list)); (yyval.var_definition)->set_line(yylineno);}
#line 1881 "parser.cpp"
    break;

  case 29: /* stmt: simple  */
#line 201 "parser.y"
                                                                                                                                                { (yyval.stmt) = (yyvsp[0].stmt); }
#line 1887 "parser.cpp"
    break;

  case 30: /* stmt: "exit"  */
#line 202 "parser.y"
                                                                                                                                                { (yyval.stmt) = new ExitStmt(); (yyval.stmt)->set_line(yylineno);}
#line 1893 "parser.cpp"
    break;

  case 31: /* stmt: "return" expr  */
#line 203 "parser.y"
                                                                                                                                        { (yyval.stmt) = new ReturnStmt((yyvsp[0].expr)); (yyval.stmt)->set_line(yylineno);}
#line 1899 "parser.cpp"
    break;

  case 32: /* stmt: "if" expr ':' stmt_list elsif_list "end"  */
#line 204 "parser.y"
                                                                                                                { (yyval.stmt) = new If((yyvsp[-4].expr),(yyvsp[-2].stmt_list),(yyvsp[-1].ifClass)); (yyval.stmt)->set_line(yylineno);}
#line 1905 "parser.cpp"
    break;

  case 33: /* stmt: "for" simple_list ';' expr ';' simple_list ':' stmt_list "end"  */
#line 205 "parser.y"
                                                                                        { (yyval.stmt) = new For((yyvsp[-7].stmt_list),(yyvsp[-5].expr),(yyvsp[-3].stmt_list),(yyvsp[-1].stmt_list)); (yyval.stmt)->set_line(yylineno);}
#line 1911 "parser.cpp"
    break;

  case 34: /* elsif_list: else  */
#line 209 "parser.y"
                                                                                                { (yyval.ifClass) = (yyvsp[0].ifClass); }
#line 1917 "parser.cpp"
    break;

  case 35: /* elsif_list: "elsif" expr ':' stmt_list elsif_list  */
#line 210 "parser.y"
                                                                { (yyval.ifClass) = new If((yyvsp[-3].expr),(yyvsp[-1].stmt_list),(yyvsp[0].ifClass)); (yyval.ifClass)->set_line(yylineno);}
#line 1923 "parser.cpp"
    break;

  case 36: /* else: %empty  */
#line 214 "parser.y"
                                                                { (yyval.ifClass) = NULL; }
#line 1929 "parser.cpp"
    break;

  case 37: /* else: "else" ':' stmt_list  */
#line 215 "parser.y"
                                                        { (yyval.ifClass) = new If(NULL,(yyvsp[0].stmt_list),NULL); (yyval.ifClass)->set_line(yylineno);}
#line 1935 "parser.cpp"
    break;

  case 38: /* simple: "skip"  */
#line 219 "parser.y"
                                                                        { (yyval.stmt) = new SkipStmt(); (yyval.stmt)->set_line(yylineno);}
#line 1941 "parser.cpp"
    break;

  case 39: /* simple: atom ":=" expr  */
#line 220 "parser.y"
                                                                { (yyval.stmt) = new AssignStmt((yyvsp[-2].expr),(yyvsp[0].expr)); (yyval.stmt)->set_line(yylineno);}
#line 1947 "parser.cpp"
    break;

  case 40: /* simple: atom ":=" "new" type '[' expr ']'  */
#line 221 "parser.y"
                                                     { (yyval.stmt) = new ArrayInit((yyvsp[-6].expr),(yyvsp[-3].type),(yyvsp[-1].expr)); (yyval.stmt)->set_line(yylineno);}
#line 1953 "parser.cpp"
    break;

  case 41: /* simple: call  */
#line 222 "parser.y"
                                                                        { (yyval.stmt) = (yyvsp[0].call_object); }
#line 1959 "parser.cpp"
    break;

  case 42: /* simple_list: simple  */
#line 226 "parser.y"
                                                                        { (yyval.stmt_list) = new StmtList((yyvsp[0].stmt)); (yyval.stmt_list)->set_line(yylineno);}
#line 1965 "parser.cpp"
    break;

  case 43: /* simple_list: simple_list ',' simple  */
#line 227 "parser.y"
                                                        { (yyvsp[-2].stmt_list)->append((yyvsp[0].stmt)); (yyval.stmt_list) = (yyvsp[-2].stmt_list); }
#line 1971 "parser.cpp"
    break;

  case 44: /* call: T_var '(' expr_list ')'  */
#line 231 "parser.y"
                                                        { (yyval.call_object) = new CallObject((yyvsp[-3].str),(yyvsp[-1].expr_list)); (yyval.call_object)->set_line(yylineno);}
#line 1977 "parser.cpp"
    break;

  case 45: /* expr_list: %empty  */
#line 235 "parser.y"
                                                                { (yyval.expr_list) = new ExprList(); (yyval.expr_list)->set_line(yylineno);}
#line 1983 "parser.cpp"
    break;

  case 46: /* expr_list: expr_head expr  */
#line 236 "parser.y"
                                                                { (yyvsp[-1].expr_list)->append((yyvsp[0].expr)); (yyval.expr_list) = (yyvsp[-1].expr_list); }
#line 1989 "parser.cpp"
    break;

  case 47: /* expr_head: %empty  */
#line 240 "parser.y"
                                                                                { (yyval.expr_list) = new ExprList(); (yyval.expr_list)->set_line(yylineno);}
#line 1995 "parser.cpp"
    break;

  case 48: /* expr_head: expr_head expr ','  */
#line 241 "parser.y"
                                                        { (yyvsp[-2].expr_list)->append((yyvsp[-1].expr)); (yyval.expr_list) = (yyvsp[-2].expr_list); }
#line 2001 "parser.cpp"
    break;

  case 49: /* atom: T_var  */
#line 245 "parser.y"
                                                                        { (yyval.expr) = new Var((yyvsp[0].str)); (yyval.expr)->set_line(yylineno);}
#line 2007 "parser.cpp"
    break;

  case 50: /* atom: T_constString  */
#line 246 "parser.y"
                                                                { (yyval.expr) = new ConstString((yyvsp[0].str)); (yyval.expr)->set_line(yylineno);}
#line 2013 "parser.cpp"
    break;

  case 51: /* atom: T_constString '[' expr ']'  */
#line 247 "parser.y"
                                                { (yyval.expr) = new ConstString((yyvsp[-3].str),(yyvsp[-1].expr)); (yyval.expr)->set_line(yylineno);}
#line 2019 "parser.cpp"
    break;

  case 52: /* atom: T_var '[' expr ']'  */
#line 248 "parser.y"
                                                        { (yyval.expr) = new Var((yyvsp[-3].str),(yyvsp[-1].expr)); (yyval.expr)->set_line(yylineno);}
#line 2025 "parser.cpp"
    break;

  case 53: /* atom: call  */
#line 249 "parser.y"
                                                                        { (yyval.expr) = (yyvsp[0].call_object); }
#line 2031 "parser.cpp"
    break;

  case 54: /* expr: atom  */
#line 253 "parser.y"
                                                                        { (yyval.expr) = (yyvsp[0].expr); }
#line 2037 "parser.cpp"
    break;

  case 55: /* expr: T_constInt  */
#line 254 "parser.y"
                                                                { (yyval.expr) = new ConstInt((yyvsp[0].num)); (yyval.expr)->set_line(yylineno);}
#line 2043 "parser.cpp"
    break;

  case 56: /* expr: T_constChar  */
#line 255 "parser.y"
                                                                { (yyval.expr) = new ConstChar((yyvsp[0].num)); (yyval.expr)->set_line(yylineno);}
#line 2049 "parser.cpp"
    break;

  case 57: /* expr: '(' expr ')'  */
#line 256 "parser.y"
                                                                { (yyval.expr) = (yyvsp[-1].expr); }
#line 2055 "parser.cpp"
    break;

  case 58: /* expr: '+' expr  */
#line 257 "parser.y"
                                                        { (yyval.expr) = new BinOp(NULL,'+',(yyvsp[0].expr)); (yyval.expr)->set_line(yylineno);}
#line 2061 "parser.cpp"
    break;

  case 59: /* expr: '-' expr  */
#line 258 "parser.y"
                                                        { (yyval.expr) = new BinOp(NULL,'-',(yyvsp[0].expr)); (yyval.expr)->set_line(yylineno);}
#line 2067 "parser.cpp"
    break;

  case 60: /* expr: expr '+' expr  */
#line 259 "parser.y"
                                                                { (yyval.expr) = new BinOp((yyvsp[-2].expr),'+',(yyvsp[0].expr)); (yyval.expr)->set_line(yylineno);}
#line 2073 "parser.cpp"
    break;

  case 61: /* expr: expr '-' expr  */
#line 260 "parser.y"
                                                                { (yyval.expr) = new BinOp((yyvsp[-2].expr),'-',(yyvsp[0].expr)); (yyval.expr)->set_line(yylineno);}
#line 2079 "parser.cpp"
    break;

  case 62: /* expr: expr '*' expr  */
#line 261 "parser.y"
                                                                { (yyval.expr) = new BinOp((yyvsp[-2].expr),'*',(yyvsp[0].expr)); (yyval.expr)->set_line(yylineno);}
#line 2085 "parser.cpp"
    break;

  case 63: /* expr: expr '/' expr  */
#line 262 "parser.y"
                                                                { (yyval.expr) = new BinOp((yyvsp[-2].expr),'/',(yyvsp[0].expr)); (yyval.expr)->set_line(yylineno);}
#line 2091 "parser.cpp"
    break;

  case 64: /* expr: expr "mod" expr  */
#line 263 "parser.y"
                                                                { (yyval.expr) = new BinOp((yyvsp[-2].expr),'%',(yyvsp[0].expr)); (yyval.expr)->set_line(yylineno);}
#line 2097 "parser.cpp"
    break;

  case 65: /* expr: expr '=' expr  */
#line 264 "parser.y"
                                                                { (yyval.expr) = new RelOp((yyvsp[-2].expr),eq,(yyvsp[0].expr)); (yyval.expr)->set_line(yylineno);}
#line 2103 "parser.cpp"
    break;

  case 66: /* expr: expr '>' expr  */
#line 265 "parser.y"
                                                                { (yyval.expr) = new RelOp((yyvsp[-2].expr),gt,(yyvsp[0].expr)); (yyval.expr)->set_line(yylineno);}
#line 2109 "parser.cpp"
    break;

  case 67: /* expr: expr '<' expr  */
#line 266 "parser.y"
                                                                { (yyval.expr) = new RelOp((yyvsp[-2].expr),lt,(yyvsp[0].expr)); (yyval.expr)->set_line(yylineno);}
#line 2115 "parser.cpp"
    break;

  case 68: /* expr: expr "<>" expr  */
#line 267 "parser.y"
                                                                { (yyval.expr) = new RelOp((yyvsp[-2].expr),neq,(yyvsp[0].expr)); (yyval.expr)->set_line(yylineno);}
#line 2121 "parser.cpp"
    break;

  case 69: /* expr: expr "<=" expr  */
#line 268 "parser.y"
                                                                { (yyval.expr) = new RelOp((yyvsp[-2].expr),le,(yyvsp[0].expr)); (yyval.expr)->set_line(yylineno);}
#line 2127 "parser.cpp"
    break;

  case 70: /* expr: expr ">=" expr  */
#line 269 "parser.y"
                                                                { (yyval.expr) = new RelOp((yyvsp[-2].expr),ge,(yyvsp[0].expr)); (yyval.expr)->set_line(yylineno);}
#line 2133 "parser.cpp"
    break;

  case 71: /* expr: "true"  */
#line 270 "parser.y"
                                                                        { (yyval.expr) = new LogOp(TRUE); (yyval.expr)->set_line(yylineno);}
#line 2139 "parser.cpp"
    break;

  case 72: /* expr: "false"  */
#line 271 "parser.y"
                                                                        { (yyval.expr) = new LogOp(FALSE); (yyval.expr)->set_line(yylineno);}
#line 2145 "parser.cpp"
    break;

  case 73: /* expr: "not" expr  */
#line 272 "parser.y"
                                                                { (yyval.expr) = new LogOp(NOT,NULL,(yyvsp[0].expr)); (yyval.expr)->set_line(yylineno);}
#line 2151 "parser.cpp"
    break;

  case 74: /* expr: expr "and" expr  */
#line 273 "parser.y"
                                                                { (yyval.expr) = new LogOp(AND,(yyvsp[-2].expr),(yyvsp[0].expr)); (yyval.expr)->set_line(yylineno);}
#line 2157 "parser.cpp"
    break;

  case 75: /* expr: expr "or" expr  */
#line 274 "parser.y"
                                                                { (yyval.expr) = new LogOp(OR,(yyvsp[-2].expr),(yyvsp[0].expr)); (yyval.expr)->set_line(yylineno);}
#line 2163 "parser.cpp"
    break;

  case 76: /* expr: "nil"  */
#line 276 "parser.y"
                                                                        { (yyval.expr) = new ListOp(nil,NULL,NULL); (yyval.expr)->set_line(yylineno);}
#line 2169 "parser.cpp"
    break;

  case 77: /* expr: "nil?" '(' expr ')'  */
#line 277 "parser.y"
                                                        { (yyval.expr) = new ListOp(nilq,NULL,(yyvsp[-1].expr)); (yyval.expr)->set_line(yylineno);}
#line 2175 "parser.cpp"
    break;

  case 78: /* expr: expr '#' expr  */
#line 278 "parser.y"
                                                                { (yyval.expr) = new ListOp(append,(yyvsp[-2].expr),(yyvsp[0].expr)); (yyval.expr)->set_line(yylineno);}
#line 2181 "parser.cpp"
    break;

  case 79: /* expr: "head" '(' expr ')'  */
#line 279 "parser.y"
                                                        { (yyval.expr) = new ListOp(head,NULL,(yyvsp[-1].expr)); (yyval.expr)->set_line(yylineno);}
#line 2187 "parser.cpp"
    break;

  case 80: /* expr: "tail" '(' expr ')'  */
#line 280 "parser.y"
                                                        { (yyval.expr) = new ListOp(tail,NULL,(yyvsp[-1].expr)); (yyval.expr)->set_line(yylineno);}
#line 2193 "parser.cpp"
    break;


#line 2197 "parser.cpp"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;
  *++yylsp = yyloc;

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
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken, &yylloc};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          goto yyexhaustedlab;
      }
    }

  yyerror_range[1] = yylloc;
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
                      yytoken, &yylval, &yylloc);
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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

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


#if 1
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturn;
#endif


/*-------------------------------------------------------.
| yyreturn -- parsing is finished, clean up and return.  |
`-------------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 283 "parser.y"


// const char * filename;

int main(int argc, char *argv[])
{
	char *filename;

	for(int i=1; i<argc; i++)
	{
		if(strcmp(argv[i], "-o") == 0)
			optimize = true;
		else
			filename = argv[i];
	}
	
	yyin = fopen(filename,"r");
	initSymbolTable(ST_SIZE);
	openScope();
	initPreBuiltFunctionsInST();
	int result = yyparse();
	destroySymbolTable();
	fclose(yyin);
	return result;
}
