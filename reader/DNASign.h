#ifndef DNASIGN_H
#define DNASIGN_H

#include "pandabase.h"
#include "DNANode.h"

class EXPCL_PANDASKEL DNASign : public DNANode
{
	PUBLISHED:
		DNASign(string name);
		~DNASign(void);
};

#endif
