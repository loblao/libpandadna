#pragma once

#include "dnabase.h"
#include <vector>
#include <map>

#include <texture.h>
#include <textFont.h>

#include <nodePath.h>

#include "BlockHandle.h"

using namespace std;

typedef vector<string> strvec_t;
typedef map<string, strvec_t> catalog_map_t;

typedef map<string, Texture*> texture_map_t;
typedef map<string, TextFont*> font_map_t;
typedef map<string, NodePath*> node_map_t;

typedef map<unsigned char, BlockHandle> block_map_t;

#include "DNASuitPoint.h"
typedef vector<DNASuitPoint> suit_point_vec_t;

#include "DNASuitEdge.h"

typedef vector<DNASuitEdge> suit_edge_vec_t;
typedef map<unsigned short, suit_edge_vec_t> suit_edge_map_t;

#include "DNABattleCell.h"

typedef vector<DNABattleCell> battle_cell_vec_t;

class EXPCL_PANDASKEL DNAStorage
{
	PUBLISHED:
		DNAStorage(void);
		~DNAStorage(void);

		void store_catalog_code(const string& root, const string& code);
		string get_catalog_code(const string& category, unsigned int index);
		int get_num_catalog_codes(const string& category);

		void store_texture(const string& code, Texture* texture);
		Texture* find_texture(const string& code);
		void reset_textures();

		void store_font(const string& code, TextFont* font);
		TextFont* find_font(const string& code);
		void reset_fonts();

		void store_node(const string& code, NodePath* node);
		void reset_nodes();
		void store_hood_node(const string& code, NodePath* node);
		void reset_hood_nodes();
		void store_place_node(const string& code, NodePath* node);
		void reset_place_nodes();
		NodePath* find_node(const string& code);

		DNASuitPoint get_suit_point_at_index(unsigned short index);
		void reset_suit_points();

		string get_block(string name);
		string get_block_building_type(unsigned short index);
		string get_title_from_block_number(unsigned short index);
		unsigned short get_zone_from_block_number(unsigned short index);
		void reset_blocks();

		void store_block_door(unsigned short index, NodePath door);
		NodePath get_door_pos_hpr_from_block_number(unsigned short index);

		unsigned char get_num_block_numbers();

		DNASuitEdge get_suit_edge(unsigned short start_index, unsigned short end_index);

		//void remove_battle_cell(DNABattleCell cell); // To do
		void reset_battle_cells();

		DNABattleCell get_battle_cell(unsigned short index);
		unsigned short get_num_battle_cells();
 
	public:
		void store_block(unsigned char block_number, const string& title,
					     const string& article, const string& bldg_type,
					 	 unsigned short zone);

		void store_suit_point(unsigned short index, unsigned char point_type,
							  LVector3f* pos, char landmark_building_index);

		void store_suit_edge(unsigned short index, unsigned short start_point,
							 unsigned short end_point, unsigned short zone_id);

		void store_battle_cell(unsigned short width, unsigned short height, LVector3f* pos);
		
	private:
		catalog_map_t m_catalog_codes;
		texture_map_t m_textures;
		font_map_t m_fonts;

		node_map_t m_nodes;
		node_map_t m_hood_nodes;
		node_map_t m_place_nodes;
		block_map_t m_blocks;
		suit_point_vec_t m_suit_points;
		suit_edge_map_t m_suit_edges;
		battle_cell_vec_t m_battle_cells;

#ifndef P3_INTERROGATE
		BlockHandle _get_block_by_index(unsigned short index);
#endif
};
