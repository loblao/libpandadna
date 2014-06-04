#ifndef DNAINTERACTIVEPROP_H
#define DNAINTERACTIVEPROP_H

#include "pandabase.h"
#include "DNAAnimProp.h"

class EXPCL_PANDASKEL DNAInteractiveProp : public DNAAnimProp
{
	PUBLISHED:
		DNAInteractiveProp(string name);
		~DNAInteractiveProp(void);
};

#endif
