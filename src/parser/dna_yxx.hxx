/* A Bison parser, made by GNU Bison 3.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

#ifndef YY_DNAYY_DNA_YXX_HXX_INCLUDED
# define YY_DNAYY_DNA_YXX_HXX_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int dnayydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    SIGNED_INTEGER = 258,
    UNSIGNED_INTEGER = 259,
    FLOAT_REAL = 260,
    UNQUOTED_STRING = 261,
    QUOTED_STRING = 262,
    STORE_SUIT_POINT = 263,
    GROUP = 264,
    VISGROUP = 265,
    VIS = 266,
    DNA_STREET_POINT = 267,
    DNA_FRONT_DOOR_POINT = 268,
    DNA_SIDE_DOOR_POINT = 269,
    DNA_COGHQ_IN_POINT = 270,
    DNA_COGHQ_OUT_POINT = 271,
    SUIT_EDGE = 272,
    BATTLE_CELL = 273,
    PROP = 274,
    POS = 275,
    HPR = 276,
    SCALE = 277,
    CODE = 278,
    COLOR = 279,
    MODEL = 280,
    STORE_NODE = 281,
    SIGN = 282,
    BASELINE = 283,
    WIDTH = 284,
    HEIGHT = 285,
    STOMP = 286,
    STUMBLE = 287,
    INDENT = 288,
    WIGGLE = 289,
    KERN = 290,
    TEXT = 291,
    LETTERS = 292,
    STORE_FONT = 293,
    FLAT_BUILDING = 294,
    WALL = 295,
    WINDOWS = 296,
    COUNT = 297,
    CORNICE = 298,
    LANDMARK_BUILDING = 299,
    TITLE = 300,
    ARTICLE = 301,
    BUILDING_TYPE = 302,
    DOOR = 303,
    STORE_TEXTURE = 304,
    STREET = 305,
    TEXTURE = 306,
    GRAPHIC = 307,
    HOODMODEL = 308,
    PLACEMODEL = 309,
    FLAGS = 310,
    NODE = 311,
    FLAT_DOOR = 312,
    ANIM = 313,
    CELL_ID = 314,
    ANIM_PROP = 315,
    INTERACTIVE_PROP = 316,
    ANIM_BUILDING = 317
  };
#endif
/* Tokens.  */
#define SIGNED_INTEGER 258
#define UNSIGNED_INTEGER 259
#define FLOAT_REAL 260
#define UNQUOTED_STRING 261
#define QUOTED_STRING 262
#define STORE_SUIT_POINT 263
#define GROUP 264
#define VISGROUP 265
#define VIS 266
#define DNA_STREET_POINT 267
#define DNA_FRONT_DOOR_POINT 268
#define DNA_SIDE_DOOR_POINT 269
#define DNA_COGHQ_IN_POINT 270
#define DNA_COGHQ_OUT_POINT 271
#define SUIT_EDGE 272
#define BATTLE_CELL 273
#define PROP 274
#define POS 275
#define HPR 276
#define SCALE 277
#define CODE 278
#define COLOR 279
#define MODEL 280
#define STORE_NODE 281
#define SIGN 282
#define BASELINE 283
#define WIDTH 284
#define HEIGHT 285
#define STOMP 286
#define STUMBLE 287
#define INDENT 288
#define WIGGLE 289
#define KERN 290
#define TEXT 291
#define LETTERS 292
#define STORE_FONT 293
#define FLAT_BUILDING 294
#define WALL 295
#define WINDOWS 296
#define COUNT 297
#define CORNICE 298
#define LANDMARK_BUILDING 299
#define TITLE 300
#define ARTICLE 301
#define BUILDING_TYPE 302
#define DOOR 303
#define STORE_TEXTURE 304
#define STREET 305
#define TEXTURE 306
#define GRAPHIC 307
#define HOODMODEL 308
#define PLACEMODEL 309
#define FLAGS 310
#define NODE 311
#define FLAT_DOOR 312
#define ANIM 313
#define CELL_ID 314
#define ANIM_PROP 315
#define INTERACTIVE_PROP 316
#define ANIM_BUILDING 317

/* Value type.  */


extern YYSTYPE dnayylval;

int dnayyparse (void);

#endif /* !YY_DNAYY_DNA_YXX_HXX_INCLUDED  */
