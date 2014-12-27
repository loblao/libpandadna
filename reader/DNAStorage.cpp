#include "DNAStorage.h"

#include <staticTextFont.h>

#include <modelPool.h>
#include <texturePool.h>
#include <fontPool.h>

DNAStorage::DNAStorage() {};
DNAStorage::~DNAStorage()
{
	reset_battle_cells();
	reset_fonts();
	reset_textures();
	reset_nodes();
	reset_hood_nodes();
	reset_place_nodes();
	m_catalog_codes.clear();
	reset_suit_points();
	m_suit_edges.clear();
	reset_blocks();

	ModelPool::garbage_collect();
	TexturePool::garbage_collect();
	FontPool::garbage_collect();
};

void DNAStorage::store_catalog_code(const string& root, const string& code)
{
	map<string, vector<string>>::iterator it, e;

	e = m_catalog_codes.end();
	it = m_catalog_codes.find(root);

	if (it == e)
	{
		// new root
		strvec_t v(0);
		v.push_back(code);
		m_catalog_codes[root] = v;
		return;
	};

	it->second.push_back(code);
};

string DNAStorage::get_catalog_code(const string& category, unsigned int index)
{
	map<string, vector<string>>::iterator it = m_catalog_codes.find(category);

	if (it == m_catalog_codes.end())
	{
		// no such category
		cerr << "DNAStorage(fatal): no such category " << category << ", the app will crash now!" << endl;
	};

	strvec_t v = it->second;

	if (index >= v.size())
	{
		// bad index
		cerr << "DNAStorage(fatal): bad index " << index << ", the app will crash now!" << endl;
	};

	string item = v.at(index);
	return item;
};

int DNAStorage::get_num_catalog_codes(const string& category)
{
	catalog_map_t::iterator it = m_catalog_codes.find(category);

	if (it == m_catalog_codes.end())
	{
		// no such category
		return -1;
	};

	strvec_t v = it->second;

	return v.size();
};

void DNAStorage::store_texture(const string& code, Texture* texture)
{
	m_textures[code] = texture;
}

Texture* DNAStorage::find_texture(const string& code)
{
	texture_map_t::iterator it = m_textures.find(code);
	if (it == m_textures.end())
	{
		cerr << "DNAStorage(fatal): no such texture " << code << ", the app will crash now!" << endl;
	};

	return it->second;
};

void DNAStorage::reset_textures()
{
	m_textures.clear();
}

void DNAStorage::store_font(const string& code, TextFont* font)
{
	m_fonts[code] = font;
}

TextFont* DNAStorage::find_font(const string& code)
{
	font_map_t::iterator it = m_fonts.find(code);
	if (it == m_fonts.end())
	{
		cerr << "DNAStorage(fatal): no such font " << code << ", the app will crash now!" << endl;
	};

	return it->second;
};

void DNAStorage::reset_fonts()
{
	m_fonts.clear();
}

void DNAStorage::store_node(const std::string &code, NodePath *node)
{
	m_nodes[code] = node;
};

void DNAStorage::reset_nodes()
{
	for (node_map_t::iterator it = m_nodes.begin(); it != m_nodes.end(); it++)
	{
		(it->second)->remove_node();
		delete it->second;
	};
	m_nodes.clear();
};

void DNAStorage::store_hood_node(const std::string &code, NodePath *node)
{
	m_hood_nodes[code] = node;
};

void DNAStorage::reset_hood_nodes()
{
	for (node_map_t::iterator it = m_hood_nodes.begin(); it != m_hood_nodes.end(); it++)
	{
		(it->second)->remove_node();
		delete it->second;
	};
	m_hood_nodes.clear();
};

void DNAStorage::store_place_node(const std::string &code, NodePath *node)
{
	m_place_nodes[code] = node;
};

void DNAStorage::reset_place_nodes()
{
	for (node_map_t::iterator it = m_place_nodes.begin(); it != m_place_nodes.end(); it++)
	{
		(it->second)->remove_node();
		delete it->second;
	};
	m_place_nodes.clear();
};

NodePath* DNAStorage::find_node(const string& code)
{
	node_map_t::iterator it;

	it = m_nodes.find(code);
	if (it != m_nodes.end())
	{
		return it->second;
	};

	it = m_hood_nodes.find(code);
	if (it != m_hood_nodes.end())
	{
		return it->second;
	};

	it = m_place_nodes.find(code);
	if (it != m_place_nodes.end())
	{
		return it->second;
	};

	NodePath np = NodePath::not_found();
	NodePath *r = new NodePath(np);
	return r;
};

