#ifndef TURTLE_AST_H
#define TURTLE_AST_H

#include <stddef.h>
#include <stdbool.h>

// simple commands
enum ast_cmd {
  CMD_UP,
  CMD_DOWN,
  CMD_RIGHT,
  CMD_LEFT,
  CMD_HEADING,
  CMD_FORWARD,
  CMD_BACKWARD,
  CMD_POSITION,
  CMD_HOME,
  CMD_COLOR,
  CMD_PRINT,
};

// internal functions
enum ast_func {
  FUNC_COS,
  FUNC_RANDOM,
  FUNC_SIN,
  FUNC_SQRT,
  FUNC_TAN,
};

// kind of a node in the abstract syntax tree
enum ast_kind {
  KIND_CMD_SIMPLE,
  KIND_CMD_REPEAT,
  KIND_CMD_BLOCK,
  KIND_CMD_PROC,
  KIND_CMD_CALL,
  KIND_CMD_SET,

  KIND_COLOR,

  KIND_EXPR_FUNC,
  KIND_EXPR_VALUE,
  KIND_EXPR_UNOP,
  KIND_EXPR_BINOP,
  KIND_EXPR_BLOCK,
  KIND_EXPR_NAME,
  KIND_EXPR_PROC_NAME,
};

enum color {
  COLOR_BLACK,
  COLOR_WHITE,
  COLOR_RED,
  COLOR_GREEN,
  COLOR_BLUE,
  COLOR_YELLOW,
  COLOR_CYAN,
  COLOR_MAGENTA,
  COLOR_GREY,
};

#define AST_CHILDREN_MAX 3

// a node in the abstract syntax tree
struct ast_node {
  enum ast_kind kind; // kind of the node

  union {
    enum ast_cmd cmd;   // kind == KIND_CMD_SIMPLE
    double value;       // kind == KIND_EXPR_VALUE, for literals
    char op;            // kind == KIND_EXPR_BINOP or kind == KIND_EXPR_UNOP, for operators in expressions
    char *name;         // kind == KIND_EXPR_NAME, the name of procedures and variables
    enum ast_func func; // kind == KIND_EXPR_FUNC, a function
  } u;

  size_t children_count;  // the number of children of the node
  struct ast_node *children[AST_CHILDREN_MAX];  // the children of the node (arguments of commands, etc)
  struct ast_node *next;  // the next node in the sequence
};


// TODO: make some constructors to use in parser.y
// for example:
struct ast_node *make_expr_value(double value);

struct ast_node *make_cmd_forward(struct ast_node *expr);
struct ast_node *make_cmd_backward(struct ast_node *expr);
struct ast_node *make_cmd_left(struct ast_node *expr);
struct ast_node *make_cmd_right(struct ast_node *expr);
struct ast_node *make_cmd_up(struct ast_node *expr);
struct ast_node *make_cmd_down(struct ast_node *expr);
struct ast_node *make_cmd_heading(struct ast_node *expr);
struct ast_node *make_cmd_position(struct ast_node *expr, struct ast_node *expr2);
struct ast_node *make_cmd_home();
struct ast_node *make_cmd_color(struct ast_node *expr);
struct ast_node *make_cmd_print(struct ast_node *expr);
struct ast_node *make_cmd_set(struct ast_node *expr , struct ast_node *value);
struct ast_node *make_cmd_proc(struct ast_node *name, struct ast_node *block);
struct ast_node *make_cmd_call(struct ast_node *name);

struct ast_node *make_cmd_repeat(struct ast_node *expr, struct ast_node *cmd);
struct ast_node *make_cmd_block(struct ast_node *cmds);

struct ast_node *make_expr_binop(char op, struct ast_node *left, struct ast_node *right);
struct ast_node *make_expr_unop(char op, struct ast_node *expr);

struct ast_node *make_expr_func(enum ast_func func, struct ast_node *expr);
struct ast_node *make_expr_func_rdm(struct ast_node *expr1 , struct ast_node *expr2);

struct ast_node *make_color_node(struct ast_node *r, struct ast_node *g, struct ast_node *b);
struct ast_node *make_color_node_from_name(enum color name);

struct ast_node *make_name_node(char *name);
struct ast_node *make_proc_name_node(char *name);






char* func_to_string(enum ast_func func);
char* cmd_to_string(enum ast_cmd cmd);
void ast_print_node(struct ast_node *node);



// root of the abstract syntax tree
struct ast {
  struct ast_node *unit;
};

// do not forget to destroy properly! no leaks allowed!
void ast_destroy(struct ast *self);
void ast_destroy_node(struct ast_node *node);

/*
  struct which represent variables in Turtle's language
*/
struct var {
  char *name; //name of the variable
  double value; //variable's value
};

// Dynamic array of variables
struct vars {
  size_t size;
  size_t capacity;
  struct var *data;
};

// create the dynamic array of variables
struct vars *vars_create();
struct var *vars_get(struct vars *self, char *name);
void vars_set(struct vars *self, char *name, double value);
void vars_print(struct vars *self);
void vars_destroy(struct vars *self);


// create the procedure dynamic array ( a procedure is an alias to a command or a block of commands)

struct proc {
  char *name;
  struct ast_node *cmds;
};

struct procs {
  size_t size;
  size_t capacity;
  struct proc *data;
};

struct procs *procs_create();
struct proc *procs_get(struct procs *self, char *name);
void procs_set(struct procs *self, char *name, struct ast_node *cmds);
void procs_print(struct procs *self);
void procs_destroy(struct procs *self);

// the execution context
struct context {
  double x;
  double y;
  double angle;
  bool up;

  struct vars *vars;
  struct procs *procs;

};

// create an initial context
void context_create(struct context *self);
void context_destroy(struct context *self);

// print the tree as if it was a Turtle program
void ast_print(const struct ast *self);


// evaluate the tree and generate some basic primitives
void ast_eval(const struct ast *self, struct context *ctx);

/*

*/
double ast_eval_node(struct ast_node *node, struct context *ctx);
double ast_eval_cmd_simple(struct ast_node *node, struct context *ctx);
double ast_eval_cmd_repeat(struct ast_node *node, struct context *ctx);
double ast_eval_cmd_set(struct ast_node *node, struct context *ctx);
double ast_eval_cmd_proc(struct ast_node *node, struct context *ctx);
double ast_eval_cmd_call(struct ast_node *node, struct context *ctx);
double ast_eval_name(struct ast_node *node, struct context *ctx);
double ast_eval_cmd_block(struct ast_node *node, struct context *ctx);
double ast_eval_binop(struct ast_node *node, struct context *ctx);
double ast_eval_unop(struct ast_node *node, struct context *ctx);
double ast_eval_func(struct ast_node *node, struct context *ctx);


/*
  procedures 
*/
double deg_to_rad(double angle);
void set_angle(enum ast_cmd cmd ,double angle, struct context *ctx); // used for left, right and heading

void get_move_command(double x, double y,  struct context *ctx); // print LineTo Or MoveTo depending on the up state
void get_color_command(struct ast_node *node, struct context *ctx);


void move(double distance, struct context *ctx);
double get_random_value(double min, double max);


#endif /* TURTLE_AST_H */
