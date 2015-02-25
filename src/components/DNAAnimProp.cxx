#include "DNAAnimProp.h"

#include <modelNode.h>

TypeHandle DNAAnimProp::_type_handle;

DNAAnimProp::DNAAnimProp(const std::string& name): DNAProp(name), m_anim_name("")
{
}

DNAAnimProp::~DNAAnimProp()
{
}

void DNAAnimProp::make_from_dgi(DatagramIterator& dgi, DNAStorage* store)
{
    DNAProp::make_from_dgi(dgi, store);
    m_anim_name = dgi.get_string();
}

void DNAAnimProp::traverse(NodePath& np, DNAStorage* store)
{
    NodePath _np;
    
    if (m_code == "DCS")
    {
        PT(ModelNode) node = new ModelNode(m_name);
        node->set_preserve_transform(ModelNode::PT_net);
        _np = np.attach_new_node(node);
    }
    
    else
    {
        /// XXX TO DO: Check find_node result
        _np = store->find_node(m_code).copy_to(np);
        _np.set_name(m_name);
    }
    
    _np.set_tag("DNAAnim", m_anim_name);
    _np.set_pos_hpr_scale(m_pos, m_hpr, m_scale);
    _np.set_color_scale(m_color);
    traverse_children(_np, store);
}
