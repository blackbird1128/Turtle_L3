#include <assert.h>
#include <stdlib.h>
#include <time.h>

#include "turtle-ast.h"
#include "turtle-lexer.h"
#include "turtle-parser.h"

int main() {

  srand(time(NULL));

  struct ast root;
  int ret = yyparse(&root);

  if (ret != 0) {
    return ret;
  }

  yylex_destroy();

  assert(root.unit);

  struct context ctx;
  context_create(&ctx);
  printf("Context: ");
  printf("X: %f\nY: %f\n", ctx.x, ctx.y);
  printf("UP ? %d\n", ctx.up);
  printf("Angle: %f\n", ctx.angle);

  ast_eval(&root, &ctx);
  //ast_print(&root);

  ast_destroy(&root);

  return ret;
}
