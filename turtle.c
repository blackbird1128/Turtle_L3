#include <assert.h>
#include <stdlib.h>
#include <time.h>

#include "turtle-ast.h"
#include "turtle-lexer.h"
#include "turtle-parser.h"

int main() {

  srand(time(NULL));


  //TESTS TO DEBUG
  // struct ast test;
  // struct ast_node node_1;
  // struct ast_node node_2;
  // struct ast_node node_3;

  // test.unit = &node_1;

  // node_1.children_count = 2;
  // node_2.children_count = node_3.children_count = 0;

  // node_1.children[0] = &node_2;
  // node_1.children[1] = &node_3;

  // node_1.kind = KIND_EXPR_FUNC;
  // node_1.u.func = FUNC_TAN;

  // node_2.kind = KIND_EXPR_VALUE;
  // node_2.u.value = 80;
  // node_3.kind = KIND_CMD_SIMPLE;
  // node_3.u.cmd = CMD_PRINT;

  // node_1.next = node_2.next = node_3.next = NULL;

  // ast_print(&test);


  struct ast root;
  int ret = yyparse(&root);

  if (ret != 0) {
    return ret;
  }

  yylex_destroy();

  assert(root.unit);

  struct context ctx;
  context_create(&ctx);

  ast_eval(&root, &ctx);
  ast_print(&root);

  ast_destroy(&root);

  return ret;
}
