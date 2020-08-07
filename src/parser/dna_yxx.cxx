/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1


/* Substitute the variable and function names.  */
#define yyparse         dnayyparse
#define yylex           dnayylex
#define yyerror         dnayyerror
#define yydebug         dnayydebug
#define yynerrs         dnayynerrs
#define yylval          dnayylval
#define yychar          dnayychar

/* First part of user prologue.  */
#line 1 "dna.yxx"

#include "dnaLexerDefs.h"
#include "dnaParserDefs.h"

// #define DO_YYDEBUG

#ifdef DO_YYDEBUG
#define YYDEBUG 1
#endif
#include "dna_yxx.hxx"

#include "DNAVisGroup.h"
#include "DNANode.h"
#include "DNAProp.h"
#include "DNASign.h"
#include "DNASignText.h"
#include "DNASignBaseline.h"
#include "DNASignGraphic.h"
#include "DNAWall.h"
#include "DNAWindows.h"
#include "DNALandmarkBuilding.h"
#include "DNAFlatBuilding.h"
#include "DNADoor.h"
#include "DNAFlatDoor.h"
#include "DNAStreet.h"
#include "DNAAnimBuilding.h"
#include "DNAAnimProp.h"
#include "DNAInteractiveProp.h"
#include "DNACornice.h"

#include "texturePool.h"
#include "fontPool.h"

// Because our token type contains objects of type string, which
// require correct copy construction (and not simply memcpying), we
// cannot use bison's built-in auto-stack-grow feature.  As an easy
// solution, we ensure here that we have enough yacc stack to start
// with, and that it doesn't ever try to grow.
#define YYINITDEPTH 1000
#define YYMAXDEPTH 1000

////////////////////////////////////////////////////////////////////
// Static variables
////////////////////////////////////////////////////////////////////

static DNALoader* _loader = nullptr;
static DNAStorage* _store = nullptr;
static PT(DNAGroup) _cur_comp = nullptr;
static PT(DNAGroup) _sign_text = nullptr;
static std::string _model_name, _model_type;

////////////////////////////////////////////////////////////////////
// Defining the interface to the parser.
////////////////////////////////////////////////////////////////////

void dna_init_parser(std::istream &in, const std::string &filename,
                     DNALoader* loader, DNAStorage* store,
                     PT(DNAGroup) root) {
#ifdef DO_YYDEBUG
  dnayydebug = 1;
#endif
  dna_init_lexer(in, filename);
  _loader = loader;
  _store = store;
  _cur_comp = root;
}

void dna_cleanup_parser() {
  _loader = nullptr;
  _store = nullptr;
  _cur_comp = nullptr;
  _sign_text = nullptr;
  _model_name = "";
  _model_type = "";
}

static void _store_model(const std::string& root, const std::string &code, const std::string& search) {
  _store->store_catalog_code(root, code);

  Filename filename(_model_name);
  if (!filename.get_extension().size())
    filename.set_extension("bam");

  if (_model_type == "hood_model")
    _store->store_hood_node(filename, search, code);

  else if (_model_type == "place_model")
    _store->store_place_node(filename, search, code);

  else
    _store->store_node(filename, search, code);
}

static block_number_t _get_visgroup_zoneid(PT(DNAGroup) g) {
  if (!g->get_vis_group()) {
    dnayywarning("landmarkbuilding not in visgroup");
    return 0;
  }

  std::string name = g->get_vis_group()->get_name();
  auto idx = name.find(':');
  if (idx != std::string::npos)
    name = name.substr(0, idx);

  return atoi(name.c_str());
}


#line 186 "dna_yxx.cxx"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
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



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  87
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1328

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  66
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  127
/* YYNRULES -- Number of rules.  */
#define YYNRULES  230
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  496

#define YYUNDEFTOK  2
#define YYMAXUTOK   317


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    64,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    63,     2,    65,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   181,   181,   182,   185,   186,   187,   188,   189,   192,
     196,   200,   205,   211,   216,   222,   227,   232,   237,   242,
     248,   252,   257,   266,   275,   284,   289,   294,   299,   304,
     311,   314,   315,   316,   317,   318,   319,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   334,   339,   344,
     349,   353,   357,   362,   367,   370,   375,   380,   385,   390,
     394,   399,   404,   408,   413,   422,   431,   440,   449,   458,
     467,   476,   490,   504,   513,   523,   532,   541,   550,   560,
     571,   580,   586,   587,   590,   591,   592,   593,   594,   597,
     602,   607,   612,   617,   618,   619,   620,   623,   624,   627,
     630,   635,   640,   641,   642,   643,   644,   645,   646,   647,
     648,   649,   652,   657,   658,   659,   660,   663,   666,   667,
     668,   671,   672,   673,   676,   677,   680,   681,   682,   683,
     684,   687,   690,   691,   694,   695,   696,   699,   704,   710,
     717,   724,   731,   737,   742,   747,   752,   757,   762,   767,
     772,   777,   782,   787,   792,   797,   802,   807,   812,   817,
     822,   827,   832,   837,   842,   847,   853,   859,   865,   871,
     877,   883,   889,   890,   891,   894,   895,   896,   897,   900,
     901,   902,   903,   904,   907,   908,   909,   912,   913,   914,
     917,   918,   921,   922,   923,   926,   927,   928,   931,   932,
     933,   936,   937,   938,   941,   942,   943,   946,   947,   948,
     951,   952,   953,   954,   957,   958,   959,   962,   963,   964,
     967,   972,   977,   983,   986,   987,   990,   994,   999,  1003,
    1009
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "SIGNED_INTEGER", "UNSIGNED_INTEGER",
  "FLOAT_REAL", "UNQUOTED_STRING", "QUOTED_STRING", "STORE_SUIT_POINT",
  "GROUP", "VISGROUP", "VIS", "DNA_STREET_POINT", "DNA_FRONT_DOOR_POINT",
  "DNA_SIDE_DOOR_POINT", "DNA_COGHQ_IN_POINT", "DNA_COGHQ_OUT_POINT",
  "SUIT_EDGE", "BATTLE_CELL", "PROP", "POS", "HPR", "SCALE", "CODE",
  "COLOR", "MODEL", "STORE_NODE", "SIGN", "BASELINE", "WIDTH", "HEIGHT",
  "STOMP", "STUMBLE", "INDENT", "WIGGLE", "KERN", "TEXT", "LETTERS",
  "STORE_FONT", "FLAT_BUILDING", "WALL", "WINDOWS", "COUNT", "CORNICE",
  "LANDMARK_BUILDING", "TITLE", "ARTICLE", "BUILDING_TYPE", "DOOR",
  "STORE_TEXTURE", "STREET", "TEXTURE", "GRAPHIC", "HOODMODEL",
  "PLACEMODEL", "FLAGS", "NODE", "FLAT_DOOR", "ANIM", "CELL_ID",
  "ANIM_PROP", "INTERACTIVE_PROP", "ANIM_BUILDING", "'['", "','", "']'",
  "$accept", "dna", "object", "number", "lpoint3f", "suitpoint",
  "suitpointtype", "string", "dnagroupdef", "dnanodedef", "visgroupdef",
  "dnagroup", "visgroup", "string_opt_list", "vis", "empty", "group",
  "dnanode", "dnanode_grp", "sign", "signgraphic", "prop", "signbaseline",
  "signtext", "flatbuilding", "wall", "windows", "cornice",
  "landmarkbuilding", "street", "door", "propdef", "animpropdef",
  "interactivepropdef", "flatbuildingdef", "walldef", "windowsdef",
  "cornicedef", "landmarkbuildingdef", "animbuildingdef", "doordef",
  "flatdoordef", "streetdef", "signdef", "signgraphicdef", "baselinedef",
  "textdef", "suitedge", "battlecell", "subgroup_list", "subvisgroup_list",
  "pos", "hpr", "scale", "flags", "dnanode_sub", "dnaprop_sub",
  "dnaanimprop_sub", "dnainteractiveprop_sub", "anim", "baseline_sub",
  "text_sub", "signgraphic_sub", "flatbuilding_sub", "wall_sub",
  "windows_sub", "cornice_sub", "landmarkbuilding_sub", "animbuilding_sub",
  "door_sub", "street_sub", "texture", "street_color", "title", "article",
  "building_type", "lb_wall_color", "ab_anim", "windowcount",
  "baseline_width", "signgraphic_width", "flatbuilding_width",
  "baseline_height", "signgraphic_height", "wall_height", "stomp",
  "indent", "kern", "stumble", "wiggle", "prop_code",
  "landmarkbuilding_code", "baseline_code", "door_code",
  "signgraphic_code", "cornice_code", "street_code", "wall_code",
  "windows_code", "prop_color", "baseline_color", "door_color",
  "signgraphic_color", "cornice_color", "wall_color", "windows_color",
  "subprop_list", "subanimprop_list", "subinteractiveprop_list",
  "subbaseline_list", "subtext_list", "subdnanode_list",
  "subsigngraphic_list", "subflatbuilding_list", "subwall_list",
  "subwindows_list", "subcornice_list", "sublandmarkbuilding_list",
  "subanimbuilding_list", "subdoor_list", "substreet_list", "modeldef",
  "model", "modelnode_list", "node", "store_texture", "font", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,    91,    44,    93
};
# endif

