#include "DNANode.h"

TypeHandle DNANode::_type_handle;

DNANode::DNANode(const std::string& name): DNAGroup(name), m_pos(LVecBase3f(0)),
                                           m_hpr(LVecBase3f(0)), m_scale(LVecBase3f(1))
{
}

DNANode::~DNANode()
{
}

void DNANode::make_from_dgi(DatagramIterator& dgi, DNAStorage* store)
{
    DNAGroup::make_from_dgi(dgi, store);

    float x, y, z, h, p, r, sx, sy, sz;
    x = dgi.get_int32() / 100.0;
    y = dgi.get_int32() / 100.0;
    z = dgi.get_int32() / 100.0;
    h = dgi.get_int32() / 100.0;
    p = dgi.get_int32() / 100.0;
    r = dgi.get_int32() / 100.0;
    sx = dgi.get_int16() / 100.0;
    sy = dgi.get_int16() / 100.0;
    sz = dgi.get_int16() / 100.0;

    m_pos = LVecBase3f(x, y, z);
    m_hpr = LVecBase3f(h, p, r);
    m_scale = LVecBase3f(sx, sy, sz);
}

void DNANode::traverse(NodePath& np, DNAStorage* store)
{
    NodePath _np = np.attach_new_node(m_name);
    _np.set_pos_hpr_scale(m_pos, m_hpr, m_scale);
    traverse_children(_np, store);
}
