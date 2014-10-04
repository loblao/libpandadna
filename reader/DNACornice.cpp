#include "DNACornice.h"
#include <decalEffect.h>

DNACornice::DNACornice(string name) : DNAGroup(name), m_color(new LVector4f(1)) {}
DNACornice::~DNACornice(void) {}

void DNACornice::make_from_dgi(DatagramIterator &dgi, DNAStorage *store)
{
	DNAGroup::make_from_dgi(dgi, store);
	m_code = dgi_extract_string8(dgi);
	m_color = dgi_extract_color(dgi);
};

void DNACornice::traverse(NodePath& np, DNAStorage* store)
{
	float parent_x_scale = np.get_parent().get_scale().get_x();
	float parent_z_scale = np.get_scale().get_z();

	float scale_ratio = parent_x_scale / parent_z_scale;

	NodePath* node = store->find_node(m_code);
	if (node->is_empty())
	{
		stringstream ss;
		ss << "code " << m_code << " not found in storage!";
		cout << "DNACornice(fatal): " << ss.str() << endl;
		throw ss.str();
	};

	NodePath internal_node = np.attach_new_node("cornice-internal");

	NodePath np_d = node->find("**/*_d").copy_to(internal_node);
	np_d.set_scale(1, scale_ratio, scale_ratio);
	np_d.set_effect(DecalEffect::make());

	NodePath node_nd = node->find("**/*_nd");
	NodePath np_nd = node_nd.copy_to(internal_node, 1);
	np_nd.set_scale(1, scale_ratio, scale_ratio);

	internal_node.set_pos(0, 0, node_nd.get_scale().get_z());
	internal_node.set_color(*m_color);
};

void DNACornice::set_code(const string& code)
{
	m_code = code;
};

string DNACornice::get_code()
{
	return m_code;
};

void DNACornice::set_color(LVector4f* color)
{
	m_color = color;
};

LVector4f* DNACornice::get_color()
{
	return m_color;
};
