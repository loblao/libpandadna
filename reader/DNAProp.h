#ifndef DNAPROP_H
#define DNAPROP_H

#include "pandabase.h"
#include "DNANode.h"

class EXPCL_PANDASKEL DNAProp : public DNANode
{
	PUBLISHED:
		DNAProp(string name);
		~DNAProp(void);

	public:
		void make_from_dgi(DatagramIterator& dgi, DNAStorage* store);

	private:
		string m_code;
		LVector4f* m_color;
};

#endif
