#include "DNAStorage.h"
#include "DNAGroup.h"

#include <loader.h>
#include <algorithm>
#include <cctype>

DNAStorage::DNAStorage()
{
}

DNAStorage::~DNAStorage()
{
}

void DNAStorage::store_DNA_vis_group(DNAVisGroup* group)
{
    m_vis_groups.push_back(group);
}

size_t DNAStorage::get_num_DNA_vis_groups()
{
    return m_vis_groups.size();
}

size_t DNAStorage::get_num_DNA_vis_groups_AI()
{
    return get_num_DNA_vis_groups();
}

size_t DNAStorage::get_num_visibles_in_DNA_vis_group(size_t index)
{
    return get_DNA_vis_group_AI(index)->get_num_visibles();
}

std::string DNAStorage::get_visible_name(size_t index, size_t visible_index)
{
    return get_DNA_vis_group_AI(index)->get_visible(visible_index);
}

DNAVisGroup* DNAStorage::get_DNA_vis_group_AI(size_t index)
{
    return m_vis_groups.at(index);
}

std::string DNAStorage::get_DNA_vis_group_name(size_t index)
{
    return get_DNA_vis_group_AI(index)->get_name();
}

void DNAStorage::reset_DNA_vis_groups()
{
    m_vis_groups.clear();
}

void DNAStorage::reset_DNA_vis_groups_AI()
{
    reset_DNA_vis_groups();
}

void DNAStorage::store_texture(const std::string& name, PT(Texture) texture)
{
    m_textures[name] = texture;
}

PT(Texture) DNAStorage::find_texture(const std::string& name)
{
    for (texture_map_t::iterator it = m_textures.begin(); it != m_textures.end(); ++it)
    {
        if (it->first == name)
            return it->second;
    }
    
    return NULL;
}

void DNAStorage::reset_textures()
{
    m_textures.clear();
}

void DNAStorage::store_font(const std::string& code, PT(TextFont) font, const std::string& filename)
{
    m_fonts[code] = font;
    m_font_filenames[code] = filename;
}

PT(TextFont) DNAStorage::find_font(const std::string& code)
{
    for (font_map_t::iterator it = m_fonts.begin(); it != m_fonts.end(); ++it)
    {
        if (it->first == code)
            return it->second;
    }
    
    return NULL;
}

void DNAStorage::reset_fonts()
{
    m_fonts.clear();
    m_font_filenames.clear();
}

void DNAStorage::store_catalog_code(const std::string& category,
                                    const std::string& code)
{
    m_catalog_codes[category].push_back(code);
}

size_t DNAStorage::get_num_catalog_codes(const std::string& category)
{
    return m_catalog_codes[category].size();
}

std::string DNAStorage::get_catalog_code(const std::string& category,
                                         size_t index)
{
    return m_catalog_codes[category].at(index);
}

NodePath DNAStorage::find_node(const std::string& code)
{
    std::string filename, search;
    if (m_nodes.count(code))
    {
        filename = m_nodes[code][0];
        search = m_nodes[code][1];
    }
    
    else if (m_hood_nodes.count(code))
    {
        filename = m_hood_nodes[code][0];
        search = m_hood_nodes[code][1];
    }
    
    else if (m_place_nodes.count(code))
    {
        filename = m_place_nodes[code][0];
        search = m_place_nodes[code][1];
    }
    
    else
        return NodePath();
        
    NodePath model = NodePath(Loader::get_global_ptr()->load_sync(Filename(filename)));
    if (search.size())
    {
        std::stringstream ss;
        ss << "**/" << search;
        model = model.find(ss.str());
    }
    model.set_tag("DNACode", code);
    return model;
}

void DNAStorage::store_node(const std::string& filename,
                            const std::string& search,
                            const std::string& code)
{
    string_vec_t def(2);
    def[0] = filename;
    def[1] = search;
    m_nodes[code] = def;
}

void DNAStorage::store_hood_node(const std::string& filename,
                                 const std::string& search,
                                 const std::string& code)
{
    string_vec_t def(2);
    def[0] = filename;
    def[1] = search;
    m_hood_nodes[code] = def;
}

void DNAStorage::store_place_node(const std::string& filename,
                                  const std::string& search,
                                  const std::string& code)
{
    string_vec_t def(2);
    def[0] = filename;
    def[1] = search;
    m_place_nodes[code] = def;
}

