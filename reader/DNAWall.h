#ifndef DNAWALL_H
#define DNAWALL_H

#include "pandabase.h"
#include "DNANode.h"

class EXPCL_PANDASKEL DNAWall : public DNANode
{
	PUBLISHED:
		DNAWall(string name);
		~DNAWall(void);

	public:
		void make_from_dgi(DatagramIterator& dgi, DNAStorage* store);
		virtual void traverse(NodePath& np, DNAStorage* store);
		virtual bool is_wall();

	protected:
		string m_code;
		float m_height;
		LVector4f* m_color;
};

#endif
