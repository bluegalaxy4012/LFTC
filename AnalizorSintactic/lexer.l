%{
#include <iostream>
#include <vector>
#include <utility>
#include "TabelaSimboluri.h"
#include "parser.tab.h"

using namespace std;

extern int currentLine;
extern vector<pair<int, int>> FIP;
extern TabelaSimboluri TS_ID;
extern TabelaSimboluri TS_CONST;
extern bool hasLexicalErrors;

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
OCT_DIGIT   [0-7]
BIN_DIGIT   [01]
LETTER      [a-zA-Z]

ID          {LETTER}({LETTER}|{DIGIT}|_)*

INT_BIN     0b{BIN_DIGIT}+
INT_HEX     0x{HEX_DIGIT}+
INT_OCT     0{OCT_DIGIT}+
INT_DEC     0|([1-9]{DIGIT}*)

FLOAT       (\+|-)?[0-9]+\.[0-9]+
STRING      \"[^\"\n]*\"

%%

[ \t]+      ;
\n          { currentLine++; }

"#include <iostream>"   { addToFIP(DIR_INCLUDE, -1); return DIR_INCLUDE; }
"using namespace std;"  { addToFIP(DIR_USING, -1); return DIR_USING; }

"int"       { addToFIP(KEY_INT, -1); return KEY_INT; }
"float"     { addToFIP(KEY_FLOAT, -1); return KEY_FLOAT; }
"string"    { addToFIP(KEY_STRING, -1); return KEY_STRING; }
"std::string" { addToFIP(KEY_STRING, -1); return KEY_STRING; }
"if"        { addToFIP(KEY_IF, -1); return KEY_IF; }
"else"      { addToFIP(KEY_ELSE, -1); return KEY_ELSE; }
"while"     { addToFIP(KEY_WHILE, -1); return KEY_WHILE; }
"do"        { addToFIP(KEY_DO, -1); return KEY_DO; }
"doend"     { addToFIP(KEY_DOEND, -1); return KEY_DOEND; }
"return"    { addToFIP(KEY_RETURN, -1); return KEY_RETURN; }
"main"      { addToFIP(KEY_MAIN, -1); return KEY_MAIN; }
"cin"       { addToFIP(KEY_CIN, -1); return KEY_CIN; }
"cout"      { addToFIP(KEY_COUT, -1); return KEY_COUT; }

"+"         { addToFIP(OP_PLUS, -1); return OP_PLUS; }
"-"         { addToFIP(OP_MINUS, -1); return OP_MINUS; }
"*"         { addToFIP(OP_MULT, -1); return OP_MULT; }
"/"         { addToFIP(OP_DIV, -1); return OP_DIV; }
"%"         { addToFIP(OP_MOD, -1); return OP_MOD; }
"="         { addToFIP(OP_ASSIGN, -1); return OP_ASSIGN; }
"=="        { addToFIP(OP_EQ, -1); return OP_EQ; }
"!="        { addToFIP(OP_NEQ, -1); return OP_NEQ; }
"<"         { addToFIP(OP_LT, -1); return OP_LT; }
"<="        { addToFIP(OP_LTE, -1); return OP_LTE; }
">"         { addToFIP(OP_GT, -1); return OP_GT; }
">="        { addToFIP(OP_GTE, -1); return OP_GTE; }
"&&"        { addToFIP(OP_AND, -1); return OP_AND; }
"||"        { addToFIP(OP_OR, -1); return OP_OR; }
">>"        { addToFIP(OP_READ, -1); return OP_READ; }
"<<"        { addToFIP(OP_WRITE, -1); return OP_WRITE; }

"("         { addToFIP(DELIM_LPAREN, -1); return DELIM_LPAREN; }
")"         { addToFIP(DELIM_RPAREN, -1); return DELIM_RPAREN; }
"{"         { addToFIP(DELIM_LBRACE, -1); return DELIM_LBRACE; }
"}"         { addToFIP(DELIM_RBRACE, -1); return DELIM_RBRACE; }
";"         { addToFIP(DELIM_SEMICOLON, -1); return DELIM_SEMICOLON; }
","         { addToFIP(DELIM_COMMA, -1); return DELIM_COMMA; }

{INT_BIN}   { int idx = addToTS(TS_CONST, yytext); addToFIP(CONST_INT, idx); return CONST_INT; }
{INT_HEX}   { int idx = addToTS(TS_CONST, yytext); addToFIP(CONST_INT, idx); return CONST_INT; }
{INT_OCT}   { int idx = addToTS(TS_CONST, yytext); addToFIP(CONST_INT, idx); return CONST_INT; }
{FLOAT}     { int idx = addToTS(TS_CONST, yytext); addToFIP(CONST_FLOAT, idx); return CONST_FLOAT; }
{INT_DEC}   { int idx = addToTS(TS_CONST, yytext); addToFIP(CONST_INT, idx); return CONST_INT; }
{STRING}    { int idx = addToTS(TS_CONST, yytext); addToFIP(CONST_STRING, idx); return CONST_STRING; }

{ID}        {
    if (yyleng > 250) {
        cout << "Eroare lexicala la linia " << currentLine << ": Identificator prea lung: " << yytext << '\n';
        hasLexicalErrors = true;
        return ID;
    } else {
        int idx = addToTS(TS_ID, yytext);
        addToFIP(ID, idx);
        return ID;
    }
}

{DIGIT}+{LETTER}+               { cout << "Eroare lexicala la linia " << currentLine << ": Constanta numerica malformata: " << yytext << '\n'; hasLexicalErrors = true; }
{DIGIT}*\.{DIGIT}*[a-zA-Z_]+    { cout << "Eroare lexicala la linia " << currentLine << ": Constanta float malformata: " << yytext << '\n'; hasLexicalErrors = true; }
0[xX]{HEX_DIGIT}*[a-gA-Gj-zJ-Z_]+ { cout << "Eroare lexicala la linia " << currentLine << ": Constanta hex malformata: " << yytext << '\n'; hasLexicalErrors = true; }

\"[^\"\n]*$ { cout << "Eroare lexicala la linia " << currentLine << ": String neterminat" << '\n'; hasLexicalErrors = true; }
.           { cout << "Eroare lexicala la linia " << currentLine << ": Caracter invalid: " << yytext << '\n'; hasLexicalErrors = true; }

%%
