/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
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
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

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

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "types.h"
    #include "math.h"    
    #include "exec_fun.h"

    int yydebug = 1; // Enables debug mode for parsing
    extern int yylineno; // Keeps track of the line number in the source file
    void yyerror (const char *msg); // Error handling function for the parser
    int yylex(void); // Function prototype for the lexer
    int var_get(char *id); // Function prototype to retrieve variable values
    int var_set(char *id, int val); // Function prototype to set variable values
    ast_type *root = NULL; // Root of the abstract syntax tree (AST)
    extern FILE *yyin; // File pointer for input
    node_s *head = NULL; // Pointer to the top of the stack

// Function to create a node with no children
ast_type *node0(int type){
 	ast_type *t = calloc(1, sizeof(ast_type)); 
	if ( t == NULL ){
		printf("Error memory allocation!");
		exit(EXIT_FAILURE);
	}
	t -> type = type;
	return t;
} 

// Function to create a node with one child
ast_type *node1(int type, ast_type *child0){
 	ast_type *t = node0(type); 
	t -> type = type;
	t -> child[0] = child0;  
	return t;
} 

// Function to create a node with two children
ast_type *node2(int type, ast_type *child0, ast_type *child1){
	ast_type *t = node0(type);
	t -> type = type;
	t -> child[0] = child0;
	t -> child[1] = child1;
	return t;
}

// Function to create a node with three children
ast_type *node3(int type, ast_type *child0, ast_type *child1, ast_type *child2){
	ast_type *t = node0(type);                                                        
        t -> type = type;                                                                 
        t -> child[0] = child0;                                                           
        t -> child[1] = child1;
	t -> child[2] = child2;							   
        return t;    
}

// Function to create a node with four children
ast_type *node4(int type, ast_type *child0, ast_type *child1, ast_type *child2, ast_type *child3){
        ast_type *t = node0(type);
        t -> type = type;
        t -> child[0] = child0;
        t -> child[1] = child1;
        t -> child[2] = child2;
	t -> child[3] = child3; 
        return t;
}

// Global scope pointer, used to track the current scope in the program
Scope *global_scope = NULL;


