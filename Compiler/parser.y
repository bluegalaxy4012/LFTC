%{
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

extern int yylex();
extern int yyparse();
extern FILE* yyin;
void yyerror(const char *s);

vector<string> variabile;

void check_var(char* var) {
    bool found = false;
    for(const string& s : variabile) {
        if(s == var) found = true;
    }
    if(!found) {
        cerr << "Eroare semantica: variabila " << var << " nedeclarata\n";
        exit(1);
    }
}
%}

%union {
    char* valString;
}

%token KEY_INT KEY_MAIN KEY_RETURN KEY_CIN KEY_COUT
%token OP_READ OP_WRITE OP_PLUS OP_MINUS OP_MULT OP_ASSIGN
%token DELIM_SEMICOLON DELIM_COMMA DELIM_LPAREN DELIM_RPAREN DELIM_LBRACE DELIM_RBRACE

%token <valString> ID CONST_INT

%%

program : header functie_principala
        ;

header : /* gol sau includeuri ignorate de lexer */
       ;

functie_principala : KEY_INT KEY_MAIN DELIM_LPAREN DELIM_RPAREN bloc
                   ;

bloc : DELIM_LBRACE {
        cout << "extern printf, scanf, exit\n";
        cout << "section .text\n";
        cout << "global main\n\n";
        cout << "main:\n";
     } 
     declaratii instructiuni return_statement DELIM_RBRACE {
        cout << "\n";
        cout << "section .data\n";
        cout << "format_in: db \"%d\", 0\n";
        cout << "format_out: db \"%d\", 10, 0\n"; // 10 = \n
        for(const string& v : variabile) {
            cout << v << ": dd 0\n";
        }
     }
     ;

declaratii : declaratie declaratii
           |
           ;

declaratie : KEY_INT lista_id DELIM_SEMICOLON
           ;

lista_id : ID { 
             variabile.push_back($1); 
           }
         | ID DELIM_COMMA lista_id { 
             variabile.push_back($1); 
           }
         ;

instructiuni : instructiune instructiuni
             |
             ;

instructiune : atribuire 
             | citire 
             | scriere 
             ;

atribuire : ID OP_ASSIGN expresie DELIM_SEMICOLON {
              check_var($1);
              cout << "pop eax\n";
              cout << "mov [" << $1 << "], eax\n";
          }
          ;

citire : KEY_CIN OP_READ ID DELIM_SEMICOLON {
            check_var($3);
            cout << "push " << $3 << "\n";
            cout << "push format_in\n";
            cout << "call scanf\n";
            cout << "add esp, 8\n";
       }
       ;

scriere : KEY_COUT OP_WRITE expresie DELIM_SEMICOLON {
            cout << "pop eax\n";
            cout << "push eax\n";
            cout << "push format_out\n";
            cout << "call printf\n";
            cout << "add esp, 8\n";
        }
       ;

expresie : expresie OP_PLUS term {
             cout << "pop ebx\n";
             cout << "pop eax\n";
             cout << "add eax, ebx\n";
             cout << "push eax\n";
         }
         | expresie OP_MINUS term {
             cout << "pop ebx\n";
             cout << "pop eax\n";
             cout << "sub eax, ebx\n";
             cout << "push eax\n";
         }
         | term
         ;

term : term OP_MULT factor {
         cout << "pop ebx\n";
         cout << "pop eax\n";
         cout << "imul eax, ebx\n";
         cout << "push eax\n";
     }
     | factor
     ;

factor : ID {
           check_var($1);
           cout << "push dword [" << $1 << "]\n";
       }
       | CONST_INT {
           cout << "push " << $1 << "\n";
       }
       | DELIM_LPAREN expresie DELIM_RPAREN
       ;

return_statement : KEY_RETURN CONST_INT DELIM_SEMICOLON {
                     cout << "push 0\n";
                     cout << "call exit\n";
                 }
                 ;

%%

void yyerror(const char *s) {
    cerr << "Eroare sintactica: " << s << '\n';
    exit(1);
}

int main(int argc, char** argv) {
    if(argc > 1) yyin = fopen(argv[1], "r");
    yyparse();
    return 0;
}