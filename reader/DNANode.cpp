#include "DNANode.h"

DNANode::DNANode(string name) : DNAGroup(name) {}
DNANode::~DNANode(void) {}

void DNANode::make_from_dgi(DatagramIterator& dgi, DNAStorage* store)
{
	DNAGroup::make_from_dgi(dgi, store);

	int x = dgi.get_int32();
	int y = dgi.get_int32();
	int z = dgi.get_int32();

	m_pos = new LVector3f(x / 100, y / 100, z / 100);

	short h = dgi.get_int16();
	short p = dgi.get_int16();
	short r = dgi.get_int16();

	m_hpr = new LVector3f(h / 100, p / 100, r / 100);

	short sx = dgi.get_int16();
	short sy = dgi.get_int16();
	short sz = dgi.get_int16();

	m_scale = new LVector3f(sz / 100, sy / 100, sz / 100);
};
