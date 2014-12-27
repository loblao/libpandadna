#include "DNASign.h"
#include <modelNode.h>

DNASign::DNASign(string name) : DNANode(name), m_color(new LVector4f(1)) {}
DNASign::~DNASign(void) {}

void DNASign::make_from_dgi(DatagramIterator& dgi, DNAStorage* store)
{
	DNANode::make_from_dgi(dgi, store);
	m_code = dgi_extract_string8(dgi);
	m_color = dgi_extract_color(dgi);
};

void DNASign::traverse(NodePath& np, DNAStorage* store)
{
	NodePath dec_node = np.find("**/sign_decal");
	if (dec_node.is_empty())
	{
		dec_node = np.find("**/*_front");
	};

	bool is_geom_node = (dec_node.is_empty()) ? false : dec_node.get_node(0)->is_geom_node();
	if (!is_geom_node)
	{
		dec_node = np.find("**/+GeomNode");
	};

	if (dec_node.is_empty())
	{
		stringstream ss;
		ss << "dec_node is empty (code=" << m_code << ", name=" << m_name << ")";
		cout << "DNASign::traverse(fatal): " << ss.str() << endl;
		throw ss.str();
	}

	NodePath _np;
	if (m_code.length() > 0)
	{
		NodePath* result = store->find_node(m_code);

		if (result->is_empty())
		{
			stringstream ss;
			ss << "code " << m_code << " of sign " << m_name << " not found";
			cout << "DNASign::traverse(fatal): " << ss.str() << endl;
			throw ss.str();
		}

		_np = result->copy_to(dec_node);
		_np.set_name("sign");
	}

	else
	{
		ModelNode* m = new ModelNode("sign");
		_np = dec_node.attach_new_node(m);
	};

	if (_np.is_empty())
	{
		stringstream ss;
		ss << "_np is empty (code=" << m_code << ", name=" << m_name << ")";
		cout << "DNASign::traverse(fatal): " << ss.str() << endl;
		throw ss.str();
	}

	_np.set_depth_offset(50);
	NodePath origin = np.find("**/*sign_origin");

	_np.set_pos_hpr_scale(origin, *m_pos, *m_hpr, *m_scale);

	for (comp_vec_t::iterator child = m_children.begin(); child != m_children.end(); child++)
	{
        (*child)->traverse(_np, store);
	};

    _np.flatten_strong();
};

void DNASign::set_code(const string& code)
{
	m_code = code;
};

string DNASign::get_code()
{
	return m_code;
};

void DNASign::set_color(LVector4f* color)
{
	m_color = color;
};

LVector4f* DNASign::get_color()
{
	return m_color;
};
