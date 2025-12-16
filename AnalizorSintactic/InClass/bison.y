%{

#include <stdio.h>

int total_cuvinte = 0;
int cuvinte_declinate = 0;

int yylex();
void yyerror(const char *s);

%}

%token TOKEN_CUVANT
%token TOKEN_LIMBAJ

%%

input: | input el;

el: TOKEN_CUVANT {
        total_cuvinte++;
    }
    | TOKEN_LIMBAJ {
        total_cuvinte++;
        cuvinte_declinate++;
    };

%%

void yyerror(const char *s) {
    fprintf(stderr, "Eroare: %s\n", s);
}

int main() {
    yyparse();

    printf("total cuvinte: %d\n", total_cuvinte);
    printf("cuvinte declinate din \"limbaj\": %d\n", cuvinte_declinate);

    return 0;
}