void DNAStorage::reset_nodes()
{
    m_nodes.clear();
}

void DNAStorage::reset_hood_nodes()
{
    m_hood_nodes.clear();
}

void DNAStorage::reset_place_nodes()
{
    m_place_nodes.clear();
}

void DNAStorage::reset_hood()
{
    reset_block_numbers();
}

void DNAStorage::store_block_door(block_number_t block_number, NodePath& door)
{
    m_block_doors[block_number] = door;
}

void DNAStorage::store_block_zone(block_number_t block_number, zone_id_t zone_id)
{
    m_block_zones[block_number] = zone_id;
}

void DNAStorage::store_block_number(block_number_t block_number)
{
    m_block_numbers.push_back(block_number);
}

void DNAStorage::store_block_title(block_number_t block_number,
                                   const std::string& title)
{
    m_block_titles[block_number] = title;
}

void DNAStorage::store_block_article(block_number_t block_number,
                                     const std::string& article)
{
    m_block_articles[block_number] = article;
}

void DNAStorage::store_block_building_type(block_number_t block_number,
                                           const std::string& bldg_type)
{
    m_block_building_types[block_number] = bldg_type;
}

void DNAStorage::store_block(block_number_t block_number, const std::string& title,
                             const std::string& article, const std::string& bldg_type,
                             zone_id_t zone_id)
{
    store_block_number(block_number);
    store_block_title(block_number, title);
    store_block_article(block_number, article);
    store_block_building_type(block_number, bldg_type);
    store_block_zone(block_number, zone_id);
}

size_t DNAStorage::get_num_block_numbers()
{
    return m_block_numbers.size();
}

bool is_not_digit (char c)
{
    return std::isdigit(c) == 0;
}

std::string DNAStorage::get_block(const std::string& name)
{
    typedef std::string::const_iterator const_iterator_t;
    const const_iterator_t colon_position = std::find(name.begin(), name.end(), ':');

    if (colon_position == name.end())
    {
        return "";
    }

    std::reverse_iterator<const_iterator_t> rstart(colon_position); 
    std::reverse_iterator<const_iterator_t> rend = std::find_if(rstart, name.rend(), is_not_digit); 

    std::string out(rstart, rend);
    std::reverse(out.begin(), out.end());
    return out;
}

std::string DNAStorage::get_block_building_type(block_number_t block_number)
{
    return m_block_building_types[block_number];
}

std::string DNAStorage::get_title_from_block_number(block_number_t block_number)
{
    return m_block_titles[block_number];
}

NodePath DNAStorage::get_door_pos_hpr_from_block_number(block_number_t block_number)
{
    dna_cat.info() << "get_door_pos_hpr_from_block_number " << block_number << std::endl;
    return m_block_doors[block_number];
}

size_t DNAStorage::get_block_number_at(size_t index)
{
    return m_block_numbers.at(index);
}

zone_id_t DNAStorage::get_zone_from_block_number(block_number_t block_number)
{
    return m_block_zones[block_number];
}

void DNAStorage::reset_block_numbers()
{
    m_block_numbers.clear();
    m_block_zones.clear();
    m_block_articles.clear();
    m_block_doors.clear();
    m_block_titles.clear();
    m_block_building_types.clear();
}

void DNAStorage::reset_block_zones()
{
    m_block_zones.clear();
}

bool DNAStorage::allow_suit_origin(NodePath& np)
{
    // NOTICE: game-specific hack
    if (np.get_name().find("gag_shop") != std::string::npos)
        return false;
        
    if (np.get_name().find("pet_shop") != std::string::npos)
        return false;
        
    return true;
}

void DNAStorage::store_suit_edge(point_index_t start_index, point_index_t end_index,
                                 zone_id_t zone_id)
{
    DNASuitPoint* start_point = get_suit_point_with_index(start_index);
    DNASuitPoint* end_point = get_suit_point_with_index(end_index);
    
    if (!start_point || !end_point)
    {
        dna_cat.warning() << "attempted to add edge with unknown start_point(" << start_index
                          << ") and/or unknown end_point ("  << end_index << ")" << std::endl;
        return;
    }

    m_suit_edges[start_index].push_back(new DNASuitEdge(start_point, end_point, zone_id));
}

