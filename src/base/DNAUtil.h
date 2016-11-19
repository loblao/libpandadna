#ifndef _H_DNA_UTIL_
#define _H_DNA_UTIL_

#include <decalEffect.h>
#include <nodePathCollection.h>
#include <pandabase.h>

#include "dnabase.h"

#include "DNAGroup.h"

class EXPCL_DNA DNAUtil
{
    
    PUBLISHED:
        DNAUtil();
        ~DNAUtil();
        
        void reparent_node_to(NodePath np, NodePath np1);
        void apply_decal_effect_to_node(NodePath np);
        void flatten_node_strong(NodePath np);
        void set_node_scale(NodePath np, LPoint3f scale);
        void set_node_pos_hpr(NodePath np, int32_t x, int32_t y, int32_t z, int32_t h, int32_t p, int32_t r);
        void set_node_hpr(NodePath np, int32_t h, int32_t p, int32_t r);
        void set_node_pos(NodePath np, int32_t x, int32_t y, int32_t z);
};

#endif