%{
 # include<stdio.h>
  int yyerror(char*);
  int yylex();
%}
%token INT INTNUM ID
%%
s1 : s1 s|s;
s : INTD {printf("Proper integer declaration. \n");}; 
INTD: INT IV';';
IV: IDN|IV','IDN|IDN'='INTNUM|IV','IDN'='INTNUM; 
IDN: ID;

%%
int main(){
    yyparse();
    return 0;
}
int yyerror(char *s){
    return 1;
}