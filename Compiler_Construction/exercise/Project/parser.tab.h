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
    T_OPERATOR = 261,              /* T_OPERATOR  */
    T_STRING = 262,                /* T_STRING  */
    T_SENDBACK = 263,              /* T_SENDBACK  */
    T_THROWUP = 264,               /* T_THROWUP  */
    T_GO = 265,                    /* T_GO  */
    T_ALL_SET = 266,               /* T_ALL_SET  */
    T_IMAGINE = 267,               /* T_IMAGINE  */
    T_NAH = 268,                   /* T_NAH  */
    T_ONE_BY_ONE = 269,            /* T_ONE_BY_ONE  */
    T_AS_LONG_AS = 270,            /* T_AS_LONG_AS  */
    T_EQUAL = 271,                 /* T_EQUAL  */
    T_NEQUAL = 272,                /* T_NEQUAL  */
    T_GEQUAL = 273,                /* T_GEQUAL  */
    T_LEQUAL = 274,                /* T_LEQUAL  */
    T_IN = 275,                    /* T_IN  */
    T_LPAREN = 276,                /* T_LPAREN  */
    T_RPAREN = 277,                /* T_RPAREN  */
    T_LCURPAR = 278,               /* T_LCURPAR  */
    T_RCURPAR = 279,               /* T_RCURPAR  */
    T_A_NEW_ONE = 280,             /* T_A_NEW_ONE  */
    T_ZIP = 281,                   /* T_ZIP  */
    T_CHECK = 282,                 /* T_CHECK  */
    T_IS = 283,                    /* T_IS  */
    T_COLON = 284,                 /* T_COLON  */
    T_DEFAULT = 285,               /* T_DEFAULT  */
    T_COMMA = 286,                 /* T_COMMA  */
    T_WHOLEY_TYPE = 287,           /* T_WHOLEY_TYPE  */
    T_FLOATY_TYPE = 288,           /* T_FLOATY_TYPE  */
    T_STRING_TYPE = 289            /* T_STRING_TYPE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 24 "parser.y"

    int num;
    double fnum;
    char *str;
    char *id;
    char op;
    value_t val;

#line 107 "parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
