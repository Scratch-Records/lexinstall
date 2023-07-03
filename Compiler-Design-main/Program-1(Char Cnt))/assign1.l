%{
#include<stdio.h>
int char_cnt = 0;
int word_cnt = 0;
int line_cnt = 0;
int tab_cnt = 0;
int space_cnt = 0;
%}

%%
[\n] {line_cnt += 1; char_cnt+= yyleng;}
[\t] { tab_cnt++; char_cnt+= yyleng;}
[ ] {space_cnt++; char_cnt+= yyleng;}
[^ \t\n]+ {word_cnt += 1;char_cnt += yyleng;}
%%

int main(){
    printf("Input : ");
    yylex();
    printf("Number of chars : %d\n",char_cnt);
    printf("Number of words : %d\n",word_cnt);
    printf("Number of lines : %d\n",line_cnt);
    printf("Number of tabs : %d\n",tab_cnt);
    printf("Number of space : %d\n",space_cnt);
    return 0;
}
int yywrap(){ return 1;}