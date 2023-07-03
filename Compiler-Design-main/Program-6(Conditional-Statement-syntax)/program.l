%{
 # include<stdio.h>
 # include "y.tab.h"
%}
digits [0-9]

%%
"int" {return INT;}
"if" {return IF;}
"while" {return WHILE;}
"true" {return TRUEE;}
"false" {return FALSEE;}
"do" {return DO;}
"for" {return FOR;}
{digits}+ {return NUM;}
"<"|"<="|">"|">="|"!="|"==" {return RELOP;}
"&&" {return AND;}
"||" {return OR;}
"!" {return NOT;}
"++" {return INC;}
"--" {return DEC;}
[a-zA-Z][a-zA-Z0-9]* {return ID;}
[-\)\(\{\}\[\]+*/,;=] {return yytext[0];}
[ \t\n]  { }
%%
int yywrap(){
    return 1;
}