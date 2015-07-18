#include "DNAAnimBuilding.h"

TypeHandle DNAAnimBuilding::_type_handle;

DNAAnimBuilding::DNAAnimBuilding(const std::string& name): DNALandmarkBuilding(name),
                                                           m_anim_name("")
{
}

DNAAnimBuilding::~DNAAnimBuilding()
{
}

void DNAAnimBuilding::make_from_dgi(DatagramIterator& dgi, DNAStorage* store)
{
    DNALandmarkBuilding::make_from_dgi(dgi, store);
    m_anim_name = dgi.get_string();
}

void DNAAnimBuilding::traverse(NodePath& np, DNAStorage* store)
{
    NodePath result = store->find_node(m_code);
    if (result.is_empty())
    {
        raise_code_not_found();
        return;
    }
    
    NodePath _np = result.copy_to(np);
    _np.set_name(m_name);
    _np.set_pos_hpr_scale(m_pos, m_hpr, m_scale);
    _np.set_tag("DNAAnim", m_anim_name);
    setup_suit_building_origin(np, _np);
    traverse_children(_np, store);
    _np.flatten_strong();
}
