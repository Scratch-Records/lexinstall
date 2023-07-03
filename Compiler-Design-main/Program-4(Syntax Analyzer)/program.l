%{
 # include<stdio.h>
 # include "y.tab.h"
%}
article "a"|"an"|"the"
noun "Sahil"|"boy"|"student"|"song"|"apple"
pronoun "he"|"she"|"it"
verb "is"|"has"|"will"|"eats"|"sings"
conj "and"|"but"
%%
{article} {return ARTICLE;}
{noun} {return NOUN;}
{pronoun} {return PRO;}
{verb} {return VERB;}
{conj} {return CONJ;}
"." {return yytext[0];}
%%

int yywrap(){
    return 1;
}
