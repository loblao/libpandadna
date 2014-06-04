#ifndef DNAWALL_H
#define DNAWALL_H

#include "pandabase.h"
#include "DNANode.h"

class EXPCL_PANDASKEL DNAWall : public DNANode
{
	PUBLISHED:
		DNAWall(string name);
		~DNAWall(void);
};

#endif
