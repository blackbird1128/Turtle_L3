%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "turtle-ast.h"
#include "turtle-parser.h"


%}


/*
    -- Convention used in the lexer --
    
    -We use the subject prefix KW for each command ex : a KW_FORWARD token is returned when forward is parsed
    -FCT prefix is used for the different commands ex : FCT_RANDOM, FCT_TAN
    -No prefix are used for the color, a token with the same name but written with capital letters is returned ex : "red" --> "RED" is returned
*/


%option warn 8bit nodefault noyywrap

DIGIT [0-9]
INT {DIGIT}+
DOUBLE {INT}*(("."|e-|e+|E|e){DIGIT}+)?
LEFT_BRACKET "{"
RIGHT_BRACKET "}"
LEFT_PARENTHESIS "("
RIGHT_PARENTHESIS ")"
COMMA ","
VAR [A-Z][A-Z0-9]*


%%

{INT}+                { yylval.value = strtod(yytext, NULL); return VALUE; }
{DOUBLE}              { yylval.value = strtod(yytext, NULL); return VALUE; }
{VAR}                 { yylval.name = yytext; return NAME; }



"print"               {return CMD_PRINT;}
"up"                  {return KW_UP;}
"down"                {return KW_DOWN;}
"home"                {return KW_HOME;}
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
"set"                 {return KW_SET;}
"proc"                {return KW_PROC;}
"call"                {return KW_CALL;}

"+"                  {return '+';}
"-"                  {return '-';}
"*"                  {return '*';}
"/"                  {return '/';}
"^"                  {return '^';}


{LEFT_BRACKET}                  {return '{';}
{RIGHT_BRACKET}                 {return '}';}
{LEFT_PARENTHESIS}              {return '(';}
{RIGHT_PARENTHESIS}             {return ')';}
{COMMA}                          {return ',';}




[\n\t ]*              /* whitespace */
.                     { fprintf(stderr, "Unknown token: '%s'\n", yytext); exit(EXIT_FAILURE); }

%%
 