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

%token           '+'           PLUS
%token           '-'           MINUS
%token           '*'           MULT
%token           '/'           DIV
%token           '^'           POW

%token          '('           LPAREN
%token          ')'           RPAREN


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
%token            KW_SET       "set"
%token            KW_PROC      "proc"
%token            KW_CALL      "call"




/* TODO: add other tokens */

%left '+' '-'
%left '*' '/'
%left '^'
%left UNARY_MINUS


%type <node> unit cmds cmd expr param color name

%%

unit:
    cmds              { $$ = $1; ret->unit = $$; }
;

cmds:
    cmd cmds          { $$->next = $2; $$ = $1; }
  | /* empty */       { $$ = NULL; }
;


name:
    NAME { $$ = make_name_node($1); };

param:
    expr            { $$ = $1; }
  |  name      { $$ = $1; }  
  |  cmd             { $$ = $1; }
;

color:
    RED   { $$ = make_color_node_from_name(COLOR_RED); }
  | BLUE  { $$ = make_color_node_from_name(COLOR_BLUE); }
  | GREEN { $$ = make_color_node_from_name(COLOR_GREEN); }
  | CYAN  { $$ = make_color_node_from_name(COLOR_CYAN); }
  | MAGENTA  { $$ = make_color_node_from_name(COLOR_MAGENTA); }
  | YELLOW  { $$ = make_color_node_from_name(COLOR_YELLOW); }
  | BLACK { $$ = make_color_node_from_name(COLOR_BLACK); }
  | GREY { $$ = make_color_node_from_name(COLOR_GREY); }
  | WHITE { $$ = make_color_node_from_name(COLOR_WHITE); }
  | expr expr expr    {  $$ = make_color_node($1, $2, $3); }



cmd:
     KW_FORWARD param   { $$ = make_cmd_forward($2); }
  |  KW_BACKWARD param  { $$ = make_cmd_backward($2); }
  |  KW_RIGHT param     { $$ = make_cmd_right($2); }
  |  KW_LEFT param      { $$ = make_cmd_left($2); }
  |  KW_PRINT param     { $$ = make_cmd_print($2); }
  |  KW_HEADING param   { $$ = make_cmd_heading($2); }
  |  KW_UP param        { $$ = make_cmd_up($2); }
  |  KW_DOWN param      { $$ = make_cmd_down($2); }
  |  KW_COLOR color    { $$ = make_cmd_color($2); }
  |  KW_POSITION param param { $$ = make_cmd_position($2, $3); }
  |  KW_HOME      { $$ = make_cmd_home(); }
  |  KW_REPEAT param cmd  { $$ = make_cmd_repeat($2, $3); } 
  | '{' cmds '}'       { $$ = make_cmd_block($2); }
  | KW_SET name expr  { $$ = make_cmd_set($2, $3); }
  | KW_PROC name '{' cmds '}'  {$$ = make_cmd_proc($2, $4); }
  | KW_CALL name       { $$ = make_cmd_call($2); }
;



expr:
    VALUE             { $$ = make_expr_value($1); }
  | name             { $$ =  $1 ;} 
  |  '-' VALUE %prec UNARY_MINUS { $$= make_expr_value(-1*$2); }
  |  expr '+' expr     { $$ = make_expr_binop('+', $1 , $3); }
  |  expr '-' expr     { $$ = make_expr_binop('-', $1 , $3); }
  |  expr '*' expr     { $$ = make_expr_binop('*', $1 , $3); }
  |  expr '/' expr     { $$ = make_expr_binop('/', $1 , $3); }
  |  expr '^' expr     { $$ = make_expr_binop('^', $1 , $3); }
  |  FCT_SIN '(' expr ')'         { $$ = make_expr_func(FUNC_SIN, $3); }
  |  FCT_COS '(' expr ')'         { $$ = make_expr_func(FUNC_COS, $3); }
  |  FCT_TAN '(' expr ')'         { $$ = make_expr_func(FUNC_TAN, $3); }
  |  FCT_SQRT '(' expr ')'        { $$ = make_expr_func(FUNC_SQRT, $3); }
  |  FCT_RANDOM '(' expr ',' expr ')'      { $$ = make_expr_func_rdm( $3, $5); }
  |  '(' expr ')' { $$ = $2; }
  |  '-' '(' expr ')' { $$ = make_expr_unop('-', $3); }
 
  /* TODO: add identifier */
;

%%

void yyerror(struct ast *ret, const char *msg) {
  (void) ret;
  fprintf(stderr, "%s\n", msg);
}
