#include "turtle-ast.h"

#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define PI 3.141592653589793


/*
  Implementation of procedures that create nodes
  --> Return an ast_node value considereing its parameters
*/

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

struct ast_node *make_cmd_proc(struct ast_node *name, struct ast_node *block)
{
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_PROC;
  node->children_count = 2;
  node->children[0] = name;
  node->children[1] = block;
  return node;
}

struct ast_node *make_cmd_call(struct ast_node *name)
{
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_CALL;
  node->children_count = 1;
  node->children[0] = name;
  return node;
}


struct ast_node *make_cmd_block(struct ast_node *cmds){
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_BLOCK;
  node->children_count = 1;
  node->children[0] = cmds;
  return node;
}

struct ast_node *make_name_node(char *name) {
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_EXPR_NAME;
  node->u.name = strcpy(calloc(strlen(name) + 1, sizeof(char)), name);
  return node;
}



struct ast_node *make_cmd_set(struct ast_node *expr, struct ast_node *value){
  struct ast_node *node = calloc(1, sizeof(struct ast_node));
  node->kind = KIND_CMD_SET;
  node->children_count = 2;
  node->children[0] = expr;
  node->children[1] = value;
  return node;
}

/* Vars : */

/*
  Constructs an array of struct var
  Returns a struct vars variable
*/
struct vars *vars_create()
{
  struct vars *vars = calloc(1, sizeof(struct vars));
  vars->data = calloc(10, sizeof(struct var));
  vars->size = 0;
  vars->capacity = 10;
  return vars;
}

/*
  Get a variable in a struct vars variable considering its name
  If it is not present --> returns NULL
*/
struct var *vars_get(struct vars *self, char *name)
{
  for (int i = 0; i < self->size; i++) {
    if (strcmp(self->data[i].name, name) == 0) {
      return &self->data[i];
    }
  }
  return NULL;
}

/*
  Set a value in a struct vars variable considering its name
  If it is not present --> does nothing
*/
void vars_set(struct vars *self, char *name, double value)
{
  struct var *var = vars_get(self, name);
  if (var == NULL) {
    if (self->size == self->capacity) {
      self->capacity *= 2;
      self->data = realloc(self->data, self->capacity * sizeof(struct var));
    }
    var = &self->data[self->size++];
    var->name = name;
  }
  var->value = value;
}

/*
  Print a struct vars variable
*/
void vars_print(struct vars *self)
{
  for (int i = 0; i < self->size; i++) {
    printf("%s = %f\n", self->data[i].name, self->data[i].value);
  }
}

/*
  Destroy a struct vars variable
*/
void vars_destroy(struct vars *self)
{
  for (int i = 0; i < self->size; i++) {
    free(self->data[i].name);
  }
  free(self->data);
  free(self);
}

/* Procs : */


struct procs *procs_create()
{
  struct procs *procs = calloc(1, sizeof(struct procs));
  procs->data = calloc(10, sizeof(struct proc));
  procs->size = 0;
  procs->capacity = 10;
  return procs;
}

struct proc *procs_get(struct procs *self, char *name)
{
  for (int i = 0; i < self->size; i++) {
    if (strcmp(self->data[i].name, name) == 0) {
      return &self->data[i];
    }
  }
  return NULL;
}

void procs_set(struct procs *self, char *name, struct ast_node *cmds)
{
  struct proc *proc = procs_get(self, name);
  if (proc == NULL) {
    if (self->size == self->capacity) {
      self->capacity *= 2;
      self->data = realloc(self->data, self->capacity * sizeof(struct proc));
    }
    proc = &self->data[self->size++];
    proc->name = name;
  }
  proc->cmds = cmds;

}

void procs_print(struct procs *self)
{
  for (int i = 0; i < self->size; i++) {
    printf("%s:\n", self->data[i].name);
    ast_print_node(self->data[i].cmds);
  }
}

void procs_destroy(struct procs *self)
{
  for (int i = 0; i < self->size; i++) {
    ast_destroy_node(self->data[i].cmds);
  }
  free(self->data);
  free(self);
}




