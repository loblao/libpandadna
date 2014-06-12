#include "DNAStreet.h"

DNAStreet::DNAStreet(string name) : DNANode(name), m_street_color(new LVector4f(1)),
									m_sidewalk_color(new LVector4f(1)),
									m_curb_color(new LVector4f(1)) {}
DNAStreet::~DNAStreet(void) {}

void DNAStreet::make_from_dgi(DatagramIterator &dgi, DNAStorage *store)
{
	DNANode::make_from_dgi(dgi, store);
	m_code = dgi_extract_string8(dgi);
	
	m_street_tex = dgi_extract_string8(dgi);
	m_sidewalk_tex = dgi_extract_string8(dgi);
	m_curb_tex = dgi_extract_string8(dgi);

	m_street_color = dgi_extract_color(dgi);
	m_sidewalk_color = dgi_extract_color(dgi);
	m_curb_color = dgi_extract_color(dgi);
};


void DNAStreet::traverse(NodePath np, DNAStorage* store)
{
	NodePath* result = store->find_node(m_code);
	if (result->is_empty())
	{
		stringstream ss;
		ss << "DNAStreet(fatal): no such code: " << m_code << " in storage!";
        cerr << ss.str();
		throw ss.str();
	};

    NodePath _np = result->copy_to(np);
	_np.set_name(m_name);
	
    NodePath street_node = _np.find("**/*_street");
	if (!street_node.is_empty())
	{
		if (m_street_tex.size() > 0)
		{
			Texture* street_tex = store->find_texture(m_street_tex);
			street_node.set_texture(street_tex, 1);
		};
		street_node.set_color_scale(*m_street_color);
	};

    NodePath sidewalk_node = _np.find("**/*_sidewalk");
	if (!sidewalk_node.is_empty())
	{
		
		if (m_sidewalk_tex.size() > 0)
		{
			Texture* sidewalk_tex = store->find_texture(m_sidewalk_tex);
			sidewalk_node.set_texture(sidewalk_tex, 1);
		};
		sidewalk_node.set_color_scale(*m_sidewalk_color);
	};

    NodePath curb_node = _np.find("**/*_curb");
	if (!curb_node.is_empty())
	{
		if (m_curb_tex.size() > 0)
		{
			Texture* curb_tex = store->find_texture(m_curb_tex);
			curb_node.set_texture(curb_tex, 1);
		};
		curb_node.set_color_scale(*m_curb_color);
	};

    _np.set_pos(*m_pos);
	_np.set_hpr(*m_hpr);
	_np.set_scale(*m_scale);
};
