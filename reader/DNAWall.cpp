#include "DNAWall.h"
#include "DNAFlatBuilding.h"

DNAWall::DNAWall(string name) : DNANode(name), m_color(new LVector4f(1)) {}
DNAWall::~DNAWall(void) {}

void DNAWall::make_from_dgi(DatagramIterator &dgi, DNAStorage *store)
{
	DNANode::make_from_dgi(dgi, store);
	m_code = dgi_extract_string8(dgi);
	m_height = dgi.get_int16() / 100;
	m_color = dgi_extract_color(dgi);
};

void DNAWall::traverse(NodePath& np, DNAStorage* store)
{
	NodePath* result = store->find_node(m_code);

	if (result->is_empty())
	{
		stringstream ss;
		ss << "code " << m_code << " not found in storage!";
		cerr << "DNAWall(fatal): " << ss.str() << endl;
		throw ss.str();
	}

	NodePath _np = result->copy_to(np);

	m_pos->set_z(DNAFlatBuilding::current_wall_height);
	m_scale->set_z(m_height);

	_np.set_pos(*m_pos);
	_np.set_hpr(*m_hpr);
	_np.set_scale(*m_scale);
	_np.set_color(*m_color);

    for (comp_vec_t::iterator child = m_children.begin(); child != m_children.end(); child++)
	{
        (*child)->traverse(_np, store);
	};

	DNAFlatBuilding::current_wall_height += m_height;
};

bool DNAWall::is_wall()
{
	return true;
};

void DNAWall::set_code(const string& code)
{
	m_code = code;
};

string DNAWall::get_code()
{
	return m_code;
};

void DNAWall::set_color(LVector4f* color)
{
	m_color = color;
};

LVector4f* DNAWall::get_color()
{
	return m_color;
};

void DNAWall::set_height(float h)
{
	m_height = h;
};

float DNAWall::get_height()
{
	return m_height;
};
