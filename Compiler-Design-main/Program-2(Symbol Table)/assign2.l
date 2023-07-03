%{
# include<stdio.h>
# include<string.h>
struct symtab
{
char *name;
};
struct symtab sym[10],*k;
struct symtab *install_id(char *s);
void disp();

%}
letter [A-Za-z]
digits [0-9]
id {letter}({letter}|{digits})*
num {digits}+(\.{digits}+)?([eE][-+]?{digits}+)?
bop [-\+\*\\\**\%]
uop "++"|"--"
relop "<"|"<="|">"|">="|"!="|"=="
lop "&&"|"||"
bitlop "&"|"!"|"\|"|">>"|"<<"|"~"|"^"
assignmentop "=="|"==="|"!="|"!=="|">"|"<"|">="|"<="|"?"
comparisonop "="|"+="|"-="|"*="|"/="|"%="|"**="
keyword "break"|"var"|"const"|"let"|"continue"|"delete"|"do"|"else"|"false"|"for"|"function"|"if"|"new"|"null"|"return"|"this"|"throw"|"true"|"try"|"typeof"|"while"
punc [,;'"\(\)\[\]\{\}]
string \"(.)*\"
spaces [ \t]
newlines [\n]
comment "/\*"(.|\n)*"\*/"|"//"(.)*

%%
{spaces}+ {}
{keyword} {printf("\n 🔹Keyword-> %s\n",yytext);}
{id} {k=install_id(yytext);printf("\n 🔹identifier -> %s\n",yytext);}
{digits}+ {printf("\n 🔹Digits-> %s\n",yytext);}
{punc} {printf("\n 🔹Punctuation-> %s",yytext);}
{string} {printf("\n 🔹String-> %s\n",yytext);}
{bop} {printf("\n 🔹Binary Operator-> %s\n", yytext);}
{uop} {printf("\n 🔹Unary operator-> %s\n",yytext);}
{bitlop} {printf("\n 🔹Bitwise operator-> %s\n",yytext);}
{assignmentop} {printf("\n 🔹Assignment operator-> %s\n",yytext);}
{comparisonop} {printf("\n 🔹Comparison operator-> %s\n",yytext);}
{comment} {printf("\n 🔹Comment-> %s\n",yytext);}
%%

void disp()
{
    struct symtab *p;
    printf("\n 🔹symbol table\n");
    for(p = sym ; p<&sym[10] ; p++)
    {
        if(p->name){
            printf("%s\n",p->name);
        }
    }
}
struct symtab *install_id(char *s)
{
    struct symtab *p;
    for(p = sym ;p<&sym[10];p++)
    {
        if(p->name && !strcmp(s,p->name))
        {
            return p;
        }
        if(!p->name)
        {
            p->name=strdup(s);
            return p;
        }
    }
}
int yywrap()
{
    return 1;
}
int main()
{
    yylex();
    disp();
    yywrap();
}