#include "DNAProp.h"

DNAProp::DNAProp(string name) : DNANode(name), m_color(new LVector4f(1)) {}
DNAProp::~DNAProp(void) {}

void DNAProp::make_from_dgi(DatagramIterator& dgi, DNAStorage* store)
{
	DNANode::make_from_dgi(dgi, store);
	m_code = dgi_extract_string8(dgi);
	m_color = dgi_extract_color(dgi);
};
