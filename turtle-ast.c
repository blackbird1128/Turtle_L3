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

struct ast_node *make_color_node(struct ast_node *r, struct ast_node *g, struct ast_node *b)
{
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_COLOR;
  node->children_count = 3;
  node->children[0] = r;
  node->children[1] = g;
  node->children[2] = b;
  return node;
}


struct ast_node *make_color_node_from_name(enum color col)
{
  struct ast_node *node_r = calloc(1, sizeof(struct ast_node));
  node_r->kind = KIND_EXPR_VALUE;
  node_r->children_count = 0;

  struct ast_node *node_g = calloc(1, sizeof(struct ast_node));
  node_g->kind = KIND_EXPR_VALUE;
  node_g->children_count = 0;


  struct ast_node *node_b = calloc(1, sizeof(struct ast_node));
  node_b->kind = KIND_EXPR_VALUE;
  node_b->children_count = 0;

  switch (col)
  {
  case COLOR_BLACK:
    node_r->u.value = 0;
    node_g->u.value = 0;
    node_b->u.value = 0;
    return make_color_node(node_r, node_g, node_b);
  case COLOR_WHITE:
    node_r->u.value = 1;
    node_g->u.value = 1;
    node_b->u.value = 1;
    return make_color_node(node_r, node_g, node_b);
  case COLOR_RED:
    node_r->u.value = 1;
    node_g->u.value = 0;
    node_b->u.value = 0;
    return make_color_node(node_r, node_g, node_b);
  case COLOR_GREEN:
    node_r->u.value = 0;
    node_g->u.value = 1;
    node_b->u.value = 0;
    return make_color_node(node_r, node_g, node_b);
  case COLOR_BLUE:
    node_r->u.value = 0;
    node_g->u.value = 0;
    node_b->u.value = 1;
    return make_color_node(node_r, node_g, node_b);
  case COLOR_YELLOW:
    node_r->u.value = 1;
    node_g->u.value = 1;
    node_b->u.value = 0;
    return make_color_node(node_r, node_g, node_b);
  case COLOR_CYAN:
    node_r->u.value = 0;
    node_g->u.value = 1;
    node_b->u.value = 1;
    return make_color_node(node_r, node_g, node_b);
  case COLOR_MAGENTA:
    node_r->u.value = 1;
    node_g->u.value = 0;
    node_b->u.value = 1;
    return make_color_node(node_r, node_g, node_b);
  case COLOR_GREY:
    node_r->u.value = 0.5;
    node_g->u.value = 0.5;
    node_b->u.value = 0.5;
    return make_color_node(node_r, node_g, node_b);
  }
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
  self->x = self->y = 0;
  self->angle = 0;
  self->up = false;
}

/*
 * eval
 */



void set_angle(enum ast_cmd cmd, double angle , struct context *ctx) {
  double new_angle = ctx->angle;
  switch (cmd) {
    case CMD_LEFT:
      new_angle =  fmod( new_angle + angle  , 360.0);
      break;
    case CMD_RIGHT:
      new_angle = fmod( new_angle - angle  , 360.0);
      if(new_angle < 0) {
        new_angle += 360;
      }
      ctx->angle += angle;
      break;
    default:
      break;
  }
} 

double deg_to_rad(double angle) {
  return angle * PI / 180.0;
}
void move(double dist, struct context *ctx) {
  double angle = ctx->angle;
  ctx->x -= dist * cos(deg_to_rad(angle));
  ctx->y -= dist * sin(deg_to_rad(angle));
}

void get_move_command(double x, double y,  struct context *ctx)
{
  if(ctx->up)
  {
    printf("MoveTo %f %f\n", y, x);
  }
  else
  {
    printf("LineTo %f %f\n", y, x);
  }
}


double get_random_value(double min, double max)
{
  return min + (double)rand() / ((double)RAND_MAX / (max - min));
}


double ast_eval_node(struct ast_node *node, struct context *ctx) {
  double result = 0;
  switch (node->kind) {
  case KIND_CMD_SIMPLE:
    result = ast_eval_cmd_simple(node, ctx);
    break;
  case KIND_CMD_REPEAT:
    result = ast_eval_cmd_repeat(node, ctx);
    break;
  case KIND_CMD_BLOCK:
    result =  ast_eval_cmd_block(node, ctx);
    break;
  case KIND_EXPR_BINOP:
    result =  ast_eval_binop(node, ctx);
    break;
  case KIND_EXPR_UNOP:
    result = ast_eval_unop(node, ctx);
    break;
  case KIND_EXPR_FUNC:
    result = ast_eval_func(node, ctx);
    break;
  case KIND_EXPR_VALUE:
    result =  node->u.value;
    break;
  case KIND_COLOR:
    printf("Color %f %f %f\n", ast_eval_node(node->children[0], ctx), ast_eval_node(node->children[1], ctx), ast_eval_node(node->children[2], ctx));
    break;
  default:
    break;
  }
  if(node->next != NULL) {
    ast_eval_node(node->next, ctx);
  }
  return result;


}

