%{
    #include <stdio.h>
    #include "bison.tab.h"
%}

%option noyywrap

%%

"limbaj"|"limbajul"|"limbajului"|"limbaje"|"limbajele"|"limbajelor" { return TOKEN_LIMBAJ; }

[a-z]+ { return TOKEN_CUVANT; }

[ \t\n]+ { }

. { }

%%
