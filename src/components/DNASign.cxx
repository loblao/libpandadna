#include "DNASign.h"

#include "modelNode.h"
#include "decalEffect.h"

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

    PT(ModelNode) node = new ModelNode("sign");
    _np = decal_node.attach_new_node(node);

    if (m_code.size())
    {
        NodePath sign_node = store->find_node(m_code);
        if (sign_node.is_empty())
        {
            dna_cat.warning() << "Sign not found in storage: " << m_code << std::endl;
            return;
        }

        _np = sign_node.copy_to(_np);
        _np.set_name("sign");
    }

    _np.set_depth_write(1);

    std::string np_name = np.get_name();

    // Thank you Panda3D for requiring this nasty hack!
    // Fixes the sign text on the Cog HQ tunnels aside from
    // the Bossbot HQ tunnel.
    if (np_name.find("linktunnel_") != std::string::npos && np_name.find("hq_") != std::string::npos)
        m_pos[1] -= 0.45;

    origin = np.find("**/*sign_origin");
    _np.set_pos_hpr_scale(origin, m_pos, m_hpr, m_scale);
    _np.set_color(m_color);
    traverse_children(_np, store);

    LMatrix4f mat = _np.get_transform(np)->get_mat();
    store->store_block_sign_transform(atoi(store->get_block(np_name).c_str()), mat);
}
