#include "DNAGroup.h"

DNAGroup::DNAGroup(string name) : m_name(name) {};
DNAGroup::~DNAGroup(void) {};

void DNAGroup::make_from_dgi(DatagramIterator &dgi, DNAStorage* /*store*/)
{
	string name, parent_name, vis_group_name;
	
	name = dgi_extract_string8(dgi);
	parent_name = dgi_extract_string8(dgi);
	vis_group_name = dgi_extract_string8(dgi);

	m_name = name;
};

DNAVisGroup* DNAGroup::get_vis_group()
{
	return m_vis_group;
};
		
void DNAGroup::add(DNAGroup* child)
{
	m_children.push_back(child);
};

DNAGroup* DNAGroup::at(size_t index)
{
	return m_children.at(index);
};

size_t DNAGroup::get_num_children()
{
	return m_children.size();
};
	
void DNAGroup::set_parent(DNAGroup* parent)
{
	m_parent = parent;
	m_vis_group = parent->get_vis_group();
	parent->add(this);
};

void DNAGroup::clear_parent()
{
	m_parent = NULL;
	m_vis_group = NULL;
};

DNAGroup* DNAGroup::get_parent()
{
	return m_parent;
};

string DNAGroup::get_name()
{
	return m_name;
};

void DNAGroup::traverse(NodePath& np, DNAStorage* store)
{
	NodePath _np = np.attach_new_node(m_name);
	for (comp_vec_t::iterator child = m_children.begin(); child != m_children.end(); child++)
	{
        (*child)->traverse(_np, store);
	};
};
