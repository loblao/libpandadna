#include "DNALandmarkBuilding.h"

#include <cctype>

TypeHandle DNALandmarkBuilding::_type_handle;

DNALandmarkBuilding::DNALandmarkBuilding(const std::string& name): DNANode(name), m_code(""),
                                                                   m_wall_color(LVecBase4f(1))
{
}

DNALandmarkBuilding::~DNALandmarkBuilding()
{
}

void DNALandmarkBuilding::make_from_dgi(DatagramIterator& dgi, DNAStorage* store)
{
    DNANode::make_from_dgi(dgi, store);   
    m_code = dgi.get_string();
    m_wall_color = DGI_EXTRACT_COLOR;
}

void DNALandmarkBuilding::traverse(NodePath& np, DNAStorage* store)
{
    NodePath result = store->find_node(m_code);
    if (result.is_empty())
    {
        raise_code_not_found(m_code.c_str());
        return;
    }
    
    NodePath _np = result.copy_to(np);
    _np.set_name(m_name);
    _np.set_pos_hpr_scale(m_pos, m_hpr, m_scale);
    
    if (store->allow_suit_origin(_np))
        setup_suit_building_origin(np, _np);

    traverse_children(_np, store);

    if (m_name.find("gag_shop") == std::string::npos)
        _np.flatten_strong();
}

void DNALandmarkBuilding::setup_suit_building_origin(NodePath& a, NodePath& b)
{
    if ((m_name.substr(0, 2) == "tb") && (isdigit(m_name[2])) && (m_name.find(":") != std::string::npos))
    {
        std::stringstream ss;
        ss << 's' << m_name.substr(1, m_name.size());
        
        NodePath node = b.find("**/*suit_building_origin");
        if (node.is_empty())
        {
            dna_cat.warning() << m_name << " couldn't find suit building origin" << std::endl;
            node = a.attach_new_node(ss.str());
            node.set_pos_hpr_scale(m_pos, m_hpr, m_scale);
        }
        
        else
        {
            node.wrt_reparent_to(a);
            node.set_name(ss.str());
        }
    }
}
