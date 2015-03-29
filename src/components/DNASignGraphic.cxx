#include "DNASignGraphic.h"

TypeHandle DNASignGraphic::_type_handle;

DNASignGraphic::DNASignGraphic(const std::string& name): DNAProp(name), m_width(0),
                                                         m_height(0)
{
}

DNASignGraphic::~DNASignGraphic()
{
}

void DNASignGraphic::make_from_dgi(DatagramIterator& dgi, DNAStorage* store)
{
    DNAProp::make_from_dgi(dgi, store);
    m_width = dgi.get_int16() / 100.0;
    m_height = dgi.get_int16() / 100.0;
    dgi.get_bool();
}

void DNASignGraphic::traverse(NodePath& np, DNAStorage* store)
{
    NodePath result = store->find_node(m_code);
    if (result.is_empty())
    {
        raise_code_not_found();
        return;
    }
    
    NodePath _np = result.copy_to(np);
    _np.set_scale(m_scale);
    _np.set_scale(_np, reinterpret_cast<DNANode*>(m_parent)->get_scale());
    _np.set_pos_hpr(m_pos, m_hpr);

    _np.set_depth_write(true);
    _np.set_depth_test(true);
    _np.set_depth_offset(10);
    _np.set_y(_np, -.025);
    
    traverse_children(_np, store);
}
