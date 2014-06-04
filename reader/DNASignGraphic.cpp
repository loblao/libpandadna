#include "DNASignGraphic.h"

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
