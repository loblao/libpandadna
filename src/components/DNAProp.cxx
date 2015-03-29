#include "DNAProp.h"

#include <modelNode.h>

TypeHandle DNAProp::_type_handle;

DNAProp::DNAProp(const std::string& name): DNANode(name), m_code(""),
                                           m_color(LVecBase4f(1))
{
}

DNAProp::~DNAProp()
{
}

void DNAProp::make_from_dgi(DatagramIterator& dgi, DNAStorage* store)
{
    DNANode::make_from_dgi(dgi, store);
    m_code = dgi.get_string();
    m_color = DGI_EXTRACT_COLOR;
}

void DNAProp::traverse(NodePath& np, DNAStorage* store)
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
        NodePath result = store->find_node(m_code);
        if (result.is_empty())
            return;
        
        _np = result.copy_to(np);
    }
    
    _np.set_name(m_name);
    _np.set_pos_hpr_scale(m_pos, m_hpr, m_scale);
    _np.set_color_scale(m_color);
    
    traverse_children(_np, store);
}

void DNAProp::raise_code_not_found()
{
    DNAGroup::raise_code_not_found(m_code.c_str());
}
