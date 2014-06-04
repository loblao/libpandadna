#include "DNAWall.h"

DNAWall::DNAWall(string name) : DNANode(name), m_color(new LVector4f(1)) {}
DNAWall::~DNAWall(void) {}

void DNAWall::make_from_dgi(DatagramIterator &dgi, DNAStorage *store)
{
	DNANode::make_from_dgi(dgi, store);
	m_code = dgi_extract_string8(dgi);
	m_height = dgi.get_int16() / 100;
	m_color = dgi_extract_color(dgi);
};