#define YYPACT_NINF (-310)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    1266,   -44,    59,    59,    59,    59,  -310,  -310,  -310,   -37,
      59,  -310,  -310,  -310,    59,  -310,   -13,    59,  -310,    59,
      59,    59,  -310,    59,    59,    59,    43,  -310,  -310,    -2,
       0,     6,  -310,  -310,  -310,  -310,  -310,  -310,  -310,  -310,
    -310,  -310,  -310,  -310,  -310,  -310,  -310,  -310,  -310,     9,
      14,    15,    17,    22,    25,    26,    27,    31,    35,    38,
      46,    49,    51,    52,    53,    54,  -310,  -310,  -310,    41,
    -310,  -310,  -310,  -310,  -310,  -310,    59,  -310,  -310,    59,
    -310,  -310,  -310,  -310,  -310,  -310,  -310,  -310,  -310,  -310,
    -310,  -310,  -310,  -310,  -310,  -310,  -310,  -310,  -310,  -310,
    -310,  -310,  -310,  -310,  -310,  -310,  -310,  -310,  -310,  -310,
    -310,  -310,   -17,    59,    59,  -310,  1221,  -310,  1149,  -310,
    1185,  -310,   806,  -310,   605,  -310,   502,  -310,  1051,  -310,
     659,  -310,   708,  -310,   855,  -310,   217,  -310,   163,  -310,
     904,   953,  -310,   757,  1002,  -310,   556,  -310,   114,  -310,
    1100,  -310,   -16,    44,    59,    -1,  -310,  -310,    55,    56,
      57,  -310,  -310,  -310,  -310,  -310,  -310,    58,    62,    63,
    -310,  -310,  -310,  -310,  -310,    64,    66,  -310,  -310,  -310,
    -310,  -310,    67,  -310,  -310,  -310,  -310,  -310,    68,  -310,
    -310,  -310,  -310,  -310,    76,  -310,  -310,  -310,  -310,    77,
      93,    96,  -310,  -310,  -310,  -310,  -310,  -310,    97,    98,
     100,  -310,  -310,  -310,  -310,  -310,  -310,   102,   104,  -310,
    -310,  -310,  -310,  -310,   105,   115,   117,   118,   125,  -310,
    -310,  -310,  -310,  -310,  -310,  -310,  -310,   126,  -310,  -310,
    -310,  -310,  -310,   129,   130,  -310,  -310,  -310,  -310,  -310,
    -310,   131,   132,   133,  -310,  -310,  -310,  -310,  -310,  -310,
    -310,   134,   135,   137,   138,  -310,  -310,  -310,  -310,  -310,
    -310,  -310,   142,   149,   151,   153,   154,   155,   159,   166,
     168,   169,  -310,  -310,  -310,  -310,  -310,  -310,  -310,  -310,
    -310,  -310,  -310,  -310,  -310,   170,  -310,  -310,  -310,   171,
    -310,  -310,  -310,  -310,  -310,  -310,  -310,   113,    37,  -310,
      42,    41,    41,    41,    59,    41,    41,    59,    41,    59,
      41,    41,    59,    41,    41,    59,    41,    41,    59,    41,
      59,    41,    59,    59,    59,    59,    59,    41,    59,    41,
      59,    59,    41,    41,    41,    59,    41,    41,    41,    41,
      41,    41,    41,    41,    59,    59,    59,    41,  -310,  -310,
      41,   165,   177,   178,  -310,    41,    41,   181,    41,   182,
     183,   184,   185,    41,   186,   187,    41,   189,   190,    41,
     194,    41,   201,   203,   205,   206,   207,    41,   210,    41,
     211,   215,    41,   216,   218,   219,    41,   221,   222,   223,
     224,   225,   227,   229,   231,   235,    59,    10,    41,  -310,
    -310,  -310,     2,  -310,   237,    41,  -310,    41,  -310,  -310,
    -310,  -310,    41,  -310,  -310,    41,  -310,  -310,    41,  -310,
      41,  -310,  -310,  -310,  -310,  -310,    41,  -310,    41,  -310,
    -310,    41,  -310,  -310,  -310,    41,  -310,  -310,  -310,  -310,
    -310,  -310,  -310,  -310,  -310,    48,    41,  -310,  -310,  -310,
    -310,  -310,   239,    41,    41,    41,    41,    41,    41,    41,
      41,    41,  -310,   241,   244,  -310,   247,   253,   255,   256,
     258,   259,   261,   263,   269,  -310,  -310,  -310,  -310,  -310,
    -310,  -310,  -310,  -310,  -310,  -310
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,    76,    78,    79,     0,
       0,    68,    69,    70,     0,    73,     0,     0,    77,     0,
       0,     0,    74,     0,     0,     0,     0,     3,     4,     0,
       0,     0,    31,    32,     5,    33,    46,    38,    45,    37,
      39,    40,    41,    42,    34,    35,    43,    44,    36,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     6,     8,     7,     0,
      21,    20,    22,    24,    64,   220,     0,    67,    71,     0,
      75,   221,   222,    23,    65,    66,    72,     1,     2,    30,
      30,    30,    30,    30,    30,    30,    30,    30,    30,    30,
      30,    30,    30,    30,    30,    30,    30,    30,    30,    10,
       9,    11,     0,     0,     0,    83,     0,   191,     0,    88,
       0,   174,     0,   178,     0,   183,     0,   197,     0,   200,
       0,   203,     0,   206,     0,   209,     0,   213,     0,   216,
       0,     0,   219,     0,     0,   194,     0,   186,     0,   189,
       0,   225,     0,     0,     0,     0,    25,    82,     0,     0,
       0,    47,    93,    94,    95,    96,   190,     0,     0,     0,
      26,    87,    84,    85,    86,     0,     0,    50,   172,   173,
      97,    98,     0,    51,   175,   176,   177,    99,     0,    52,
     179,   180,   181,   182,     0,    55,   195,   196,   117,     0,
       0,     0,    56,   198,   199,   118,   119,   120,     0,     0,
       0,    57,   201,   202,   123,   121,   122,     0,     0,    58,
     204,   205,   124,   125,     0,     0,     0,     0,     0,    59,
     207,   208,   127,   128,   129,   130,   126,     0,    60,   210,
     211,   212,   131,     0,     0,    62,   214,   215,   132,   133,
      63,     0,     0,     0,    61,   217,   218,   135,   136,   134,
      48,     0,     0,     0,     0,    49,   192,   193,   113,   114,
     115,   116,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    53,   111,   184,   185,   104,   105,   108,   106,
     107,   109,   110,   102,   103,     0,    54,   187,   188,     0,
     223,   224,    15,    16,    17,    18,    19,     0,     0,   228,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   230,   229,
       0,     0,     0,     0,    30,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    89,
      90,    91,     0,    28,     0,     0,   156,     0,   101,   100,
     147,   163,     0,   150,   164,     0,   144,   161,     0,   157,
       0,   139,   140,   141,   143,   159,     0,   162,     0,   137,
     160,     0,   146,   149,   158,     0,   145,   148,   151,   154,
     152,   155,   153,    92,   112,     0,     0,    13,    12,    29,
      27,    80,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   226,     0,     0,    81,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   227,    14,   165,   170,   171,
     169,   142,   167,   138,   168,   166
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -310,  -310,   209,    39,  -309,  -310,  -310,    -3,  -310,  -310,
    -310,  -310,  -310,  -310,  -310,   -66,    12,  -310,  -310,  -310,
    -310,  -310,  -310,  -310,  -310,  -310,  -310,  -310,  -310,  -310,
    -310,  -310,  -310,  -310,  -310,  -310,  -310,  -310,  -310,  -310,
    -310,  -310,  -310,  -310,  -310,  -310,  -310,  -310,  -310,  -310,
    -310,  -310,  -310,  -310,  -310,   167,  -111,    -4,  -310,  -310,
    -310,  -310,  -310,  -310,  -310,  -310,  -310,   198,  -310,  -310,
    -310,  -310,  -310,  -310,  -310,  -310,  -310,  -310,  -310,  -310,
    -310,  -310,  -310,  -310,  -310,  -310,  -310,  -310,  -310,  -310,
    -310,  -310,  -310,  -310,  -310,  -310,  -310,  -310,  -310,  -310,
    -310,  -310,  -310,  -310,  -310,  -310,   236,  -310,  -310,  -310,
    -310,  -310,  -310,  -310,  -310,  -310,  -310,  -310,  -310,   242,
    -310,  -310,  -310,  -310,  -310,  -310,  -310
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    26,    27,   360,   361,    28,   307,    72,    29,    30,
      31,    32,    33,   412,   171,   121,   162,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,   173,   174,   116,
     120,   163,   164,   165,   283,   178,   179,   186,   193,   187,
     285,   298,   267,   197,   204,   213,   221,   231,   241,   247,
     256,   257,   258,   232,   233,   234,   235,   242,   214,   286,
     268,   198,   287,   269,   205,   288,   289,   290,   291,   292,
     180,   236,   293,   248,   270,   222,   259,   206,   215,   181,
     294,   249,   271,   223,   207,   216,   122,   124,   126,   148,
     150,   118,   146,   128,   130,   132,   134,   136,   138,   140,
     143,    65,    66,   152,   301,    67,    68
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      73,    74,    75,   362,   363,    70,    71,    77,    70,    71,
     299,    78,    34,   185,    80,   191,    81,    82,    83,    69,
      84,    85,    86,   115,   117,   119,    76,   123,   125,   127,
     129,   131,   133,   135,   137,   139,   139,   142,    34,   145,
     147,   149,   151,    87,   109,   110,   111,   153,   407,   300,
      79,     1,     2,     3,    70,    71,   302,   303,   304,   305,
     306,    89,     4,    90,   309,    70,    71,   459,     5,    91,
       6,     7,    92,   113,   456,   457,   114,    93,    94,     8,
      95,     9,    10,    11,    12,    96,    13,    14,    97,    98,
      99,    15,    16,    17,   100,    18,    19,    20,   101,    21,
      22,   102,   358,    23,    24,    25,   462,   359,   112,   103,
     154,   155,   104,   472,   105,   106,   107,   108,   311,   312,
     313,   314,   192,     2,     3,   315,   316,   317,   157,   318,
     319,   320,   172,     4,   158,   159,   160,   272,   273,   321,
     322,     6,     7,   274,   275,   276,   277,   278,   279,   280,
       8,   308,   310,    10,    11,    12,   323,    13,    14,   324,
     325,   326,    15,   327,    17,   328,    18,   329,   330,   281,
      21,    22,     2,     3,    23,    24,    25,   357,   331,   282,
     332,   333,     4,   158,   159,   160,   224,   225,   334,   335,
       6,     7,   336,   337,   338,   339,   340,   341,   342,     8,
     343,   344,    10,    11,    12,   345,    13,    14,   226,   227,
     228,    15,   346,    17,   347,    18,   348,   349,   350,    21,
      22,   237,   351,    23,    24,    25,     2,     3,   238,   352,
     409,   353,   354,   355,   356,    88,     4,   158,   159,   160,
     224,   225,   410,   411,     6,     7,   416,   418,   419,   420,
     421,   423,   424,     8,   426,   427,    10,    11,    12,   429,
      13,    14,   226,   227,   228,    15,   431,    17,   432,    18,
     433,   434,   435,    21,    22,   437,   439,    23,    24,    25,
     440,   442,   229,   443,   444,   166,   446,   447,   448,   449,
     450,   184,   451,   190,   452,   196,   453,   203,   413,   212,
     454,   220,   461,   230,   475,   239,   485,   246,   246,   486,
     255,   364,   487,   266,   367,   284,   369,   297,   488,   372,
     489,   490,   375,   491,   492,   378,   493,   380,   494,   382,
     383,   384,   385,   386,   495,   388,   240,   390,   391,     0,
     144,     0,   395,     0,   141,     0,     0,     0,     0,     0,
       0,   404,   405,   406,   365,   366,     0,   368,     0,   370,
     371,     0,   373,   374,     0,   376,   377,     0,   379,     0,
     381,     0,     0,     0,     0,     0,   387,     0,   389,     0,
       0,   392,   393,   394,     0,   396,   397,   398,   399,   400,
     401,   402,   403,     0,     0,     0,     0,     0,     0,   408,
       0,     0,     0,   455,   414,   415,     0,   417,     0,   460,
       0,     0,   422,     0,     0,   425,     0,     0,   428,     0,
     430,     0,     0,     0,     0,     0,   436,     0,   438,     0,
       0,   441,     0,     0,     0,   445,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   458,     0,     0,
       0,     0,   473,     0,     0,     0,   463,     0,     0,     0,
       0,   464,     0,     0,   465,     0,     0,   466,     0,   467,
       0,     0,     0,     0,     0,   468,     0,   469,     0,     0,
     470,     0,     0,     0,   471,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   474,     0,     0,     0,     0,
       0,     0,   476,   477,   478,   479,   480,   481,   482,   483,
     484,     2,     3,     0,     0,     0,     0,     0,     0,     0,
       0,     4,   158,   159,   160,   175,   176,     0,     0,     6,
       7,     0,     0,     0,     0,     0,     0,     0,     8,     0,
       0,    10,    11,    12,     0,    13,    14,     0,     0,     0,
      15,     0,    17,     0,    18,     0,     0,     0,    21,    22,
     182,   188,    23,    24,    25,     2,     3,   189,     0,     0,
       0,     0,     0,     0,     0,     4,   158,   159,   160,   261,
     262,     0,     0,     6,     7,   263,   264,     0,     0,     0,
       0,     0,     8,     0,     0,    10,    11,    12,     0,    13,
      14,     0,     0,     0,    15,     0,    17,     0,    18,     0,
       0,     0,    21,    22,     2,     3,    23,    24,    25,     0,
       0,   265,     0,     0,     4,   158,   159,   160,   175,   176,
       0,     0,     6,     7,     0,     0,     0,     0,     0,     0,
       0,     8,     0,     0,    10,    11,    12,     0,    13,    14,
       0,     0,     0,    15,     0,    17,     0,    18,     0,     0,
       0,    21,    22,   182,     0,    23,    24,    25,     2,     3,
     183,     0,     0,     0,     0,     0,     0,     0,     4,   158,
     159,   160,   199,   200,     0,     0,     6,     7,     0,   201,
       0,     0,     0,     0,     0,     8,     0,     0,    10,    11,
      12,     0,    13,    14,     0,     0,     0,    15,     0,    17,
       0,    18,     0,     0,     0,    21,    22,     2,     3,    23,
      24,    25,     0,     0,   202,     0,     0,     4,   158,   159,
     160,   208,   209,     0,     0,     6,     7,     0,     0,     0,
       0,     0,     0,     0,     8,     0,     0,    10,    11,    12,
     210,    13,    14,     0,     0,     0,    15,     0,    17,     0,
      18,     0,     0,     0,    21,    22,     2,     3,    23,    24,
      25,     0,     0,   211,     0,     0,     4,   158,   159,   160,
     251,   252,     0,     0,     6,     7,     0,     0,     0,     0,
       0,     0,     0,     8,     0,     0,    10,    11,    12,     0,
      13,    14,     0,     0,     0,    15,     0,    17,   253,    18,
       0,     0,     0,    21,    22,     2,     3,    23,    24,    25,
       0,     0,   254,     0,     0,     4,   158,   159,   160,   175,
     176,     0,     0,     6,     7,     0,     0,     0,     0,     0,
       0,     0,     8,     0,     0,    10,    11,    12,     0,    13,
      14,     0,     0,     0,    15,     0,    17,     0,    18,     0,
       0,     0,    21,    22,     2,     3,    23,    24,    25,     0,
       0,   177,     0,     0,     4,   158,   159,   160,   217,   218,
       0,     0,     6,     7,     0,     0,     0,     0,     0,     0,
       0,     8,     0,     0,    10,    11,    12,     0,    13,    14,
       0,     0,     0,    15,     0,    17,     0,    18,     0,     0,
       0,    21,    22,     2,     3,    23,    24,    25,     0,     0,
     219,     0,     0,     4,   158,   159,   160,   243,   244,     0,
       0,     6,     7,     0,     0,     0,     0,     0,     0,     0,
       8,     0,     0,    10,    11,    12,     0,    13,    14,     0,
       0,     0,    15,     0,    17,     0,    18,     0,     0,     0,
      21,    22,     2,     3,    23,    24,    25,     0,     0,   245,
       0,     0,     4,   158,   159,   160,   243,   244,     0,     0,
       6,     7,     0,     0,     0,     0,     0,     0,     0,     8,
       0,     0,    10,    11,    12,     0,    13,    14,     0,     0,
       0,    15,     0,    17,     0,    18,     0,     0,     0,    21,
      22,     2,     3,    23,    24,    25,     0,     0,   250,     0,
       0,     4,   158,   159,   160,   175,   176,     0,     0,     6,
       7,     0,     0,     0,     0,     0,     0,     0,     8,     0,
       0,    10,    11,    12,     0,    13,    14,     0,     0,     0,
      15,     0,    17,     0,    18,     0,     0,     0,    21,    22,
       2,     3,    23,    24,    25,     0,     0,   260,     0,     0,
       4,   158,   159,   160,     0,     0,     0,     0,     6,     7,
     194,     0,     0,     0,     0,     0,     0,     8,     0,     0,
      10,    11,    12,     0,    13,    14,     0,     0,     0,    15,
       0,    17,     0,    18,     0,     0,     0,    21,    22,     2,
       3,    23,    24,    25,     0,     0,   195,     0,     0,     4,
     158,   159,   160,     0,     0,     0,     0,     6,     7,     0,
       0,     0,     0,     0,     0,     0,     8,   295,     0,    10,
      11,    12,     0,    13,    14,     0,     0,     0,    15,     0,
      17,     0,    18,     0,     0,     0,    21,    22,     2,     3,
      23,    24,    25,     0,     0,   296,     0,     0,     4,   158,
     159,   160,     0,     0,     0,     0,     6,     7,     0,     0,
       0,     0,     0,     0,     0,     8,     0,     0,    10,    11,
      12,     0,    13,    14,     2,     3,   167,    15,     0,    17,
       0,    18,   168,   169,     4,    21,    22,     0,     0,    23,
      24,    25,     6,     7,   161,     0,     0,     0,     0,     0,
       0,     8,     0,     0,    10,    11,    12,     0,    13,    14,
       2,     3,     0,    15,     0,    17,     0,    18,     0,     0,
       4,    21,    22,     0,     0,    23,    24,    25,     6,     7,
     170,     0,     0,     0,     0,     0,     0,     8,     0,     0,
      10,    11,    12,     0,    13,    14,     0,     0,     0,    15,
       0,    17,     0,    18,     1,     2,     3,    21,    22,     0,
       0,    23,    24,    25,     0,     4,   156,     0,     0,     0,
       0,     5,     0,     6,     7,     0,     0,     0,     0,     0,
       0,     0,     8,     0,     9,    10,    11,    12,     0,    13,
      14,     0,     0,     0,    15,    16,    17,     0,    18,    19,
      20,     0,    21,    22,     0,     0,    23,    24,    25
};

