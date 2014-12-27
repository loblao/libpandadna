#include "DNAInteractiveProp.h"
#include <modelNode.h>

DNAInteractiveProp::DNAInteractiveProp(string name) : DNAAnimProp(name) {}
DNAInteractiveProp::~DNAInteractiveProp(void) {}

void DNAInteractiveProp::make_from_dgi(DatagramIterator &dgi, DNAStorage *store)
{
	DNAAnimProp::make_from_dgi(dgi, store);
	m_cell_id = dgi.get_int16();
};

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
		NodePath* result = store->find_node(m_code);
		_np = result->copy_to(np);
		_np.set_name(m_name);
	};

	_np.set_tag("DNAAnim", m_anim_name);

	stringstream ss;
	ss << m_cell_id;
    _np.set_tag("DNACellIndex", ss.str());

	_np.set_pos_hpr_scale(*m_pos, *m_hpr, *m_scale);
	_np.set_color_scale(*m_color);

	for (comp_vec_t::iterator child = m_children.begin(); child != m_children.end(); child++)
	{
		(*child)->traverse(_np, store);
	};
};

void DNAInteractiveProp::set_cell_id(short cell_id)
{
	m_cell_id = cell_id;
};

short DNAInteractiveProp::get_cell_id()
{
	return m_cell_id;
};
