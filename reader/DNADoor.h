#ifndef DNADOOR_H
#define DNADOOR_H

#include "pandabase.h"
#include "DNAGroup.h"

class EXPCL_PANDASKEL DNADoor : public DNAGroup
{
	PUBLISHED:
		DNADoor(string name);
		~DNADoor(void);

	public:
		void make_from_dgi(DatagramIterator& dgi, DNAStorage* store);
		virtual void traverse(NodePath& np, DNAStorage* store);

	protected:
		string m_code;
		LVector4f* m_color;
};

#endif
