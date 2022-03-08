%{
#include <stdio.h>
#include <math.h>

#include "turtle-ast.h"

int yylex();
void yyerror(struct ast *ret, const char *);

%}

%debug
%defines

%define parse.error verbose

%parse-param { struct ast *ret }

%union {
  double value;
  char *name;
  struct ast_node *node;
}

%token <value>    VALUE       "value"
%token <name>     NAME        "name"

%token            RED          "red"
%token            GREEN        "green"
%token            BLUE         "blue"
%token            CYAN         "cyan"
%token            MAGENTA      "magenta"
%token            YELLOW       "yellow"
%token            BLACK        "black"
%token            GREY         "grey"
%token            WHITE        "white"

%token           FCT_SIN       "sin"
%token           FCT_COS       "cos"
%token           FCT_TAN       "tan"
%token           FCT_SQRT      "sqrt"
%token           FCT_RANDOM    "random"



%token            KW_FORWARD   "forward"
%token            KW_BACKWARD  "backward"
%token            KW_POSITION  "position"
%token            KW_RIGHT     "right"
%token            KW_LEFT      "left"
%token            KW_PRINT     "print"
%token            KW_HEADING   "heading"
%token            KW_UP        "up"
%token            KW_DOWN      "down"
%token            KW_COLOR     "color"
%token            KW_HOME      "home"
%token            KW_REPEAT    "repeat"



/* TODO: add other tokens */

%left '+' '-'
%left '*' '/'
%left '^'
%left UNARY_MINUS


%type <node> unit cmds cmd expr param

%%

unit:
    cmds              { $$ = $1; ret->unit = $$; }
;

cmds:
    cmd cmds          { $1->next = $2; $$ = $1; }
  | /* empty */       { $$ = NULL; }
;

param:
    expr            { $$ = $1; }
  |  cmd             { $$ = $1; }
;


cmd:
    KW_FORWARD param   { $$ = make_cmd_forward($1); }
  |  KW_BACKWARD param  { $$ = make_cmd_backward($1); }
  |  KW_RIGHT param     { $$ = make_cmd_right($1); }
  |  KW_LEFT param      { $$ = make_cmd_left($1); }
  |  KW_PRINT param     { $$ = make_cmd_print($1); }
  |  KW_HEADING param   { $$ = make_cmd_heading($1); }
  |  KW_UP param        { $$ = make_cmd_up($1); }
  |  KW_DOWN param      { $$ = make_cmd_down($1); }
  |  KW_COLOR param     { $$ = make_cmd_color($1); }
  |  KW_POSITION param param { $$ = make_cmd_position($1, $2); }
  |  KW_HOME      { $$ = make_cmd_home(); }
  |  KW_REPEAT param cmd  { $$ = make_cmd_repeat($1, $2); } 
  | '{' cmds '}'       { }
;


color:
    RED
  | GREEN
  | BLUE
  | CYAN
  | MAGENTA
  | YELLOW
  | BLACK
  | GREY
  | WHITE
  | expr expr expr    { /* TODO */ }


expr:
    VALUE             { $$ = make_expr_value($1); }
  |  '-' VALUE %prec UNARY_MINUS { /* TODO */ }
  |  expr '+' expr     { $$ = make_expr_binop($2, $1 , $3); }
  |  expr '-' expr     { $$ = make_expr_binop($2, $1 , $3); }
  |  expr '^' expr     { $$ = make_expr_binop($2, $1 , $3); }
  |  expr '*' expr     { $$ = make_expr_binop($2, $1 , $3); }
  |  expr '/' expr     { $$ = make_expr_binop($2, $1 , $3); }
  |  FCT_SIN '(' expr ')'         { /* TODO */ }
  |  FCT_COS '(' expr ')'         { /* TODO */ }
  |  FCT_TAN '(' expr ')'         { /* TODO */ }
  |  FCT_SQRT '(' expr ')'        { /* TODO */ }
  |  FCT_RANDOM '(' expr ',' expr ')'      { $$ = 0; }
  |  '(' expr ')' { /* TODO */ }
  |  '-' '(' expr ')' { /* TODO */ }
 
  /* TODO: add identifier */
;

%%

void yyerror(struct ast *ret, const char *msg) {
  (void) ret;
  fprintf(stderr, "%s\n", msg);
}
