#pragma once

#include "config_dna.h"

#include <pandabase.h>

#define COMPCODE_GROUP 1
#define COMPCODE_VISGROUP 2
#define COMPCODE_NODE 3
#define COMPCODE_PROP 4
#define COMPCODE_SIGN 5
#define COMPCODE_SIGN_BASELINE 6
#define COMPCODE_SIGN_GRAPHIC 8
#define COMPCODE_FLAT_BUILDING 9
#define COMPCODE_WALL 10
#define COMPCODE_WINDOWS 11
#define COMPCODE_CORNICE 12
#define COMPCODE_LANDMARK_BUILDING 13
#define COMPCODE_ANIM_PROP 14
#define COMPCODE_INTERACTIVE_PROP 15
#define COMPCODE_ANIM_BUILDING 16
#define COMPCODE_DOOR 17
#define COMPCODE_FLAT_DOOR 18
#define COMPCODE_STREET 19
#define COMPCODE_RETURN 255

typedef unsigned short zone_id_t;
typedef short block_number_t;
typedef unsigned short point_index_t;

#define DGI_EXTRACT_COLOR LVecBase4f(dgi.get_uint8() / 255., dgi.get_uint8() / 255., dgi.get_uint8() / 255., dgi.get_uint8() / 255.)
