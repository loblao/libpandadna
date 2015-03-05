#include "DNASign.h"

#include <modelNode.h>

TypeHandle DNASign::_type_handle;

DNASign::DNASign(const std::string& name): DNAProp(name)
{
}

DNASign::~DNASign()
{
}

void DNASign::make_from_dgi(DatagramIterator& dgi, DNAStorage* store)
{
    DNAProp::make_from_dgi(dgi, store);
}

void DNASign::traverse(NodePath& np, DNAStorage* store)
{
    NodePath decal_node, _np, origin;
    decal_node = np.find("**/sign_decal");
    if (decal_node.is_empty())
        decal_node = np.find("**/*_front");
        
    if (decal_node.is_empty() || !(decal_node.get_node(0)->is_geom_node()))
        decal_node = np.find("**/+GeomNode");
        
    if (m_code.size())
    {
        _np = store->find_node(m_code).copy_to(decal_node);
        _np.set_name("sign");
    }
    
    else
        _np = decal_node.attach_new_node(new ModelNode("sign"));
        
    _np.set_depth_offset(50);
    
    origin = np.find("**/*sign_origin");
    _np.set_pos_hpr_scale(origin, m_pos, m_hpr, m_scale);
    _np.set_color(m_color);
    _np.wrt_reparent_to(origin, 0);
    traverse_children(_np, store);
    _np.flatten_strong();
}
