#include "DNAInteractiveProp.h"

#include <modelNode.h>

TypeHandle DNAInteractiveProp::_type_handle;

DNAInteractiveProp::DNAInteractiveProp(const std::string& name): DNAAnimProp(name),
                                                                 m_cell_id(-1)
{
}

DNAInteractiveProp::~DNAInteractiveProp()
{
}

void DNAInteractiveProp::make_from_dgi(DatagramIterator& dgi, DNAStorage* store)
{
    DNAAnimProp::make_from_dgi(dgi, store);
    m_cell_id = dgi.get_int16();
}

void DNAInteractiveProp::traverse(NodePath& np, DNAStorage* store)
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

    std::stringstream ss;
    ss << m_cell_id;
    _np.set_tag("DNACellIndex", ss.str());
    
    _np.set_pos_hpr_scale(m_pos, m_hpr, m_scale);
    _np.set_color_scale(m_color);
    traverse_children(_np, store);
}