/* Parser : */


/*
  Implementation of  procedures that create nodes
  --> Return an ast_node value considering its parameters
*/

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

/*
  Create a struct ast_node which handles color node creation by name
  -step 1 : create many node for each properties of the color (RGB) 
  -step 2 : calls make_color_node procedure to return a color node with the corresponding RGB values
*/
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
  default:
    printf("Unknown color\n");
    exit(-1);
  }


  return NULL; // Remove warning
}

/*
  Destroy the abstract syntax tree
*/
void ast_destroy(struct ast *self) {
  ast_destroy_node(self->unit);
}

void ast_destroy_node(struct ast_node *node){
  if(node==NULL){
    return;
  }
  for(size_t i = 0; i<node->children_count; i++){
    ast_destroy_node(node->children[i]);
    free(node->children[i]);
  }
  ast_destroy_node(node->next);
}

/*
 * Creates a context and sets its default values
 */
void context_create(struct context *self) {
  self->x = self->y = 0;
  self->angle = 0;
  self->up = false;

  self->vars = calloc(1, sizeof(struct vars));
  vars_set(self->vars,"PI", 3.14159265358979323846);
  vars_set(self->vars, "SQRT2", 1.41421356237309504880);
  vars_set(self->vars, "SQRT3", 1.73205080756887729353);
  self->procs = calloc(1, sizeof(struct procs));
}

void context_destroy(struct context *self) {
  vars_destroy(self->vars);
  procs_destroy(self->procs);
  free(self);
}


/*
  Sets the angle which will make the pen with the context
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

/*
  Convert degree value into radian and returns its value
*/
double deg_to_rad(double angle) {
  return angle * PI / 180.0;
}

/*
  To do
*/
void move(double dist, struct context *ctx) {
  double angle = ctx->angle;
  ctx->x -= dist * cos(deg_to_rad(angle));
  ctx->y -= dist * sin(deg_to_rad(angle));
}

/*
  Print the actions of the pen (MoveTo or LineTo)
*/
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

/*
  Draw a random value between min and max (both included)
*/
double get_random_value(double min, double max)
{
  return min + (double)rand() / ((double)RAND_MAX / (max - min));
}

/*
  The procedure works as the following : 
  -Like ast_print_node, it will check the kind of the node and calls the proper procedure to evaluate the asociated nodes
*/
double ast_eval_node(struct ast_node *node, struct context *ctx) {
  double result = 0;
  switch (node->kind) {
  case KIND_CMD_SIMPLE:
    result = ast_eval_cmd_simple(node, ctx);
    break;
  case KIND_CMD_REPEAT:
    result = ast_eval_cmd_repeat(node, ctx);
    break;
  case KIND_CMD_SET:
    result = ast_eval_cmd_set(node, ctx); // define ast_eval_cmd_set
    break;
  case KIND_CMD_CALL:
    result = ast_eval_cmd_call(node, ctx);
    break;
  case KIND_CMD_PROC:
    result = ast_eval_cmd_proc(node, ctx);
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
  case KIND_EXPR_NAME:
    result = ast_eval_name(node, ctx); // DEFINE ast_eval_name
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

/*
  Evaluate the name of a variable
  If the variable doesn't exists prints an appropriate message
*/
double ast_eval_name(struct ast_node *node, struct context *ctx) {
  struct var* v =  vars_get(ctx->vars, node->u.name);
  if(v == NULL) {
    printf("Undefined variable %s\n", node->u.name);
    exit(-1);
  }
  return v->value;
}


/*
  Evaluates command sets (handles procs)
*/
double ast_eval_cmd_set(struct ast_node *node, struct context *ctx) {
  vars_set(ctx->vars, node->children[0]->u.name, ast_eval_node(node->children[1], ctx));
  return NAN;
}

/*
  Evaluates simple commands
*/
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
  return NAN;
}

/*
  Evaluates repeat loops
*/
double ast_eval_cmd_repeat(struct ast_node *node, struct context *ctx) {
  int i;
  for (i = 0; i < node->children[0]->u.value; i++) {
    ast_eval_node(node->children[1], ctx);
  }
  return NAN;
}

/*
  Evaluates repeat blocks
*/
double ast_eval_cmd_block(struct ast_node *node, struct context *ctx) {
  int i;
  for (i = 0; i < node->children_count; i++) {
    ast_eval_node(node->children[i], ctx);
  }
  return NAN;
}

double ast_eval_cmd_call(struct ast_node *node, struct context *ctx) {
  struct proc *proc =  procs_get(ctx->procs, node->children[0]->u.name);
  if(proc == NULL) {
    printf("Undefined procedure %s\n", node->children[0]->u.name);
    exit(-1);
  }
  return ast_eval_node(proc->cmds, ctx);
}

double ast_eval_cmd_proc(struct ast_node *node, struct context *ctx) {
  if(procs_get(ctx->procs, node->children[0]->u.name) != NULL) {
    printf("Procedure %s already defined\n", node->children[0]->u.name);
    exit(-1);
  }
  procs_set(ctx->procs, node->children[0]->u.name, node->children[1]);
  return NAN;
}

/*
  Evaluates expression with a binary operator (+,-,*,/)
*/
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
  default:
    printf("Unknown operator %c\n", node->u.op);
    exit(-1);
  }
  return NAN;
}

