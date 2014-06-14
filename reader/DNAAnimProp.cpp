#include "DNAAnimProp.h"
#include <modelNode.h>

DNAAnimProp::DNAAnimProp(string name) : DNAProp(name) {}
DNAAnimProp::~DNAAnimProp(void) {}

void DNAAnimProp::make_from_dgi(DatagramIterator &dgi, DNAStorage *store)
{
	DNAProp::make_from_dgi(dgi, store);
	m_anim_name = dgi_extract_string8(dgi);
};

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
		NodePath* result = store->find_node(m_code);
		_np = result->copy_to(np);
		_np.set_name(m_name);
	};

	_np.set_tag("DNAAnim", m_anim_name);

	_np.set_pos_hpr_scale(*m_pos, *m_hpr, *m_scale);
	_np.set_color_scale(*m_color);

	for (comp_vec_t::iterator child = m_children.begin(); child != m_children.end(); child++)
	{
		(*child)->traverse(_np, store);
	};
};

void DNAAnimProp::set_anim(const string& anim_name)
{
	m_anim_name = anim_name;
};

string DNAAnimProp::get_anim()
{
	return m_anim_name;
};