DNASuitEdge* DNAStorage::get_suit_edge(point_index_t start_index,
                                       point_index_t end_index)
{
    std::vector<DNASuitEdge*> edges = m_suit_edges[start_index];
    for (std::vector<DNASuitEdge*>::iterator it = edges.begin();
         it != edges.end(); ++it)
    {
        DNASuitEdge* edge = *it;
        if (edge->get_end_point()->get_index() == end_index)
            return edge;
    }
    
    return NULL;
}

void DNAStorage::store_suit_point(DNASuitPoint* suit_point)
{
    m_suit_points.push_back(suit_point);
}

DNASuitPoint* DNAStorage::get_suit_point_at_index(size_t index)
{
    return m_suit_points.at(index);
}

DNASuitPoint* DNAStorage::get_suit_point_with_index(point_index_t index)
{
    for (suit_point_vec_t::iterator it = m_suit_points.begin(); it != m_suit_points.end(); ++it)
    {
        if ((*it)->get_index() == index)
            return *it;
    }

    return NULL;
}

size_t DNAStorage::get_num_suit_points()
{
    return m_suit_points.size();
}

void DNAStorage::reset_suit_points()
{
    m_suit_points.clear();
}

DNASuitPath* DNAStorage::get_suit_path(DNASuitPoint* start_point,
                                       DNASuitPoint* end_point,
                                       unsigned short min_path_len,
                                       unsigned short max_path_len)
{
    DNASuitPath* path = new DNASuitPath;
    path->add_point(start_point);
    while (path->get_num_points() < max_path_len)
    {
        if (start_point == end_point && path->get_num_points() >= min_path_len)
            break;

        DNASuitPath* adjacent_points = get_adjacent_points(start_point);
        if (adjacent_points->get_num_points() == 0)
        {
            dna_cat.error() << "could not find DNASuitPath: point " << start_point->get_index()
                            << " has no edges" << std::endl;
            delete adjacent_points;
            delete path;
            return NULL;
        }

        // First, let's see if our end point is an adjacent point
        // If it's not, or path is still too short, advance to first
        // non-door adjacent point
        DNASuitPoint* non_door_point = NULL;

        for (size_t i = 0; i < adjacent_points->get_num_points(); ++i)
        {
            start_point = adjacent_points->get_point(i);
            if (start_point == end_point && path->get_num_points() >= (min_path_len + 1))
            {
                delete adjacent_points;
                path->add_point(start_point);
                return path;
            }

            DNASuitPoint::PointType start_point_type = start_point->get_point_type();
            if (start_point_type != DNASuitPoint::FRONT_DOOR_POINT
                && start_point_type != DNASuitPoint::SIDE_DOOR_POINT
                && non_door_point == NULL)
            {
                non_door_point = start_point;
            }
        }

        delete adjacent_points;

        if (non_door_point == NULL)
        {
            dna_cat.error() << "could not find DNASuitPath: point " << start_point->get_index()
                            << " has no non-door point edge" << std::endl;
            delete path;
            return NULL;
        }

        start_point = non_door_point;
        path->add_point(start_point);
    }
    
    return path;
}

float DNAStorage::get_suit_edge_travel_time(point_index_t start_index,
                                            point_index_t end_index,
                                            float suit_walk_speed)
{                    
    DNASuitPoint* start_point = get_suit_point_with_index(start_index);
    DNASuitPoint* end_point = get_suit_point_with_index(end_index);
    
    if (!start_point || !end_point)
        return 0;
    
    return (end_point->get_pos() - start_point->get_pos()).length() / suit_walk_speed;
}

zone_id_t DNAStorage::get_suit_edge_zone(point_index_t start_index,
                                         point_index_t end_index)
{
    DNASuitEdge* edge = get_suit_edge(start_index, end_index);
    nassertd(edge != NULL)
    {
    }
    return edge->get_zone_id();
}

DNASuitPath* DNAStorage::get_adjacent_points(DNASuitPoint* point)
{
    DNASuitPath* path = new DNASuitPath;
    point_index_t start_index = point->get_index();
    if (m_suit_edges.count(start_index) == 0)
        return path;
        
    for (std::vector<DNASuitEdge*>::iterator it = m_suit_edges[start_index].begin();
         it != m_suit_edges[start_index].end(); ++it)
        path->add_point((*it)->get_end_point());
        
    return path;
}
    
bool DNAStorage::discover_continuity()
{
    // To do
    return true;
}

