%{
#include <stdio.h>

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

%type <node> unit cmds cmd expr

%%

unit:
    cmds              { $$ = $1; ret->unit = $$; }
;

cmds:
    cmd cmds          { $1->next = $2; $$ = $1; }
  | /* empty */       { $$ = NULL; }
;

cmd:
    KW_FORWARD expr   { /* TODO */ printf("Coucou \n");}
    
;

expr:
    VALUE             { $$ = make_expr_value($1); }
    /* TODO: add identifier */
;

%%

void yyerror(struct ast *ret, const char *msg) {
  (void) ret;
  fprintf(stderr, "%s\n", msg);
}
