%{
 # include<stdio.h>
  int yyerror(char*);
  int yylex();
%}
%token VAR LET CONST STRING FLOAT ID NUM
%%
s1 : s1 s|s;
s : VARD {printf("Proper VAR declaration. \n");}; |
    LETD {printf("Proper LET declaration. \n");}; |
    CONSTD {printf("Proper CONST declaration. \n");};
VARD: VAR IV';';
LETD: LET IV';';
CONSTD: CONST IV';';
IV: IDNAME|IV','IDNAME|IDNAME'='NUM|IV','IDNAME'='NUM |
    IDNAME'='STRING|IV','IDNAME'='STRING| 
    IDNAME'='FLOAT|IV','IDNAME'='FLOAT|; 
IDNAME: ID;
%%
int main(){
    yyparse();
    return 0;
}
int yyerror(char *s){
    return 1;
}