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
    ID = 258,                      /* ID  */
    CONST_INT = 259,               /* CONST_INT  */
    CONST_FLOAT = 260,             /* CONST_FLOAT  */
    CONST_STRING = 261,            /* CONST_STRING  */
    KEY_INT = 262,                 /* KEY_INT  */
    KEY_FLOAT = 263,               /* KEY_FLOAT  */
    KEY_STRING = 264,              /* KEY_STRING  */
    KEY_IF = 265,                  /* KEY_IF  */
    KEY_ELSE = 266,                /* KEY_ELSE  */
    KEY_WHILE = 267,               /* KEY_WHILE  */
    KEY_DO = 268,                  /* KEY_DO  */
    KEY_DOEND = 269,               /* KEY_DOEND  */
    KEY_CIN = 270,                 /* KEY_CIN  */
    KEY_COUT = 271,                /* KEY_COUT  */
    KEY_MAIN = 272,                /* KEY_MAIN  */
    KEY_RETURN = 273,              /* KEY_RETURN  */
    OP_ASSIGN = 274,               /* OP_ASSIGN  */
    OP_PLUS = 275,                 /* OP_PLUS  */
    OP_MINUS = 276,                /* OP_MINUS  */
    OP_MULT = 277,                 /* OP_MULT  */
    OP_DIV = 278,                  /* OP_DIV  */
    OP_MOD = 279,                  /* OP_MOD  */
    OP_EQ = 280,                   /* OP_EQ  */
    OP_NEQ = 281,                  /* OP_NEQ  */
    OP_LT = 282,                   /* OP_LT  */
    OP_LTE = 283,                  /* OP_LTE  */
    OP_GT = 284,                   /* OP_GT  */
    OP_GTE = 285,                  /* OP_GTE  */
    OP_AND = 286,                  /* OP_AND  */
    OP_OR = 287,                   /* OP_OR  */
    OP_READ = 288,                 /* OP_READ  */
    OP_WRITE = 289,                /* OP_WRITE  */
    DELIM_SEMICOLON = 290,         /* DELIM_SEMICOLON  */
    DELIM_COMMA = 291,             /* DELIM_COMMA  */
    DELIM_LPAREN = 292,            /* DELIM_LPAREN  */
    DELIM_RPAREN = 293,            /* DELIM_RPAREN  */
    DELIM_LBRACE = 294,            /* DELIM_LBRACE  */
    DELIM_RBRACE = 295,            /* DELIM_RBRACE  */
    DIR_INCLUDE = 296,             /* DIR_INCLUDE  */
    DIR_USING = 297                /* DIR_USING  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
