%{
#include <iostream>
#include <vector>
#include <utility>
#include "atoms.h"
#include "TabelaSimboluri.h"

using namespace std;

int currentLine;
vector<pair<int, int>> FIP;
TabelaSimboluri TS_ID;
TabelaSimboluri TS_CONST;

void addToFIP(int atomCode, int tsIndex) {
    FIP.push_back({atomCode, tsIndex});
}

int addToTS(TabelaSimboluri& ts, const char* text) {
    return ts.add(string(text));
}
%}

%option noyywrap

DIGIT       [0-9]
HEX_DIGIT   [0-9a-fA-F]
LETTER      [a-zA-Z]
ID          {LETTER}({LETTER}|{DIGIT}|_)*

INT_BASE    (0|([1-9]{DIGIT}*))
HEX         0[xX]{HEX_DIGIT}+
OCTAL       0[0-7]+
FLOAT       (\+|-)?[0-9]+\.[0-9]+

STRING      \"[^\"\n]*\"

%%

[ \t]+      ;
\n          { currentLine++; }

"#include <iostream>"   { addToFIP(DIR_INCLUDE, -1); }
"using namespace std;"  { addToFIP(DIR_USING, -1); }

"int"       { addToFIP(KEYWORD_INT, -1); }
"float"     { addToFIP(KEYWORD_FLOAT, -1); }
"string" { addToFIP(KEYWORD_STRING, -1); }
"if"        { addToFIP(KEYWORD_IF, -1); }
"else"      { addToFIP(KEYWORD_ELSE, -1); }
"while"     { addToFIP(KEYWORD_WHILE, -1); }

"do"        { addToFIP(KEYWORD_DO, -1); }
"doend"     { addToFIP(KEYWORD_DOEND, -1); }

"return"    { addToFIP(KEYWORD_RETURN, -1); }
"cin"       { addToFIP(KEYWORD_CIN, -1); }
"cout"      { addToFIP(KEYWORD_COUT, -1); }

"+"         { addToFIP(OP_PLUS, -1); }
"-"         { addToFIP(OP_MINUS, -1); }
"*"         { addToFIP(OP_MULT, -1); }
"/"         { addToFIP(OP_DIV, -1); }
"%"         { addToFIP(OP_MOD, -1); }
"="         { addToFIP(OP_ASSIGN, -1); }
"=="        { addToFIP(OP_EQUAL, -1); }
"<"         { addToFIP(OP_LESS, -1); }
"<="        { addToFIP(OP_LESS_EQ, -1); }
">"         { addToFIP(OP_GREATER, -1); }
">="        { addToFIP(OP_GREATER_EQ, -1); }
"!="        { addToFIP(OP_NOT_EQ, -1); }
"&&"        { addToFIP(OP_AND, -1); }
"||"        { addToFIP(OP_OR, -1); }
">>"        { addToFIP(OP_READ, -1); }
"<<"        { addToFIP(OP_WRITE, -1); }
"("         { addToFIP(DELIM_LPAREN, -1); }
")"         { addToFIP(DELIM_RPAREN, -1); }
"{"         { addToFIP(DELIM_LBRACE, -1); }
"}"         { addToFIP(DELIM_RBRACE, -1); }
";"         { addToFIP(DELIM_SEMICOLON, -1); }
","         { addToFIP(DELIM_COMMA, -1); }

{DIGIT}+{LETTER}+               { cout << "Eroare la linia " << currentLine << ": Constanta numerica malformata: " << yytext << "\n"; }

{DIGIT}*\.{DIGIT}*[a-zA-Z_]+     { cout << "Eroare la linia " << currentLine << ": Constanta float malformata: " << yytext << "\n"; }

0[xX]{HEX_DIGIT}*[a-gA-Gj-zJ-Z_]+ { cout << "Eroare la linia " << currentLine << ": Constanta hexazecimala malformata: " << yytext << "\n"; }

{FLOAT}     { int idx = addToTS(TS_CONST, yytext); addToFIP(CONST, idx); }
{HEX}       { int idx = addToTS(TS_CONST, yytext); addToFIP(CONST, idx); }
{OCTAL}     { int idx = addToTS(TS_CONST, yytext); addToFIP(CONST, idx); }
{INT_BASE}  { int idx = addToTS(TS_CONST, yytext); addToFIP(CONST, idx); }
{STRING}    { int idx = addToTS(TS_CONST, yytext); addToFIP(CONST, idx); }

{ID}        {
    if (yyleng > 250) {
        cout << "Eroare la linia " << currentLine << ": Identificator prea lung: " << yytext << "\n";
    } else {
        int idx = addToTS(TS_ID, yytext);
        addToFIP(ID, idx);
    }
}

\"[^\"\n]*$ { cout << "Eroare la linia " << currentLine << ": String neterminat\n"; }

.           { cout << "Eroare la linia " << currentLine << ": Caracter invalid: " << yytext << "\n"; }

%%