#line 143 "parser.tab.c"

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

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_T_WHOLEY = 3,                   /* T_WHOLEY  */
  YYSYMBOL_T_FLOATY = 4,                   /* T_FLOATY  */
  YYSYMBOL_T_IDENTIFIER = 5,               /* T_IDENTIFIER  */
  YYSYMBOL_T_STRING = 6,                   /* T_STRING  */
  YYSYMBOL_T_PLUS = 7,                     /* T_PLUS  */
  YYSYMBOL_T_MINUS = 8,                    /* T_MINUS  */
  YYSYMBOL_T_MULTIPLY = 9,                 /* T_MULTIPLY  */
  YYSYMBOL_T_DIVIDE = 10,                  /* T_DIVIDE  */
  YYSYMBOL_T_LESS = 11,                    /* T_LESS  */
  YYSYMBOL_T_GREATER = 12,                 /* T_GREATER  */
  YYSYMBOL_T_GEQUAL = 13,                  /* T_GEQUAL  */
  YYSYMBOL_T_LEQUAL = 14,                  /* T_LEQUAL  */
  YYSYMBOL_T_SENDBACK = 15,                /* T_SENDBACK  */
  YYSYMBOL_T_THROWUP = 16,                 /* T_THROWUP  */
  YYSYMBOL_T_GO = 17,                      /* T_GO  */
  YYSYMBOL_T_ALL_SET = 18,                 /* T_ALL_SET  */
  YYSYMBOL_T_IMAGINE = 19,                 /* T_IMAGINE  */
  YYSYMBOL_T_NAH = 20,                     /* T_NAH  */
  YYSYMBOL_T_ONE_BY_ONE = 21,              /* T_ONE_BY_ONE  */
  YYSYMBOL_T_AS_LONG_AS = 22,              /* T_AS_LONG_AS  */
  YYSYMBOL_T_IN = 23,                      /* T_IN  */
  YYSYMBOL_T_LPAREN = 24,                  /* T_LPAREN  */
  YYSYMBOL_T_RPAREN = 25,                  /* T_RPAREN  */
  YYSYMBOL_T_LCURPAR = 26,                 /* T_LCURPAR  */
  YYSYMBOL_T_RCURPAR = 27,                 /* T_RCURPAR  */
  YYSYMBOL_T_A_NEW_ONE = 28,               /* T_A_NEW_ONE  */
  YYSYMBOL_T_ZIP_TYPE = 29,                /* T_ZIP_TYPE  */
  YYSYMBOL_T_COMMA = 30,                   /* T_COMMA  */
  YYSYMBOL_T_WHOLEY_TYPE = 31,             /* T_WHOLEY_TYPE  */
  YYSYMBOL_T_FLOATY_TYPE = 32,             /* T_FLOATY_TYPE  */
  YYSYMBOL_T_STRING_TYPE = 33,             /* T_STRING_TYPE  */
  YYSYMBOL_T_EQUAL = 34,                   /* T_EQUAL  */
  YYSYMBOL_T_RANDO = 35,                   /* T_RANDO  */
  YYSYMBOL_T_GIMME = 36,                   /* T_GIMME  */
  YYSYMBOL_T_SIZE_UP = 37,                 /* T_SIZE_UP  */
  YYSYMBOL_T_JOIN_IN = 38,                 /* T_JOIN_IN  */
  YYSYMBOL_T_FAI = 39,                     /* T_FAI  */
  YYSYMBOL_T_NEQUAL = 40,                  /* T_NEQUAL  */
  YYSYMBOL_T_OR = 41,                      /* T_OR  */
  YYSYMBOL_T_AND = 42,                     /* T_AND  */
  YYSYMBOL_43_ = 43,                       /* '['  */
  YYSYMBOL_44_ = 44,                       /* ';'  */
  YYSYMBOL_45_ = 45,                       /* ']'  */
  YYSYMBOL_YYACCEPT = 46,                  /* $accept  */
  YYSYMBOL_START = 47,                     /* START  */
  YYSYMBOL_global_declaration = 48,        /* global_declaration  */
  YYSYMBOL_block = 49,                     /* block  */
  YYSYMBOL_control_blocks = 50,            /* control_blocks  */
  YYSYMBOL_control_block = 51,             /* control_block  */
  YYSYMBOL_if_block = 52,                  /* if_block  */
  YYSYMBOL_while_block = 53,               /* while_block  */
  YYSYMBOL_for_block = 54,                 /* for_block  */
  YYSYMBOL_step = 55,                      /* step  */
  YYSYMBOL_statements = 56,                /* statements  */
  YYSYMBOL_statement = 57,                 /* statement  */
  YYSYMBOL_declaration = 58,               /* declaration  */
  YYSYMBOL_assignment = 59,                /* assignment  */
  YYSYMBOL_types = 60,                     /* types  */
  YYSYMBOL_expression = 61,                /* expression  */
  YYSYMBOL_function_def = 62,              /* function_def  */
  YYSYMBOL_function_call = 63,             /* function_call  */
  YYSYMBOL_param_list = 64,                /* param_list  */
  YYSYMBOL_arg_list = 65                   /* arg_list  */
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

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
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
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
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
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
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
#define YYFINAL  51
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   623

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  46
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  20
/* YYNRULES -- Number of rules.  */
#define YYNRULES  66
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  164

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   297


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
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    44,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    43,     2,    45,     2,     2,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40,    41,    42
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,   105,   105,   106,   110,   111,   115,   119,   120,   123,
     124,   125,   129,   133,   140,   147,   155,   158,   159,   163,
     164,   165,   166,   167,   168,   172,   173,   177,   178,   182,
     183,   184,   185,   186,   187,   188,   192,   193,   194,   195,
     196,   197,   198,   199,   200,   201,   202,   203,   204,   205,
     206,   207,   208,   209,   210,   211,   212,   213,   214,   218,
     225,   228,   229,   230,   233,   234,   235
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
  "\"end of file\"", "error", "\"invalid token\"", "T_WHOLEY", "T_FLOATY",
  "T_IDENTIFIER", "T_STRING", "T_PLUS", "T_MINUS", "T_MULTIPLY",
  "T_DIVIDE", "T_LESS", "T_GREATER", "T_GEQUAL", "T_LEQUAL", "T_SENDBACK",
  "T_THROWUP", "T_GO", "T_ALL_SET", "T_IMAGINE", "T_NAH", "T_ONE_BY_ONE",
  "T_AS_LONG_AS", "T_IN", "T_LPAREN", "T_RPAREN", "T_LCURPAR", "T_RCURPAR",
  "T_A_NEW_ONE", "T_ZIP_TYPE", "T_COMMA", "T_WHOLEY_TYPE", "T_FLOATY_TYPE",
  "T_STRING_TYPE", "T_EQUAL", "T_RANDO", "T_GIMME", "T_SIZE_UP",
  "T_JOIN_IN", "T_FAI", "T_NEQUAL", "T_OR", "T_AND", "'['", "';'", "']'",
  "$accept", "START", "global_declaration", "block", "control_blocks",
  "control_block", "if_block", "while_block", "for_block", "step",
  "statements", "statement", "declaration", "assignment", "types",
  "expression", "function_def", "function_call", "param_list", "arg_list", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-23)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     177,   -23,   -23,    57,   -23,    11,   -11,   131,    11,    84,
     -23,   -22,   -16,   -13,    13,    18,    20,    26,   141,   -23,
     -23,   -10,   -23,   -23,    63,   581,   -23,   -23,    11,    11,
      11,   -21,   581,    11,    46,    58,    60,   166,   -23,   -23,
     -23,   -23,    -2,    75,    90,    91,    92,    11,    84,    11,
      97,   -23,   -23,   -23,    64,    11,    11,    11,    11,    11,
      11,    11,    11,    11,    11,    11,    11,   581,     3,   581,
      65,    11,   425,    11,    99,    11,   -23,   -23,   -23,    85,
      76,    77,    79,   121,   102,   435,   107,    11,    10,    10,
     -23,   -23,   581,   581,   581,   581,   581,   581,    56,   188,
     -23,    11,   100,    78,   -23,   471,   115,   481,    84,   -23,
     -23,   -23,    11,   -23,   -23,    11,   581,   581,    11,   -23,
     116,   124,   140,   162,     6,   517,   527,   581,   393,    11,
     393,   -23,   142,    84,   -23,   -23,   213,   127,   161,   536,
     249,   393,   184,   179,   156,   -23,   178,    11,   -23,   285,
     -23,   176,   -23,   181,   572,   -23,   393,   393,    11,   321,
     357,   581,   -23,   -23
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    36,    37,    39,    38,     0,     0,     0,     0,     0,
      32,    29,    30,    31,     0,     0,     0,     0,     0,     2,
      22,     0,    19,    20,     0,    21,     4,    40,    66,     0,
       0,    39,    23,     0,     0,     0,     0,     0,     7,     9,
      10,    11,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     1,     3,     5,    25,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    64,     0,    27,
       0,     0,     0,     0,     0,     0,     6,     8,    51,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    44,    45,
      47,    46,    48,    49,    42,    43,    50,    41,    55,    54,
      60,     0,    52,     0,    24,     0,     0,     0,    63,    33,
      34,    35,     0,    56,    53,     0,    26,    65,     0,    52,
       0,     0,     0,     0,     0,     0,     0,    28,     0,     0,
       0,    61,     0,     0,    57,    58,     0,     0,     0,     0,
       0,     0,     0,    12,     0,    18,     0,     0,    14,     0,
      62,     0,    17,     0,     0,    59,     0,     0,     0,     0,
       0,    16,    13,    15
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -23,   -23,   186,   -23,   -23,   174,   -23,   -23,   -23,   -23,
      34,     0,   -23,   -23,    -7,    -4,   -23,   -23,   -23,   -23
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,    18,    19,    20,    37,    38,    39,    40,    41,   138,
     136,   137,    22,    23,    24,    25,    26,    27,   124,    68
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      21,    32,    43,    28,    42,    55,    56,    57,    58,    59,
      60,    61,    62,    33,     1,     2,    31,     4,    21,    57,
      58,    44,    71,    78,    67,    69,    70,    45,   100,    72,
      46,   132,    63,   101,    53,     8,   133,    47,    64,    65,
      66,    84,    48,    83,    49,    85,    14,    15,    16,    17,
      50,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,    55,    56,    57,    58,   103,    54,   105,
      73,   107,    55,    56,    57,    58,    59,    60,    61,    62,
      79,    28,    74,   116,    75,    55,    56,    57,    58,    59,
      60,    61,    62,    80,    81,    82,    29,   117,    66,    63,
      30,   123,    86,    87,   106,    64,    65,    66,   125,   108,
     102,   126,    63,    10,   127,    11,    12,    13,    64,    65,
      66,   109,   110,   119,   111,   139,   142,   113,    55,    56,
      57,    58,    59,    60,    61,    62,   144,   115,   121,   118,
     144,    51,   128,   154,     1,     2,     3,     4,   129,   144,
      34,   112,    35,    36,   161,    63,     5,     6,     7,   144,
     144,    64,    65,    66,   140,     8,   130,   131,   141,     9,
      10,   145,    11,    12,    13,   149,    14,    15,    16,    17,
       1,     2,     3,     4,    76,    34,   146,    35,    36,   150,
     159,   160,     5,     6,     7,    55,    56,    57,    58,   151,
     152,     8,   156,   153,    52,     9,    10,   157,    11,    12,
      13,    77,    14,    15,    16,    17,     1,     2,     3,     4,
       0,     0,     0,     0,     0,     0,     0,     0,     5,     6,
       7,     0,     0,     0,     0,     0,     0,     8,     0,     0,
     143,     0,    10,     0,    11,    12,    13,     0,    14,    15,
      16,    17,     1,     2,     3,     4,     0,     0,     0,     0,
       0,     0,     0,     0,     5,     6,     7,     0,     0,     0,
       0,     0,     0,     8,     0,     0,   148,     0,    10,     0,
      11,    12,    13,     0,    14,    15,    16,    17,     1,     2,
       3,     4,     0,     0,     0,     0,     0,     0,     0,     0,
       5,     6,     7,     0,     0,     0,     0,     0,     0,     8,
       0,     0,   155,     0,    10,     0,    11,    12,    13,     0,
      14,    15,    16,    17,     1,     2,     3,     4,     0,     0,
       0,     0,     0,     0,     0,     0,     5,     6,     7,     0,
       0,     0,     0,     0,     0,     8,     0,     0,   162,     0,
      10,     0,    11,    12,    13,     0,    14,    15,    16,    17,
       1,     2,     3,     4,     0,     0,     0,     0,     0,     0,
       0,     0,     5,     6,     7,     0,     0,     0,     0,     0,
       0,     8,     0,     0,   163,     0,    10,     0,    11,    12,
      13,     0,    14,    15,    16,    17,     1,     2,     3,     4,
       0,     0,     0,     0,     0,     0,     0,     0,     5,     6,
       7,     0,     0,     0,     0,     0,     0,     8,     0,     0,
       0,     0,    10,     0,    11,    12,    13,     0,    14,    15,
      16,    17,    55,    56,    57,    58,    59,    60,    61,    62,
       0,     0,    55,    56,    57,    58,    59,    60,    61,    62,
     104,     0,     0,     0,     0,     0,     0,     0,     0,    63,
     114,     0,     0,     0,     0,    64,    65,    66,     0,    63,
       0,     0,     0,     0,     0,    64,    65,    66,    55,    56,
      57,    58,    59,    60,    61,    62,     0,     0,    55,    56,
      57,    58,    59,    60,    61,    62,   120,     0,     0,     0,
       0,     0,     0,     0,     0,    63,   122,     0,     0,     0,
       0,    64,    65,    66,     0,    63,     0,     0,     0,     0,
       0,    64,    65,    66,    55,    56,    57,    58,    59,    60,
      61,    62,     0,     0,    55,    56,    57,    58,    59,    60,
      61,    62,   134,    55,    56,    57,    58,    59,    60,    61,
      62,    63,   135,     0,     0,     0,     0,    64,    65,    66,
       0,    63,     0,     0,     0,     0,   147,    64,    65,    66,
      63,     0,     0,     0,     0,     0,    64,    65,    66,    55,
      56,    57,    58,    59,    60,    61,    62,     0,    55,    56,
      57,    58,    59,    60,    61,    62,     0,     0,     0,     0,
       0,     0,   158,     0,     0,     0,    63,     0,     0,     0,
       0,     0,    64,    65,    66,    63,     0,     0,     0,     0,
       0,    64,    65,    66
};

