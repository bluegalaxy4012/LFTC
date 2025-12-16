%{
#include <iostream>
#include <vector>
#include <string>

using namespace std;

extern int yylex();
extern int currentLine;
extern char* yytext;
void yyerror(const char *s);
%}

%token ID
%token CONST_INT CONST_FLOAT CONST_STRING

%token KEY_INT KEY_FLOAT KEY_STRING
%token KEY_IF KEY_ELSE KEY_WHILE KEY_DO KEY_DOEND
%token KEY_CIN KEY_COUT KEY_MAIN KEY_RETURN

%token OP_ASSIGN
%token OP_PLUS OP_MINUS OP_MULT OP_DIV OP_MOD
%token OP_EQ OP_NEQ OP_LT OP_LTE OP_GT OP_GTE
%token OP_AND OP_OR
%token OP_READ OP_WRITE

%token DELIM_SEMICOLON DELIM_COMMA DELIM_LPAREN DELIM_RPAREN DELIM_LBRACE DELIM_RBRACE

%token DIR_INCLUDE DIR_USING

%%

program : start_program functie_principala
        ;

start_program : DIR_INCLUDE DIR_USING
              ;

functie_principala : KEY_INT KEY_MAIN DELIM_LPAREN DELIM_RPAREN DELIM_LBRACE lista_declaratii lista_instructiuni sfarsit_program DELIM_RBRACE
                   ;

sfarsit_program : KEY_RETURN CONST_INT DELIM_SEMICOLON
                ;

lista_declaratii : 
                 | declaratie lista_declaratii
                 ;

declaratie : tip lista_identificatori DELIM_SEMICOLON
           ;

tip : KEY_INT 
    | KEY_FLOAT 
    | KEY_STRING
    ;

lista_identificatori : ID
                     | ID DELIM_COMMA lista_identificatori
                     ;

lista_instructiuni : 
                   | instructiune lista_instructiuni
                   ;

instructiune : atribuire DELIM_SEMICOLON
             | citire DELIM_SEMICOLON
             | scriere DELIM_SEMICOLON
             | structura_if
             | structura_while
             | structura_do_doend
             | bloc
             ;

atribuire : ID OP_ASSIGN expresie
          ;

citire : KEY_CIN OP_READ cin_items
       ;

cin_items : ID
          | ID OP_READ cin_items
          ;

scriere : KEY_COUT OP_WRITE cout_items
        ;

cout_items : cout_item
           | cout_item OP_WRITE cout_items
           ;

cout_item : ID
          | CONST_INT
          | CONST_FLOAT
          | CONST_STRING
          ;

structura_if : KEY_IF DELIM_LPAREN expresie DELIM_RPAREN bloc altfel_op
             ;

altfel_op : KEY_ELSE bloc
          | 
          ;

structura_while : KEY_WHILE DELIM_LPAREN expresie DELIM_RPAREN bloc
                ;

structura_do_doend : KEY_DO bloc KEY_WHILE DELIM_LPAREN expresie DELIM_RPAREN KEY_DOEND DELIM_SEMICOLON
                   ;

bloc : DELIM_LBRACE lista_instructiuni DELIM_RBRACE
     ;

expresie : exp_relational
         ;

exp_relational : exp_add
               | exp_add OP_LT exp_add
               | exp_add OP_LTE exp_add
               | exp_add OP_GT exp_add
               | exp_add OP_GTE exp_add
               | exp_add OP_EQ exp_add
               | exp_add OP_NEQ exp_add
               ;

exp_add : term
        | term OP_PLUS exp_add
        | term OP_MINUS exp_add
        ;

term : factor
     | factor OP_MULT term
     | factor OP_DIV term
     | factor OP_MOD term
     ;

factor : CONST_INT
       | CONST_FLOAT
       | CONST_STRING
       | ID
       | DELIM_LPAREN expresie DELIM_RPAREN
       ;

%%

void yyerror(const char *s) {
    cout << "Eroare sintactica la linia " << currentLine << ": " << s << " (langa: '" << yytext << "')" << '\n';
}
