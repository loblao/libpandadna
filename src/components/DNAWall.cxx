#include "DNAWall.h"
#include "DNAFlatBuilding.h"

TypeHandle DNAWall::_type_handle;

DNAWall::DNAWall(const std::string& name): DNANode(name), m_code(""),
                                           m_height(0), m_color(LVecBase4f(1))
{
}

DNAWall::~DNAWall()
{
}

void DNAWall::make_from_dgi(DatagramIterator& dgi, DNAStorage* store)
{
    DNANode::make_from_dgi(dgi, store);
    m_code = dgi.get_string();
    m_height = dgi.get_int16() / 100.0;
    m_color = DGI_EXTRACT_COLOR;
}

void DNAWall::traverse(NodePath& np, DNAStorage* store)
{
    NodePath result = store->find_node(m_code);
    if (result.is_empty())
    {
        raise_code_not_found();
        return;
    }
    
    NodePath _np = result.copy_to(np);
    
    LPoint3f pos = LPoint3f(m_pos);
    pos.set_z(DNAFlatBuilding::current_wall_height);

    LPoint3f scale = LPoint3f(m_scale);
    scale.set_z(m_height);
    
    _np.set_pos_hpr_scale(pos, m_hpr, scale);
    _np.set_color(m_color);
    
    traverse_children(_np, store);
    DNAFlatBuilding::current_wall_height += m_height;
}
