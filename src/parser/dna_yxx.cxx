/* A Bison parser, made by GNU Bison 3.2.  */

/* Bison implementation for Yacc-like parsers in C

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
#define YYBISON_VERSION "3.2"

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
#line 1 "dna.yxx" /* yacc.c:338  */

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


#line 183 "dna_yxx.cxx" /* yacc.c:338  */
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

/* In a future release of Bison, this section will be replaced
   by #include "dna_yxx.hxx".  */
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

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
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
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
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
#define YYLAST   1358

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  66
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  126
/* YYNRULES -- Number of rules.  */
#define YYNRULES  229
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  495

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   317

#define YYTRANSLATE(YYX)                                                \
  ((unsigned) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
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
static const yytype_uint16 yyrline[] =
{
       0,   178,   178,   179,   182,   183,   184,   185,   186,   189,
     193,   197,   202,   208,   213,   219,   224,   229,   234,   239,
     245,   249,   254,   263,   272,   281,   286,   291,   296,   301,
     308,   311,   312,   313,   314,   315,   316,   319,   320,   321,
     322,   323,   324,   325,   326,   327,   328,   331,   336,   341,
     346,   350,   354,   359,   364,   367,   372,   377,   382,   387,
     391,   396,   401,   405,   410,   419,   428,   437,   446,   455,
     464,   473,   487,   501,   510,   520,   529,   538,   547,   556,
     565,   571,   572,   575,   576,   577,   578,   579,   582,   587,
     592,   597,   602,   603,   604,   605,   608,   609,   612,   615,
     620,   625,   626,   627,   628,   629,   630,   631,   632,   633,
     634,   637,   642,   643,   644,   645,   648,   651,   652,   653,
     656,   657,   658,   661,   662,   665,   666,   667,   668,   669,
     672,   675,   676,   679,   680,   681,   684,   689,   695,   701,
     707,   713,   719,   724,   729,   734,   739,   744,   749,   754,
     759,   764,   769,   774,   779,   784,   789,   794,   799,   804,
     809,   814,   819,   824,   829,   835,   841,   847,   853,   859,
     865,   871,   872,   873,   876,   877,   878,   879,   882,   883,
     884,   885,   886,   889,   890,   891,   894,   895,   896,   899,
     900,   903,   904,   905,   908,   909,   910,   913,   914,   915,
     918,   919,   920,   923,   924,   925,   928,   929,   930,   933,
     934,   935,   936,   939,   940,   941,   944,   945,   946,   949,
     954,   959,   965,   968,   969,   972,   976,   981,   985,   991
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
  "suitedge", "battlecell", "subgroup_list", "subvisgroup_list", "pos",
  "hpr", "scale", "flags", "dnanode_sub", "dnaprop_sub", "dnaanimprop_sub",
  "dnainteractiveprop_sub", "anim", "baseline_sub", "text_sub",
  "signgraphic_sub", "flatbuilding_sub", "wall_sub", "windows_sub",
  "cornice_sub", "landmarkbuilding_sub", "animbuilding_sub", "door_sub",
  "street_sub", "texture", "street_color", "title", "article",
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
static const yytype_uint16 yytoknum[] =
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

#define YYPACT_NINF -306

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-306)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    1264,   -55,    39,    39,    39,    39,  -306,  -306,   -44,   -37,
      39,  -306,  -306,  -306,    39,  -306,   -21,    39,  -306,    39,
      39,    39,  -306,    39,    39,    39,    47,  -306,  -306,   -15,
     -13,     0,  -306,  -306,  -306,  -306,  -306,  -306,  -306,  -306,
    -306,  -306,  -306,  -306,  -306,  -306,  -306,  -306,  -306,     2,
      14,    15,    16,    17,    18,    19,    21,    26,    29,    30,
      31,    35,    42,    50,    51,  -306,  -306,  -306,    49,  -306,
    -306,  -306,  -306,  -306,  -306,  -306,    39,  -306,  -306,    39,
    -306,  -306,  -306,  -306,  -306,  -306,  -306,  -306,  -306,  -306,
    -306,  -306,  -306,  -306,  -306,  -306,  -306,  -306,  -306,  -306,
    -306,  -306,  -306,  -306,  -306,  -306,  -306,  -306,  -306,  -306,
    -306,    -2,  -306,  1049,    39,    39,  -306,  1219,  -306,  1147,
    -306,  1183,  -306,   804,  -306,   603,  -306,   500,  -306,  1098,
    -306,   657,  -306,   706,  -306,   853,  -306,   218,  -306,   164,
    -306,   902,   951,  -306,   755,  1000,  -306,   554,  -306,   115,
    -306,   -16,    55,    53,    56,    57,    58,  -306,  -306,  -306,
    -306,  -306,  -306,  -306,    39,    -1,  -306,  -306,  -306,  -306,
      59,    60,    63,  -306,  -306,  -306,  -306,  -306,    64,    65,
    -306,  -306,  -306,  -306,  -306,    67,  -306,  -306,  -306,  -306,
    -306,    68,  -306,  -306,  -306,  -306,  -306,    69,  -306,  -306,
    -306,  -306,    77,    78,    89,  -306,  -306,  -306,  -306,  -306,
    -306,    90,    94,    97,  -306,  -306,  -306,  -306,  -306,  -306,
     101,   103,  -306,  -306,  -306,  -306,  -306,   105,   106,   116,
     118,   119,  -306,  -306,  -306,  -306,  -306,  -306,  -306,  -306,
     126,  -306,  -306,  -306,  -306,  -306,   127,   130,  -306,  -306,
    -306,  -306,  -306,  -306,   131,   132,   133,  -306,  -306,  -306,
    -306,  -306,  -306,  -306,   134,   135,   136,   138,  -306,  -306,
    -306,  -306,  -306,  -306,  -306,   139,   143,   150,   152,   154,
     155,   156,   160,   167,   168,  -306,  -306,  -306,  -306,  -306,
    -306,  -306,  -306,  -306,  -306,  -306,  -306,  -306,   169,  -306,
    -306,  -306,  -306,  -306,  -306,  -306,    54,    49,    49,    49,
      39,   113,  -306,   170,    39,    49,    49,    39,    49,    39,
      49,    49,    39,    49,    49,    39,    49,    49,    39,    49,
      39,    49,    39,    39,    39,    39,    39,    49,    39,    49,
      39,    39,    49,    49,    49,    39,    49,    49,    49,    49,
      49,    49,    49,    49,    39,    39,    49,    49,   171,   178,
     179,   182,  -306,  -306,  -306,    49,    49,   183,    49,   184,
     185,   186,   187,    49,   188,   190,    49,   191,   195,    49,
     202,    49,   204,   206,   207,   208,   211,    49,   212,    49,
     216,   217,    49,   219,   220,   221,    49,   222,   223,   224,
     225,   226,   227,   228,   229,    39,    -4,    49,  -306,  -306,
    -306,  -306,    37,  -306,   230,    49,  -306,    49,  -306,  -306,
    -306,  -306,    49,  -306,  -306,    49,  -306,  -306,    49,  -306,
      49,  -306,  -306,  -306,  -306,  -306,    49,  -306,    49,  -306,
    -306,    49,  -306,  -306,  -306,    49,  -306,  -306,  -306,  -306,
    -306,  -306,  -306,  -306,    52,    49,  -306,  -306,  -306,  -306,
    -306,   231,    49,    49,    49,    49,    49,    49,    49,    49,
      49,  -306,   232,   234,  -306,   235,   236,   237,   238,   239,
     240,   241,   243,   244,  -306,  -306,  -306,  -306,  -306,  -306,
    -306,  -306,  -306,  -306,  -306
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,    76,    78,     0,     0,
       0,    68,    69,    70,     0,    73,     0,     0,    77,     0,
       0,     0,    74,     0,     0,     0,     0,     3,     4,     0,
       0,     0,    31,    32,     5,    33,    46,    38,    45,    37,
      39,    40,    41,    42,    34,    35,    43,    44,    36,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     6,     8,     7,     0,    21,
      20,    22,    24,    64,   219,    30,     0,    67,    71,     0,
      75,   220,   221,    23,    65,    66,    72,     1,     2,    30,
      30,    30,    30,    30,    30,    30,    30,    30,    30,    30,
      30,    30,    30,    30,    30,    30,    30,    30,    10,     9,
      11,     0,   188,     0,     0,     0,    82,     0,   190,     0,
      87,     0,   173,     0,   177,     0,   182,     0,   196,     0,
     199,     0,   202,     0,   205,     0,   208,     0,   212,     0,
     215,     0,     0,   218,     0,     0,   193,     0,   185,     0,
     224,     0,     0,     0,     0,     0,     0,    54,    92,    93,
      94,    95,   186,   187,     0,     0,    25,    81,    47,   189,
       0,     0,     0,    26,    86,    83,    84,    85,     0,     0,
      50,   171,   172,    96,    97,     0,    51,   174,   175,   176,
      98,     0,    52,   178,   179,   180,   181,     0,    55,   194,
     195,   116,     0,     0,     0,    56,   197,   198,   117,   118,
     119,     0,     0,     0,    57,   200,   201,   122,   120,   121,
       0,     0,    58,   203,   204,   123,   124,     0,     0,     0,
       0,     0,    59,   206,   207,   126,   127,   128,   129,   125,
       0,    60,   209,   210,   211,   130,     0,     0,    62,   213,
     214,   131,   132,    63,     0,     0,     0,    61,   216,   217,
     134,   135,   133,    48,     0,     0,     0,     0,    49,   191,
     192,   112,   113,   114,   115,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    53,   110,   183,   184,   103,
     104,   107,   105,   106,   108,   109,   101,   102,     0,   222,
     223,    15,    16,    17,    18,    19,     0,     0,     0,     0,
       0,     0,   227,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   229,   228,    30,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    88,    89,
      90,   111,     0,    28,     0,     0,   155,     0,   100,    99,
     146,   162,     0,   149,   163,     0,   143,   160,     0,   156,
       0,   138,   139,   140,   142,   158,     0,   161,     0,   136,
     159,     0,   145,   148,   157,     0,   144,   147,   150,   153,
     151,   154,   152,    91,     0,     0,    13,    12,    29,    27,
      79,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   225,     0,     0,    80,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   226,    14,   164,   169,   170,   168,
     141,   166,   137,   167,   165
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -306,  -306,   284,    38,  -305,  -306,  -306,    -3,  -306,  -306,
    -306,  -306,  -306,  -306,  -306,   -66,    12,  -306,  -306,  -306,
    -306,  -306,  -306,  -306,  -306,  -306,  -306,  -306,  -306,  -306,
    -306,  -306,  -306,  -306,  -306,  -306,  -306,  -306,  -306,  -306,
    -306,  -306,  -306,  -306,  -306,  -306,  -306,  -306,  -306,  -306,
    -306,  -306,  -306,  -306,  1209,  -112,   -12,  -306,  -306,  -306,
    -306,  -306,  -306,  -306,  -306,  -306,    95,  -306,  -306,  -306,
    -306,  -306,  -306,  -306,  -306,  -306,  -306,  -306,  -306,  -306,
    -306,  -306,  -306,  -306,  -306,  -306,  -306,  -306,  -306,  -306,
    -306,  -306,  -306,  -306,  -306,  -306,  -306,  -306,  -306,  -306,
    -306,  -306,  -306,  -306,  -306,   129,  -306,  -306,  -306,  -306,
    -306,  -306,  -306,  -306,  -306,  -306,  -306,  -306,   210,  -306,
    -306,  -306,  -306,  -306,  -306,  -306
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    26,    27,   357,   358,    28,   306,    71,    29,    30,
      31,    32,    33,   412,   174,   122,   158,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,   176,   177,   117,   121,
     159,   160,   161,   286,   181,   182,   189,   196,   190,   288,
     163,   270,   200,   207,   216,   224,   234,   244,   250,   259,
     260,   261,   235,   236,   237,   238,   245,   217,   289,   271,
     201,   290,   272,   208,   291,   292,   293,   294,   295,   183,
     239,   296,   251,   273,   225,   262,   209,   218,   184,   297,
     252,   274,   226,   210,   219,   123,   125,   127,   149,   113,
     119,   147,   129,   131,   133,   135,   137,   139,   141,   144,
      64,    65,   151,   300,    66,    67
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint16 yytable[] =
{
      72,    73,    74,   359,   360,    69,    70,    77,    68,   112,
     298,    78,    34,   188,    80,   194,    81,    82,    83,    75,
      84,    85,    86,   116,   118,   120,    76,   124,   126,   128,
     130,   132,   134,   136,   138,   140,   140,   143,    34,   146,
     148,   150,    79,    69,    70,    69,    70,    87,    89,   299,
      90,   406,   108,   109,   110,     1,     2,     3,    69,    70,
     455,   456,   152,    91,   312,    92,     4,   301,   302,   303,
     304,   305,     5,   114,     6,     7,   115,    93,    94,    95,
      96,    97,    98,     8,    99,     9,    10,    11,    12,   100,
      13,    14,   101,   102,   103,    15,    16,    17,   104,    18,
      19,    20,   458,    21,    22,   105,   111,    23,    24,    25,
     461,   164,   165,   106,   107,   195,   307,   471,   356,   308,
     309,   310,   314,   315,     2,     3,   316,   317,   318,   167,
     319,   320,   321,   175,     4,   153,   154,   155,   275,   276,
     322,   323,     6,     7,   277,   278,   279,   280,   281,   282,
     283,     8,   324,   325,    10,    11,    12,   326,    13,    14,
     327,   311,   313,    15,   328,    17,   329,    18,   330,   331,
     284,    21,    22,     2,     3,    23,    24,    25,   362,   332,
     285,   333,   334,     4,   153,   154,   155,   227,   228,   335,
     336,     6,     7,   337,   338,   339,   340,   341,   342,   343,
       8,   344,   345,    10,    11,    12,   346,    13,    14,   229,
     230,   231,    15,   347,    17,   348,    18,   349,   350,   351,
      21,    22,   240,   352,    23,    24,    25,     2,     3,   241,
     353,   354,   355,   145,   243,   363,   408,     4,   153,   154,
     155,   227,   228,   409,   410,     6,     7,   411,   416,   418,
     419,   420,   421,   423,     8,   424,   426,    10,    11,    12,
     427,    13,    14,   229,   230,   231,    15,   429,    17,   431,
      18,   432,   433,   434,    21,    22,   435,   437,    23,    24,
      25,   439,   440,   232,   442,   443,   444,   446,   447,   448,
     449,   450,   451,   452,   453,   460,   474,   484,   413,   485,
     486,   487,   488,   489,   490,   491,   492,   361,   493,   494,
      88,   364,   142,     0,   367,     0,   369,     0,     0,   372,
       0,     0,   375,     0,     0,   378,     0,   380,     0,   382,
     383,   384,   385,   386,     0,   388,     0,   390,   391,     0,
       0,     0,   395,     0,     0,     0,     0,     0,     0,     0,
       0,   404,   405,   365,   366,     0,   368,     0,   370,   371,
       0,   373,   374,     0,   376,   377,     0,   379,     0,   381,
       0,     0,     0,     0,     0,   387,     0,   389,     0,     0,
     392,   393,   394,     0,   396,   397,   398,   399,   400,   401,
     402,   403,     0,     0,     0,   407,     0,     0,     0,     0,
       0,     0,   454,   414,   415,     0,   417,     0,     0,   459,
       0,   422,     0,     0,   425,     0,     0,   428,     0,   430,
       0,     0,     0,     0,     0,   436,     0,   438,     0,     0,
     441,     0,     0,     0,   445,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   457,     0,     0,     0,     0,
       0,   472,     0,     0,     0,   462,     0,     0,     0,     0,
     463,     0,     0,   464,     0,     0,   465,     0,   466,     0,
       0,     0,     0,     0,   467,     0,   468,     0,     0,   469,
       0,     0,     0,   470,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   473,     0,     0,     0,     0,     0,     0,
     475,   476,   477,   478,   479,   480,   481,   482,   483,     2,
       3,     0,     0,     0,     0,     0,     0,     0,     0,     4,
     153,   154,   155,   178,   179,     0,     0,     6,     7,     0,
       0,     0,     0,     0,     0,     0,     8,     0,     0,    10,
      11,    12,     0,    13,    14,     0,     0,     0,    15,     0,
      17,     0,    18,     0,     0,     0,    21,    22,   185,   191,
      23,    24,    25,     2,     3,   192,     0,     0,     0,     0,
       0,     0,     0,     4,   153,   154,   155,   264,   265,     0,
       0,     6,     7,   266,   267,     0,     0,     0,     0,     0,
       8,     0,     0,    10,    11,    12,     0,    13,    14,     0,
       0,     0,    15,     0,    17,     0,    18,     0,     0,     0,
      21,    22,     2,     3,    23,    24,    25,     0,     0,   268,
       0,     0,     4,   153,   154,   155,   178,   179,     0,     0,
       6,     7,     0,     0,     0,     0,     0,     0,     0,     8,
       0,     0,    10,    11,    12,     0,    13,    14,     0,     0,
       0,    15,     0,    17,     0,    18,     0,     0,     0,    21,
      22,   185,     0,    23,    24,    25,     2,     3,   186,     0,
       0,     0,     0,     0,     0,     0,     4,   153,   154,   155,
     202,   203,     0,     0,     6,     7,     0,   204,     0,     0,
       0,     0,     0,     8,     0,     0,    10,    11,    12,     0,
      13,    14,     0,     0,     0,    15,     0,    17,     0,    18,
       0,     0,     0,    21,    22,     2,     3,    23,    24,    25,
       0,     0,   205,     0,     0,     4,   153,   154,   155,   211,
     212,     0,     0,     6,     7,     0,     0,     0,     0,     0,
       0,     0,     8,     0,     0,    10,    11,    12,   213,    13,
      14,     0,     0,     0,    15,     0,    17,     0,    18,     0,
       0,     0,    21,    22,     2,     3,    23,    24,    25,     0,
       0,   214,     0,     0,     4,   153,   154,   155,   254,   255,
       0,     0,     6,     7,     0,     0,     0,     0,     0,     0,
       0,     8,     0,     0,    10,    11,    12,     0,    13,    14,
       0,     0,     0,    15,     0,    17,   256,    18,     0,     0,
       0,    21,    22,     2,     3,    23,    24,    25,     0,     0,
     257,     0,     0,     4,   153,   154,   155,   178,   179,     0,
       0,     6,     7,     0,     0,     0,     0,     0,     0,     0,
       8,     0,     0,    10,    11,    12,     0,    13,    14,     0,
       0,     0,    15,     0,    17,     0,    18,     0,     0,     0,
      21,    22,     2,     3,    23,    24,    25,     0,     0,   180,
       0,     0,     4,   153,   154,   155,   220,   221,     0,     0,
       6,     7,     0,     0,     0,     0,     0,     0,     0,     8,
       0,     0,    10,    11,    12,     0,    13,    14,     0,     0,
       0,    15,     0,    17,     0,    18,     0,     0,     0,    21,
      22,     2,     3,    23,    24,    25,     0,     0,   222,     0,
       0,     4,   153,   154,   155,   246,   247,     0,     0,     6,
       7,     0,     0,     0,     0,     0,     0,     0,     8,     0,
       0,    10,    11,    12,     0,    13,    14,     0,     0,     0,
      15,     0,    17,     0,    18,     0,     0,     0,    21,    22,
       2,     3,    23,    24,    25,     0,     0,   248,     0,     0,
       4,   153,   154,   155,   246,   247,     0,     0,     6,     7,
       0,     0,     0,     0,     0,     0,     0,     8,     0,     0,
      10,    11,    12,     0,    13,    14,     0,     0,     0,    15,
       0,    17,     0,    18,     0,     0,     0,    21,    22,     2,
       3,    23,    24,    25,     0,     0,   253,     0,     0,     4,
     153,   154,   155,   178,   179,     0,     0,     6,     7,     0,
       0,     0,     0,     0,     0,     0,     8,     0,     0,    10,
      11,    12,     0,    13,    14,     0,     0,     0,    15,     0,
      17,     0,    18,     0,     0,     0,    21,    22,     2,     3,
      23,    24,    25,     0,     0,   263,     0,     0,     4,   153,
     154,   155,     0,     0,     0,     0,     6,     7,     0,     0,
       0,     0,     0,     0,     0,     8,   156,     0,    10,    11,
      12,     0,    13,    14,     0,     0,     0,    15,     0,    17,
       0,    18,     0,     0,     0,    21,    22,     2,     3,    23,
      24,    25,     0,     0,   157,     0,     0,     4,   153,   154,
     155,     0,     0,     0,     0,     6,     7,   197,     0,     0,
       0,     0,     0,     0,     8,     0,     0,    10,    11,    12,
       0,    13,    14,     0,     0,     0,    15,     0,    17,     0,
      18,     0,     0,     0,    21,    22,     2,     3,    23,    24,
      25,     0,     0,   198,     0,     0,     4,   153,   154,   155,
       0,     0,     0,     0,     6,     7,     0,     0,     0,     0,
       0,     0,     0,     8,     0,     0,    10,    11,    12,     0,
      13,    14,     2,     3,   170,    15,     0,    17,     0,    18,
     171,   172,     4,    21,    22,     0,     0,    23,    24,    25,
       6,     7,   168,     0,     0,     0,     0,     0,     0,     8,
       0,     0,    10,    11,    12,     0,    13,    14,     2,     3,
       0,    15,     0,    17,     0,    18,     0,     0,     4,    21,
      22,     0,     0,    23,    24,    25,     6,     7,   173,     0,
       0,     0,     0,     0,     0,     8,     0,     0,    10,    11,
      12,     0,    13,    14,     0,     0,     0,    15,     0,    17,
       0,    18,     1,     2,     3,    21,    22,     0,     0,    23,
      24,    25,     0,     4,   166,     0,     0,     0,     0,     5,
       0,     6,     7,     0,     0,     0,     0,     0,     0,     0,
       8,     0,     9,    10,    11,    12,     0,    13,    14,     0,
       0,     0,    15,    16,    17,     0,    18,    19,    20,     0,
      21,    22,   162,     0,    23,    24,    25,     0,   169,     0,
       0,     0,     0,     0,   187,     0,   193,     0,   199,     0,
     206,     0,   215,     0,   223,     0,   233,     0,   242,     0,
     249,   249,     0,   258,     0,     0,   269,     0,   287
};

static const yytype_int16 yycheck[] =
{
       3,     4,     5,   308,   309,     6,     7,    10,    63,    75,
      26,    14,     0,   125,    17,   127,    19,    20,    21,    63,
      23,    24,    25,    89,    90,    91,    63,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,    26,   105,
     106,   107,    63,     6,     7,     6,     7,     0,    63,    65,
      63,   356,     3,     4,     5,     8,     9,    10,     6,     7,
      64,    65,    64,    63,    65,    63,    19,    12,    13,    14,
      15,    16,    25,    76,    27,    28,    79,    63,    63,    63,
      63,    63,    63,    36,    63,    38,    39,    40,    41,    63,
      43,    44,    63,    63,    63,    48,    49,    50,    63,    52,
      53,    54,    65,    56,    57,    63,    68,    60,    61,    62,
     415,   114,   115,    63,    63,   127,    63,    65,    64,    63,
      63,    63,    63,    63,     9,    10,    63,    63,    63,   117,
      63,    63,    63,   121,    19,    20,    21,    22,    23,    24,
      63,    63,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    63,    63,    39,    40,    41,    63,    43,    44,
      63,   164,   165,    48,    63,    50,    63,    52,    63,    63,
      55,    56,    57,     9,    10,    60,    61,    62,    65,    63,
      65,    63,    63,    19,    20,    21,    22,    23,    24,    63,
      63,    27,    28,    63,    63,    63,    63,    63,    63,    63,
      36,    63,    63,    39,    40,    41,    63,    43,    44,    45,
      46,    47,    48,    63,    50,    63,    52,    63,    63,    63,
      56,    57,    58,    63,    60,    61,    62,     9,    10,    65,
      63,    63,    63,   104,   139,    65,    65,    19,    20,    21,
      22,    23,    24,    65,    65,    27,    28,    65,    65,    65,
      65,    65,    65,    65,    36,    65,    65,    39,    40,    41,
      65,    43,    44,    45,    46,    47,    48,    65,    50,    65,
      52,    65,    65,    65,    56,    57,    65,    65,    60,    61,
      62,    65,    65,    65,    65,    65,    65,    65,    65,    65,
      65,    65,    65,    65,    65,    65,    65,    65,   364,    65,
      65,    65,    65,    65,    65,    65,    65,   310,    65,    65,
      26,   314,   102,    -1,   317,    -1,   319,    -1,    -1,   322,
      -1,    -1,   325,    -1,    -1,   328,    -1,   330,    -1,   332,
     333,   334,   335,   336,    -1,   338,    -1,   340,   341,    -1,
      -1,    -1,   345,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   354,   355,   315,   316,    -1,   318,    -1,   320,   321,
      -1,   323,   324,    -1,   326,   327,    -1,   329,    -1,   331,
      -1,    -1,    -1,    -1,    -1,   337,    -1,   339,    -1,    -1,
     342,   343,   344,    -1,   346,   347,   348,   349,   350,   351,
     352,   353,    -1,    -1,    -1,   357,    -1,    -1,    -1,    -1,
      -1,    -1,   405,   365,   366,    -1,   368,    -1,    -1,   412,
      -1,   373,    -1,    -1,   376,    -1,    -1,   379,    -1,   381,
      -1,    -1,    -1,    -1,    -1,   387,    -1,   389,    -1,    -1,
     392,    -1,    -1,    -1,   396,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   407,    -1,    -1,    -1,    -1,
      -1,   454,    -1,    -1,    -1,   417,    -1,    -1,    -1,    -1,
     422,    -1,    -1,   425,    -1,    -1,   428,    -1,   430,    -1,
      -1,    -1,    -1,    -1,   436,    -1,   438,    -1,    -1,   441,
      -1,    -1,    -1,   445,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   455,    -1,    -1,    -1,    -1,    -1,    -1,
     462,   463,   464,   465,   466,   467,   468,   469,   470,     9,
      10,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    19,
      20,    21,    22,    23,    24,    -1,    -1,    27,    28,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    36,    -1,    -1,    39,
      40,    41,    -1,    43,    44,    -1,    -1,    -1,    48,    -1,
      50,    -1,    52,    -1,    -1,    -1,    56,    57,    58,    59,
      60,    61,    62,     9,    10,    65,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    19,    20,    21,    22,    23,    24,    -1,
      -1,    27,    28,    29,    30,    -1,    -1,    -1,    -1,    -1,
      36,    -1,    -1,    39,    40,    41,    -1,    43,    44,    -1,
      -1,    -1,    48,    -1,    50,    -1,    52,    -1,    -1,    -1,
      56,    57,     9,    10,    60,    61,    62,    -1,    -1,    65,
      -1,    -1,    19,    20,    21,    22,    23,    24,    -1,    -1,
      27,    28,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,
      -1,    -1,    39,    40,    41,    -1,    43,    44,    -1,    -1,
      -1,    48,    -1,    50,    -1,    52,    -1,    -1,    -1,    56,
      57,    58,    -1,    60,    61,    62,     9,    10,    65,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    19,    20,    21,    22,
      23,    24,    -1,    -1,    27,    28,    -1,    30,    -1,    -1,
      -1,    -1,    -1,    36,    -1,    -1,    39,    40,    41,    -1,
      43,    44,    -1,    -1,    -1,    48,    -1,    50,    -1,    52,
      -1,    -1,    -1,    56,    57,     9,    10,    60,    61,    62,
      -1,    -1,    65,    -1,    -1,    19,    20,    21,    22,    23,
      24,    -1,    -1,    27,    28,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    36,    -1,    -1,    39,    40,    41,    42,    43,
      44,    -1,    -1,    -1,    48,    -1,    50,    -1,    52,    -1,
      -1,    -1,    56,    57,     9,    10,    60,    61,    62,    -1,
      -1,    65,    -1,    -1,    19,    20,    21,    22,    23,    24,
      -1,    -1,    27,    28,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    36,    -1,    -1,    39,    40,    41,    -1,    43,    44,
      -1,    -1,    -1,    48,    -1,    50,    51,    52,    -1,    -1,
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
      19,    20,    21,    22,    23,    24,    -1,    -1,    27,    28,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,    -1,    -1,
      39,    40,    41,    -1,    43,    44,    -1,    -1,    -1,    48,
      -1,    50,    -1,    52,    -1,    -1,    -1,    56,    57,     9,
      10,    60,    61,    62,    -1,    -1,    65,    -1,    -1,    19,
      20,    21,    22,    23,    24,    -1,    -1,    27,    28,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    36,    -1,    -1,    39,
      40,    41,    -1,    43,    44,    -1,    -1,    -1,    48,    -1,
      50,    -1,    52,    -1,    -1,    -1,    56,    57,     9,    10,
      60,    61,    62,    -1,    -1,    65,    -1,    -1,    19,    20,
      21,    22,    -1,    -1,    -1,    -1,    27,    28,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    36,    37,    -1,    39,    40,
      41,    -1,    43,    44,    -1,    -1,    -1,    48,    -1,    50,
      -1,    52,    -1,    -1,    -1,    56,    57,     9,    10,    60,
      61,    62,    -1,    -1,    65,    -1,    -1,    19,    20,    21,
      22,    -1,    -1,    -1,    -1,    27,    28,    29,    -1,    -1,
      -1,    -1,    -1,    -1,    36,    -1,    -1,    39,    40,    41,
      -1,    43,    44,    -1,    -1,    -1,    48,    -1,    50,    -1,
      52,    -1,    -1,    -1,    56,    57,     9,    10,    60,    61,
      62,    -1,    -1,    65,    -1,    -1,    19,    20,    21,    22,
      -1,    -1,    -1,    -1,    27,    28,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    36,    -1,    -1,    39,    40,    41,    -1,
      43,    44,     9,    10,    11,    48,    -1,    50,    -1,    52,
      17,    18,    19,    56,    57,    -1,    -1,    60,    61,    62,
      27,    28,    65,    -1,    -1,    -1,    -1,    -1,    -1,    36,
      -1,    -1,    39,    40,    41,    -1,    43,    44,     9,    10,
      -1,    48,    -1,    50,    -1,    52,    -1,    -1,    19,    56,
      57,    -1,    -1,    60,    61,    62,    27,    28,    65,    -1,
      -1,    -1,    -1,    -1,    -1,    36,    -1,    -1,    39,    40,
      41,    -1,    43,    44,    -1,    -1,    -1,    48,    -1,    50,
      -1,    52,     8,     9,    10,    56,    57,    -1,    -1,    60,
      61,    62,    -1,    19,    65,    -1,    -1,    -1,    -1,    25,
      -1,    27,    28,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      36,    -1,    38,    39,    40,    41,    -1,    43,    44,    -1,
      -1,    -1,    48,    49,    50,    -1,    52,    53,    54,    -1,
      56,    57,   113,    -1,    60,    61,    62,    -1,   119,    -1,
      -1,    -1,    -1,    -1,   125,    -1,   127,    -1,   129,    -1,
     131,    -1,   133,    -1,   135,    -1,   137,    -1,   139,    -1,
     141,   142,    -1,   144,    -1,    -1,   147,    -1,   149
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
     108,   109,   110,   111,   186,   187,   190,   191,    63,     6,
       7,    73,    73,    73,    73,    63,    63,    73,    73,    63,
      73,    73,    73,    73,    73,    73,    73,     0,    68,    63,
      63,    63,    63,    63,    63,    63,    63,    63,    63,    63,
      63,    63,    63,    63,    63,    63,    63,    63,     3,     4,
       5,    69,    81,   175,    73,    73,    81,   114,    81,   176,
      81,   115,    81,   171,    81,   172,    81,   173,    81,   178,
      81,   179,    81,   180,    81,   181,    81,   182,    81,   183,
      81,   184,   184,    81,   185,   171,    81,   177,    81,   174,
      81,   188,    64,    20,    21,    22,    37,    65,    82,   116,
     117,   118,   120,   126,    73,    73,    65,    82,    65,   120,
      11,    17,    18,    65,    80,    82,   112,   113,    23,    24,
      65,   120,   121,   155,   164,    58,    65,   120,   121,   122,
     124,    59,    65,   120,   121,   122,   123,    29,    65,   120,
     128,   146,    23,    24,    30,    65,   120,   129,   149,   162,
     169,    23,    24,    42,    65,   120,   130,   143,   163,   170,
      23,    24,    65,   120,   131,   160,   168,    23,    24,    45,
      46,    47,    65,   120,   132,   138,   139,   140,   141,   156,
      58,    65,   120,   132,   133,   142,    23,    24,    65,   120,
     134,   158,   166,    65,    23,    24,    51,    65,   120,   135,
     136,   137,   161,    65,    23,    24,    29,    30,    65,   120,
     127,   145,   148,   159,   167,    23,    24,    29,    30,    31,
      32,    33,    34,    35,    55,    65,   119,   120,   125,   144,
     147,   150,   151,   152,   153,   154,   157,   165,    26,    65,
     189,    12,    13,    14,    15,    16,    72,    63,    63,    63,
      63,    73,    65,    73,    63,    63,    63,    63,    63,    63,
      63,    63,    63,    63,    63,    63,    63,    63,    63,    63,
      63,    63,    63,    63,    63,    63,    63,    63,    63,    63,
      63,    63,    63,    63,    63,    63,    63,    63,    63,    63,
      63,    63,    63,    63,    63,    63,    64,    69,    70,    70,
      70,    73,    65,    65,    73,    69,    69,    73,    69,    73,
      69,    69,    73,    69,    69,    73,    69,    69,    73,    69,
      73,    69,    73,    73,    73,    73,    73,    69,    73,    69,
      73,    73,    69,    69,    69,    73,    69,    69,    69,    69,
      69,    69,    69,    69,    73,    73,    70,    69,    65,    65,
      65,    65,    79,    81,    69,    69,    65,    69,    65,    65,
      65,    65,    69,    65,    65,    69,    65,    65,    69,    65,
      69,    65,    65,    65,    65,    65,    69,    65,    69,    65,
      65,    69,    65,    65,    65,    69,    65,    65,    65,    65,
      65,    65,    65,    65,    73,    64,    65,    69,    65,    73,
      65,    70,    69,    69,    69,    69,    69,    69,    69,    69,
      69,    65,    73,    69,    65,    69,    69,    69,    69,    69,
      69,    69,    69,    69,    65,    65,    65,    65,    65,    65,
      65,    65,    65,    65,    65
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
     113,   114,   114,   115,   115,   115,   115,   115,   116,   117,
     118,   119,   120,   120,   120,   120,   121,   121,   122,   123,
     124,   125,   125,   125,   125,   125,   125,   125,   125,   125,
     125,   126,   127,   127,   127,   127,   128,   129,   129,   129,
     130,   130,   130,   131,   131,   132,   132,   132,   132,   132,
     133,   134,   134,   135,   135,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   163,   164,   165,   166,   167,   168,   169,
     170,   171,   171,   171,   172,   172,   172,   172,   173,   173,
     173,   173,   173,   174,   174,   174,   175,   175,   175,   176,
     176,   177,   177,   177,   178,   178,   178,   179,   179,   179,
     180,   180,   180,   181,   181,   181,   182,   182,   182,   183,
     183,   183,   183,   184,   184,   184,   185,   185,   185,   186,
     186,   186,   187,   188,   188,   189,   189,   190,   190,   191
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     8,    10,     1,     1,     1,     1,     1,
       1,     1,     2,     2,     2,     4,     4,     2,     1,     5,
       0,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     2,     2,     2,     2,     1,     1,
       1,     2,     2,     1,     1,     2,     1,     1,     1,     5,
       6,     2,     1,     2,     2,     2,     2,     1,     4,     4,
       4,     4,     1,     1,     1,     1,     1,     1,     1,     4,
       4,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     4,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     4,     7,     4,     4,
       4,     7,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     7,     7,     7,     7,     7,     7,
       7,     2,     2,     1,     2,     2,     2,     1,     2,     2,
       2,     2,     1,     2,     2,     1,     2,     2,     1,     2,
       1,     2,     2,     1,     2,     2,     1,     2,     2,     1,
       2,     2,     1,     2,     2,     1,     2,     2,     1,     2,
       2,     2,     1,     2,     2,     1,     2,     2,     1,     2,
       2,     2,     4,     2,     1,     5,     6,     5,     6,     6
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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
  YYUSE (yytype);
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
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
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
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
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
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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
            /* Fall through.  */
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

  if (! yyres)
    return yystrlen (yystr);

  return (YYSIZE_T) (yystpcpy (yyres, yystr) - yyres);
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
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

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
      int yyn = yypact[*yyssp];
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
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
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
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
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
          yyp++;
          yyformat++;
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
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

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
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
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
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = (yytype_int16) yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = (YYSIZE_T) (yyssp - yyss + 1);

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
| yyreduce -- Do a reduction.  |
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
#line 190 "dna.yxx" /* yacc.c:1645  */
    {
  (yyval.u.real) = (double)(yyvsp[0].u.uint64);
}
#line 1970 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 10:
#line 194 "dna.yxx" /* yacc.c:1645  */
    {
  (yyval.u.real) = (double)(yyvsp[0].u.int64);
}
#line 1978 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 11:
#line 198 "dna.yxx" /* yacc.c:1645  */
    {
  (yyval.u.real) = (yyvsp[0].u.real);
}
#line 1986 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 12:
#line 203 "dna.yxx" /* yacc.c:1645  */
    {
  LPoint3f p((yyvsp[-2].u.real), (yyvsp[-1].u.real), (yyvsp[0].u.real));
  (yyval.point3) = p;
}
#line 1995 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 13:
#line 209 "dna.yxx" /* yacc.c:1645  */
    {
  PT(DNASuitPoint) point = new DNASuitPoint((yyvsp[-5].u.real), (DNASuitPoint::PointType)(yyvsp[-3].u.uint64), (yyvsp[-1].point3));
  _store->store_suit_point(point);
}
#line 2004 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 14:
#line 214 "dna.yxx" /* yacc.c:1645  */
    {
  PT(DNASuitPoint) point = new DNASuitPoint((yyvsp[-7].u.real), (DNASuitPoint::PointType)(yyvsp[-5].u.uint64), (yyvsp[-3].point3), (yyvsp[-1].u.real));
  _store->store_suit_point(point);
}
#line 2013 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 15:
#line 220 "dna.yxx" /* yacc.c:1645  */
    {
  #undef DNA_STREET_POINT
  (yyval.u.uint64) = (uint64_t)DNASuitPoint::STREET_POINT;
}
#line 2022 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 16:
#line 225 "dna.yxx" /* yacc.c:1645  */
    {
  #undef DNA_FRONT_DOOR_POINT
  (yyval.u.uint64) = (uint64_t)DNASuitPoint::FRONT_DOOR_POINT;
}
#line 2031 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 17:
#line 230 "dna.yxx" /* yacc.c:1645  */
    {
  #undef DNA_SIDE_DOOR_POINT
  (yyval.u.uint64) = (uint64_t)DNASuitPoint::SIDE_DOOR_POINT;
}
#line 2040 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 18:
#line 235 "dna.yxx" /* yacc.c:1645  */
    {
  #undef DNA_COGHQ_IN_POINT
  (yyval.u.uint64) = (uint64_t)DNASuitPoint::COGHQ_IN_POINT;
}
#line 2049 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 19:
#line 240 "dna.yxx" /* yacc.c:1645  */
    {
  #undef DNA_COGHQ_OUT_POINT
  (yyval.u.uint64) = (uint64_t)DNASuitPoint::COGHQ_OUT_POINT;
}
#line 2058 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 20:
#line 246 "dna.yxx" /* yacc.c:1645  */
    {
  (yyval.str) = (yyvsp[0].str);
}
#line 2066 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 21:
#line 250 "dna.yxx" /* yacc.c:1645  */
    {
  (yyval.str) = (yyvsp[0].str);
}
#line 2074 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 22:
#line 255 "dna.yxx" /* yacc.c:1645  */
    {
  PT(DNAGroup) g = new DNAGroup((yyvsp[0].str));
  g->set_parent(_cur_comp);
  g->set_vis_group(_cur_comp->get_vis_group());
  _cur_comp->add(g);
  _cur_comp = g;
}
#line 2086 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 23:
#line 264 "dna.yxx" /* yacc.c:1645  */
    {
  PT(DNAGroup) g = new DNANode((yyvsp[0].str));
  g->set_parent(_cur_comp);
  g->set_vis_group(_cur_comp->get_vis_group());
  _cur_comp->add(g);
  _cur_comp = g;
}
#line 2098 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 24:
#line 273 "dna.yxx" /* yacc.c:1645  */
    {
  PT(DNAGroup) g = new DNAVisGroup((yyvsp[0].str));
  g->set_parent(_cur_comp);
  _cur_comp->add(g);
  _cur_comp = g;
  _store->store_DNA_vis_group(DCAST(DNAVisGroup, g));
}
#line 2110 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 25:
#line 282 "dna.yxx" /* yacc.c:1645  */
    {
  _cur_comp = _cur_comp->get_parent();
}
#line 2118 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 26:
#line 287 "dna.yxx" /* yacc.c:1645  */
    {
  _cur_comp = _cur_comp->get_parent();
}
#line 2126 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 27:
#line 292 "dna.yxx" /* yacc.c:1645  */
    {
  (yyvsp[-1].str_vec).push_back((yyvsp[0].str));
  (yyval.str_vec) = (yyvsp[-1].str_vec);
}
#line 2135 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 28:
#line 297 "dna.yxx" /* yacc.c:1645  */
    {
  (yyval.str_vec) = {};
}
#line 2143 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 29:
#line 302 "dna.yxx" /* yacc.c:1645  */
    {
  DCAST(DNAVisGroup, _cur_comp)->add_visible((yyvsp[-2].str));
  for (auto& vis : (yyvsp[-1].str_vec))
    DCAST(DNAVisGroup, _cur_comp)->add_visible(vis);
}
#line 2153 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 47:
#line 332 "dna.yxx" /* yacc.c:1645  */
    {
  _cur_comp = _cur_comp->get_parent();
}
#line 2161 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 48:
#line 337 "dna.yxx" /* yacc.c:1645  */
    {
  _cur_comp = _cur_comp->get_parent();
}
#line 2169 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 49:
#line 342 "dna.yxx" /* yacc.c:1645  */
    {
  _cur_comp = _cur_comp->get_parent();
}
#line 2177 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 50:
#line 347 "dna.yxx" /* yacc.c:1645  */
    {
  _cur_comp = _cur_comp->get_parent();
}
#line 2185 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 51:
#line 351 "dna.yxx" /* yacc.c:1645  */
    {
  _cur_comp = _cur_comp->get_parent();
}
#line 2193 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 52:
#line 355 "dna.yxx" /* yacc.c:1645  */
    {
  _cur_comp = _cur_comp->get_parent();
}
#line 2201 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 53:
#line 360 "dna.yxx" /* yacc.c:1645  */
    {
  _cur_comp = _cur_comp->get_parent();
}
#line 2209 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 55:
#line 368 "dna.yxx" /* yacc.c:1645  */
    {
  _cur_comp = _cur_comp->get_parent();
}
#line 2217 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 56:
#line 373 "dna.yxx" /* yacc.c:1645  */
    {
  _cur_comp = _cur_comp->get_parent();
}
#line 2225 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 57:
#line 378 "dna.yxx" /* yacc.c:1645  */
    {
  _cur_comp = _cur_comp->get_parent();
}
#line 2233 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 58:
#line 383 "dna.yxx" /* yacc.c:1645  */
    {
  _cur_comp = _cur_comp->get_parent();
}
#line 2241 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 59:
#line 388 "dna.yxx" /* yacc.c:1645  */
    {
  _cur_comp = _cur_comp->get_parent();
}
#line 2249 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 60:
#line 392 "dna.yxx" /* yacc.c:1645  */
    {
  _cur_comp = _cur_comp->get_parent();
}
#line 2257 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 61:
#line 397 "dna.yxx" /* yacc.c:1645  */
    {
  _cur_comp = _cur_comp->get_parent();
}
#line 2265 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 62:
#line 402 "dna.yxx" /* yacc.c:1645  */
    {
  _cur_comp = _cur_comp->get_parent();
}
#line 2273 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 63:
#line 406 "dna.yxx" /* yacc.c:1645  */
    {
  _cur_comp = _cur_comp->get_parent();
}
#line 2281 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 64:
#line 411 "dna.yxx" /* yacc.c:1645  */
    {
  PT(DNAGroup) g = new DNAProp((yyvsp[0].str));
  g->set_parent(_cur_comp);
  g->set_vis_group(_cur_comp->get_vis_group());
  _cur_comp->add(g);
  _cur_comp = g;
}
#line 2293 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 65:
#line 420 "dna.yxx" /* yacc.c:1645  */
    {
  PT(DNAGroup) g = new DNAAnimProp((yyvsp[0].str));
  g->set_parent(_cur_comp);
  g->set_vis_group(_cur_comp->get_vis_group());
  _cur_comp->add(g);
  _cur_comp = g;
}
#line 2305 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 66:
#line 429 "dna.yxx" /* yacc.c:1645  */
    {
  PT(DNAGroup) g = new DNAInteractiveProp((yyvsp[0].str));
  g->set_parent(_cur_comp);
  g->set_vis_group(_cur_comp->get_vis_group());
  _cur_comp->add(g);
  _cur_comp = g;
}
#line 2317 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 67:
#line 438 "dna.yxx" /* yacc.c:1645  */
    {
  PT(DNAGroup) g = new DNAFlatBuilding((yyvsp[0].str));
  g->set_parent(_cur_comp);
  g->set_vis_group(_cur_comp->get_vis_group());
  _cur_comp->add(g);
  _cur_comp = g;
}
#line 2329 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 68:
#line 447 "dna.yxx" /* yacc.c:1645  */
    {
  PT(DNAGroup) g = new DNAWall("wall");
  g->set_parent(_cur_comp);
  g->set_vis_group(_cur_comp->get_vis_group());
  _cur_comp->add(g);
  _cur_comp = g;
}
#line 2341 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 69:
#line 456 "dna.yxx" /* yacc.c:1645  */
    {
  PT(DNAGroup) g = new DNAWindows("windows");
  g->set_parent(_cur_comp);
  g->set_vis_group(_cur_comp->get_vis_group());
  _cur_comp->add(g);
  _cur_comp = g;
}
#line 2353 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 70:
#line 465 "dna.yxx" /* yacc.c:1645  */
    {
  PT(DNAGroup) g = new DNACornice("cornice");
  g->set_parent(_cur_comp);
  g->set_vis_group(_cur_comp->get_vis_group());
  _cur_comp->add(g);
  _cur_comp = g;
}
#line 2365 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 71:
#line 474 "dna.yxx" /* yacc.c:1645  */
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
#line 2382 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 72:
#line 488 "dna.yxx" /* yacc.c:1645  */
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
#line 2399 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 73:
#line 502 "dna.yxx" /* yacc.c:1645  */
    {
  PT(DNAGroup) g = new DNADoor("door");
  g->set_parent(_cur_comp);
  g->set_vis_group(_cur_comp->get_vis_group());
  _cur_comp->add(g);
  _cur_comp = g;
}
#line 2411 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 74:
#line 511 "dna.yxx" /* yacc.c:1645  */
    {
  PT(DNAGroup) g = new DNAFlatDoor("flat_door");
  g->set_parent(_cur_comp);
  g->set_vis_group(_cur_comp->get_vis_group());
  _cur_comp->add(g);
  DCAST(DNAFlatBuilding, _cur_comp->get_parent())->set_has_door(true);
  _cur_comp = g;
}
#line 2424 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 75:
#line 521 "dna.yxx" /* yacc.c:1645  */
    {
  PT(DNAGroup) g = new DNAStreet((yyvsp[0].str));
  g->set_parent(_cur_comp);
  g->set_vis_group(_cur_comp->get_vis_group());
  _cur_comp->add(g);
  _cur_comp = g;
}
#line 2436 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 76:
#line 530 "dna.yxx" /* yacc.c:1645  */
    {
  PT(DNAGroup) g = new DNASign("sign");
  g->set_parent(_cur_comp);
  g->set_vis_group(_cur_comp->get_vis_group());
  _cur_comp->add(g);
  _cur_comp = g;
}
#line 2448 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 77:
#line 539 "dna.yxx" /* yacc.c:1645  */
    {
  PT(DNAGroup) g = new DNASignGraphic("graphic");
  g->set_parent(_cur_comp);
  g->set_vis_group(_cur_comp->get_vis_group());
  _cur_comp->add(g);
  _cur_comp = g;
}
#line 2460 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 78:
#line 548 "dna.yxx" /* yacc.c:1645  */
    {
  PT(DNAGroup) g = new DNASignBaseline("baseline");
  g->set_parent(_cur_comp);
  g->set_vis_group(_cur_comp->get_vis_group());
  _cur_comp->add(g);
  _cur_comp = g;
}
#line 2472 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 79:
#line 557 "dna.yxx" /* yacc.c:1645  */
    {
  PT(DNASuitEdge) edge = _store->store_suit_edge((yyvsp[-2].u.real), (yyvsp[-1].u.real), atoi(_cur_comp->get_name().c_str()));
  if (!edge) {
    dnayyerror("store_suit_edge failed");
  }
  DCAST(DNAVisGroup, _cur_comp)->add_suit_edge(edge);
}
#line 2484 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 80:
#line 566 "dna.yxx" /* yacc.c:1645  */
    {
  PT(DNABattleCell) cell = new DNABattleCell((yyvsp[-3].u.real), (yyvsp[-2].u.real), (yyvsp[-1].point3));
  DCAST(DNAVisGroup, _cur_comp)->add_battle_cell(cell);
}
#line 2493 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 88:
#line 583 "dna.yxx" /* yacc.c:1645  */
    {
  DCAST(DNANode, _cur_comp)->set_pos((yyvsp[-1].point3));
}
#line 2501 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 89:
#line 588 "dna.yxx" /* yacc.c:1645  */
    {
  DCAST(DNANode, _cur_comp)->set_hpr((yyvsp[-1].point3));
}
#line 2509 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 90:
#line 593 "dna.yxx" /* yacc.c:1645  */
    {
  DCAST(DNANode, _cur_comp)->set_scale((yyvsp[-1].point3));
}
#line 2517 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 91:
#line 598 "dna.yxx" /* yacc.c:1645  */
    {
  DCAST(DNASignBaseline, _cur_comp)->set_flags((yyvsp[-1].str));
}
#line 2525 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 99:
#line 616 "dna.yxx" /* yacc.c:1645  */
    {
  DCAST(DNAInteractiveProp, _cur_comp)->set_cell_id((yyvsp[-1].u.real));
}
#line 2533 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 100:
#line 621 "dna.yxx" /* yacc.c:1645  */
    {
  DCAST(DNAAnimProp, _cur_comp)->set_anim_name((yyvsp[-1].str));
}
#line 2541 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 111:
#line 638 "dna.yxx" /* yacc.c:1645  */
    {
  DCAST(DNASignBaseline, _cur_comp)->m_text += (yyvsp[-1].str);
}
#line 2549 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 136:
#line 685 "dna.yxx" /* yacc.c:1645  */
    {
  DCAST(DNAStreet, _cur_comp)->set_texture((yyvsp[-1].str));
}
#line 2557 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 137:
#line 690 "dna.yxx" /* yacc.c:1645  */
    {
  LVecBase4f color((yyvsp[-4].u.real), (yyvsp[-3].u.real), (yyvsp[-2].u.real), (yyvsp[-1].u.real));
  DCAST(DNAStreet, _cur_comp)->set_color(color);
}
#line 2566 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 138:
#line 696 "dna.yxx" /* yacc.c:1645  */
    {
  block_number_t block_number = atoi(_store->get_block(_cur_comp->get_name()).c_str());
  _store->store_block_title(block_number, (yyvsp[-1].str));
}
#line 2575 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 139:
#line 702 "dna.yxx" /* yacc.c:1645  */
    {
  block_number_t block_number = atoi(_store->get_block(_cur_comp->get_name()).c_str());
  _store->store_block_article(block_number, (yyvsp[-1].str));
}
#line 2584 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 140:
#line 708 "dna.yxx" /* yacc.c:1645  */
    {
  block_number_t block_number = atoi(_store->get_block(_cur_comp->get_name()).c_str());
  _store->store_block_building_type(block_number, (yyvsp[-1].str));
}
#line 2593 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 141:
#line 714 "dna.yxx" /* yacc.c:1645  */
    {
  LVecBase4f color((yyvsp[-4].u.real), (yyvsp[-3].u.real), (yyvsp[-2].u.real), (yyvsp[-1].u.real));
  DCAST(DNALandmarkBuilding, _cur_comp)->set_wall_color(color);
}
#line 2602 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 142:
#line 720 "dna.yxx" /* yacc.c:1645  */
    {
  DCAST(DNAAnimBuilding, _cur_comp)->set_anim_name((yyvsp[-1].str));
}
#line 2610 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 143:
#line 725 "dna.yxx" /* yacc.c:1645  */
    {
  DCAST(DNAWindows, _cur_comp)->set_window_count((yyvsp[-1].u.real));
}
#line 2618 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 144:
#line 730 "dna.yxx" /* yacc.c:1645  */
    {
  DCAST(DNASignBaseline, _cur_comp)->set_width((yyvsp[-1].u.real));
}
#line 2626 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 145:
#line 735 "dna.yxx" /* yacc.c:1645  */
    {
  DCAST(DNASignGraphic, _cur_comp)->set_width((yyvsp[-1].u.real));
}
#line 2634 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 146:
#line 740 "dna.yxx" /* yacc.c:1645  */
    {
  DCAST(DNAFlatBuilding, _cur_comp)->set_width((yyvsp[-1].u.real));
}
#line 2642 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 147:
#line 745 "dna.yxx" /* yacc.c:1645  */
    {
  DCAST(DNASignBaseline, _cur_comp)->set_height((yyvsp[-1].u.real));
}
#line 2650 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 148:
#line 750 "dna.yxx" /* yacc.c:1645  */
    {
  DCAST(DNASignGraphic, _cur_comp)->set_height((yyvsp[-1].u.real));
}
#line 2658 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 149:
#line 755 "dna.yxx" /* yacc.c:1645  */
    {
  DCAST(DNAWall, _cur_comp)->set_height((yyvsp[-1].u.real));
}
#line 2666 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 150:
#line 760 "dna.yxx" /* yacc.c:1645  */
    {
  DCAST(DNASignBaseline, _cur_comp)->set_stomp((yyvsp[-1].u.real));
}
#line 2674 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 151:
#line 765 "dna.yxx" /* yacc.c:1645  */
    {
  DCAST(DNASignBaseline, _cur_comp)->set_indent((yyvsp[-1].u.real));
}
#line 2682 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 152:
#line 770 "dna.yxx" /* yacc.c:1645  */
    {
  DCAST(DNASignBaseline, _cur_comp)->set_kern((yyvsp[-1].u.real));
}
#line 2690 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 153:
#line 775 "dna.yxx" /* yacc.c:1645  */
    {
  DCAST(DNASignBaseline, _cur_comp)->set_stumble((yyvsp[-1].u.real));
}
#line 2698 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 154:
#line 780 "dna.yxx" /* yacc.c:1645  */
    {
  DCAST(DNASignBaseline, _cur_comp)->set_wiggle((yyvsp[-1].u.real));
}
#line 2706 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 155:
#line 785 "dna.yxx" /* yacc.c:1645  */
    {
  DCAST(DNAProp, _cur_comp)->set_code((yyvsp[-1].str));
}
#line 2714 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 156:
#line 790 "dna.yxx" /* yacc.c:1645  */
    {
  DCAST(DNALandmarkBuilding, _cur_comp)->set_code((yyvsp[-1].str));
}
#line 2722 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 157:
#line 795 "dna.yxx" /* yacc.c:1645  */
    {
  DCAST(DNASignBaseline, _cur_comp)->set_code((yyvsp[-1].str));
}
#line 2730 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 158:
#line 800 "dna.yxx" /* yacc.c:1645  */
    {
  DCAST(DNADoor, _cur_comp)->set_code((yyvsp[-1].str));
}
#line 2738 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 159:
#line 805 "dna.yxx" /* yacc.c:1645  */
    {
  DCAST(DNASignGraphic, _cur_comp)->set_code((yyvsp[-1].str));
}
#line 2746 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 160:
#line 810 "dna.yxx" /* yacc.c:1645  */
    {
  DCAST(DNACornice, _cur_comp)->set_code((yyvsp[-1].str));
}
#line 2754 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 161:
#line 815 "dna.yxx" /* yacc.c:1645  */
    {
  DCAST(DNAStreet, _cur_comp)->set_code((yyvsp[-1].str));
}
#line 2762 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 162:
#line 820 "dna.yxx" /* yacc.c:1645  */
    {
  DCAST(DNAWall, _cur_comp)->set_code((yyvsp[-1].str));
}
#line 2770 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 163:
#line 825 "dna.yxx" /* yacc.c:1645  */
    {
  DCAST(DNAWindows, _cur_comp)->set_code((yyvsp[-1].str));
}
#line 2778 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 164:
#line 830 "dna.yxx" /* yacc.c:1645  */
    {
  LVecBase4f color((yyvsp[-4].u.real), (yyvsp[-3].u.real), (yyvsp[-2].u.real), (yyvsp[-1].u.real));
  DCAST(DNAProp, _cur_comp)->set_color(color);
}
#line 2787 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 165:
#line 836 "dna.yxx" /* yacc.c:1645  */
    {
  LVecBase4f color((yyvsp[-4].u.real), (yyvsp[-3].u.real), (yyvsp[-2].u.real), (yyvsp[-1].u.real));
  DCAST(DNASignBaseline, _cur_comp)->set_color(color);
}
#line 2796 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 166:
#line 842 "dna.yxx" /* yacc.c:1645  */
    {
  LVecBase4f color((yyvsp[-4].u.real), (yyvsp[-3].u.real), (yyvsp[-2].u.real), (yyvsp[-1].u.real));
  DCAST(DNADoor, _cur_comp)->set_color(color);
}
#line 2805 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 167:
#line 848 "dna.yxx" /* yacc.c:1645  */
    {
  LVecBase4f color((yyvsp[-4].u.real), (yyvsp[-3].u.real), (yyvsp[-2].u.real), (yyvsp[-1].u.real));
  DCAST(DNASignGraphic, _cur_comp)->set_color(color);
}
#line 2814 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 168:
#line 854 "dna.yxx" /* yacc.c:1645  */
    {
  LVecBase4f color((yyvsp[-4].u.real), (yyvsp[-3].u.real), (yyvsp[-2].u.real), (yyvsp[-1].u.real));
  DCAST(DNACornice, _cur_comp)->set_color(color);
}
#line 2823 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 169:
#line 860 "dna.yxx" /* yacc.c:1645  */
    {
  LVecBase4f color((yyvsp[-4].u.real), (yyvsp[-3].u.real), (yyvsp[-2].u.real), (yyvsp[-1].u.real));
  DCAST(DNAWall, _cur_comp)->set_color(color);
}
#line 2832 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 170:
#line 866 "dna.yxx" /* yacc.c:1645  */
    {
  LVecBase4f color((yyvsp[-4].u.real), (yyvsp[-3].u.real), (yyvsp[-2].u.real), (yyvsp[-1].u.real));
  DCAST(DNAWindows, _cur_comp)->set_color(color);
}
#line 2841 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 219:
#line 950 "dna.yxx" /* yacc.c:1645  */
    {
  _model_type = "model";
  _model_name = (yyvsp[0].str);
}
#line 2850 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 220:
#line 955 "dna.yxx" /* yacc.c:1645  */
    {
  _model_type = "hood_model";
  _model_name = (yyvsp[0].str);
}
#line 2859 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 221:
#line 960 "dna.yxx" /* yacc.c:1645  */
    {
  _model_type = "place_model";
  _model_name = (yyvsp[0].str);
}
#line 2868 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 225:
#line 973 "dna.yxx" /* yacc.c:1645  */
    {
  _store_model((yyvsp[-2].str), (yyvsp[-1].str), (yyvsp[-1].str));
}
#line 2876 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 226:
#line 977 "dna.yxx" /* yacc.c:1645  */
    {
  _store_model((yyvsp[-3].str), (yyvsp[-2].str), (yyvsp[-1].str));
}
#line 2884 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 227:
#line 982 "dna.yxx" /* yacc.c:1645  */
    {
  _store->store_texture((yyvsp[-2].str), TexturePool::load_texture((yyvsp[-1].str)));
}
#line 2892 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 228:
#line 986 "dna.yxx" /* yacc.c:1645  */
    {
  _store->store_catalog_code((yyvsp[-3].str), (yyvsp[-2].str));
  _store->store_texture((yyvsp[-2].str), TexturePool::load_texture((yyvsp[-1].str)));
}
#line 2901 "dna_yxx.cxx" /* yacc.c:1645  */
    break;

  case 229:
#line 992 "dna.yxx" /* yacc.c:1645  */
    {
  _store->store_catalog_code((yyvsp[-3].str), (yyvsp[-2].str));

  Filename filename((yyvsp[-1].str));
  if (!filename.get_extension().size())
    filename.set_extension("bam");

  _store->store_font((yyvsp[-2].str), FontPool::load_font(filename), filename);
}
#line 2915 "dna_yxx.cxx" /* yacc.c:1645  */
    break;


#line 2919 "dna_yxx.cxx" /* yacc.c:1645  */
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
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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
                  yystos[*yyssp], yyvsp);
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
