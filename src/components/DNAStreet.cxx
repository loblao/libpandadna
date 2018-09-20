#include "DNAStreet.h"

TypeHandle DNAStreet::_type_handle;

DNAStreet::DNAStreet(const std::string& name): DNANode(name), m_code(""),
                                               m_street_texture(""),
                                               m_sidewalk_texture(""),
                                               m_curb_texture(""),
                                               m_street_color(LVecBase4f(1)),
                                               m_sidewalk_color(LVecBase4f(1)),
                                               m_curb_color(LVecBase4f(1)),
                                               m_set_texture_count(0),
                                               m_set_color_count(0)
{
}

DNAStreet::~DNAStreet()
{
}

void DNAStreet::make_from_dgi(DatagramIterator& dgi, DNAStorage* store)
{
    DNANode::make_from_dgi(dgi, store);
    m_code = dgi.get_string();
    m_street_texture = dgi.get_string();
    m_sidewalk_texture = dgi.get_string();
    m_curb_texture = dgi.get_string();
    dgi_extract_color(dgi, m_street_color);
    dgi_extract_color(dgi, m_sidewalk_color);
    dgi_extract_color(dgi, m_curb_color);
}

void DNAStreet::traverse(NodePath& np, DNAStorage* store)
{
    NodePath result = store->find_node(m_code);
    if (result.is_empty())
    {
        raise_code_not_found();
        return;
    }

    NodePath _np = result.copy_to(np);
    _np.set_name(m_name);

    PT(Texture) street_texture = get_texture(m_street_texture, store);
    PT(Texture) sidewalk_texture = get_texture(m_sidewalk_texture, store);
    PT(Texture) curb_texture = get_texture(m_curb_texture, store);

    NodePath street_node = _np.find("**/*_street");
    NodePath sidewalk_node = _np.find("**/*_sidewalk");
    NodePath curb_node = _np.find("**/*_curb");

    if (!street_node.is_empty() && street_texture)
    {
        street_node.set_texture(street_texture, 1);
        street_node.set_color_scale(m_street_color);
    }

    if (!sidewalk_node.is_empty() && sidewalk_texture)
    {
        sidewalk_node.set_texture(sidewalk_texture, 1);
        sidewalk_node.set_color_scale(m_sidewalk_color);
    }

    if (!curb_node.is_empty() && curb_node)
    {
        curb_node.set_texture(curb_texture, 1);
        curb_node.set_color_scale(m_curb_color);
    }

    _np.set_pos_hpr_scale(m_pos, m_hpr, m_scale);
}

void DNAStreet::set_texture(const std::string& texture)
{
    if (m_set_texture_count == 0)
        set_street_texture(texture);

    else if (m_set_texture_count == 1)
        set_sidewalk_texture(texture);

    else if (m_set_texture_count == 2)
        set_curb_texture(texture);

    else
    {
        dna_cat.warning() << "tried to add a 4th texture to DNAStreet!" << std::endl;
        return;
    }

    m_set_texture_count++;
}

void DNAStreet::set_color(LVecBase4f color)
{
    if (m_set_color_count == 0)
        set_street_color(color);

    else if (m_set_color_count == 1)
        set_sidewalk_color(color);

    else if (m_set_color_count == 2)
        set_curb_color(color);

    else
    {
        dna_cat.warning() << "tried to add a 4th color to DNAStreet!" << std::endl;
        return;
    }

    m_set_color_count++;
}

PT(Texture) DNAStreet::get_texture(const std::string& texture, DNAStorage* store)
{
    if (!texture.size())
        return nullptr;

    PT(Texture) tex = store->find_texture(texture);
    if (!tex)
    {
        raise_code_not_found(texture.c_str());
        return nullptr;
    }

    return tex;
}