void DNAStorage::store_block(unsigned char block_number, const string& title,
							 const string& article, const string& bldg_type,
							 unsigned short zone)
{
	BlockHandle b = BlockHandle();
	b.set_title(title);
	b.set_article(article);
	b.set_type(bldg_type);
	b.set_zone(zone);

	m_blocks[block_number] = b;
};

void DNAStorage::store_suit_point(unsigned short index, unsigned char point_type,
								  LVector3f *pos, char landmark_building_index)
{
	DNASuitPoint p = DNASuitPoint(index, point_type, pos, landmark_building_index);
	m_suit_points.push_back(p);
};

DNASuitPoint DNAStorage::get_suit_point_at_index(unsigned short index)
{
	return m_suit_points.at(index);
};

void DNAStorage::reset_suit_points()
{
	m_suit_points.clear();
};

BlockHandle DNAStorage::_get_block_by_index(unsigned short index)
{
	block_map_t::iterator it = m_blocks.find(index);
	if (it == m_blocks.end())
	{
		BlockHandle dummy = BlockHandle();
		return dummy;
	}
	return it->second;
};

string DNAStorage::get_block(std::string name)
{
	string block = name.substr(name.find(':') - 2, name.find(':'));
	if (string(1, block.at(0)).find_first_not_of("0123456789") != std::string::npos)
	{
		block = block.substr(1);
	}

    return block;
};

string DNAStorage::get_block_building_type(unsigned short index)
{
	BlockHandle b = _get_block_by_index(index);
	return b.get_type();
};

string DNAStorage::get_title_from_block_number(unsigned short index)
{
	BlockHandle b = _get_block_by_index(index);
	return b.get_title();
};

unsigned short DNAStorage::get_zone_from_block_number(unsigned short index)
{
	BlockHandle b = _get_block_by_index(index);
	return b.get_zone();
};

void DNAStorage::store_block_door(unsigned short index, NodePath door)
{
	BlockHandle b = _get_block_by_index(index);
	b.set_door(door);
};

NodePath DNAStorage::get_door_pos_hpr_from_block_number(unsigned short index)
{
	BlockHandle b = _get_block_by_index(index);
	return b.get_door();
};

unsigned char DNAStorage::get_num_block_numbers()
{
	return m_blocks.size();
};

void DNAStorage::reset_blocks()
{
	m_blocks.clear();
};

void DNAStorage::store_suit_edge(unsigned short index, unsigned short start_point,
								 unsigned short end_point, unsigned short zone_id)
{
	DNASuitEdge e = DNASuitEdge();
	e.set_start_point(start_point);
	e.set_end_point(end_point);
	e.set_zone_id(zone_id);

	suit_edge_map_t::iterator it;
	it = m_suit_edges.find(index);

	if (it == m_suit_edges.end())
	{
		suit_edge_vec_t v(0);
		v.push_back(e);
		m_suit_edges[index] = v;
		return;
	};

	it->second.push_back(e);
};

DNASuitEdge DNAStorage::get_suit_edge(unsigned short start_index, unsigned short end_index)
{
	suit_edge_map_t::iterator it = m_suit_edges.find(start_index);
	if (it == m_suit_edges.end())
	{
		cerr << "DNAStorage(fatal): no such edge for start index " << start_index;
		cerr << ", the app will crash now!" << endl;
	};
	
	suit_edge_vec_t v = it->second;
	for (size_t i = 0; i < v.size(); i++)
	{
		DNASuitEdge e = v.at(i);
		if (e.get_end_point() == end_index)
		{
			return e;
		}
	};

	cerr << "DNAStorage(fatal): such edge with start index " << start_index;
	cerr << " exists, but doesn't match end index " << end_index << ", the app will crash now!";
	cerr << endl;
	throw string();
};

void DNAStorage::store_battle_cell(unsigned short width, unsigned short height, LVector3f *pos)
{
	DNABattleCell c = DNABattleCell();
	c.set_width_height(width, height);
	c.set_pos(pos);
	m_battle_cells.push_back(c);
};

void DNAStorage::reset_battle_cells()
{
	m_battle_cells.clear();
};

DNABattleCell DNAStorage::get_battle_cell(unsigned short index)
{
	return m_battle_cells.at(index);
};

unsigned short DNAStorage::get_num_battle_cells()
{
	return m_battle_cells.size();
};
