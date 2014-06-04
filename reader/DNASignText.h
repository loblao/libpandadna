#ifndef DNASIGNTEXT_H
#define DNASIGNTEXT_H

#include "pandabase.h"
#include "DNANode.h"

class EXPCL_PANDASKEL DNASignText : public DNANode
{
	PUBLISHED:
		DNASignText(string name);
		~DNASignText(void);

	public:
		void make_from_dgi(DatagramIterator& dgi, DNAStorage* store);

	private:
		string m_letters;
};

#endif