static const yytype_int16 yycheck[] =
{
       0,     5,     9,    24,     8,     7,     8,     9,    10,    11,
      12,    13,    14,    24,     3,     4,     5,     6,    18,     9,
      10,    43,    43,    25,    28,    29,    30,    43,    25,    33,
      43,    25,    34,    30,    44,    24,    30,    24,    40,    41,
      42,    48,    24,    47,    24,    49,    35,    36,    37,    38,
      24,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,     7,     8,     9,    10,    71,     5,    73,
      24,    75,     7,     8,     9,    10,    11,    12,    13,    14,
       5,    24,    24,    87,    24,     7,     8,     9,    10,    11,
      12,    13,    14,     3,     3,     3,    39,   101,    42,    34,
      43,   108,     5,    39,     5,    40,    41,    42,   112,    24,
      45,   115,    34,    29,   118,    31,    32,    33,    40,    41,
      42,    45,    45,    45,    45,   129,   133,    25,     7,     8,
       9,    10,    11,    12,    13,    14,   136,    30,    23,    39,
     140,     0,    26,   147,     3,     4,     5,     6,    24,   149,
      19,    30,    21,    22,   158,    34,    15,    16,    17,   159,
     160,    40,    41,    42,   130,    24,    26,     5,    26,    28,
      29,    44,    31,    32,    33,   141,    35,    36,    37,    38,
       3,     4,     5,     6,    18,    19,    25,    21,    22,     5,
     156,   157,    15,    16,    17,     7,     8,     9,    10,    20,
      44,    24,    26,    25,    18,    28,    29,    26,    31,    32,
      33,    37,    35,    36,    37,    38,     3,     4,     5,     6,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    15,    16,
      17,    -1,    -1,    -1,    -1,    -1,    -1,    24,    -1,    -1,
      27,    -1,    29,    -1,    31,    32,    33,    -1,    35,    36,
      37,    38,     3,     4,     5,     6,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    15,    16,    17,    -1,    -1,    -1,
      -1,    -1,    -1,    24,    -1,    -1,    27,    -1,    29,    -1,
      31,    32,    33,    -1,    35,    36,    37,    38,     3,     4,
       5,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      15,    16,    17,    -1,    -1,    -1,    -1,    -1,    -1,    24,
      -1,    -1,    27,    -1,    29,    -1,    31,    32,    33,    -1,
      35,    36,    37,    38,     3,     4,     5,     6,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    15,    16,    17,    -1,
      -1,    -1,    -1,    -1,    -1,    24,    -1,    -1,    27,    -1,
      29,    -1,    31,    32,    33,    -1,    35,    36,    37,    38,
       3,     4,     5,     6,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    15,    16,    17,    -1,    -1,    -1,    -1,    -1,
      -1,    24,    -1,    -1,    27,    -1,    29,    -1,    31,    32,
      33,    -1,    35,    36,    37,    38,     3,     4,     5,     6,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    15,    16,
      17,    -1,    -1,    -1,    -1,    -1,    -1,    24,    -1,    -1,
      -1,    -1,    29,    -1,    31,    32,    33,    -1,    35,    36,
      37,    38,     7,     8,     9,    10,    11,    12,    13,    14,
      -1,    -1,     7,     8,     9,    10,    11,    12,    13,    14,
      25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    34,
      25,    -1,    -1,    -1,    -1,    40,    41,    42,    -1,    34,
      -1,    -1,    -1,    -1,    -1,    40,    41,    42,     7,     8,
       9,    10,    11,    12,    13,    14,    -1,    -1,     7,     8,
       9,    10,    11,    12,    13,    14,    25,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    34,    25,    -1,    -1,    -1,
      -1,    40,    41,    42,    -1,    34,    -1,    -1,    -1,    -1,
      -1,    40,    41,    42,     7,     8,     9,    10,    11,    12,
      13,    14,    -1,    -1,     7,     8,     9,    10,    11,    12,
      13,    14,    25,     7,     8,     9,    10,    11,    12,    13,
      14,    34,    25,    -1,    -1,    -1,    -1,    40,    41,    42,
      -1,    34,    -1,    -1,    -1,    -1,    30,    40,    41,    42,
      34,    -1,    -1,    -1,    -1,    -1,    40,    41,    42,     7,
       8,     9,    10,    11,    12,    13,    14,    -1,     7,     8,
       9,    10,    11,    12,    13,    14,    -1,    -1,    -1,    -1,
      -1,    -1,    30,    -1,    -1,    -1,    34,    -1,    -1,    -1,
      -1,    -1,    40,    41,    42,    34,    -1,    -1,    -1,    -1,
      -1,    40,    41,    42
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,     6,    15,    16,    17,    24,    28,
      29,    31,    32,    33,    35,    36,    37,    38,    47,    48,
      49,    57,    58,    59,    60,    61,    62,    63,    24,    39,
      43,     5,    61,    24,    19,    21,    22,    50,    51,    52,
      53,    54,    61,    60,    43,    43,    43,    24,    24,    24,
      24,     0,    48,    44,     5,     7,     8,     9,    10,    11,
      12,    13,    14,    34,    40,    41,    42,    61,    65,    61,
      61,    43,    61,    24,    24,    24,    18,    51,    25,     5,
       3,     3,     3,    61,    60,    61,     5,    39,    61,    61,
      61,    61,    61,    61,    61,    61,    61,    61,    61,    61,
      25,    30,    45,    61,    25,    61,     5,    61,    24,    45,
      45,    45,    30,    25,    25,    30,    61,    61,    39,    45,
      25,    23,    25,    60,    64,    61,    61,    61,    26,    24,
      26,     5,    25,    30,    25,    25,    56,    57,    55,    61,
      56,    26,    60,    27,    57,    44,    25,    30,    27,    56,
       5,    20,    44,    25,    61,    27,    26,    26,    30,    56,
      56,    61,    27,    27
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    46,    47,    47,    48,    48,    49,    50,    50,    51,
      51,    51,    52,    52,    53,    54,    55,    56,    56,    57,
      57,    57,    57,    57,    57,    58,    58,    59,    59,    60,
      60,    60,    60,    60,    60,    60,    61,    61,    61,    61,
      61,    61,    61,    61,    61,    61,    61,    61,    61,    61,
      61,    61,    61,    61,    61,    61,    61,    61,    61,    62,
      63,    64,    64,    64,    65,    65,    65
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     2,     3,     1,     2,     1,
       1,     1,     7,    11,     7,    11,     5,     3,     2,     1,
       1,     1,     1,     2,     4,     2,     4,     3,     6,     1,
       1,     1,     1,     4,     4,     4,     1,     1,     1,     1,
       1,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     4,     4,     3,     3,     4,     6,     6,     9,
       4,     2,     4,     0,     1,     3,     0
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
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
                       &yyvsp[(yyi + 1) - (yynrhs)]);
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
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
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

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

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
    YYNOMEM;
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

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* START: global_declaration  */
#line 105 "parser.y"
                        { root = node1(_START, (yyvsp[0].ast)); }
