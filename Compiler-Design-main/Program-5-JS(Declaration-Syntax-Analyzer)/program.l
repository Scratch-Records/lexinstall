%{
 # include<stdio.h>
 # include "y.tab.h"
%}
digits [0-9]
flotnum {digits}+(\.{digits}+)?([eE][-+]?{digits}+)?
string \"(.)*\"

%%
"var" {return VAR;}
"let" {return LET;}
"const" {return CONST;}
{string} {return STRING;}
{flotnum} {return FLOAT;}
[a-zA-Z][a-zA-Z0-9]* {return ID;}
{digits}+ {return NUM;}
[,;=] {return yytext[0];}
%%
int yywrap(){
    return 1;
}

