#ifndef DNAANIMPROP_H
#define DNAANIMPROP_H

#include "pandabase.h"
#include "DNAProp.h"

class EXPCL_PANDASKEL DNAAnimProp : public DNAProp
{
	PUBLISHED:
		DNAAnimProp(string name);
		~DNAAnimProp(void);

	public:
		void make_from_dgi(DatagramIterator& dgi, DNAStorage* store);
		virtual void traverse(NodePath& np, DNAStorage* store);

	protected:
		string m_anim_name;
};

#endif
