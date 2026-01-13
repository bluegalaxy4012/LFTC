%{
#include <iostream>
#include <string.h>
#include "parser.tab.h"

using namespace std;
%}

%option noyywrap

%%

[ \t\n]+ ;

"#include <iostream>" ;
"using namespace std;" ;

"int" { return KEY_INT; }
"main"  { return KEY_MAIN; }
"return" { return KEY_RETURN; }
"cin" { return KEY_CIN; }
"cout" { return KEY_COUT; }

">>" { return OP_READ; }
"<<" { return OP_WRITE; }

"+" { return OP_PLUS; }
"-" { return OP_MINUS; }
"*" { return OP_MULT; }
"=" { return OP_ASSIGN; }

";" { return DELIM_SEMICOLON; }
"," { return DELIM_COMMA; }
"(" { return DELIM_LPAREN; }
")" { return DELIM_RPAREN; }
"{" { return DELIM_LBRACE; }
"}" { return DELIM_RBRACE; }

[a-zA-Z][a-zA-Z0-9_]* { 
    yylval.valString = strdup(yytext);
    return ID; 
}

[0-9]+ { 
    yylval.valString = strdup(yytext);
    return CONST_INT; 
}

. { cout << "Eroare lexicala: " << yytext << '\n'; }

%%