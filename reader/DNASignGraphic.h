#ifndef DNASIGNGRAPHIC_H
#define DNASIGNGRAPHIC_H

#include "pandabase.h"
#include "DNANode.h"

class EXPCL_PANDASKEL DNASignGraphic : public DNANode
{
	PUBLISHED:
		DNASignGraphic(string name);
		~DNASignGraphic(void);
};

#endif