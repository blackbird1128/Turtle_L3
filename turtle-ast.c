#include "turtle-ast.h"

#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define PI 3.141592653589793

struct ast_node *make_expr_value(double value) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_EXPR_VALUE;
  node->u.value = value;
  return node;
}

struct ast_node *make_cmd_forward(struct ast_node *expr){
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = CMD_FORWARD;
  node->children_count = 1;
  node->children[0] = expr;
  return node;
}

struct ast_node *make_cmd_backward(struct ast_node *expr){
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = CMD_BACKWARD;
  node->children_count = 1;
  node->children[0] = expr;
  return node;
}

struct ast_node *make_cmd_left(struct ast_node *expr){
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = CMD_LEFT;
  node->children_count = 1;
  node->children[0] = expr;
  return node;
}

struct ast_node *make_cmd_right(struct ast_node *expr){
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = CMD_RIGHT;
  node->children_count = 1;
  node->children[0] = expr;
  return node;
}

struct ast_node *make_cmd_up(struct ast_node *expr){
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = CMD_UP;
  node->children_count = 1;
  node->children[0] = expr;
  return node;
}

struct ast_node *make_cmd_down(struct ast_node *expr){
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = CMD_DOWN;
  node->children_count = 1;
  node->children[0] = expr;
  return node;
}

struct ast_node *make_cmd_heading(struct ast_node *expr){
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = CMD_HEADING;
  node->children_count = 1;
  node->children[0] = expr;
  return node;
}

struct ast_node *make_cmd_position(struct ast_node *expr , struct ast_node *expr2){
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = CMD_POSITION;
  node->children_count = 2;
  node->children[0] = expr;
  node->children[1] = expr2;
  return node;
}

struct ast_node *make_cmd_home(){
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = CMD_HOME;
  node->children_count = 0;
  return node;
}

struct ast_node *make_cmd_color(struct ast_node *expr)
{
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = CMD_COLOR;
  node->children_count = 1;
  node->children[0] = expr;
  return node;
}

struct ast_node *make_cmd_print(struct ast_node *expr)
{
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_SIMPLE;
  node->u.cmd = CMD_PRINT;
  node->children_count = 1;
  node->children[0] = expr;
  return node;
}

struct ast_node *make_cmd_repeat(struct ast_node *expr, struct ast_node *cmd){
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_REPEAT;
  node->children_count = 2;
  node->children[0] = expr;
  node->children[1] = cmd;
  return node;
}

struct ast_node *make_expr_binop(char op, struct ast_node *left, struct ast_node *right)
{
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_EXPR_BINOP;
  node->u.op = op;
  node->children_count = 2;
  node->children[0] = left;
  node->children[1] = right;
  return node;
}

void ast_destroy(struct ast *self) {
  ast_destroy_node(self->unit);
  free(self);
}

static void ast_destroy_node(struct ast_node *node){
  for(size_t i = 0; i<node->children_count; i++){
    ast_destroy_node(node->children[i]);
    free(node->children[i]);
  }
}

/*
 * context
 */

void context_create(struct context *self) {
  self->x = self->y = 500;
  self->angle = 0;
  self->up = false;
}

/*
 * eval
 */

void ast_eval(const struct ast *self, struct context *ctx) {

}

/*
 * print
 */

void ast_print(const struct ast *self) {
  ast_print_node(self->unit);
}

static void ast_print_node(const struct ast_node *node){
  if(node==NULL){
    fprintf(stderr,"\n");
    return;
  }
  
  switch(node->kind){
    case KIND_CMD_SIMPLE:
      switch(node->u.cmd){
        case CMD_UP:
          fprintf(stderr,"up ");
          break;
        case CMD_DOWN:
          fprintf(stderr,"down ");
          break;
        case CMD_RIGHT:
          fprintf(stderr,"right ");
          break;
        case CMD_LEFT:
          fprintf(stderr,"left ");
          break;
        case CMD_HEADING:
          fprintf(stderr,"heading ");
          break;
        case CMD_FORWARD:
          fprintf(stderr,"forward ");
          break;
        case CMD_BACKWARD:
          fprintf(stderr,"backward ");
          break;
        case CMD_POSITION:
          fprintf(stderr,"position ");
          break;
        case CMD_HOME:
          fprintf(stderr,"home ");
          break;
        case CMD_COLOR:
          fprintf(stderr,"color ");
          break;
        case CMD_PRINT:
          fprintf(stderr,"print ");
          break;
      }
      break;
      case KIND_EXPR_VALUE:
        fprintf(stderr,"%f ",node->u.value);
        break;
      case KIND_EXPR_BINOP:
        fprintf(stderr,"%c ",node->u.op);
        break;
      case KIND_EXPR_UNOP:
        fprintf(stderr,"%c ",node->u.op);
        break;
      case KIND_EXPR_NAME:
        fprintf(stderr,"%s ",node->u.name);
        break;
      case KIND_EXPR_FUNC:
        switch(node->u.func){
          case FUNC_COS:
            fprintf(stderr,"cos ");
            break;
          case FUNC_SIN:
            fprintf(stderr,"sin ");
            break;
          case FUNC_TAN:
            fprintf(stderr,"tan ");
            break;
          case FUNC_RANDOM:
            fprintf(stderr,"random ");
            break;
          case FUNC_SQRT:
            fprintf(stderr,"sqrt ");
            break;
        }
        break;
  }


  for(size_t i = 0; i<node->children_count; i++){
    ast_print_node(node->children[i]);
  }
  //Recursively printing the following nodes
  ast_print_node(node->next);
}
