#ifndef DNAGROUP_H
#define DNAGROUP_H

#include "dnabase.h"
#include "DNAStorage.h"

class DNAGroup; // fwd decl
class DNAVisGroup; // fwd decl

typedef vector<DNAGroup*> comp_vec_t;

class EXPCL_PANDASKEL DNAGroup
{
	PUBLISHED:
		DNAGroup(string name);
		~DNAGroup(void);

		DNAVisGroup* get_vis_group();
		
		void add(DNAGroup* child);
		DNAGroup* at(size_t index);
		size_t get_num_children();
		
		void set_parent(DNAGroup* parent);
		void clear_parent();
		DNAGroup* get_parent();

		string get_name();

	public:
		void make_from_dgi(DatagramIterator& dgi, DNAStorage* store);

	protected:
		string m_name;
		comp_vec_t m_children;
		DNAGroup* m_parent;
		DNAVisGroup* m_vis_group;
};

#endif
