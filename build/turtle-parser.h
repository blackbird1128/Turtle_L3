/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_USERS_JEREMYPERRIN_DOCUMENTS_FAC_3EME_ANNEE_CMI_INFORMATIQUE_SEMESTRE_6_ANALYSE_SYNTAXIQUE_PROJET_TURTLE_L3_BUILD_TURTLE_PARSER_H_INCLUDED
# define YY_YY_USERS_JEREMYPERRIN_DOCUMENTS_FAC_3EME_ANNEE_CMI_INFORMATIQUE_SEMESTRE_6_ANALYSE_SYNTAXIQUE_PROJET_TURTLE_L3_BUILD_TURTLE_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    VALUE = 258,                   /* "value"  */
    NAME = 259,                    /* "name"  */
    RED = 260,                     /* "red"  */
    GREEN = 261,                   /* "green"  */
    BLUE = 262,                    /* "blue"  */
    CYAN = 263,                    /* "cyan"  */
    MAGENTA = 264,                 /* "magenta"  */
    YELLOW = 265,                  /* "yellow"  */
    BLACK = 266,                   /* "black"  */
    GREY = 267,                    /* "grey"  */
    WHITE = 268,                   /* "white"  */
    FCT_SIN = 269,                 /* "sin"  */
    FCT_COS = 270,                 /* "cos"  */
    FCT_TAN = 271,                 /* "tan"  */
    FCT_SQRT = 272,                /* "sqrt"  */
    FCT_RANDOM = 273,              /* "random"  */
    KW_FORWARD = 274,              /* "forward"  */
    KW_BACKWARD = 275,             /* "backward"  */
    KW_POSITION = 276,             /* "position"  */
    KW_RIGHT = 277,                /* "right"  */
    KW_LEFT = 278,                 /* "left"  */
    KW_PRINT = 279,                /* "print"  */
    KW_HEADING = 280,              /* "heading"  */
    KW_UP = 281,                   /* "up"  */
    KW_DOWN = 282,                 /* "down"  */
    KW_COLOR = 283,                /* "color"  */
    KW_HOME = 284,                 /* "home"  */
    KW_REPEAT = 285,               /* "repeat"  */
    UNARY_MINUS = 286              /* UNARY_MINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 19 "turtle-parser.y"

  double value;
  char *name;
  struct ast_node *node;

#line 101 "/Users/jeremyperrin/Documents/FAC/3eme_Annee_CMI_Informatique/semestre_6/Analyse_Syntaxique/Projet/Turtle_L3/build/turtle-parser.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (struct ast *ret);


#endif /* !YY_YY_USERS_JEREMYPERRIN_DOCUMENTS_FAC_3EME_ANNEE_CMI_INFORMATIQUE_SEMESTRE_6_ANALYSE_SYNTAXIQUE_PROJET_TURTLE_L3_BUILD_TURTLE_PARSER_H_INCLUDED  */
