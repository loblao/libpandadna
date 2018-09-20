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

    m_pos[0] = dgi.get_int32() / 100.0;
    m_pos[1] = dgi.get_int32() / 100.0;
    m_pos[2] = dgi.get_int32() / 100.0;
    m_hpr[0] = dgi.get_int32() / 100.0;
    m_hpr[1] = dgi.get_int32() / 100.0;
    m_hpr[2] = dgi.get_int32() / 100.0;
    m_scale[0] = dgi.get_int16() / 100.0;
    m_scale[1] = dgi.get_int16() / 100.0;
    m_scale[2] = dgi.get_int16() / 100.0;
}

void DNANode::traverse(NodePath& np, DNAStorage* store)
{
    NodePath _np = np.attach_new_node(m_name);
    _np.set_pos_hpr_scale(m_pos, m_hpr, m_scale);
    traverse_children(_np, store);
}
