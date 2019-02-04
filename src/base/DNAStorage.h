#ifndef _H_DNA_STORAGE_
#define _H_DNA_STORAGE_

#include "dnabase.h"

#include "DNASuitEdge.h"
#include "DNASuitPath.h"
#include "DNAVisGroup.h"

#include "textFont.h"
#include "texture.h"
#include "nodePath.h"

#ifndef CPPPARSER
typedef struct {
    NodePath np;
    std::string filename;
    std::string search;
} nodedef_t;

typedef std::vector<std::string> string_vec_t;
typedef std::map<std::string, nodedef_t> nodes_t;
typedef std::vector<PT(DNAVisGroup)> visgroup_vec_t;
typedef std::map<point_index_t, std::vector<PT(DNASuitEdge)> > suit_edge_map_t;
typedef std::map<std::string, PT(TextFont)> font_map_t;
typedef std::map<std::string, std::string> font_filename_map_t;
typedef std::map<block_number_t, std::string> block_string_map_t;
typedef std::map<block_number_t, NodePath> door_vec_t;
typedef std::vector<block_number_t> block_number_vec_t;
typedef std::map<block_number_t, zone_id_t> block_zone_vec_t;
typedef std::map<std::string, PT(Texture)> texture_map_t;
typedef std::map<std::string, string_vec_t> catalog_codes_map_t;
typedef std::map<block_number_t, LMatrix4f> transform_map_t;
#endif

class EXPCL_DNA DNAStorage
{
    PUBLISHED:
        DNAStorage();
        ~DNAStorage();

        INLINE void reset_DNA_groups()
        {
        }

        INLINE void reset_battle_cells()
        {
        }

        void store_DNA_vis_group(DNAVisGroup* group);
        size_t get_num_DNA_vis_groups();
        size_t get_num_DNA_vis_groups_AI();

        size_t get_num_visibles_in_DNA_vis_group(size_t index);
        std::string get_visible_name(size_t index, size_t visible_index);

        DNAVisGroup* get_DNA_vis_group_AI(size_t index);
        std::string get_DNA_vis_group_name(size_t index);

        void reset_DNA_vis_groups();
        void reset_DNA_vis_groups_AI();

        void store_texture(const std::string& name, PT(Texture) texture);
        PT(Texture) find_texture(const std::string& name);
        void reset_textures();

        void store_font(const std::string& code, PT(TextFont) font, const std::string& filename="");
        PT(TextFont) find_font(const std::string& code);
        void reset_fonts();

        void store_catalog_code(const std::string& category,
                                const std::string& code);
        size_t get_num_catalog_codes(const std::string& category);
        std::string get_catalog_code(const std::string& category,
                                     size_t index);

        NodePath find_node(const std::string& code);
        void store_node(const std::string& filename, const std::string& search,
                        const std::string& code);
        void store_hood_node(const std::string& filename, const std::string& search,
                             const std::string& code);
        void store_place_node(const std::string& filename, const std::string& search,
                              const std::string& code);
        void reset_nodes();
        void reset_hood_nodes();
        void reset_place_nodes();
        void reset_hood();

        void store_block_door(block_number_t block_number, NodePath& door);
        void store_block_zone(block_number_t block_number, zone_id_t zone_id);
        void store_block_number(block_number_t block_number);
        void store_block_title(block_number_t block_number,
                               const std::string& title);
        void store_block_article(block_number_t block_number,
                                 const std::string& article);
        void store_block_building_type(block_number_t block_number,
                                       const std::string& bldg_type);
        void store_block_sign_transform(block_number_t block_number, LMatrix4f mat);
        void store_block(block_number_t block_number, const std::string& title,
                         const std::string& article, const std::string& bldg_type,
                         zone_id_t zone_id);

        size_t get_num_block_numbers();
        std::string get_block(const std::string& name);
        std::string get_block_building_type(block_number_t block_number);
        std::string get_title_from_block_number(block_number_t block_number);
        NodePath get_door_pos_hpr_from_block_number(block_number_t block_number);
        size_t get_block_number_at(size_t index);
        zone_id_t get_zone_from_block_number(block_number_t block_number);
        LMatrix4f get_sign_transform_from_block_number(block_number_t block_number);

        void reset_block_numbers();
        void reset_block_zones();

        PT(DNASuitEdge) store_suit_edge(point_index_t start_index, point_index_t end_index,
                                        zone_id_t zone_id);
        PT(DNASuitEdge) get_suit_edge(point_index_t start_index,
                                      point_index_t end_index);

        void store_suit_point(PT(DNASuitPoint) suit_point);
        PT(DNASuitPoint) get_suit_point_at_index(size_t index);
        PT(DNASuitPoint) get_suit_point_with_index(point_index_t index);
        size_t get_num_suit_points();
        void reset_suit_points();

        PT(DNASuitPath) get_suit_path(PT(DNASuitPoint) start_point,
                                      PT(DNASuitPoint) end_point,
                                      unsigned short min_path_len=40,
                                      unsigned short max_path_len=300);

        float get_suit_edge_travel_time(point_index_t start_index,
                                        point_index_t end_index,
                                        float suit_walk_speed);

        zone_id_t get_suit_edge_zone(point_index_t start_index,
                                     point_index_t end_index);
        PT(DNASuitPath) get_adjacent_points(PT(DNASuitPoint) point);
        bool discover_continuity();

        void write_pdna(Datagram& dg);
        void write_dna(std::ostream& out);

#ifndef CPPPARSER
    private:
        std::string _reverse_catalog_lookup(const std::string& code);
        void store_node_np(const std::string& code, nodedef_t& def);
        void get_adjacent_points(PT(DNASuitPoint) point, suit_point_vec_t& vec);

        suit_point_vec_t m_suit_points;
        visgroup_vec_t m_vis_groups;
        suit_edge_map_t m_suit_edges;
        nodes_t m_nodes;
        nodes_t m_hood_nodes;
        nodes_t m_place_nodes;
        font_map_t m_fonts;
        font_filename_map_t m_font_filenames;
        block_string_map_t m_block_titles;
        block_string_map_t m_block_articles;
        block_string_map_t m_block_building_types;
        door_vec_t m_block_doors;
        block_number_vec_t m_block_numbers;
        block_zone_vec_t m_block_zones;
        texture_map_t m_textures;
        catalog_codes_map_t m_catalog_codes;
        transform_map_t m_block_transforms;
#endif
};
#endif
