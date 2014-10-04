#include "DNAProp.h"
#include <modelNode.h>

DNAProp::DNAProp(string name) : DNANode(name), m_color(new LVector4f(1)) {}
DNAProp::~DNAProp(void) {}

void DNAProp::make_from_dgi(DatagramIterator& dgi, DNAStorage* store)
{
	DNANode::make_from_dgi(dgi, store);
	m_code = dgi_extract_string8(dgi);
	m_color = dgi_extract_color(dgi);
};

void DNAProp::traverse(NodePath& np, DNAStorage* store)
{
	NodePath _np;
	if (strcmp(m_code.c_str(), "DCS") == 0)
	{
		ModelNode* node = new ModelNode(m_name);
		node->set_preserve_transform(ModelNode::PT_net);
		_np = np.attach_new_node(node);
	}

	else
	{
		NodePath* result = store->find_node(m_code);
		if (result->is_empty())
		{
			stringstream ss;
			ss << "code " << m_code << " of prop " << m_name << " not found";
			cout << "DNAProp::traverse(fatal): " << ss.str() << endl;
			throw ss.str();
		}
		_np = result->copy_to(np);
	};

	_np.set_pos(*m_pos);
	_np.set_hpr(*m_hpr);
	_np.set_scale(*m_scale);
	_np.set_color_scale(*m_color);

	_np.set_name(m_name);

	for (comp_vec_t::iterator child = m_children.begin(); child != m_children.end(); child++)
	{
        (*child)->traverse(_np, store);
	};
};

void DNAProp::set_code(const string& code)
{
	m_code = code;
};

string DNAProp::get_code()
{
	return m_code;
};

void DNAProp::set_color(LVector4f* color)
{
	m_color = color;
};

LVector4f* DNAProp::get_color()
{
	return m_color;
};
