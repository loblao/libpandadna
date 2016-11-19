#include "DNAUtil.h"
#include "DNAGroup.h"

#include <decalEffect.h>
#include <nodePathCollection.h>
#include <pandabase.h>


DNAUtil::DNAUtil(){
}

DNAUtil::~DNAUtil(){
}

void DNAUtil::reparent_node_to(NodePath np, NodePath np1) { 
    np.reparent_to(np1);    
}

void DNAUtil::apply_decal_effect_to_node(NodePath np) {
    np.set_effect(DecalEffect::make());
}

void DNAUtil::flatten_node_strong(NodePath np) {
    np.flatten_strong();
}

void DNAUtil::set_node_scale(NodePath np, LPoint3f scale) {
    np.set_scale(scale);
}

void DNAUtil::set_node_pos_hpr(NodePath np, int32_t x, int32_t y, int32_t z, int32_t h, int32_t p, int32_t r) {
    np.set_x(x);
    np.set_y(y);
    np.set_z(z);
    np.set_h(h);
    np.set_p(p);
    np.set_r(r);
}

void DNAUtil::set_node_pos(NodePath np, int32_t x, int32_t y, int32_t z) {
    np.set_x(x);
    np.set_y(y);
    np.set_z(z);
}

void DNAUtil::set_node_hpr(NodePath np, int32_t h, int32_t p, int32_t r) {
    np.set_h(h);
    np.set_p(p);
    np.set_r(r);
}



