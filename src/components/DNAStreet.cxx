#include "DNAStreet.h"

TypeHandle DNAStreet::_type_handle;

DNAStreet::DNAStreet(const std::string& name): DNANode(name), m_code(""),
                                               m_street_texture(""),
                                               m_sidewalk_texture(""),
                                               m_curb_texture(""),
                                               m_street_color(LVecBase4f(1)),
                                               m_sidewalk_color(LVecBase4f(1)),
                                               m_curb_color(LVecBase4f(1))
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
    m_street_color = DGI_EXTRACT_COLOR;
    m_sidewalk_color = DGI_EXTRACT_COLOR;
    m_curb_color = DGI_EXTRACT_COLOR;
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
        
PT(Texture) DNAStreet::get_texture(const std::string& texture, DNAStorage* store)
{
    if (!texture.size())
        return NULL;
   
    PT(Texture) tex = store->find_texture(texture);
    if (!tex)
    {
        raise_code_not_found(texture.c_str());
        return NULL;
    }

    return tex;
}
