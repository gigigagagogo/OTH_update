/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    T_WHOLEY = 258,                /* T_WHOLEY  */
    T_FLOATY = 259,                /* T_FLOATY  */
    T_IDENTIFIER = 260,            /* T_IDENTIFIER  */
    T_STRING = 261,                /* T_STRING  */
    T_PLUS = 262,                  /* T_PLUS  */
    T_MINUS = 263,                 /* T_MINUS  */
    T_MULTIPLY = 264,              /* T_MULTIPLY  */
    T_DIVIDE = 265,                /* T_DIVIDE  */
    T_LESS = 266,                  /* T_LESS  */
    T_GREATER = 267,               /* T_GREATER  */
    T_GEQUAL = 268,                /* T_GEQUAL  */
    T_LEQUAL = 269,                /* T_LEQUAL  */
    T_SENDBACK = 270,              /* T_SENDBACK  */
    T_THROWUP = 271,               /* T_THROWUP  */
    T_GO = 272,                    /* T_GO  */
    T_ALL_SET = 273,               /* T_ALL_SET  */
    T_IMAGINE = 274,               /* T_IMAGINE  */
    T_NAH = 275,                   /* T_NAH  */
    T_ONE_BY_ONE = 276,            /* T_ONE_BY_ONE  */
    T_AS_LONG_AS = 277,            /* T_AS_LONG_AS  */
    T_IN = 278,                    /* T_IN  */
    T_LPAREN = 279,                /* T_LPAREN  */
    T_RPAREN = 280,                /* T_RPAREN  */
    T_LCURPAR = 281,               /* T_LCURPAR  */
    T_RCURPAR = 282,               /* T_RCURPAR  */
    T_A_NEW_ONE = 283,             /* T_A_NEW_ONE  */
    T_ZIP_TYPE = 284,              /* T_ZIP_TYPE  */
    T_COMMA = 285,                 /* T_COMMA  */
    T_WHOLEY_TYPE = 286,           /* T_WHOLEY_TYPE  */
    T_FLOATY_TYPE = 287,           /* T_FLOATY_TYPE  */
    T_STRING_TYPE = 288,           /* T_STRING_TYPE  */
    T_EQUAL = 289,                 /* T_EQUAL  */
    T_RANDO = 290,                 /* T_RANDO  */
    T_GIMME = 291,                 /* T_GIMME  */
    T_FAI = 292,                   /* T_FAI  */
    T_NEQUAL = 293                 /* T_NEQUAL  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 70 "parser.y"

    int num;
    double fnum;
    char *str;
    char *id;
    char op;
    value_t val;
    ast_type *ast;

#line 112 "parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