double ast_eval_cmd_simple(struct ast_node *node, struct context *ctx) {
  switch (node->u.cmd) {
  case CMD_FORWARD:

    move(ast_eval_node(node->children[0], ctx), ctx);
    get_move_command(ctx->x, ctx->y, ctx);
    return NAN;
     // y axis is inverted
    break;
  case CMD_BACKWARD:
    move(-ast_eval_node(node->children[0], ctx), ctx);
    get_move_command(ctx->x, ctx->y, ctx);
    return NAN;
    break;
  case CMD_UP:
    ctx->up = true;
    return NAN;
    break;
  case CMD_DOWN:
    ctx->up = false;
    return NAN;
    break;
  case CMD_LEFT:
    set_angle(node->u.cmd, ast_eval_node(node->children[0], ctx), ctx);
    return NAN;
    break;
  case CMD_RIGHT:
    set_angle(node->u.cmd, ast_eval_node(node->children[0], ctx), ctx);
    return NAN;
    break;
  case CMD_HOME:
    ctx->x = 0;
    ctx->y = 0;
    printf("MoveTo 0.0, 0.0\n");
    return NAN;
    break;

  case CMD_HEADING:
    ctx->angle = node->children[0]->u.value;
    return NAN;
    break;
  case CMD_POSITION:
    ctx->x = ast_eval_node(node->children[0], ctx);
    ctx->y = ast_eval_node(node->children[1], ctx);
    return NAN;
    break;
  case CMD_COLOR:
    ast_eval_node(node->children[0], ctx);
    break;
  case CMD_PRINT: // we already displayed the message
    return NAN;
    break;
  }
}

double ast_eval_cmd_repeat(struct ast_node *node, struct context *ctx) {
  int i;
  for (i = 0; i < node->children[0]->u.value; i++) {
    ast_eval_node(node->children[1], ctx);
  }
}

double ast_eval_cmd_block(struct ast_node *node, struct context *ctx) {
  int i;
  for (i = 0; i < node->children_count; i++) {
    ast_eval_node(node->children[i], ctx);
  }
}

double ast_eval_binop(struct ast_node *node, struct context *ctx) {
  switch (node->u.op) {
  case '+':
    return ast_eval_node(node->children[0], ctx) + ast_eval_node(node->children[1], ctx);
    break;
  case '-':
    return ast_eval_node(node->children[0], ctx) - ast_eval_node(node->children[1], ctx);
    break;
  case '*':
    return ast_eval_node(node->children[0], ctx) * ast_eval_node(node->children[1], ctx);
    break;
  case '/':
    return ast_eval_node(node->children[0], ctx) / ast_eval_node(node->children[1], ctx);
    break;
  }
}

double ast_eval_unop(struct ast_node *node, struct context *ctx) {
  switch (node->u.op) {
  case '-':
    return -ast_eval_node(node->children[0], ctx);
  case '+':
    return +ast_eval_node(node->children[0], ctx);
    break;
  }
}

double ast_eval_func(struct ast_node *node, struct context *ctx) {
  switch (node->u.func) {
  case FUNC_RANDOM:
    return  get_random_value( ast_eval_node(node->children[0], ctx), ast_eval_node(node->children[1], ctx));
    break;
  case FUNC_COS:
    return cos(deg_to_rad(ast_eval_node(node->children[0], ctx)));
    break;
  case FUNC_SIN:
    return sin(deg_to_rad(ast_eval_node(node->children[0], ctx)));
    break;
  case FUNC_TAN:
    return  tan(deg_to_rad(ast_eval_node(node->children[0], ctx)));
    break;
  case FUNC_SQRT:
    return  sqrt(ast_eval_node(node->children[0], ctx));
    break;  
  }
}



void ast_eval(const struct ast *self, struct context *ctx) {
  ast_eval_node(self->unit, ctx);

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
      if (node->u.cmd == CMD_COLOR)
      {
        printf("color (");
        ast_print_node(node->children[0]);
        printf(")\n");
        break;
      }
      else
      {
        printf("%s\n", cmd_to_string(node->u.cmd));
      }

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
    case KIND_COLOR:
      ast_print_node(node->children[0]);
      ast_print_node(node->children[1]);
      ast_print_node(node->children[2]);
      break;
  }
  printf("\n");
  ast_print_node(node->next);

}







void ast_print(const struct ast *self) {
    ast_print_node(self->unit);
  }