static const yytype_int16 yycheck[] =
{
       3,     4,     5,   312,   313,     6,     7,    10,     6,     7,
      26,    14,     0,   124,    17,   126,    19,    20,    21,    63,
      23,    24,    25,    89,    90,    91,    63,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,    26,   105,
     106,   107,   108,     0,     3,     4,     5,    64,   357,    65,
      63,     8,     9,    10,     6,     7,    12,    13,    14,    15,
      16,    63,    19,    63,    65,     6,     7,    65,    25,    63,
      27,    28,    63,    76,    64,    65,    79,    63,    63,    36,
      63,    38,    39,    40,    41,    63,    43,    44,    63,    63,
      63,    48,    49,    50,    63,    52,    53,    54,    63,    56,
      57,    63,    65,    60,    61,    62,   415,    65,    69,    63,
     113,   114,    63,    65,    63,    63,    63,    63,    63,    63,
      63,    63,   126,     9,    10,    63,    63,    63,   116,    63,
      63,    63,   120,    19,    20,    21,    22,    23,    24,    63,
      63,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,   154,   155,    39,    40,    41,    63,    43,    44,    63,
      63,    63,    48,    63,    50,    63,    52,    63,    63,    55,
      56,    57,     9,    10,    60,    61,    62,    64,    63,    65,
      63,    63,    19,    20,    21,    22,    23,    24,    63,    63,
      27,    28,    63,    63,    63,    63,    63,    63,    63,    36,
      63,    63,    39,    40,    41,    63,    43,    44,    45,    46,
      47,    48,    63,    50,    63,    52,    63,    63,    63,    56,
      57,    58,    63,    60,    61,    62,     9,    10,    65,    63,
      65,    63,    63,    63,    63,    26,    19,    20,    21,    22,
      23,    24,    65,    65,    27,    28,    65,    65,    65,    65,
      65,    65,    65,    36,    65,    65,    39,    40,    41,    65,
      43,    44,    45,    46,    47,    48,    65,    50,    65,    52,
      65,    65,    65,    56,    57,    65,    65,    60,    61,    62,
      65,    65,    65,    65,    65,   118,    65,    65,    65,    65,
      65,   124,    65,   126,    65,   128,    65,   130,   364,   132,
      65,   134,    65,   136,    65,   138,    65,   140,   141,    65,
     143,   314,    65,   146,   317,   148,   319,   150,    65,   322,
      65,    65,   325,    65,    65,   328,    65,   330,    65,   332,
     333,   334,   335,   336,    65,   338,   138,   340,   341,    -1,
     104,    -1,   345,    -1,   102,    -1,    -1,    -1,    -1,    -1,
      -1,   354,   355,   356,   315,   316,    -1,   318,    -1,   320,
     321,    -1,   323,   324,    -1,   326,   327,    -1,   329,    -1,
     331,    -1,    -1,    -1,    -1,    -1,   337,    -1,   339,    -1,
      -1,   342,   343,   344,    -1,   346,   347,   348,   349,   350,
     351,   352,   353,    -1,    -1,    -1,    -1,    -1,    -1,   360,
      -1,    -1,    -1,   406,   365,   366,    -1,   368,    -1,   412,
      -1,    -1,   373,    -1,    -1,   376,    -1,    -1,   379,    -1,
     381,    -1,    -1,    -1,    -1,    -1,   387,    -1,   389,    -1,
      -1,   392,    -1,    -1,    -1,   396,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   408,    -1,    -1,
      -1,    -1,   455,    -1,    -1,    -1,   417,    -1,    -1,    -1,
      -1,   422,    -1,    -1,   425,    -1,    -1,   428,    -1,   430,
      -1,    -1,    -1,    -1,    -1,   436,    -1,   438,    -1,    -1,
     441,    -1,    -1,    -1,   445,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   456,    -1,    -1,    -1,    -1,
      -1,    -1,   463,   464,   465,   466,   467,   468,   469,   470,
     471,     9,    10,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    19,    20,    21,    22,    23,    24,    -1,    -1,    27,
      28,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,    -1,
      -1,    39,    40,    41,    -1,    43,    44,    -1,    -1,    -1,
      48,    -1,    50,    -1,    52,    -1,    -1,    -1,    56,    57,
      58,    59,    60,    61,    62,     9,    10,    65,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    19,    20,    21,    22,    23,
      24,    -1,    -1,    27,    28,    29,    30,    -1,    -1,    -1,
      -1,    -1,    36,    -1,    -1,    39,    40,    41,    -1,    43,
      44,    -1,    -1,    -1,    48,    -1,    50,    -1,    52,    -1,
      -1,    -1,    56,    57,     9,    10,    60,    61,    62,    -1,
      -1,    65,    -1,    -1,    19,    20,    21,    22,    23,    24,
      -1,    -1,    27,    28,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    36,    -1,    -1,    39,    40,    41,    -1,    43,    44,
      -1,    -1,    -1,    48,    -1,    50,    -1,    52,    -1,    -1,
      -1,    56,    57,    58,    -1,    60,    61,    62,     9,    10,
      65,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    19,    20,
      21,    22,    23,    24,    -1,    -1,    27,    28,    -1,    30,
      -1,    -1,    -1,    -1,    -1,    36,    -1,    -1,    39,    40,
      41,    -1,    43,    44,    -1,    -1,    -1,    48,    -1,    50,
      -1,    52,    -1,    -1,    -1,    56,    57,     9,    10,    60,
      61,    62,    -1,    -1,    65,    -1,    -1,    19,    20,    21,
      22,    23,    24,    -1,    -1,    27,    28,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    36,    -1,    -1,    39,    40,    41,
      42,    43,    44,    -1,    -1,    -1,    48,    -1,    50,    -1,
      52,    -1,    -1,    -1,    56,    57,     9,    10,    60,    61,
      62,    -1,    -1,    65,    -1,    -1,    19,    20,    21,    22,
      23,    24,    -1,    -1,    27,    28,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    36,    -1,    -1,    39,    40,    41,    -1,
      43,    44,    -1,    -1,    -1,    48,    -1,    50,    51,    52,
      -1,    -1,    -1,    56,    57,     9,    10,    60,    61,    62,
      -1,    -1,    65,    -1,    -1,    19,    20,    21,    22,    23,
      24,    -1,    -1,    27,    28,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    36,    -1,    -1,    39,    40,    41,    -1,    43,
      44,    -1,    -1,    -1,    48,    -1,    50,    -1,    52,    -1,
      -1,    -1,    56,    57,     9,    10,    60,    61,    62,    -1,
      -1,    65,    -1,    -1,    19,    20,    21,    22,    23,    24,
      -1,    -1,    27,    28,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    36,    -1,    -1,    39,    40,    41,    -1,    43,    44,
      -1,    -1,    -1,    48,    -1,    50,    -1,    52,    -1,    -1,
      -1,    56,    57,     9,    10,    60,    61,    62,    -1,    -1,
      65,    -1,    -1,    19,    20,    21,    22,    23,    24,    -1,
      -1,    27,    28,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      36,    -1,    -1,    39,    40,    41,    -1,    43,    44,    -1,
      -1,    -1,    48,    -1,    50,    -1,    52,    -1,    -1,    -1,
      56,    57,     9,    10,    60,    61,    62,    -1,    -1,    65,
      -1,    -1,    19,    20,    21,    22,    23,    24,    -1,    -1,
      27,    28,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,
      -1,    -1,    39,    40,    41,    -1,    43,    44,    -1,    -1,
      -1,    48,    -1,    50,    -1,    52,    -1,    -1,    -1,    56,
      57,     9,    10,    60,    61,    62,    -1,    -1,    65,    -1,
      -1,    19,    20,    21,    22,    23,    24,    -1,    -1,    27,
      28,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,    -1,
      -1,    39,    40,    41,    -1,    43,    44,    -1,    -1,    -1,
      48,    -1,    50,    -1,    52,    -1,    -1,    -1,    56,    57,
       9,    10,    60,    61,    62,    -1,    -1,    65,    -1,    -1,
      19,    20,    21,    22,    -1,    -1,    -1,    -1,    27,    28,
      29,    -1,    -1,    -1,    -1,    -1,    -1,    36,    -1,    -1,
      39,    40,    41,    -1,    43,    44,    -1,    -1,    -1,    48,
      -1,    50,    -1,    52,    -1,    -1,    -1,    56,    57,     9,
      10,    60,    61,    62,    -1,    -1,    65,    -1,    -1,    19,
      20,    21,    22,    -1,    -1,    -1,    -1,    27,    28,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    36,    37,    -1,    39,
      40,    41,    -1,    43,    44,    -1,    -1,    -1,    48,    -1,
      50,    -1,    52,    -1,    -1,    -1,    56,    57,     9,    10,
      60,    61,    62,    -1,    -1,    65,    -1,    -1,    19,    20,
      21,    22,    -1,    -1,    -1,    -1,    27,    28,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    36,    -1,    -1,    39,    40,
      41,    -1,    43,    44,     9,    10,    11,    48,    -1,    50,
      -1,    52,    17,    18,    19,    56,    57,    -1,    -1,    60,
      61,    62,    27,    28,    65,    -1,    -1,    -1,    -1,    -1,
      -1,    36,    -1,    -1,    39,    40,    41,    -1,    43,    44,
       9,    10,    -1,    48,    -1,    50,    -1,    52,    -1,    -1,
      19,    56,    57,    -1,    -1,    60,    61,    62,    27,    28,
      65,    -1,    -1,    -1,    -1,    -1,    -1,    36,    -1,    -1,
      39,    40,    41,    -1,    43,    44,    -1,    -1,    -1,    48,
      -1,    50,    -1,    52,     8,     9,    10,    56,    57,    -1,
      -1,    60,    61,    62,    -1,    19,    65,    -1,    -1,    -1,
      -1,    25,    -1,    27,    28,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    36,    -1,    38,    39,    40,    41,    -1,    43,
      44,    -1,    -1,    -1,    48,    49,    50,    -1,    52,    53,
      54,    -1,    56,    57,    -1,    -1,    60,    61,    62
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     8,     9,    10,    19,    25,    27,    28,    36,    38,
      39,    40,    41,    43,    44,    48,    49,    50,    52,    53,
      54,    56,    57,    60,    61,    62,    67,    68,    71,    74,
      75,    76,    77,    78,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   187,   188,   191,   192,    63,
       6,     7,    73,    73,    73,    73,    63,    73,    73,    63,
      73,    73,    73,    73,    73,    73,    73,     0,    68,    63,
      63,    63,    63,    63,    63,    63,    63,    63,    63,    63,
      63,    63,    63,    63,    63,    63,    63,    63,    63,     3,
       4,     5,    69,    73,    73,    81,   115,    81,   177,    81,
     116,    81,   172,    81,   173,    81,   174,    81,   179,    81,
     180,    81,   181,    81,   182,    81,   183,    81,   184,    81,
     185,   185,    81,   186,   172,    81,   178,    81,   175,    81,
     176,    81,   189,    64,    73,    73,    65,    82,    20,    21,
      22,    65,    82,   117,   118,   119,   121,    11,    17,    18,
      65,    80,    82,   113,   114,    23,    24,    65,   121,   122,
     156,   165,    58,    65,   121,   122,   123,   125,    59,    65,
     121,   122,   123,   124,    29,    65,   121,   129,   147,    23,
      24,    30,    65,   121,   130,   150,   163,   170,    23,    24,
      42,    65,   121,   131,   144,   164,   171,    23,    24,    65,
     121,   132,   161,   169,    23,    24,    45,    46,    47,    65,
     121,   133,   139,   140,   141,   142,   157,    58,    65,   121,
     133,   134,   143,    23,    24,    65,   121,   135,   159,   167,
      65,    23,    24,    51,    65,   121,   136,   137,   138,   162,
      65,    23,    24,    29,    30,    65,   121,   128,   146,   149,
     160,   168,    23,    24,    29,    30,    31,    32,    33,    34,
      35,    55,    65,   120,   121,   126,   145,   148,   151,   152,
     153,   154,   155,   158,   166,    37,    65,   121,   127,    26,
      65,   190,    12,    13,    14,    15,    16,    72,    73,    65,
      73,    63,    63,    63,    63,    63,    63,    63,    63,    63,
      63,    63,    63,    63,    63,    63,    63,    63,    63,    63,
      63,    63,    63,    63,    63,    63,    63,    63,    63,    63,
      63,    63,    63,    63,    63,    63,    63,    63,    63,    63,
      63,    63,    63,    63,    63,    63,    63,    64,    65,    65,
      69,    70,    70,    70,    73,    69,    69,    73,    69,    73,
      69,    69,    73,    69,    69,    73,    69,    69,    73,    69,
      73,    69,    73,    73,    73,    73,    73,    69,    73,    69,
      73,    73,    69,    69,    69,    73,    69,    69,    69,    69,
      69,    69,    69,    69,    73,    73,    73,    70,    69,    65,
      65,    65,    79,    81,    69,    69,    65,    69,    65,    65,
      65,    65,    69,    65,    65,    69,    65,    65,    69,    65,
      69,    65,    65,    65,    65,    65,    69,    65,    69,    65,
      65,    69,    65,    65,    65,    69,    65,    65,    65,    65,
      65,    65,    65,    65,    65,    73,    64,    65,    69,    65,
      73,    65,    70,    69,    69,    69,    69,    69,    69,    69,
      69,    69,    65,    73,    69,    65,    69,    69,    69,    69,
      69,    69,    69,    69,    69,    65,    65,    65,    65,    65,
      65,    65,    65,    65,    65,    65
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    66,    67,    67,    68,    68,    68,    68,    68,    69,
      69,    69,    70,    71,    71,    72,    72,    72,    72,    72,
      73,    73,    74,    75,    76,    77,    78,    79,    79,    80,
      81,    82,    82,    82,    82,    82,    82,    83,    83,    83,
      83,    83,    83,    83,    83,    83,    83,    84,    85,    86,
      87,    87,    87,    88,    89,    90,    91,    92,    93,    94,
      94,    95,    96,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   115,   116,   116,   116,   116,   116,   117,
     118,   119,   120,   121,   121,   121,   121,   122,   122,   123,
     124,   125,   126,   126,   126,   126,   126,   126,   126,   126,
     126,   126,   127,   128,   128,   128,   128,   129,   130,   130,
     130,   131,   131,   131,   132,   132,   133,   133,   133,   133,
     133,   134,   135,   135,   136,   136,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   163,   164,   165,   166,   167,   168,   169,
     170,   171,   172,   172,   172,   173,   173,   173,   173,   174,
     174,   174,   174,   174,   175,   175,   175,   176,   176,   176,
     177,   177,   178,   178,   178,   179,   179,   179,   180,   180,
     180,   181,   181,   181,   182,   182,   182,   183,   183,   183,
     184,   184,   184,   184,   185,   185,   185,   186,   186,   186,
     187,   187,   187,   188,   189,   189,   190,   190,   191,   191,
     192
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     8,    10,     1,     1,     1,     1,     1,
       1,     1,     2,     2,     2,     4,     4,     2,     1,     5,
       0,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     2,     2,     2,     2,     1,     1,
       1,     2,     2,     1,     1,     2,     1,     1,     1,     1,
       5,     6,     2,     1,     2,     2,     2,     2,     1,     4,
       4,     4,     4,     1,     1,     1,     1,     1,     1,     1,
       4,     4,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     4,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     4,     7,     4,
       4,     4,     7,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     7,     7,     7,     7,     7,
       7,     7,     2,     2,     1,     2,     2,     2,     1,     2,
       2,     2,     2,     1,     2,     2,     1,     2,     2,     1,
       2,     1,     2,     2,     1,     2,     2,     1,     2,     2,
       1,     2,     2,     1,     2,     2,     1,     2,     2,     1,
       2,     2,     2,     1,     2,     2,     1,     2,     2,     1,
       2,     2,     2,     4,     2,     1,     5,     6,     5,     6,
       6
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 9:
#line 193 "dna.yxx"
{
  (yyval.u.real) = (double)(yyvsp[0].u.uint64);
}
#line 2071 "dna_yxx.cxx"
    break;

  case 10:
#line 197 "dna.yxx"
{
  (yyval.u.real) = (double)(yyvsp[0].u.int64);
}
#line 2079 "dna_yxx.cxx"
    break;

  case 11:
#line 201 "dna.yxx"
{
  (yyval.u.real) = (yyvsp[0].u.real);
}
#line 2087 "dna_yxx.cxx"
    break;

  case 12:
#line 206 "dna.yxx"
{
  LPoint3f p((yyvsp[-2].u.real), (yyvsp[-1].u.real), (yyvsp[0].u.real));
  (yyval.point3) = p;
}
#line 2096 "dna_yxx.cxx"
    break;

  case 13:
#line 212 "dna.yxx"
{
  PT(DNASuitPoint) point = new DNASuitPoint((yyvsp[-5].u.real), (DNASuitPoint::PointType)(yyvsp[-3].u.uint64), (yyvsp[-1].point3));
  _store->store_suit_point(point);
}
#line 2105 "dna_yxx.cxx"
    break;

  case 14:
#line 217 "dna.yxx"
{
  PT(DNASuitPoint) point = new DNASuitPoint((yyvsp[-7].u.real), (DNASuitPoint::PointType)(yyvsp[-5].u.uint64), (yyvsp[-3].point3), (yyvsp[-1].u.real));
  _store->store_suit_point(point);
}
#line 2114 "dna_yxx.cxx"
    break;

  case 15:
#line 223 "dna.yxx"
{
  #undef DNA_STREET_POINT
  (yyval.u.uint64) = (uint64_t)DNASuitPoint::STREET_POINT;
}
#line 2123 "dna_yxx.cxx"
    break;

  case 16:
#line 228 "dna.yxx"
{
  #undef DNA_FRONT_DOOR_POINT
  (yyval.u.uint64) = (uint64_t)DNASuitPoint::FRONT_DOOR_POINT;
}
#line 2132 "dna_yxx.cxx"
    break;

  case 17:
#line 233 "dna.yxx"
{
  #undef DNA_SIDE_DOOR_POINT
  (yyval.u.uint64) = (uint64_t)DNASuitPoint::SIDE_DOOR_POINT;
}
#line 2141 "dna_yxx.cxx"
    break;

  case 18:
#line 238 "dna.yxx"
{
  #undef DNA_COGHQ_IN_POINT
  (yyval.u.uint64) = (uint64_t)DNASuitPoint::COGHQ_IN_POINT;
}
#line 2150 "dna_yxx.cxx"
    break;

  case 19:
#line 243 "dna.yxx"
{
  #undef DNA_COGHQ_OUT_POINT
  (yyval.u.uint64) = (uint64_t)DNASuitPoint::COGHQ_OUT_POINT;
}
#line 2159 "dna_yxx.cxx"
    break;

  case 20:
#line 249 "dna.yxx"
{
  (yyval.str) = (yyvsp[0].str);
}
#line 2167 "dna_yxx.cxx"
    break;

  case 21:
#line 253 "dna.yxx"
{
  (yyval.str) = (yyvsp[0].str);
}
#line 2175 "dna_yxx.cxx"
    break;

  case 22:
#line 258 "dna.yxx"
{
  PT(DNAGroup) g = new DNAGroup((yyvsp[0].str));
  g->set_parent(_cur_comp);
  g->set_vis_group(_cur_comp->get_vis_group());
  _cur_comp->add(g);
  _cur_comp = g;
}
#line 2187 "dna_yxx.cxx"
    break;

  case 23:
#line 267 "dna.yxx"
{
  PT(DNAGroup) g = new DNANode((yyvsp[0].str));
  g->set_parent(_cur_comp);
  g->set_vis_group(_cur_comp->get_vis_group());
  _cur_comp->add(g);
  _cur_comp = g;
}
#line 2199 "dna_yxx.cxx"
    break;

  case 24:
#line 276 "dna.yxx"
{
  PT(DNAGroup) g = new DNAVisGroup((yyvsp[0].str));
  g->set_parent(_cur_comp);
  _cur_comp->add(g);
  _cur_comp = g;
  _store->store_DNA_vis_group(DCAST(DNAVisGroup, g));
}
#line 2211 "dna_yxx.cxx"
    break;

  case 25:
#line 285 "dna.yxx"
{
  _cur_comp = _cur_comp->get_parent();
}
#line 2219 "dna_yxx.cxx"
    break;

  case 26:
#line 290 "dna.yxx"
{
  _cur_comp = _cur_comp->get_parent();
}
#line 2227 "dna_yxx.cxx"
    break;

  case 27:
#line 295 "dna.yxx"
{
  (yyvsp[-1].str_vec).push_back((yyvsp[0].str));
  (yyval.str_vec) = (yyvsp[-1].str_vec);
}
#line 2236 "dna_yxx.cxx"
    break;

  case 28:
#line 300 "dna.yxx"
{
  (yyval.str_vec) = {};
}
#line 2244 "dna_yxx.cxx"
    break;

  case 29:
#line 305 "dna.yxx"
{
  DCAST(DNAVisGroup, _cur_comp)->add_visible((yyvsp[-2].str));
  for (auto& vis : (yyvsp[-1].str_vec))
    DCAST(DNAVisGroup, _cur_comp)->add_visible(vis);
}
#line 2254 "dna_yxx.cxx"
    break;

  case 47:
#line 335 "dna.yxx"
{
  _cur_comp = _cur_comp->get_parent();
}
#line 2262 "dna_yxx.cxx"
    break;

  case 48:
#line 340 "dna.yxx"
{
  _cur_comp = _cur_comp->get_parent();
}
#line 2270 "dna_yxx.cxx"
    break;

  case 49:
#line 345 "dna.yxx"
{
  _cur_comp = _cur_comp->get_parent();
}
#line 2278 "dna_yxx.cxx"
    break;

  case 50:
#line 350 "dna.yxx"
{
  _cur_comp = _cur_comp->get_parent();
}
#line 2286 "dna_yxx.cxx"
    break;

  case 51:
#line 354 "dna.yxx"
{
  _cur_comp = _cur_comp->get_parent();
}
#line 2294 "dna_yxx.cxx"
    break;

  case 52:
#line 358 "dna.yxx"
{
  _cur_comp = _cur_comp->get_parent();
}
#line 2302 "dna_yxx.cxx"
    break;

  case 53:
#line 363 "dna.yxx"
{
  _cur_comp = _cur_comp->get_parent();
}
#line 2310 "dna_yxx.cxx"
    break;

  case 55:
#line 371 "dna.yxx"
{
  _cur_comp = _cur_comp->get_parent();
}
#line 2318 "dna_yxx.cxx"
    break;

  case 56:
#line 376 "dna.yxx"
{
  _cur_comp = _cur_comp->get_parent();
}
#line 2326 "dna_yxx.cxx"
    break;

  case 57:
#line 381 "dna.yxx"
{
  _cur_comp = _cur_comp->get_parent();
}
#line 2334 "dna_yxx.cxx"
    break;

  case 58:
#line 386 "dna.yxx"
{
  _cur_comp = _cur_comp->get_parent();
}
#line 2342 "dna_yxx.cxx"
    break;

  case 59:
#line 391 "dna.yxx"
{
  _cur_comp = _cur_comp->get_parent();
}
#line 2350 "dna_yxx.cxx"
    break;

  case 60:
#line 395 "dna.yxx"
{
  _cur_comp = _cur_comp->get_parent();
}
#line 2358 "dna_yxx.cxx"
    break;

  case 61:
#line 400 "dna.yxx"
{
  _cur_comp = _cur_comp->get_parent();
}
#line 2366 "dna_yxx.cxx"
    break;

  case 62:
#line 405 "dna.yxx"
{
  _cur_comp = _cur_comp->get_parent();
}
#line 2374 "dna_yxx.cxx"
    break;

  case 63:
#line 409 "dna.yxx"
{
  _cur_comp = _cur_comp->get_parent();
}
#line 2382 "dna_yxx.cxx"
    break;

  case 64:
#line 414 "dna.yxx"
{
  PT(DNAGroup) g = new DNAProp((yyvsp[0].str));
  g->set_parent(_cur_comp);
  g->set_vis_group(_cur_comp->get_vis_group());
  _cur_comp->add(g);
  _cur_comp = g;
}
#line 2394 "dna_yxx.cxx"
    break;

  case 65:
#line 423 "dna.yxx"
{
  PT(DNAGroup) g = new DNAAnimProp((yyvsp[0].str));
  g->set_parent(_cur_comp);
  g->set_vis_group(_cur_comp->get_vis_group());
  _cur_comp->add(g);
  _cur_comp = g;
}
#line 2406 "dna_yxx.cxx"
    break;

  case 66:
#line 432 "dna.yxx"
{
  PT(DNAGroup) g = new DNAInteractiveProp((yyvsp[0].str));
  g->set_parent(_cur_comp);
  g->set_vis_group(_cur_comp->get_vis_group());
  _cur_comp->add(g);
  _cur_comp = g;
}
#line 2418 "dna_yxx.cxx"
    break;

  case 67:
#line 441 "dna.yxx"
{
  PT(DNAGroup) g = new DNAFlatBuilding((yyvsp[0].str));
  g->set_parent(_cur_comp);
  g->set_vis_group(_cur_comp->get_vis_group());
  _cur_comp->add(g);
  _cur_comp = g;
}
#line 2430 "dna_yxx.cxx"
    break;

  case 68:
#line 450 "dna.yxx"
{
  PT(DNAGroup) g = new DNAWall("wall");
  g->set_parent(_cur_comp);
  g->set_vis_group(_cur_comp->get_vis_group());
  _cur_comp->add(g);
  _cur_comp = g;
}
#line 2442 "dna_yxx.cxx"
    break;

  case 69:
#line 459 "dna.yxx"
{
  PT(DNAGroup) g = new DNAWindows("windows");
  g->set_parent(_cur_comp);
  g->set_vis_group(_cur_comp->get_vis_group());
  _cur_comp->add(g);
  _cur_comp = g;
}
#line 2454 "dna_yxx.cxx"
    break;

  case 70:
#line 468 "dna.yxx"
{
  PT(DNAGroup) g = new DNACornice("cornice");
  g->set_parent(_cur_comp);
  g->set_vis_group(_cur_comp->get_vis_group());
  _cur_comp->add(g);
  _cur_comp = g;
}
#line 2466 "dna_yxx.cxx"
    break;

  case 71:
#line 477 "dna.yxx"
{
  PT(DNAGroup) g = new DNALandmarkBuilding((yyvsp[0].str));
  g->set_parent(_cur_comp);
  g->set_vis_group(_cur_comp->get_vis_group());
  _cur_comp->add(g);
  _cur_comp = g;

  block_number_t block_number = atoi(_store->get_block((yyvsp[0].str)).c_str());
  zone_id_t zone_id = _get_visgroup_zoneid(g);
  _store->store_block_number(block_number);
  _store->store_block_zone(block_number, zone_id);
}
#line 2483 "dna_yxx.cxx"
    break;

  case 72:
#line 491 "dna.yxx"
{
  PT(DNAGroup) g = new DNAAnimBuilding((yyvsp[0].str));
  g->set_parent(_cur_comp);
  g->set_vis_group(_cur_comp->get_vis_group());
  _cur_comp->add(g);
  _cur_comp = g;

  block_number_t block_number = atoi(_store->get_block((yyvsp[0].str)).c_str());
  zone_id_t zone_id = _get_visgroup_zoneid(g);
  _store->store_block_number(block_number);
  _store->store_block_zone(block_number, zone_id);
}
#line 2500 "dna_yxx.cxx"
    break;

  case 73:
#line 505 "dna.yxx"
{
  PT(DNAGroup) g = new DNADoor("door");
  g->set_parent(_cur_comp);
  g->set_vis_group(_cur_comp->get_vis_group());
  _cur_comp->add(g);
  _cur_comp = g;
}
#line 2512 "dna_yxx.cxx"
    break;

  case 74:
#line 514 "dna.yxx"
{
  PT(DNAGroup) g = new DNAFlatDoor("flat_door");
  g->set_parent(_cur_comp);
  g->set_vis_group(_cur_comp->get_vis_group());
  _cur_comp->add(g);
  DCAST(DNAFlatBuilding, _cur_comp->get_parent())->set_has_door(true);
  _cur_comp = g;
}
#line 2525 "dna_yxx.cxx"
    break;

  case 75:
#line 524 "dna.yxx"
{
  PT(DNAGroup) g = new DNAStreet((yyvsp[0].str));
  g->set_parent(_cur_comp);
  g->set_vis_group(_cur_comp->get_vis_group());
  _cur_comp->add(g);
  _cur_comp = g;
}
#line 2537 "dna_yxx.cxx"
    break;

  case 76:
#line 533 "dna.yxx"
{
  PT(DNAGroup) g = new DNASign("sign");
  g->set_parent(_cur_comp);
  g->set_vis_group(_cur_comp->get_vis_group());
  _cur_comp->add(g);
  _cur_comp = g;
}
#line 2549 "dna_yxx.cxx"
    break;

  case 77:
#line 542 "dna.yxx"
{
  PT(DNAGroup) g = new DNASignGraphic("graphic");
  g->set_parent(_cur_comp);
  g->set_vis_group(_cur_comp->get_vis_group());
  _cur_comp->add(g);
  _cur_comp = g;
}
#line 2561 "dna_yxx.cxx"
    break;

  case 78:
#line 551 "dna.yxx"
{
  PT(DNAGroup) g = new DNASignBaseline("baseline");
  g->set_parent(_cur_comp);
  g->set_vis_group(_cur_comp->get_vis_group());
  _cur_comp->add(g);
  _cur_comp = g;
  _sign_text = nullptr; 
}
#line 2574 "dna_yxx.cxx"
    break;

  case 79:
#line 561 "dna.yxx"
{
  if (!_sign_text) {
	PT(DNAGroup) g = new DNASignText("text");
	g->set_parent(_cur_comp);
	g->set_vis_group(_cur_comp->get_vis_group());
	_cur_comp->add(g);
	_sign_text = g;
	}
}
#line 2588 "dna_yxx.cxx"
    break;

  case 80:
#line 572 "dna.yxx"
{
  PT(DNASuitEdge) edge = _store->store_suit_edge((yyvsp[-2].u.real), (yyvsp[-1].u.real), atoi(_cur_comp->get_name().c_str()));
  if (!edge) {
    dnayyerror("store_suit_edge failed");
  }
  DCAST(DNAVisGroup, _cur_comp)->add_suit_edge(edge);
}
#line 2600 "dna_yxx.cxx"
    break;

  case 81:
#line 581 "dna.yxx"
{
  PT(DNABattleCell) cell = new DNABattleCell((yyvsp[-3].u.real), (yyvsp[-2].u.real), (yyvsp[-1].point3));
  DCAST(DNAVisGroup, _cur_comp)->add_battle_cell(cell);
}
#line 2609 "dna_yxx.cxx"
    break;

  case 89:
#line 598 "dna.yxx"
{
  DCAST(DNANode, _cur_comp)->set_pos((yyvsp[-1].point3));
}
#line 2617 "dna_yxx.cxx"
    break;

  case 90:
#line 603 "dna.yxx"
{
  DCAST(DNANode, _cur_comp)->set_hpr((yyvsp[-1].point3));
}
#line 2625 "dna_yxx.cxx"
    break;

  case 91:
#line 608 "dna.yxx"
{
  DCAST(DNANode, _cur_comp)->set_scale((yyvsp[-1].point3));
}
#line 2633 "dna_yxx.cxx"
    break;

  case 92:
#line 613 "dna.yxx"
{
  DCAST(DNASignBaseline, _cur_comp)->set_flags((yyvsp[-1].str));
}
#line 2641 "dna_yxx.cxx"
    break;

  case 100:
#line 631 "dna.yxx"
{
  DCAST(DNAInteractiveProp, _cur_comp)->set_cell_id((yyvsp[-1].u.real));
}
#line 2649 "dna_yxx.cxx"
    break;

  case 101:
#line 636 "dna.yxx"
{
  DCAST(DNAAnimProp, _cur_comp)->set_anim_name((yyvsp[-1].str));
}
#line 2657 "dna_yxx.cxx"
    break;

  case 112:
#line 653 "dna.yxx"
{
  DCAST(DNASignText, _sign_text)->m_letters += (yyvsp[-1].str);
}
#line 2665 "dna_yxx.cxx"
    break;

  case 137:
#line 700 "dna.yxx"
{
  DCAST(DNAStreet, _cur_comp)->set_texture((yyvsp[-1].str));
}
#line 2673 "dna_yxx.cxx"
    break;

  case 138:
#line 705 "dna.yxx"
{
  LVecBase4f color((yyvsp[-4].u.real), (yyvsp[-3].u.real), (yyvsp[-2].u.real), (yyvsp[-1].u.real));
  DCAST(DNAStreet, _cur_comp)->set_color(color);
}
#line 2682 "dna_yxx.cxx"
    break;

  case 139:
#line 711 "dna.yxx"
{
  DCAST(DNALandmarkBuilding, _cur_comp)->set_title((yyvsp[-1].str));
  block_number_t block_number = atoi(_store->get_block(_cur_comp->get_name()).c_str());
  _store->store_block_title(block_number, (yyvsp[-1].str));
}
#line 2692 "dna_yxx.cxx"
    break;

  case 140:
#line 718 "dna.yxx"
{
  DCAST(DNALandmarkBuilding, _cur_comp)->set_article((yyvsp[-1].str));
  block_number_t block_number = atoi(_store->get_block(_cur_comp->get_name()).c_str());
  _store->store_block_article(block_number, (yyvsp[-1].str));
}
#line 2702 "dna_yxx.cxx"
    break;

  case 141:
#line 725 "dna.yxx"
{
  DCAST(DNALandmarkBuilding, _cur_comp)->set_building_type((yyvsp[-1].str));
  block_number_t block_number = atoi(_store->get_block(_cur_comp->get_name()).c_str());
  _store->store_block_building_type(block_number, (yyvsp[-1].str));
}
#line 2712 "dna_yxx.cxx"
    break;

  case 142:
#line 732 "dna.yxx"
{
  LVecBase4f color((yyvsp[-4].u.real), (yyvsp[-3].u.real), (yyvsp[-2].u.real), (yyvsp[-1].u.real));
  DCAST(DNALandmarkBuilding, _cur_comp)->set_wall_color(color);
}
#line 2721 "dna_yxx.cxx"
    break;

  case 143:
#line 738 "dna.yxx"
{
  DCAST(DNAAnimBuilding, _cur_comp)->set_anim_name((yyvsp[-1].str));
}
#line 2729 "dna_yxx.cxx"
    break;

  case 144:
#line 743 "dna.yxx"
{
  DCAST(DNAWindows, _cur_comp)->set_window_count((yyvsp[-1].u.real));
}
#line 2737 "dna_yxx.cxx"
    break;

  case 145:
#line 748 "dna.yxx"
{
  DCAST(DNASignBaseline, _cur_comp)->set_width((yyvsp[-1].u.real));
}
#line 2745 "dna_yxx.cxx"
    break;

  case 146:
#line 753 "dna.yxx"
{
  DCAST(DNASignGraphic, _cur_comp)->set_width((yyvsp[-1].u.real));
}
#line 2753 "dna_yxx.cxx"
    break;

  case 147:
#line 758 "dna.yxx"
{
  DCAST(DNAFlatBuilding, _cur_comp)->set_width((yyvsp[-1].u.real));
}
#line 2761 "dna_yxx.cxx"
    break;

  case 148:
#line 763 "dna.yxx"
{
  DCAST(DNASignBaseline, _cur_comp)->set_height((yyvsp[-1].u.real));
}
#line 2769 "dna_yxx.cxx"
    break;

  case 149:
#line 768 "dna.yxx"
{
  DCAST(DNASignGraphic, _cur_comp)->set_height((yyvsp[-1].u.real));
}
#line 2777 "dna_yxx.cxx"
    break;

  case 150:
#line 773 "dna.yxx"
{
  DCAST(DNAWall, _cur_comp)->set_height((yyvsp[-1].u.real));
}
#line 2785 "dna_yxx.cxx"
    break;

  case 151:
#line 778 "dna.yxx"
{
  DCAST(DNASignBaseline, _cur_comp)->set_stomp((yyvsp[-1].u.real));
}
#line 2793 "dna_yxx.cxx"
    break;

  case 152:
#line 783 "dna.yxx"
{
  DCAST(DNASignBaseline, _cur_comp)->set_indent((yyvsp[-1].u.real));
}
#line 2801 "dna_yxx.cxx"
    break;

  case 153:
#line 788 "dna.yxx"
{
  DCAST(DNASignBaseline, _cur_comp)->set_kern((yyvsp[-1].u.real));
}
#line 2809 "dna_yxx.cxx"
    break;

  case 154:
#line 793 "dna.yxx"
{
  DCAST(DNASignBaseline, _cur_comp)->set_stumble((yyvsp[-1].u.real));
}
#line 2817 "dna_yxx.cxx"
    break;

  case 155:
#line 798 "dna.yxx"
{
  DCAST(DNASignBaseline, _cur_comp)->set_wiggle((yyvsp[-1].u.real));
}
#line 2825 "dna_yxx.cxx"
    break;

  case 156:
#line 803 "dna.yxx"
{
  DCAST(DNAProp, _cur_comp)->set_code((yyvsp[-1].str));
}
#line 2833 "dna_yxx.cxx"
    break;

  case 157:
#line 808 "dna.yxx"
{
  DCAST(DNALandmarkBuilding, _cur_comp)->set_code((yyvsp[-1].str));
}
#line 2841 "dna_yxx.cxx"
    break;

  case 158:
#line 813 "dna.yxx"
{
  DCAST(DNASignBaseline, _cur_comp)->set_code((yyvsp[-1].str));
}
#line 2849 "dna_yxx.cxx"
    break;

  case 159:
#line 818 "dna.yxx"
{
  DCAST(DNADoor, _cur_comp)->set_code((yyvsp[-1].str));
}
#line 2857 "dna_yxx.cxx"
    break;

  case 160:
#line 823 "dna.yxx"
{
  DCAST(DNASignGraphic, _cur_comp)->set_code((yyvsp[-1].str));
}
#line 2865 "dna_yxx.cxx"
    break;

  case 161:
#line 828 "dna.yxx"
{
  DCAST(DNACornice, _cur_comp)->set_code((yyvsp[-1].str));
}
#line 2873 "dna_yxx.cxx"
    break;

  case 162:
#line 833 "dna.yxx"
{
  DCAST(DNAStreet, _cur_comp)->set_code((yyvsp[-1].str));
}
#line 2881 "dna_yxx.cxx"
    break;

  case 163:
#line 838 "dna.yxx"
{
  DCAST(DNAWall, _cur_comp)->set_code((yyvsp[-1].str));
}
#line 2889 "dna_yxx.cxx"
    break;

  case 164:
#line 843 "dna.yxx"
{
  DCAST(DNAWindows, _cur_comp)->set_code((yyvsp[-1].str));
}
#line 2897 "dna_yxx.cxx"
    break;

  case 165:
#line 848 "dna.yxx"
{
  LVecBase4f color((yyvsp[-4].u.real), (yyvsp[-3].u.real), (yyvsp[-2].u.real), (yyvsp[-1].u.real));
  DCAST(DNAProp, _cur_comp)->set_color(color);
}
#line 2906 "dna_yxx.cxx"
    break;

  case 166:
#line 854 "dna.yxx"
{
  LVecBase4f color((yyvsp[-4].u.real), (yyvsp[-3].u.real), (yyvsp[-2].u.real), (yyvsp[-1].u.real));
  DCAST(DNASignBaseline, _cur_comp)->set_color(color);
}
#line 2915 "dna_yxx.cxx"
    break;

  case 167:
#line 860 "dna.yxx"
{
  LVecBase4f color((yyvsp[-4].u.real), (yyvsp[-3].u.real), (yyvsp[-2].u.real), (yyvsp[-1].u.real));
  DCAST(DNADoor, _cur_comp)->set_color(color);
}
#line 2924 "dna_yxx.cxx"
    break;

  case 168:
#line 866 "dna.yxx"
{
  LVecBase4f color((yyvsp[-4].u.real), (yyvsp[-3].u.real), (yyvsp[-2].u.real), (yyvsp[-1].u.real));
  DCAST(DNASignGraphic, _cur_comp)->set_color(color);
}
#line 2933 "dna_yxx.cxx"
    break;

  case 169:
#line 872 "dna.yxx"
{
  LVecBase4f color((yyvsp[-4].u.real), (yyvsp[-3].u.real), (yyvsp[-2].u.real), (yyvsp[-1].u.real));
  DCAST(DNACornice, _cur_comp)->set_color(color);
}
#line 2942 "dna_yxx.cxx"
    break;

  case 170:
#line 878 "dna.yxx"
{
  LVecBase4f color((yyvsp[-4].u.real), (yyvsp[-3].u.real), (yyvsp[-2].u.real), (yyvsp[-1].u.real));
  DCAST(DNAWall, _cur_comp)->set_color(color);
}
#line 2951 "dna_yxx.cxx"
    break;

  case 171:
#line 884 "dna.yxx"
{
  LVecBase4f color((yyvsp[-4].u.real), (yyvsp[-3].u.real), (yyvsp[-2].u.real), (yyvsp[-1].u.real));
  DCAST(DNAWindows, _cur_comp)->set_color(color);
}
#line 2960 "dna_yxx.cxx"
    break;

  case 220:
#line 968 "dna.yxx"
{
  _model_type = "model";
  _model_name = (yyvsp[0].str);
}
#line 2969 "dna_yxx.cxx"
    break;

  case 221:
#line 973 "dna.yxx"
{
  _model_type = "hood_model";
  _model_name = (yyvsp[0].str);
}
#line 2978 "dna_yxx.cxx"
    break;

  case 222:
#line 978 "dna.yxx"
{
  _model_type = "place_model";
  _model_name = (yyvsp[0].str);
}
#line 2987 "dna_yxx.cxx"
    break;

  case 226:
#line 991 "dna.yxx"
{
  _store_model((yyvsp[-2].str), (yyvsp[-1].str), (yyvsp[-1].str));
}
#line 2995 "dna_yxx.cxx"
    break;

  case 227:
#line 995 "dna.yxx"
{
  _store_model((yyvsp[-3].str), (yyvsp[-2].str), (yyvsp[-1].str));
}
#line 3003 "dna_yxx.cxx"
    break;

  case 228:
#line 1000 "dna.yxx"
{
  _store->store_texture((yyvsp[-2].str), TexturePool::load_texture((yyvsp[-1].str)));
}
#line 3011 "dna_yxx.cxx"
    break;

  case 229:
#line 1004 "dna.yxx"
{
  _store->store_catalog_code((yyvsp[-3].str), (yyvsp[-2].str));
  _store->store_texture((yyvsp[-2].str), TexturePool::load_texture((yyvsp[-1].str)));
}
#line 3020 "dna_yxx.cxx"
    break;

  case 230:
#line 1010 "dna.yxx"
{
  _store->store_catalog_code((yyvsp[-3].str), (yyvsp[-2].str));

  Filename filename((yyvsp[-1].str));
  if (!filename.get_extension().size())
    filename.set_extension("bam");

  _store->store_font((yyvsp[-2].str), FontPool::load_font(filename), filename);
}
#line 3034 "dna_yxx.cxx"
    break;


#line 3038 "dna_yxx.cxx"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
