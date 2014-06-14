#ifndef DNAINTERACTIVEPROP_H
#define DNAINTERACTIVEPROP_H

#include "pandabase.h"
#include "DNAAnimProp.h"

class EXPCL_PANDASKEL DNAInteractiveProp : public DNAAnimProp
{
	PUBLISHED:
		DNAInteractiveProp(string name);
		~DNAInteractiveProp(void);

	public:
		void make_from_dgi(DatagramIterator& dgi, DNAStorage* store);

	private:
		short m_cell_id;
};

#endif