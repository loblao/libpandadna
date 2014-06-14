#include "DNAVisGroup.h"

DNAVisGroup::DNAVisGroup(string name) : DNAGroup(name) {}
DNAVisGroup::~DNAVisGroup(void) {}

void DNAVisGroup::make_from_dgi(DatagramIterator& dgi, DNAStorage* store)
{
	DNAGroup::make_from_dgi(dgi, store);

	unsigned short num_edges = dgi.get_uint16();
	for (unsigned short i = 0; i < num_edges; i++)
	{
		unsigned short start_point = dgi.get_uint16();
		unsigned short end_point = dgi.get_uint16();
		add_suit_edge(store->get_suit_edge(start_point, end_point));
	};

	unsigned short num_visibles = dgi.get_uint16();
	for (unsigned short i = 0; i < num_visibles; i++)
	{
		add_visible(dgi_extract_string8(dgi));
	};

	unsigned short num_cells = dgi.get_uint16();
	for (unsigned short i = 0; i < num_cells; i++)
	{
		unsigned char w = dgi.get_uint8();
		unsigned char h = dgi.get_uint8();

		int x = dgi.get_int32();
		int y = dgi.get_int32();
		int z = dgi.get_int32();

		DNABattleCell c = DNABattleCell();
		c.set_width_height(w, h);
		c.set_pos(new LVector3f(x / 100.0, y / 100.0, z / 100.0));
		add_battle_cell(c);
	};
};

void DNAVisGroup::add_battle_cell(DNABattleCell cell)
{
	m_cells.push_back(cell);
};

void DNAVisGroup::add_suit_edge(DNASuitEdge edge)
{
	m_edges.push_back(edge);
};

void DNAVisGroup::add_visible(string visible)
{
	m_visibles.push_back(visible);
};

size_t DNAVisGroup::get_num_battle_cells()
{
	return m_cells.size();
};

size_t DNAVisGroup::get_num_suit_edges()
{
	return m_edges.size();
};

size_t DNAVisGroup::get_num_visibles()
{
	return m_visibles.size();
};

DNABattleCell DNAVisGroup::get_battle_cell(size_t index)
{
	return m_cells.at(index);
};

DNASuitEdge DNAVisGroup::get_suit_edge(size_t index)
{
	return m_edges.at(index);
};

string DNAVisGroup::get_visible_name(size_t index)
{
	return m_visibles.at(index);
};

void DNAVisGroup::traverse(NodePath& np, DNAStorage* store)
{
	DNAGroup::traverse(np, store);
};

DNAVisGroup* DNAVisGroup::get_vis_group()
{
	return this;
};
