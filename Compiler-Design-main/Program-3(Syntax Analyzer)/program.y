%{
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

struct symtab
{
    char *name;
    double val;
} SYM[20];

void disp();
struct symtab *install_id(char *s);

int yylex();
void yyerror(const char* s);

%}

%union {
  double v;
  struct symtab *p;
}

%token SIN COS NUM id
%type<v> E

%right '='
%left '+' '-'
%left '*' '/'
%nonassoc UMINUS

%%

lines: lines S
    | S
	;

S: id '=' E '\n' {
        $1->val = $3;
    }
 | E '\n' {
        printf("ans = %lf\n", $1);
    }
 ;

E: E '+' E {
        $$ = $1 + $3;
    }
 | E '-' E {
        $$ = $1 - $3;
    }
 | E '*' E {
        $$ = $1 * $3;
    }
 | E '/' E {
        $$ = $1 / $3;
    }
 | '-' E %prec UMINUS {
        $$ = -$2;
    }
 | '(' E ')' {
        $$ = $2;
    }
 | NUM {
        $$ = $1;
    }
 | id {
        $$ = $1->val;
    }
 | SIN '(' E ')' {
        $$ = sin(($3 * 3.14) / 180);
    }
 | COS '(' E ')' {
        $$ = cos(($3 * 3.14) / 180);
    }
 ;

%%

int yylex() {
    // Add your lexer code here
    return 0;
}

void yyerror(const char* s) {
    printf("Parse error: %s\n", s);
}

int main()
{
    memset(SYM, 0, sizeof(SYM));
    yyparse();
    disp();
    return 0;
}

void disp()
{
    struct symtab *k;
    for (k = SYM; k < &SYM[20]; k++)
    {
        if (k->name)
        {
            printf("%s\t%f\n", k->name, k->val);
        }
    }
}

struct symtab *install_id(char *s)
{
    struct symtab *k;
    for (k = SYM; k < &SYM[20]; k++)
    {
        if (k->name && !strcmp(k->name, s))
            return k;
        else if (!k->name)
        {
            k->name = strdup(s);
            return k;
        }
    }
    return NULL; // Added return statement to handle case when the symbol table is full
}