#define PACK_NODES(X) dg.add_uint16(X.size()); for (nodes_t::iterator it = X.begin(); it != X.end(); ++it) {dg.add_string(it->first);\
                                    dg.add_string((it->second)[0]); dg.add_string((it->second)[1]);}

void DNAStorage::write_pdna(Datagram& dg)
{
    // Catalog codes
    dg.add_uint16(m_catalog_codes.size());
    for (catalog_codes_map_t::iterator it = m_catalog_codes.begin(); it != m_catalog_codes.end(); ++it)
    {
        dg.add_string(it->first);
        
        string_vec_t codes = it->second;
        dg.add_uint8(codes.size());
        for (string_vec_t::iterator code = codes.begin(); code != codes.end(); ++code)
            dg.add_string(*code);
    }
    
    // Textures
    dg.add_uint16(m_textures.size());
    for (texture_map_t::iterator it = m_textures.begin(); it != m_textures.end(); ++it)
    {
        dg.add_string(it->first);
        dg.add_string((it->second)->get_filename());
    }
    
    // Fonts
    dg.add_uint16(m_fonts.size());
    for (font_map_t::iterator it = m_fonts.begin(); it != m_fonts.end(); ++it)
    {
        dg.add_string(it->first);
        dg.add_string(m_font_filenames[it->first]);
    }
    
    // Nodes
    PACK_NODES(m_nodes);
    PACK_NODES(m_hood_nodes);
    PACK_NODES(m_place_nodes);
    
    // Blocks
    dg.add_uint16(m_block_numbers.size());
    for (block_number_vec_t::iterator it = m_block_numbers.begin(); it != m_block_numbers.end(); ++it)
    {
        block_number_t block_number = *it;
        dg.add_uint8(block_number);
        dg.add_uint16(m_block_zones[block_number]);
        dg.add_string(m_block_titles[block_number]);
        dg.add_string(m_block_articles[block_number]);
        dg.add_string(m_block_building_types[block_number]);
    }
    
    // Suit points
    dg.add_uint16(m_suit_points.size());
    for (suit_point_vec_t::iterator it = m_suit_points.begin(); it != m_suit_points.end(); ++it)
    {
        DNASuitPoint* point = *it;
        dg.add_uint16(point->get_index());
        dg.add_uint8(point->get_point_type());
        
        dg.add_int32(floor(point->get_pos().get_x() * 100));
        dg.add_int32(floor(point->get_pos().get_y() * 100));
        dg.add_int32(floor(point->get_pos().get_z() * 100));
        
        dg.add_int16(point->get_landmark_building_index());
    }

    // Suit edges
    dg.add_uint16(m_suit_edges.size());
    for (suit_edge_map_t::iterator it = m_suit_edges.begin(); it != m_suit_edges.end(); ++it)
    {
        point_index_t start_point_index = it->first;
        std::vector<DNASuitEdge*> edges = it->second;
        
        dg.add_uint16(start_point_index);
        dg.add_uint16(edges.size());
        
        for (std::vector<DNASuitEdge*>::iterator it = edges.begin(); it != edges.end(); ++it)
        {
            DNASuitEdge* edge = *it;
            dg.add_uint16(edge->get_end_point()->get_index());
            dg.add_uint16(edge->get_zone_id());
        }
    }
}

