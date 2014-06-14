#include "DNASignGraphic.h"
#include <decalEffect.h>
#include "DNASign.h"

DNASignGraphic::DNASignGraphic(string name) : DNANode(name), m_color(new LVector4f(1)) {}
DNASignGraphic::~DNASignGraphic(void) {}

void DNASignGraphic::make_from_dgi(DatagramIterator& dgi, DNAStorage* store)
{
	DNANode::make_from_dgi(dgi, store);
	m_code = dgi_extract_string8(dgi);
	m_color = dgi_extract_color(dgi);
	m_width = dgi.get_int16() / 100;
	m_height = dgi.get_int16() / 100;
	m_b_default_color = dgi.get_bool();
};

void DNASignGraphic::traverse(NodePath& np, DNAStorage* store)
{
	NodePath* result = store->find_node(m_code);
	if (result->is_empty())
	{
		stringstream ss;
		ss << "code " << m_code << " not in storage!";
		cout << "DNASignGraphic(fatal): " << ss.str() << endl;
		throw ss.str();
	}

	NodePath _np = result->copy_to(np);
	_np.set_scale(*m_scale);

	DNASign* p = reinterpret_cast<DNASign*>(m_parent);
	LVector3f* s = p->get_scale();
	_np.set_scale(_np, *s);

	_np.set_pos(*m_pos);
	_np.set_hpr(*m_hpr);
	
	for (comp_vec_t::iterator child = m_children.begin(); child != m_children.end(); child++)
	{
		(*child)->traverse(_np, store);
	};
};

void DNASignGraphic::set_code(const string& code)
{
	m_code = code;
};

string DNASignGraphic::get_code()
{
	return m_code;
};

void DNASignGraphic::set_color(LVector4f* color)
{
	m_color = color;
};

LVector4f* DNASignGraphic::get_color()
{
	return m_color;
};

void DNASignGraphic::set_width(float w)
{
	m_width = w;
};

float DNASignGraphic::get_width()
{
	return m_width;
};

void DNASignGraphic::set_height(float h)
{
	m_height = h;
};

float DNASignGraphic::get_height()
{
	return m_height;
};