#line 1657 "parser.tab.c"
    break;

  case 3: /* START: START global_declaration  */
#line 106 "parser.y"
                               { root = node2(_START, root, (yyvsp[0].ast)); }
#line 1663 "parser.tab.c"
    break;

  case 4: /* global_declaration: function_def  */
#line 110 "parser.y"
                 { (yyval.ast) = (yyvsp[0].ast); }
#line 1669 "parser.tab.c"
    break;

  case 5: /* global_declaration: statement ';'  */
#line 111 "parser.y"
                    { (yyval.ast) = (yyvsp[-1].ast); }
#line 1675 "parser.tab.c"
    break;

  case 6: /* block: T_GO control_blocks T_ALL_SET  */
#line 115 "parser.y"
                                   { (yyval.ast) = (yyvsp[-1].ast); }
#line 1681 "parser.tab.c"
    break;

  case 7: /* control_blocks: control_block  */
#line 119 "parser.y"
                      { (yyval.ast) = node1(_CONTROLBLOCK, (yyvsp[0].ast)); }
#line 1687 "parser.tab.c"
    break;

  case 8: /* control_blocks: control_blocks control_block  */
#line 120 "parser.y"
                                       { (yyval.ast) = node2(_CONTROLBLOCK, (yyvsp[-1].ast), (yyvsp[0].ast)); }