void DNAStorage::write_dna(std::ostream& out)
{   
    // Suit points
    for (suit_point_vec_t::iterator it = m_suit_points.begin(); it != m_suit_points.end(); ++it)
    {
        DNASuitPoint* point = *it;

        out << "store_suit_point [ " << point->get_index() << ", ";
        switch (point->get_point_type())
        {
            case DNASuitPoint::STREET_POINT:
                out << "STREET_POINT, ";
                break;
                
            case DNASuitPoint::FRONT_DOOR_POINT:
                out << "FRONT_DOOR_POINT, ";
                break;
                
            case DNASuitPoint::SIDE_DOOR_POINT:
                out << "SIDE_DOOR_POINT, ";
                break;
                
            case DNASuitPoint::COGHQ_IN_POINT:
                out << "COGHQ_IN_POINT, ";
                break;
                
            case DNASuitPoint::COGHQ_OUT_POINT:
                out << "COGHQ_OUT_POINT, ";
                break;
                
            default:
                out << "UNKNOWN_POINT, ";
                break;
        }
        
        LVecBase3f pos = point->get_pos();
        
        out << pos.get_x() << " " << pos.get_y() << " " << pos.get_z();
        
        block_number_t block = point->get_landmark_building_index();
        if (block != -1)
            out << ", " << block;
        
        out << " ]" << std::endl;
    }
    
    // Textures
    for (texture_map_t::iterator it = m_textures.begin(); it != m_textures.end(); ++it)
    {
        out << "store_texture [ \"" << _reverse_catalog_lookup(it->first) << "\" \""
            << it->first << "\" \"" << (it->second)->get_filename() << "\" ]" << std::endl;
    }
    
    // Fonts
    for (font_map_t::iterator it = m_fonts.begin(); it != m_fonts.end(); ++it)
    {
        out << "store_texture [ \"" << _reverse_catalog_lookup(it->first) << "\" \""
            << it->first << "\" \"" << m_font_filenames[it->first] << "\" ]" << std::endl;
    }
    
    // Nodes
    typedef std::map<std::string, std::vector<string_vec_t> > str2strstr_t; // {filename: ((code, search), (code, search), ...)}
    str2strstr_t _models;
    for (nodes_t::iterator it = m_nodes.begin(); it != m_nodes.end(); ++it)
    {
        string_vec_t v(2);
        v[0] = it->first;
        v[1] = (it->second)[1];
        _models[(it->second)[0]].push_back(v);
    }
    
    for (str2strstr_t::iterator it = _models.begin(); it != _models.end(); ++it)
    {
        out << "model \"" << it->first << "\" [" << std::endl;
        std::vector<string_vec_t> data = it->second;
        for (std::vector<string_vec_t>::iterator cs = data.begin(); cs != data.end(); ++cs)
        {
            string_vec_t codesearch = *cs;
            out << "    store_node [ \"" << _reverse_catalog_lookup(codesearch[0]) << "\" \""
                << codesearch[0] << "\" ";
            if (codesearch[1].size())
                out << "\"" << codesearch[1] <<  "\" ";
            
            out << "]" << std::endl;
        }
        out << "]" << std::endl;
    }
    
    _models.clear();
    
    // Hood nodes
    for (nodes_t::iterator it = m_hood_nodes.begin(); it != m_hood_nodes.end(); ++it)
    {
        string_vec_t v(2);
        v[0] = it->first;
        v[1] = (it->second)[1];
        _models[(it->second)[0]].push_back(v);
    }
    
    for (str2strstr_t::iterator it = _models.begin(); it != _models.end(); ++it)
    {
        out << "hood_model \"" << it->first << "\" [" << std::endl;
        std::vector<string_vec_t> data = it->second;
        for (std::vector<string_vec_t>::iterator cs = data.begin(); cs != data.end(); ++cs)
        {
            string_vec_t codesearch = *cs;
            out << "    store_node [ \"" << _reverse_catalog_lookup(codesearch[0]) << "\" \""
                << codesearch[0] << "\" ";
            if (codesearch[1].size())
                out << "\"" << codesearch[1] <<  "\" ";
            
            out << "]" << std::endl;
        }
        out << "]" << std::endl;
    }
    
    _models.clear();
    
    // Place nodes
    for (nodes_t::iterator it = m_place_nodes.begin(); it != m_place_nodes.end(); ++it)
    {
        string_vec_t v(2);
        v[0] = it->first;
        v[1] = (it->second)[1];
        _models[(it->second)[0]].push_back(v);
    }
    
    for (str2strstr_t::iterator it = _models.begin(); it != _models.end(); ++it)
    {
        out << "place_model \"" << it->first << "\" [" << std::endl;
        std::vector<string_vec_t> data = it->second;
        for (std::vector<string_vec_t>::iterator cs = data.begin(); cs != data.end(); ++cs)
        {
            string_vec_t codesearch = *cs;
            out << "    store_node [ \"" << _reverse_catalog_lookup(codesearch[0]) << "\" \""
                << codesearch[0] << "\" ";
            if (codesearch[1].size())
                out << "\"" << codesearch[1] <<  "\" ";
            
            out << "]" << std::endl;
        }
        out << "]" << std::endl;
    }
    
    _models.clear();
}

std::string DNAStorage::_reverse_catalog_lookup(const std::string& code)
{
    for (catalog_codes_map_t::iterator it = m_catalog_codes.begin(); it != m_catalog_codes.end(); ++it)
    {
        if (std::find((it->second).begin(), (it->second).end(), code) != (it->second).end())
            return it->first;
    }
    return std::string("not_found");
}
