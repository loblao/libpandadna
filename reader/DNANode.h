#ifndef DNANODE_H
#define DNANODE_H

#include "pandabase.h"
#include "DNAGroup.h"

class EXPCL_PANDASKEL DNANode : public DNAGroup
{
	PUBLISHED:
		DNANode(string name);
		~DNANode(void);

		void set_pos(LVector3f* pos);
		LVector3f* get_pos();

		void set_hpr(LVector3f* hpr);
		LVector3f* get_hpr();
		
		void set_scale(LVector3f* scale);
		LVector3f* get_scale();

	public:
		void make_from_dgi(DatagramIterator& dgi, DNAStorage* store);
		virtual void traverse(NodePath& np, DNAStorage* store);

	protected:
		LVector3f* m_pos;
		LVector3f* m_hpr;
		LVector3f* m_scale;
};

#endif