#line 1693 "parser.tab.c"
    break;

  case 9: /* control_block: if_block  */
#line 123 "parser.y"
                      { (yyval.ast) = (yyvsp[0].ast); }
#line 1699 "parser.tab.c"
    break;

  case 10: /* control_block: while_block  */
#line 124 "parser.y"
                  { (yyval.ast) = (yyvsp[0].ast); }
#line 1705 "parser.tab.c"
    break;

  case 11: /* control_block: for_block  */
#line 125 "parser.y"
                { (yyval.ast) = (yyvsp[0].ast); }
#line 1711 "parser.tab.c"
    break;

  case 12: /* if_block: T_IMAGINE T_LPAREN expression T_RPAREN T_LCURPAR statements T_RCURPAR  */
#line 130 "parser.y"
        {
		(yyval.ast) = node3(_IF, (yyvsp[-4].ast), (yyvsp[-1].ast), NULL);
	}
#line 1719 "parser.tab.c"
    break;

  case 13: /* if_block: T_IMAGINE T_LPAREN expression T_RPAREN T_LCURPAR statements T_RCURPAR T_NAH T_LCURPAR statements T_RCURPAR  */
#line 134 "parser.y"
        { 
		(yyval.ast) = node3(_IF, (yyvsp[-8].ast), (yyvsp[-5].ast), (yyvsp[-1].ast));
	}
#line 1727 "parser.tab.c"
    break;

  case 14: /* while_block: T_AS_LONG_AS T_LPAREN expression T_RPAREN T_LCURPAR statements T_RCURPAR  */
#line 141 "parser.y"
           { 
		(yyval.ast) = node2(_WHILE, (yyvsp[-4].ast), (yyvsp[-1].ast));
	   }
#line 1735 "parser.tab.c"
    break;

  case 15: /* for_block: T_ONE_BY_ONE T_LPAREN T_IDENTIFIER T_IN T_LPAREN step T_RPAREN T_RPAREN T_LCURPAR statements T_RCURPAR  */
#line 148 "parser.y"
        { 
		(yyval.ast) = node3(_FOR, node0(_IDENTIFIER), (yyvsp[-5].ast), (yyvsp[-1].ast));
		(yyval.ast)->child[0]->val.s = (yyvsp[-8].id);
	}
#line 1744 "parser.tab.c"
    break;

  case 16: /* step: expression T_COMMA expression T_COMMA expression  */