/*
  Evaluates expression with a unary operator (+,-)
*/
double ast_eval_unop(struct ast_node *node, struct context *ctx) {
  switch (node->u.op) {
  case '-':
    return -ast_eval_node(node->children[0], ctx);
  case '+':
    return +ast_eval_node(node->children[0], ctx);
    break;
  default:
    printf("Unknown unary operator %c\n", node->u.op);
    exit(-1);
  }
  return NAN; // Remove warning
}

/*
  Evaluates functions
*/
double ast_eval_func(struct ast_node *node, struct context *ctx) {
  double result = NAN;
  switch (node->u.func) {
  case FUNC_RANDOM:;

    double min = ast_eval_node(node->children[0], ctx);
    double max = ast_eval_node(node->children[1], ctx);
    if(min > max){
      printf("Error: min > max for random\n");
      exit(-1);
    }
    result = get_random_value(min, max);
    break;
  case FUNC_COS:
    result = cos(deg_to_rad(ast_eval_node(node->children[0], ctx)));
    break;
  case FUNC_SIN:
    result = sin(deg_to_rad(ast_eval_node(node->children[0], ctx)));
    break;
  case FUNC_TAN:
    result =   tan(deg_to_rad(ast_eval_node(node->children[0], ctx)));
    break;
  case FUNC_SQRT:;
    double x = ast_eval_node(node->children[0], ctx);
    if(x < 0) {
      printf("Error: sqrt of negative number\n");
      exit(-1);
    }
    result = sqrt(x);
    break;  
  }
  return result;
}


void ast_eval(const struct ast *self, struct context *ctx) {
  ast_eval_node(self->unit, ctx);
}

/*
  Get the name of functions
  Return the conventional name of functions into a string
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


/*
  Get the name of commands
  Return the conventional name of commands into a string 
*/
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

/*
  Prints the children of a node
*/
void print_childrens(struct ast_node *node) {
  for(int i = 0; i < node->children_count; i++) {
    ast_print_node(node->children[i]);
  }
}

/*
  Print a node according to its kind
*/
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
    case KIND_CMD_SET:
      printf("set ");
      ast_print_node(node->children[0]);
      printf(" ");
      ast_print_node(node->children[1]);
      break;
    case KIND_CMD_PROC:
      printf("proc ");
      ast_print_node(node->children[0]);
      printf(" ");
      ast_print_node(node->children[1]);
      break;
    case KIND_CMD_CALL:
      printf("call ");
      ast_print_node(node->children[0]);
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
    default:
      printf("unknown or unused node\n");
      exit(-1);
      break;
  }
  printf("\n");
  ast_print_node(node->next);

}


void ast_print(const struct ast *self) {
  ast_print_node(self->unit);
}