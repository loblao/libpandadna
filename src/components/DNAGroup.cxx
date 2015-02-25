#include "DNAGroup.h"

TypeHandle DNAGroup::_type_handle;

DNAGroup::DNAGroup(const std::string& name): m_name(name), m_parent(NULL),
                                             m_vis_group(NULL)
{
}

DNAGroup::~DNAGroup()
{
}

void DNAGroup::set_name(const std::string& name)
{
    m_name = name;
}

const std::string& DNAGroup::get_name()
{
    return m_name;
}
        
void DNAGroup::add(DNAGroup* group)
{
    m_children.push_back(group);
}

DNAGroup* DNAGroup::at(size_t index)
{
    return m_children.at(index);
}

size_t DNAGroup::get_num_children()
{
    return m_children.size();
}
        
void DNAGroup::set_vis_group(DNAGroup* group)
{
    m_vis_group = group;
}

DNAGroup* DNAGroup::get_vis_group()
{
    return m_vis_group;
}
        
void DNAGroup::set_parent(DNAGroup* group)
{
    m_parent = group;
}

DNAGroup* DNAGroup::get_parent()
{
    return m_parent;
}

void DNAGroup::clear_parent()
{
    m_parent = NULL;
    m_vis_group = NULL;
}

void DNAGroup::make_from_dgi(DatagramIterator& dgi, DNAStorage* store)
{
    m_name = dgi.get_string();
    dgi.get_string();
    dgi.get_string();
}

void DNAGroup::traverse(NodePath& np, DNAStorage* store)
{
    traverse_children(np.attach_new_node(m_name), store);
}

void DNAGroup::raise_code_not_found()
{
    raise_code_not_found("<unknown>");
}

void DNAGroup::raise_code_not_found(const char* code)
{
    dna_cat.fatal() << "code not found: " << code << std::endl;
    assert(false);
}

void DNAGroup::traverse_children(NodePath& np, DNAStorage* store)
{
    for (dna_group_vec_t::iterator it = m_children.begin(); it != m_children.end(); ++it)
        (*it)->traverse(np, store);
}
