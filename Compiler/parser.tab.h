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
    KEY_INT = 258,                 /* KEY_INT  */
    KEY_MAIN = 259,                /* KEY_MAIN  */
    KEY_RETURN = 260,              /* KEY_RETURN  */
    KEY_CIN = 261,                 /* KEY_CIN  */
    KEY_COUT = 262,                /* KEY_COUT  */
    OP_READ = 263,                 /* OP_READ  */
    OP_WRITE = 264,                /* OP_WRITE  */
    OP_PLUS = 265,                 /* OP_PLUS  */
    OP_MINUS = 266,                /* OP_MINUS  */
    OP_MULT = 267,                 /* OP_MULT  */
    OP_ASSIGN = 268,               /* OP_ASSIGN  */
    DELIM_SEMICOLON = 269,         /* DELIM_SEMICOLON  */
    DELIM_COMMA = 270,             /* DELIM_COMMA  */
    DELIM_LPAREN = 271,            /* DELIM_LPAREN  */
    DELIM_RPAREN = 272,            /* DELIM_RPAREN  */
    DELIM_LBRACE = 273,            /* DELIM_LBRACE  */
    DELIM_RBRACE = 274,            /* DELIM_RBRACE  */
    ID = 275,                      /* ID  */
    CONST_INT = 276                /* CONST_INT  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 28 "parser.y"

    char* valString;

#line 89 "parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
