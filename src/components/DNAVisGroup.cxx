#include "DNAStorage.h"
#include "DNAVisGroup.h"

TypeHandle DNAVisGroup::_type_handle;

DNAVisGroup::DNAVisGroup(const std::string& name): DNAGroup(name)
{
    m_vis_group = this;
}

DNAVisGroup::~DNAVisGroup()
{
}
        
void DNAVisGroup::add_visible(const std::string& visible)
{
    m_visibles.push_back(visible);
}

bool DNAVisGroup::remove_visible(const std::string& visible)
{
    visibles_vec_t::iterator it = std::find(m_visibles.begin(), m_visibles.end(), visible);
    if (it == m_visibles.end())
        return false;
        
    m_visibles.erase(it);
    return true;
}

size_t DNAVisGroup::get_num_visibles()
{
    return m_visibles.size();
}

const std::string& DNAVisGroup::get_visible(size_t index)
{
    return m_visibles.at(index);
}
        
void DNAVisGroup::add_suit_edge(DNASuitEdge* edge)
{
    m_suit_edges.push_back(edge);
}

bool DNAVisGroup::remove_suit_edge(DNASuitEdge* edge)
{
    suit_edge_vec_t::iterator it = std::find(m_suit_edges.begin(), m_suit_edges.end(), edge);
    if (it == m_suit_edges.end())
        return false;
        
    m_suit_edges.erase(it);
    return true;
}

size_t DNAVisGroup::get_num_suit_edges()
{
    return m_suit_edges.size();
}

DNASuitEdge* DNAVisGroup::get_suit_edge(size_t index)
{
    return m_suit_edges.at(index);
}
        
void DNAVisGroup::add_battle_cell(DNABattleCell* cell)
{
    m_battle_cells.push_back(cell);
}

bool DNAVisGroup::remove_battle_cell(DNABattleCell* cell)
{
    battle_cell_vec_t::iterator it = std::find(m_battle_cells.begin(),
                                               m_battle_cells.end(),
                                               cell);
    if (it == m_battle_cells.end())
        return false;
        
    m_battle_cells.erase(it);
    return true;
}

size_t DNAVisGroup::get_num_battle_cells()
{
    return m_battle_cells.size();
}

DNABattleCell* DNAVisGroup::get_battle_cell(size_t index)
{
    return m_battle_cells.at(index);
}

void DNAVisGroup::make_from_dgi(DatagramIterator& dgi, DNAStorage* store)
{
    unsigned short i, num_edges, num_visibles, num_cells;
    DNAGroup::make_from_dgi(dgi, store);
    
    num_edges = dgi.get_uint16();
    for (i = 0; i < num_edges; i++)
    {
        point_index_t start_point = dgi.get_uint16();
        point_index_t end_point = dgi.get_uint16();
        add_suit_edge(store->get_suit_edge(start_point, end_point));
    }
    
    num_visibles = dgi.get_uint16();
    for (i = 0; i < num_visibles; i++)
        add_visible(dgi.get_string());
        
    num_cells = dgi.get_uint16();
    for (i = 0; i < num_cells; i++)
    {
        unsigned char w = dgi.get_uint8();
        unsigned char h = dgi.get_uint8();
        float x, y, z;
        x = dgi.get_int32() / 100.0;
        y = dgi.get_int32() / 100.0;
        z = dgi.get_int32() / 100.0;
        add_battle_cell(new DNABattleCell(w, h, LPoint3f(x, y, z)));
    }
}

void DNAVisGroup::traverse(NodePath& np, DNAStorage* store)
{
    DNAGroup::traverse(np, store);
}
