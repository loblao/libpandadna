#include "DNAAnimBuilding.h"

DNAAnimBuilding::DNAAnimBuilding(string name) : DNALandmarkBuilding(name) {}
DNAAnimBuilding::~DNAAnimBuilding(void) {}

void DNAAnimBuilding::traverse(NodePath& np, DNAStorage* store)
{
	NodePath* result = store->find_node(m_code);
	if (result->is_empty())
	{
		stringstream ss;
		ss << "DNAAnimBuilding code " << m_code << " not found in store!";
		cerr << ss.str() << endl;
		throw ss.str();
	};

	NodePath _np = result->copy_to(np);
	_np.set_name(m_name);
	_np.set_pos_hpr_scale(*m_pos, *m_hpr, *m_scale);
	_np.set_tag("DNAAnim", m_anim_name);
	setup_suit_building_origin(np, _np);
	
	for (comp_vec_t::iterator child = m_children.begin(); child != m_children.end(); child++)
	{
		(*child)->traverse(_np, store);
	};
	_np.flatten_strong();
};

void DNAAnimBuilding::set_anim(const string& anim_name)
{
	m_anim_name = anim_name;
};

string DNAAnimBuilding::get_anim()
{
	return m_anim_name;
};
