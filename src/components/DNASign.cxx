#include "DNASign.h"

#include <modelNode.h>
#include <decalEffect.h>

TypeHandle DNASign::_type_handle;

DNASign::DNASign(const std::string& name): DNAProp(name)
{
}

DNASign::~DNASign()
{
}

void DNASign::make_from_dgi(DatagramIterator& dgi, DNAStorage* store)
{
    DNAProp::make_from_dgi(dgi, store);
}

void DNASign::traverse(NodePath& np, DNAStorage* store)
{
    NodePath decal_node, _np, origin;
    decal_node = np.find("**/sign_decal");
    if (decal_node.is_empty())
        decal_node = np.find("**/*_front");

    if (!decal_node.node()->is_geom_node())
        decal_node = decal_node.find("**/+GeomNode");

    if (decal_node.is_empty())
        decal_node = np.find("**/+GeomNode");

    decal_node.set_effect(DecalEffect::make());

    if (m_code.size())
    {
        _np = store->find_node(m_code).copy_to(decal_node);
        _np.set_name("sign");
    }

    else
        _np = decal_node.attach_new_node(new ModelNode("sign"));

    _np.set_depth_offset(50);

    origin = np.find("**/*sign_origin");
    _np.set_pos_hpr_scale(origin, m_pos, m_hpr, m_scale);
    _np.set_color(m_color);
    traverse_children(_np, store);
    _np.flatten_strong();

    LMatrix4f mat = _np.get_transform()->get_mat();
    store->store_block_sign_transform(atoi(store->get_block(np.get_name()).c_str()), mat);
}
