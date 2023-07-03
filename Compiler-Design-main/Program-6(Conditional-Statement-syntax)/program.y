%{
 # include<stdio.h>
  int yyerror(char*);
  int yylex();
%}
%token ID NUM IF WHILE DO FOR TRUEE FALSEE INC DEC INT
%right '='
%left '+' '-'
%left '*' '/'
%left OR
%left AND
%nonassoc NOT
%right RELOP

%%
s1 : s1 s|s;
s : ASSIGNMENT ';' {printf("Proper Assignment. \n");};|
    IF_STMT {printf("Proper IF statement. \n");};|
    WHILE_STMT {printf("Proper WHILE loop. \n");};|
    DO_WHILE_STMT {printf("Proper D0-WHILE loop. \n");};|
    FOR_STMT {printf("Proper FOR loop. \n");}
ASSIGNMENT: ID '=' E | ARR '=' E;
E: E'+'E | E'-'E |E'*'E |E'/'E | ARR | NUM | ID ;
IF_STMT: IF'('BE')''{'s1'}';
BE: BE OR BE | BE AND BE | NOT BE | ID RELOP ID | NUM RELOP ID | ID RELOP NUM | TRUEE | FALSEE | NUM | 
    ARR RELOP ARR | ARR RELOP ID | ID RELOP ARR | ARR RELOP NUM | NUM RELOP ARR | NUM RELOP NUM;
ARR: ID X;
X: X SUBSCRIPT | SUBSCRIPT;
SUBSCRIPT: '['ID']' | '['NUM']' |'['ARR']';
WHILE_STMT: WHILE'('BE')''{'s1'}';
DO_WHILE_STMT: DO'{'s1'}'WHILE'('BE')'';';
FOR_STMT: FOR'('INIT_STMT ';' BE ';' MODIFICATION ')' '{'s1'}';
INIT_STMT: ASSIGNMENT | INT ASSIGNMENT | INT ASSIGNMENT ',' INIT_STMT | ASSIGNMENT ',' INIT_STMT;
MODIFICATION: ID INC | INC ID | ID DEC | DEC ID | INIT_STMT |
             ID INC ',' MODIFICATION | ID DEC ',' MODIFICATION
            INC ID ',' MODIFICATION| DEC ID ',' MODIFICATION;

%%
int main(){
    yyparse();
    return 0;
}
int yyerror(char *s){
    return 1;
}