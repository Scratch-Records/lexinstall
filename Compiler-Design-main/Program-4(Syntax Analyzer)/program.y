%{
 # include<stdio.h>
  int yyerror(char*);
  int yylex();
%}
%token ARTICLE NOUN PRO VERB CONJ  
%nonassoc NOUN
%nonassoc CONJ
%%
s1 : s1 s | s ;
s : simple '.' {printf("Simple Sentence. \n");}|compond '.' {printf("Compound Sentence. \n");};
compond: simple CONJ simple | simple CONJ compond ;
simple: sub VERB obj ;
sub: NOUN | PRO ;
obj: NOUN | PRO | ARTICLE NOUN;
%%
int main(){
    yyparse();
    return 0;
}
int yyerror(char *s){
    return 1;
}