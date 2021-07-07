%option noyywrap
%{
#define YYSTYPE char*
#include "parser.tab.hpp"
#include <bits/stdc++.h> 
using namespace std;
%}
 
%%
"ADD" {return (ADD);}
"SUBTRACT" {return (SUBTRACT); }
"MULTIPLY"   {return (MULTIPLY); }
"DIVIDE"  {return (DIVIDE); }
"LEFT"   {return (LEFT); }
"RIGHT"   {return (RIGHT); }
"UP"    {return (UP); }
"ASSIGN" {return (ASSIGN); }  
"TO"    {return (TO); }
"VAR"   {return (VAR); }
"IS"    {return (IS); }
"VALUE" {return (VALUE); }
"IN"    {return (IN);  }
"DOWN"  { return (DOWN);}
"."     {return (FULLSTOP);}
","     {return COMMA;}
"\n"    {return (NEWLINE);}
[1-9][0-9]* {yylval=(yytext);return NUMBER;}
[0] {yylval=(yytext);return NUMBER;}
[0-9]+[A-Za-z_0-9]+ {printf("2048>Unknown token\n");}
[A-Za-z_][A-Za-z0-9_]* {yylval = yytext; return (VARIABLE);}
[' ']+    {}
.   {printf("2048>Unknown token\n");}
%%