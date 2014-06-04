#ifndef DNANODE_H
#define DNANODE_H

#include "pandabase.h"
#include "DNAGroup.h"

class EXPCL_PANDASKEL DNANode : public DNAGroup
{
	PUBLISHED:
		DNANode(string name);
		~DNANode(void);
};

#endif
