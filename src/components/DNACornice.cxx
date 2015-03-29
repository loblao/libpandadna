#include "DNACornice.h"
#include "DNAStorage.h"

#include <decalEffect.h>

TypeHandle DNACornice::_type_handle;

DNACornice::DNACornice(const std::string& name): DNAGroup(name), m_code(""),
                                                 m_color(LVecBase4f(1))
{
}

DNACornice::~DNACornice()
{
}

void DNACornice::make_from_dgi(DatagramIterator& dgi, DNAStorage* store)
{
    DNAGroup::make_from_dgi(dgi, store);
    m_code = dgi.get_string();
    m_color = DGI_EXTRACT_COLOR;
}

void DNACornice::traverse(NodePath& np, DNAStorage* store)
{
    float parent_x_scale = np.get_parent().get_scale().get_x();
    float parent_z_scale = np.get_scale().get_z();
    float scale_ratio = parent_x_scale / parent_z_scale;
    
    NodePath node = store->find_node(m_code);
    if (node.is_empty())
    {
        raise_code_not_found();
        return;
    }
    
    NodePath internal_node = np.attach_new_node("cornice-internal");
    node = node.find("**/*_d");
    
    NodePath _np = node.copy_to(internal_node, 0);
    _np.set_scale(1, scale_ratio, scale_ratio);
    _np.set_effect(DecalEffect::make());
    
    node = node.get_parent().find("**/*_nd");
    NodePath np_d = node.copy_to(internal_node, 1);
    np_d.set_scale(1, scale_ratio, scale_ratio);
    
    internal_node.set_z(node.get_scale().get_z());
    internal_node.set_color(m_color);
    internal_node.flatten_strong();
}
