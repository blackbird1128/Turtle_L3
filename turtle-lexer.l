%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "turtle-ast.h"
#include "turtle-parser.h"
%}

%option warn 8bit nodefault noyywrap

DIGIT [0-9]
INT {DIGIT}+
DOUBLE {INT}*(("."|e-|e+|E|e){DIGIT}+)?
LEFT_BRACKET "{"
RIGHT_BRACKET "}"


%%

{INT}+                { yylval.value = strtod(yytext, NULL); return VALUE; }
{DOUBLE}              { yylval.value = strtod(yytext, NULL); return VALUE; }
"print"               {return CMD_PRINT;}
"up"                  {return KW_UP;}
"down"                {return KW_DOWN;}
"red"                 {return RED;}
"green"               {return GREEN;}
"blue"                {return BLUE;}
"cyan"                {return CYAN;}
"magenta"             {return MAGENTA;}
"yellow"              {return YELLOW;}
"black"               {return BLACK;}
"grey"                {return GREY;}
"white"               {return WHITE;}
"sin"                 {return FCT_SIN;}
"cos"                 {return FCT_COS;}
"tan"                 {return FCT_TAN;}
"sqrt"                {return FCT_SQRT;}
"random"              {return FCT_RANDOM;}




"forward"             {return KW_FORWARD;}
"fw"                  {return KW_FORWARD;}
"backward"            {return KW_BACKWARD;}
"bw"                  {return KW_BACKWARD;}
"position"            {return KW_POSITION;}
"pos"                 {return KW_POSITION;}
"right"               {return KW_RIGHT;}
"rt"                  {return KW_RIGHT;}
"left"                {return KW_LEFT;}
"lt"                  {return KW_LEFT;}
"heading"             {return KW_HEADING;}
"ht"                  {return KW_HEADING;}
"color"               {return KW_COLOR;}
"home"                {return KW_HOME;}
"repeat"              {return KW_REPEAT;}

"+"                  {return '+';}
"-"                  {return '-';}
"*"                  {return '*';}
"/"                  {return '/';}
"^"                  {return '^';}


{LEFT_BRACKET}                  {return '{';}
{RIGHT_BRACKET}                 {return '}';}




[\n\t ]*              /* whitespace */
.                     { fprintf(stderr, "Unknown token: '%s'\n", yytext); exit(EXIT_FAILURE); }

%%
 