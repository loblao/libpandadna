#ifndef _H_DNA_VISGROUP_
#define _H_DNA_VISGROUP_

#include "DNASuitEdge.h"
#include "DNABattleCell.h"
#include "DNAGroup.h"

typedef std::vector<std::string> visibles_vec_t;
typedef std::vector<PT(DNASuitEdge)> suit_edge_vec_t;
typedef std::vector<PT(DNABattleCell)> battle_cell_vec_t;

class EXPCL_DNA DNAVisGroup : public DNAGroup
{
    PUBLISHED:
        DNAVisGroup(const std::string& name);
        ~DNAVisGroup();

        void add_visible(const std::string& visible);
        bool remove_visible(const std::string& visible);
        size_t get_num_visibles();
        std::string get_visible(size_t index);
        INLINE std::string get_visible_name(size_t index)
        {
            return get_visible(index);
        }

        void add_suit_edge(PT(DNASuitEdge) edge);
        bool remove_suit_edge(PT(DNASuitEdge) edge);
        size_t get_num_suit_edges();
        PT(DNASuitEdge) get_suit_edge(size_t index);

        void add_battle_cell(PT(DNABattleCell) cell);
        bool remove_battle_cell(PT(DNABattleCell) cell);
        size_t get_num_battle_cells();
        PT(DNABattleCell) get_battle_cell(size_t index);

        WRITE_PDNA
        {
            DNAGroup::write_pdna(dg, false);

            dg.add_uint16(m_suit_edges.size());
            for (suit_edge_vec_t::iterator it = m_suit_edges.begin(); it != m_suit_edges.end(); ++it)
            {
                PT(DNASuitEdge) edge = *it;
                dg.add_uint16(edge->get_start_point()->get_index());
                dg.add_uint16(edge->get_end_point()->get_index());
            }

            dg.add_uint16(m_visibles.size());
            for (visibles_vec_t::iterator it = m_visibles.begin(); it != m_visibles.end(); ++it)
                dg.add_string(*it);

            dg.add_uint16(m_battle_cells.size());
            for (battle_cell_vec_t::iterator it = m_battle_cells.begin(); it != m_battle_cells.end(); ++it)
            {
                PT(DNABattleCell) cell = *it;
                dg.add_uint8(cell->get_width());
                dg.add_uint8(cell->get_height());

                dg.add_uint32(floor(cell->get_pos().get_x() * 100));
                dg.add_uint32(floor(cell->get_pos().get_y() * 100));
                dg.add_uint32(floor(cell->get_pos().get_z() * 100));
            }

            if (recursive)
                pack_children_pdna(dg);
        }

        WRITE_DNA
        {
            DNAGroup::write_dna(out, false, indent);
            indent += 1;

            if (m_visibles.size())
            {
                INDENTED_OUT << "vis [ ";
                for (visibles_vec_t::iterator it = m_visibles.begin(); it != m_visibles.end(); ++it)
                    out << "\"" << *it << "\" ";
                out << "]" << std::endl;
            }

            for (suit_edge_vec_t::iterator it = m_suit_edges.begin(); it != m_suit_edges.end(); ++it)
            {
                PT(DNASuitEdge) edge = *it;
                INDENTED_OUT << "suit_edge [ " << edge->get_start_point()->get_index() << " "
                             << edge->get_end_point()->get_index() << " ]" << std::endl;
            }

            for (battle_cell_vec_t::iterator it = m_battle_cells.begin(); it != m_battle_cells.end(); ++it)
            {
                PT(DNABattleCell) cell = *it;
                INDENTED_OUT << "battle_cell [ " << cell->get_width() << " " << cell->get_height()
                             << " " << cell->get_pos().get_x() << " " << cell->get_pos().get_y()
                             << " " << cell->get_pos().get_z() << " ]" << std::endl;
            }

            if (recursive)
                pack_children_dna(out, indent - 1);
        }

        COMP_CODE(COMPCODE_VISGROUP);
        COMP_NAME(visgroup);

    public:
        virtual void make_from_dgi(DatagramIterator& dgi, DNAStorage* store);
        virtual void traverse(NodePath& np, DNAStorage* store);

    protected:
        visibles_vec_t m_visibles;
        suit_edge_vec_t m_suit_edges;
        battle_cell_vec_t m_battle_cells;

    TYPE_HANDLE(DNAVisGroup, DNAGroup);
};

#endif
