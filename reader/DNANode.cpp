#include "DNANode.h"

DNANode::DNANode(string name) : DNAGroup(name) {}
DNANode::~DNANode(void) {}

void DNANode::make_from_dgi(DatagramIterator& dgi, DNAStorage* store)
{
	DNAGroup::make_from_dgi(dgi, store);

	int x = dgi.get_int32();
	int y = dgi.get_int32();
	int z = dgi.get_int32();

	m_pos = new LVector3f(x / 100.0, y / 100.0, z / 100.0);

	int h = dgi.get_int32();
	int p = dgi.get_int32();
	int r = dgi.get_int32();

	m_hpr = new LVector3f(h / 100.0, p / 100.0, r / 100.0);

	short sx = dgi.get_int16();
	short sy = dgi.get_int16();
	short sz = dgi.get_int16();

	m_scale = new LVector3f(sx / 100.0, sy / 100.0, sz / 100.0);
};

void DNANode::traverse(NodePath& np, DNAStorage* store)
{
	NodePath _np = np.attach_new_node(m_name);
	_np.set_pos(*m_pos);
	_np.set_hpr(*m_hpr);
	_np.set_scale(*m_scale);

	for (comp_vec_t::iterator child = m_children.begin(); child != m_children.end(); child++)
	{
        (*child)->traverse(_np, store);
	};
};

void DNANode::set_pos(LVector3f* pos)
{
	m_pos = pos;
};

LVector3f* DNANode::get_pos()
{
	return m_pos;
};

void DNANode::set_hpr(LVector3f* hpr)
{
	m_hpr = hpr;
};

LVector3f* DNANode::get_hpr()
{
	return m_hpr;
};

void DNANode::set_scale(LVector3f* scale)
{
	m_scale = scale;
};

LVector3f* DNANode::get_scale()
{
	return m_scale;
};
