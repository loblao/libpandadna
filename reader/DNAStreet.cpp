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
