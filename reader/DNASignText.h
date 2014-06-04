#ifndef DNASIGNTEXT_H
#define DNASIGNTEXT_H

#include "pandabase.h"
#include "DNANode.h"

class EXPCL_PANDASKEL DNASignText : public DNANode
{
	PUBLISHED:
		DNASignText(string name);
		~DNASignText(void);
};

#endif