#line 155 "parser.y"
                                                         { (yyval.ast) = node3(_OPTSTEP, (yyvsp[-4].ast), (yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 1750 "parser.tab.c"
    break;

  case 17: /* statements: statements statement ';'  */
#line 158 "parser.y"
                                 { (yyval.ast) = node2(_STATEMENTS, (yyvsp[-2].ast), (yyvsp[-1].ast)); }
#line 1756 "parser.tab.c"
    break;

  case 18: /* statements: statement ';'  */
#line 159 "parser.y"
                        { (yyval.ast) = (yyvsp[-1].ast);}
#line 1762 "parser.tab.c"
    break;

  case 19: /* statement: declaration  */
#line 163 "parser.y"
                { (yyval.ast) = (yyvsp[0].ast); }
#line 1768 "parser.tab.c"
    break;

  case 20: /* statement: assignment  */
#line 164 "parser.y"
                 { (yyval.ast) = (yyvsp[0].ast); }
#line 1774 "parser.tab.c"
    break;

  case 21: /* statement: expression  */
#line 165 "parser.y"
                 { (yyval.ast) = (yyvsp[0].ast); }
#line 1780 "parser.tab.c"
    break;

  case 22: /* statement: block  */
#line 166 "parser.y"
                { (yyval.ast) = (yyvsp[0].ast); }
#line 1786 "parser.tab.c"
    break;

  case 23: /* statement: T_SENDBACK expression  */
#line 167 "parser.y"
                                { (yyval.ast) = node1(_RETURN, (yyvsp[0].ast)); }
#line 1792 "parser.tab.c"
    break;

  case 24: /* statement: T_THROWUP T_LPAREN expression T_RPAREN  */
#line 168 "parser.y"
                                             { (yyval.ast) = node1(_PRINT, (yyvsp[-1].ast));  }
#line 1798 "parser.tab.c"
    break;

  case 25: /* declaration: types T_IDENTIFIER  */
#line 172 "parser.y"
                                { (yyval.ast) = node2(_DECLARATION, (yyvsp[-1].ast), node0(_IDENTIFIER)); (yyval.ast)->child[1]->val.s = (yyvsp[0].id); }
#line 1804 "parser.tab.c"
    break;

  case 26: /* declaration: types T_IDENTIFIER T_FAI expression  */
#line 173 "parser.y"
                                                  { (yyval.ast) = node3(_DECLARATION, (yyvsp[-3].ast), node0(_IDENTIFIER), (yyvsp[0].ast)); (yyval.ast)->child[1]->val.s = (yyvsp[-2].id); }
#line 1810 "parser.tab.c"
    break;

  case 27: /* assignment: T_IDENTIFIER T_FAI expression  */
#line 177 "parser.y"
                                    { (yyval.ast) = node2(_ASSIGNMENT, node0(_IDENTIFIER), (yyvsp[0].ast)); (yyval.ast)->child[0]->val.s = (yyvsp[-2].id); }
#line 1816 "parser.tab.c"
    break;

  case 28: /* assignment: T_IDENTIFIER '[' expression ']' T_FAI expression  */
#line 178 "parser.y"
                                                         { (yyval.ast) = node3(_LIST_ASSIGNMENT, node0(_IDENTIFIER), (yyvsp[-3].ast), (yyvsp[0].ast)); (yyval.ast)->child[0]->val.s = (yyvsp[-5].id); }
#line 1822 "parser.tab.c"
    break;

  case 29: /* types: T_WHOLEY_TYPE  */
#line 182 "parser.y"
                        { (yyval.ast) = node0(_INT_TYPE); }
#line 1828 "parser.tab.c"
    break;

  case 30: /* types: T_FLOATY_TYPE  */
#line 183 "parser.y"
                        { (yyval.ast) = node0(_DOUBLE_TYPE); }
#line 1834 "parser.tab.c"
    break;

  case 31: /* types: T_STRING_TYPE  */
#line 184 "parser.y"
                        { (yyval.ast) = node0(_STRING_TYPE); }
#line 1840 "parser.tab.c"
    break;

  case 32: /* types: T_ZIP_TYPE  */
#line 185 "parser.y"
                        { (yyval.ast) = node0(_VOID_TYPE); }
#line 1846 "parser.tab.c"
    break;

  case 33: /* types: T_WHOLEY_TYPE '[' T_WHOLEY ']'  */
#line 186 "parser.y"
                                      { (yyval.ast) = node2(_LIST_TYPE, node0(_INT_TYPE), node0(_INT)); (yyval.ast)->child[1]->val.i = (yyvsp[-1].num); }
#line 1852 "parser.tab.c"
    break;

  case 34: /* types: T_FLOATY_TYPE '[' T_WHOLEY ']'  */
#line 187 "parser.y"
                                      { (yyval.ast) = node2(_LIST_TYPE, node0(_DOUBLE_TYPE), node0(_INT)); (yyval.ast)->child[1]->val.i = (yyvsp[-1].num); }
#line 1858 "parser.tab.c"
    break;

  case 35: /* types: T_STRING_TYPE '[' T_WHOLEY ']'  */
#line 188 "parser.y"
                                      { (yyval.ast) = node2(_LIST_TYPE, node0(_STRING_TYPE), node0(_INT)); (yyval.ast)->child[1]->val.i = (yyvsp[-1].num); }
#line 1864 "parser.tab.c"
    break;

  case 36: /* expression: T_WHOLEY  */
#line 192 "parser.y"
                        { (yyval.ast) = node0(_INT); (yyval.ast)->val.i = (yyvsp[0].num);  }
#line 1870 "parser.tab.c"
    break;

  case 37: /* expression: T_FLOATY  */
#line 193 "parser.y"
                        { (yyval.ast) = node0(_DOUBLE); (yyval.ast)->val.d = (yyvsp[0].fnum); }
#line 1876 "parser.tab.c"
    break;

  case 38: /* expression: T_STRING  */
#line 194 "parser.y"
                        { (yyval.ast) = node0(_STRING); (yyval.ast)->val.s = (yyvsp[0].str); }
#line 1882 "parser.tab.c"
    break;

  case 39: /* expression: T_IDENTIFIER  */
#line 195 "parser.y"
                        { (yyval.ast) = node0(_IDENTIFIER); (yyval.ast)->val.s = (yyvsp[0].id); }
#line 1888 "parser.tab.c"
    break;

  case 40: /* expression: function_call  */
#line 196 "parser.y"
                    { (yyval.ast) = (yyvsp[0].ast); }
#line 1894 "parser.tab.c"
    break;

  case 41: /* expression: expression T_NEQUAL expression  */
#line 197 "parser.y"
                                     { (yyval.ast) = node2(_NEQUAL, (yyvsp[-2].ast), (yyvsp[0].ast));  }
#line 1900 "parser.tab.c"
    break;

  case 42: /* expression: expression T_GEQUAL expression  */
#line 198 "parser.y"
                                     { (yyval.ast) = node2(_GEQUAL, (yyvsp[-2].ast), (yyvsp[0].ast));  }
#line 1906 "parser.tab.c"
    break;

  case 43: /* expression: expression T_LEQUAL expression  */
#line 199 "parser.y"
                                     { (yyval.ast) = node2(_LEQUAL, (yyvsp[-2].ast), (yyvsp[0].ast));  }
#line 1912 "parser.tab.c"
    break;

  case 44: /* expression: expression T_PLUS expression  */
#line 200 "parser.y"
                                   { (yyval.ast) = node2(_PLUS, (yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 1918 "parser.tab.c"
    break;

  case 45: /* expression: expression T_MINUS expression  */
#line 201 "parser.y"
                                    { (yyval.ast) = node2(_MINUS, (yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 1924 "parser.tab.c"
    break;

  case 46: /* expression: expression T_DIVIDE expression  */
#line 202 "parser.y"
                                     { (yyval.ast) = node2(_DIVIDE, (yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 1930 "parser.tab.c"
    break;

  case 47: /* expression: expression T_MULTIPLY expression  */
#line 203 "parser.y"
                                       { (yyval.ast) = node2(_MULTIPLY, (yyvsp[-2].ast), (yyvsp[0].ast));}
#line 1936 "parser.tab.c"
    break;

  case 48: /* expression: expression T_LESS expression  */
#line 204 "parser.y"
                                   { (yyval.ast) = node2(_LESS, (yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 1942 "parser.tab.c"
    break;

  case 49: /* expression: expression T_GREATER expression  */
#line 205 "parser.y"
                                      { (yyval.ast) = node2(_GREATER, (yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 1948 "parser.tab.c"
    break;

  case 50: /* expression: expression T_EQUAL expression  */
#line 206 "parser.y"
                                    { (yyval.ast) = node2(_EQUAL, (yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 1954 "parser.tab.c"
    break;

  case 51: /* expression: T_LPAREN expression T_RPAREN  */
#line 207 "parser.y"
                                    { (yyval.ast) = node1(_PARENSTMT, (yyvsp[-1].ast)); }
#line 1960 "parser.tab.c"
    break;

  case 52: /* expression: T_IDENTIFIER '[' expression ']'  */
#line 208 "parser.y"
                                      { (yyval.ast) = node2(_INDEX_ACCESS, node0(_IDENTIFIER), (yyvsp[-1].ast)); (yyval.ast)->child[0]->val.s = (yyvsp[-3].id); }
#line 1966 "parser.tab.c"
    break;

  case 53: /* expression: T_SIZE_UP T_LPAREN expression T_RPAREN  */
#line 209 "parser.y"
                                             { (yyval.ast) = node1(_SIZE_UP, (yyvsp[-1].ast)); }
#line 1972 "parser.tab.c"
    break;

  case 54: /* expression: expression T_AND expression  */
#line 210 "parser.y"
                                  { (yyval.ast) = node2(_AND, (yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 1978 "parser.tab.c"
    break;

  case 55: /* expression: expression T_OR expression  */
#line 211 "parser.y"
                                 { (yyval.ast) = node2(_OR, (yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 1984 "parser.tab.c"
    break;

  case 56: /* expression: T_GIMME T_LPAREN types T_RPAREN  */
#line 212 "parser.y"
                                      { (yyval.ast) = node1(_GIMME, (yyvsp[-1].ast)); }
#line 1990 "parser.tab.c"
    break;

  case 57: /* expression: T_RANDO T_LPAREN expression T_COMMA expression T_RPAREN  */
#line 213 "parser.y"
                                                              { (yyval.ast) = node2(_RANDO, (yyvsp[-3].ast), (yyvsp[-1].ast)); }
#line 1996 "parser.tab.c"
    break;

  case 58: /* expression: T_JOIN_IN T_LPAREN T_IDENTIFIER T_COMMA expression T_RPAREN  */
#line 214 "parser.y"
                                                                  { (yyval.ast) = node2(_JOIN_IN, node0(_IDENTIFIER), (yyvsp[-1].ast)), (yyval.ast)->child[0]->val.s = (yyvsp[-3].id); }
#line 2002 "parser.tab.c"
    break;

  case 59: /* function_def: T_A_NEW_ONE types T_IDENTIFIER T_LPAREN param_list T_RPAREN T_LCURPAR statements T_RCURPAR  */
#line 219 "parser.y"
        {
		 (yyval.ast) = node4(_NEWFUNC, (yyvsp[-7].ast), node0(_IDENTIFIER), (yyvsp[-4].ast), (yyvsp[-1].ast)); 
		 (yyval.ast)->child[1]->val.s = (yyvsp[-6].id);	
	}
#line 2011 "parser.tab.c"
    break;

  case 60: /* function_call: T_IDENTIFIER T_LPAREN arg_list T_RPAREN  */
#line 225 "parser.y"
                                                        { (yyval.ast) = node2(_FUNCALL, node0(_IDENTIFIER), (yyvsp[-1].ast)); (yyval.ast)->child[0]->val.s = (yyvsp[-3].id); }
#line 2017 "parser.tab.c"
    break;

  case 61: /* param_list: types T_IDENTIFIER  */
#line 228 "parser.y"
                                { (yyval.ast) = node3(_PARAMSLIST, NULL, (yyvsp[-1].ast), node0(_IDENTIFIER)); (yyval.ast)->child[2]->val.s = (yyvsp[0].id); }
#line 2023 "parser.tab.c"
    break;

  case 62: /* param_list: param_list T_COMMA types T_IDENTIFIER  */
#line 229 "parser.y"
                                                        { (yyval.ast) = node3(_PARAMSLIST, (yyvsp[-3].ast), (yyvsp[-1].ast), node0(_IDENTIFIER)); (yyval.ast)->child[2]->val.s = (yyvsp[0].id); }
#line 2029 "parser.tab.c"
    break;

  case 63: /* param_list: %empty  */
#line 230 "parser.y"
                   { (yyval.ast) = NULL; }
#line 2035 "parser.tab.c"
    break;

  case 64: /* arg_list: expression  */
#line 233 "parser.y"
                        { (yyval.ast) = node2(_ARGSLIST, NULL, (yyvsp[0].ast)); }
#line 2041 "parser.tab.c"
    break;

  case 65: /* arg_list: arg_list T_COMMA expression  */
#line 234 "parser.y"
                                      { (yyval.ast) = node2(_ARGSLIST, (yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 2047 "parser.tab.c"
    break;

  case 66: /* arg_list: %empty  */
#line 235 "parser.y"
                        { (yyval.ast) = NULL; }
#line 2053 "parser.tab.c"
    break;


#line 2057 "parser.tab.c"

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
          = {yyssp, yytoken};
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
          YYNOMEM;
      }
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
  ++yynerrs;

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


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
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
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
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

#line 237 "parser.y"


void yyerror(const char *s) {
    fprintf(stderr, "Errore alla riga %d: %s\n", yylineno, s);
}



void print_ast(ast_type *node, int depth) {
    if (!node) return;

    // Stampa l'indentazione
    for (int i = 0; i < depth; i++) {
        if (i == depth - 1)
            printf("|-- ");
        else
            printf("|   ");
    }

    printf("%d", node->type); 
    if (node->type == _INT) {
        printf(": %d", node->val.i);
    } else if (node->type == _DOUBLE) {
        printf(": %f", node->val.d); 
    }else if (node->type == _STRING || node->type == _IDENTIFIER) {
        if (node->val.s) { // Verifica che la stringa non sia NULL
            printf(": ");
            // Processa la stringa per escapare i caratteri speciali
            for (const char *c = node->val.s; *c != '\0'; c++) {
                if (*c == '\n') {
                    printf("\\gms"); // Escapa il newline
                } else if (*c == '\t') {
                    printf("\\so"); // Escapa il tab
                } else if (*c == '\\') {
                    printf("\\\\"); // Escapa il backslash
                } else {
                    putchar(*c); // Stampa normalmente gli altri caratteri
                }
            }
        } else {
            printf(": NULL");    
        }
    }

   printf("\n");

    // Stampa i figli ricorsivamente
    for (int i = 0; i < MAX_CHILD; i++) { // Supponendo massimo 3 figli
        if (node->child[i]) {
            print_ast(node->child[i], depth + 1);
        }
    }
}

value_t executor(ast_type *node, Scope *current_scope) {
    value_t result = {0}; 
    if (!node || current_scope->isReturn) {
        return result;
    }

    switch (node->type) {
	case _START: {
    		for (int i = 0; i < MAX_CHILD; i++) {
        		if (node->child[i]) {
            			executor(node->child[i], current_scope);
        		}
    		}
    		break;
	}
	case _STATEMENTS: {
		if (node->child[0] != NULL) {
        		executor(node->child[0], current_scope);
    		}

    		if (node->child[1] != NULL) {
        		executor(node->child[1], current_scope);
    		}
   	 break;
	}
	case _INT: {
            result.type = 0;
            result.u.i = node->val.i;
            break;
        }
        case _DOUBLE: {
            result.type = 1;
            result.u.d = node->val.d;
            break;
        }
        case _STRING: {
            result.type = 2;
            result.u.s = node->val.s;
            break;
        }

	case _PLUS: { 
		value_t left = executor(node->child[0], current_scope), right = executor(node->child[1], current_scope);
		result = handle_plus(left, right, result);
		break;
	}
	case _MINUS: {
		value_t left = executor(node->child[0], current_scope), right = executor(node->child[1], current_scope);
		result = handle_minus(left, right, result);
		break;
	}
	case _GREATER: { 
	    value_t left = executor(node->child[0], current_scope); 
    	    value_t right = executor(node->child[1], current_scope); 
    	    result = compare_values(left, right, 0, result); 
    	    break;
	}

	case _LESS: {
		value_t left = executor(node->child[0], current_scope);
    		value_t right = executor(node->child[1], current_scope);
    		result = compare_values(left, right, 1, result);
    		break;
	}

	case _GEQUAL: {
		value_t left = executor(node->child[0], current_scope);
    		value_t right = executor(node->child[1], current_scope);
    		result = compare_values(left, right, 2, result);
    		break;
	}

	case _LEQUAL: {
		value_t left = executor(node->child[0], current_scope);
    		value_t right = executor(node->child[1], current_scope);
    		result = compare_values(left, right, 3, result);
    		break;
	}

	case _EQUAL: {
		value_t left = executor(node->child[0], current_scope);
    		value_t right = executor(node->child[1], current_scope);
    		result = compare_values(left, right, 4, result);
    		break;
	}

	case _NEQUAL: {
		value_t left = executor(node->child[0], current_scope);
    		value_t right = executor(node->child[1], current_scope);
    		result = compare_values(left, right, 5, result);
    		break;
	}

	case _AND: {
    		result = handle_and(node, current_scope, result);
		break;
	}

	case _OR: {
    		result = handle_or(node, current_scope, result);
		break;
	}
	case _PARENSTMT:
		result = executor(node->child[0], current_scope);	
		break;
	case _PRINT: {
		result = executor(node->child[0], current_scope);
		handle_print(result);
		break;
	}
	case _DECLARATION: {
    		handle_declaration(node, current_scope);
		break;
	}
	case _ASSIGNMENT: {
    		handle_assignment(node, current_scope);
		break;
	}
	case _IDENTIFIER: {
    		result = handle_identifier(node, current_scope);
		break;
	}
	case _CONTROLBLOCK:
		executor(node->child[0], current_scope);
		break;
	case _IF: {
 		handle_if(node, current_scope);
    		break;
	}
	case _WHILE: {
		handle_while(node, current_scope);
		break;	
	}
	case _FOR: {
		handle_for(node, current_scope);
		break;	
	}
	case _NEWFUNC: {		
		handle_new_function(node, current_scope);
		break;
	}
	
	case _PARAMSLIST: {
		ht_set(current_scope->symbolTable, node->child[2]->val.s, s_pop(&head));	
		executor(node->child[0], current_scope);
		break;
	}
	case _RETURN: {
		current_scope->return_val = executor(node->child[0], current_scope);
		current_scope->isReturn = 1;
		break;
	}
	
	case _FUNCALL: {
 		result = handle_function_call(node, current_scope);
		break;
	}

	case _ARGSLIST: {
		executor(node->child[0], current_scope);
		result = executor(node->child[1], current_scope);
		s_push(&head, result);
		break;	
	}
	case _RANDO: {
    		result = handle_rando(node, current_scope, result);
		break;	
	}
	case _GIMME: {
    		result = handle_gimme(node, result);
		break;
		
	}
	case _INDEX_ACCESS: {
		result = handle_index_access(node, current_scope, result);
		break;
	}

	case _LIST_ASSIGNMENT: {
    		handle_list_assignment(node, current_scope);
		break;
	}

	case _SIZE_UP: {
		result = handle_size_up(node, current_scope, result);
    		break;
	}

	case _JOIN_IN: {
    		handle_join_in(node, current_scope);
		break;
	}


	default: {
		printf("Error type %d\n", node->type);
		exit(EXIT_FAILURE);
	}
		
     }
    
	return result;
}
int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    yyin = file;
    printf("Start parsing file: %s\n", argv[1]);

    yyparse();
    
    if (root) {
	printf("AST: \n");
	print_ast(root,0);
	printf("\n\n\n");	
	optimize_ast(root);
	printf("Optimized AST: \n");
        print_ast(root, 0);
     
        printf("\nExecution of AST:\n");
        
	global_scope = enter_scope(NULL);
	executor(root, global_scope);

        global_scope = exit_scope(global_scope);
     
    }

    // Chiudi il file
    fclose(file);

    return 0;
}

