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

struct ast_node *make_cmd_block(struct ast_node *cmds){
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_BLOCK;
  node->children_count = 1;
  node->children[0] = cmds;
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

struct ast_node *make_expr_unop(char op, struct ast_node *expr)
{
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_EXPR_UNOP;
  node->u.op = op;
  node->children_count = 1;
  node->children[0] = expr;
  return node;
}

struct ast_node *make_expr_func(enum ast_func func, struct ast_node *expr)
{
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_EXPR_FUNC;
  node->u.func = func;
  node->children_count = 1;
  node->children[0] = expr;
  return node;
}

struct ast_node *make_expr_func_rdm(struct ast_node *expr1, struct ast_node *expr2)
{
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_EXPR_FUNC;
  node->u.func = FUNC_RANDOM;
  node->children_count = 2;
  node->children[0] = expr1;
  node->children[1] = expr2;
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

void ast_eval_node(struct ast_node *node, struct context *ctx) {
  switch (node->kind) {
  case KIND_CMD_SIMPLE:
    ast_eval_cmd_simple(node, ctx);
    break;
  case KIND_CMD_REPEAT:
    ast_eval_cmd_repeat(node, ctx);
    break;
  case KIND_CMD_BLOCK:
    ast_eval_cmd_block(node, ctx);
    break;
  case KIND_EXPR_BINOP:
    ast_eval_binop(node, ctx);
    break;
  case KIND_EXPR_UNOP:
 //   ast_eval_unop(node, ctx);
    break;
  case KIND_EXPR_FUNC:
//    ast_eval_func(node, ctx);
    break;
  default:
    break;
  }
}

void ast_eval_cmd_simple(struct ast_node *node, struct context *ctx) {
  switch (node->u.cmd) {
  case CMD_UP:
    break;
  case CMD_DOWN:

    break;
  case CMD_LEFT:

    break;
  case CMD_RIGHT:
    break;
  case CMD_HOME:
    ctx->x = 0;
    ctx->y = 0;
    break;
  case CMD_HEADING:
    break;
  case CMD_POSITION:
    ctx->x = node->children[0]->u.value;
    ctx->y = node->children[1]->u.value;
    break;
  case CMD_COLOR:
    break;
  case CMD_PRINT:
    break;
  }
}

void ast_eval_cmd_repeat(struct ast_node *node, struct context *ctx) {
  int i;
  for (i = 0; i < node->children[0]->u.value; i++) {
    ast_eval_node(node->children[1], ctx);
  }
}

void ast_eval_cmd_block(struct ast_node *node, struct context *ctx) {
  int i;
  for (i = 0; i < node->children_count; i++) {
    ast_eval_node(node->children[i], ctx);
  }
}

void ast_eval_binop(struct ast_node *node, struct context *ctx) {
  switch (node->u.op) {
  case '+':
    node->u.value = node->children[0]->u.value + node->children[1]->u.value;
    break;
  case '-':
    node->u.value = node->children[0]->u.value - node->children[1]->u.value;
    break;
  case '*':
    node->u.value = node->children[0]->u.value * node->children[1]->u.value;
    break;
  case '/':
    node->u.value = node->children[0]->u.value / node->children[1]->u.value;
    break;
  }
}



void ast_eval(const struct ast *self, struct context *ctx) {


}

/*
 * print
 */



char* func_to_string(enum ast_func func)
{
  switch(func)
  {

    case FUNC_SIN:
      return "sin";
    case FUNC_COS:
      return "cos";
    case FUNC_TAN:
      return "tan";
    case FUNC_SQRT:
      return "sqrt";
    case FUNC_RANDOM:
      return "random";
    default:
      return "unknown function";
  }

}



char*  cmd_to_string(enum ast_cmd cmd) {
  switch (cmd) {
    case CMD_FORWARD:
      return "forward";
    case CMD_BACKWARD:
      return "backward";
    case CMD_LEFT:
      return "left";
    case CMD_RIGHT:
      return "right";
    case CMD_UP:
      return "up";
    case CMD_DOWN:
      return "down";
    case CMD_HEADING:
      return "heading";
    case CMD_POSITION:
      return "position";
    case CMD_HOME:
      return "home";
    case CMD_COLOR:
      return "color";
    case CMD_PRINT:
      return "print";
    default:
      return "unknown";
  }
}

void print_childrens(struct ast_node *node) {
  for (int i = 0; i < node->children_count; i++) {
    ast_print_node(node->children[i]);
  }
}


void ast_print_node(struct ast_node *node)
{
  if (node == NULL) {
    return;
  }
  switch (node->kind) {
    
    case KIND_CMD_SIMPLE:
      printf("%s ", cmd_to_string(node->u.cmd));
      print_childrens(node);
      break;
    case KIND_CMD_REPEAT:
      printf("repeat ");
      ast_print_node(node->children[0]);
      printf(" ");
      ast_print_node(node->children[1]);
      break;
    case KIND_EXPR_BINOP:
      ast_print_node(node->children[0]);
      printf(" %c ", node->u.op);
      ast_print_node(node->children[1]);
      break;
    case KIND_EXPR_UNOP:
      printf("%c ", node->u.op);
      print_childrens(node);
      break;
    case KIND_EXPR_FUNC:
      printf("%s(", func_to_string(node->u.func));
      print_childrens(node);
      printf(")");
      break;
    case KIND_EXPR_VALUE:
      printf("%f", node->u.value);
      break;  
    case KIND_EXPR_NAME:
      printf("%s", node->u.name);
      break;
    case KIND_CMD_BLOCK:
      printf("{\n\n");
      print_childrens(node);
      printf("}");
      break;
    default:
      break;
  }
  printf("\n");
  ast_print_node(node->next);

}







void ast_print(const struct ast *self) {
    ast_print_node(self->unit);
  }

