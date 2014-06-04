#ifndef DNASTREET_H
#define DNASTREET_H

#include "pandabase.h"
#include "DNANode.h"

class EXPCL_PANDASKEL DNAStreet : public DNANode
{
	PUBLISHED:
		DNAStreet(string name);
		~DNAStreet(void);
};

#endif
