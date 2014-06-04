#ifndef DNANODE_H
#define DNANODE_H

#include "pandabase.h"
#include "DNAGroup.h"

class EXPCL_PANDASKEL DNANode : public DNAGroup
{
	PUBLISHED:
		DNANode(string name);
		~DNANode(void);

	public:
		void make_from_dgi(DatagramIterator& dgi, DNAStorage* store);

	private:
		LVector3f* m_pos;
		LVector3f* m_hpr;
		LVector3f* m_scale;
};

#endif
