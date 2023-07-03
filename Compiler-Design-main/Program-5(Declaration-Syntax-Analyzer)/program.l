%{
 # include<stdio.h>
 # include "y.tab.h"
%}
%%
"int" {return INT;}
[a-zA-Z][a-zA-Z0-9]* {return ID;}
[0-9]+ {return INTNUM;}
[,;=] {return yytext[0];}
%%
int yywrap(){
    return 1;
}