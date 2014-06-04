#ifndef DNASIGN_H
#define DNASIGN_H

#include "pandabase.h"
#include "DNANode.h"

class EXPCL_PANDASKEL DNASign : public DNANode
{
	PUBLISHED:
		DNASign(string name);
		~DNASign(void);

	public:
		void make_from_dgi(DatagramIterator& dgi, DNAStorage* store);

	private:
		string m_code;
		LVector4f* m_color;
};

#endif
