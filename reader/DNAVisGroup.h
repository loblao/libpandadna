#ifndef DNAVISGROUP_H
#define DNAVISGROUP_H

#include "dnabase.h"
#include "DNAGroup.h"

class EXPCL_PANDASKEL DNAVisGroup : public DNAGroup
{
	PUBLISHED:
		DNAVisGroup(string name);
		~DNAVisGroup(void);

		void add_suit_edge(DNASuitEdge edge);
		void add_battle_cell(DNABattleCell cell);
		void add_visible(string visible);

		size_t get_num_battle_cells();
		size_t get_num_suit_edges();
		size_t get_num_visibles();

		DNABattleCell get_battle_cell(size_t index);
		DNASuitEdge get_suit_edge(size_t index);
		string get_visible_name(size_t index);

		virtual DNAVisGroup* get_vis_group();

	public:
		void make_from_dgi(DatagramIterator& dgi, DNAStorage* store);
		virtual void traverse(NodePath& np, DNAStorage* store);

	private:
		battle_cell_vec_t m_cells;
		suit_edge_vec_t m_edges;
		strvec_t m_visibles;

};

#endif
