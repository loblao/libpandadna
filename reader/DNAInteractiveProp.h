#ifndef DNAINTERACTIVEPROP_H
#define DNAINTERACTIVEPROP_H

#include "pandabase.h"
#include "DNAAnimProp.h"

class EXPCL_PANDASKEL DNAInteractiveProp : public DNAAnimProp
{
	PUBLISHED:
		DNAInteractiveProp(string name);
		~DNAInteractiveProp(void);

		void set_cell_id(short cell_id);
		short get_cell_id();

	public:
		void make_from_dgi(DatagramIterator& dgi, DNAStorage* store);
		virtual void traverse(NodePath& np, DNAStorage* store);

	private:
		short m_cell_id;
};

#endif
