#ifndef DNASIGNBASELINE_H
#define DNASIGNBASELINE_H

#include "pandabase.h"
#include "DNANode.h"

class EXPCL_PANDASKEL DNASignBaseline : public DNANode
{
	PUBLISHED:
		DNASignBaseline(string name);
		~DNASignBaseline(void);
};

#endif
