#ifndef DNAANIMPROP_H
#define DNAANIMPROP_H

#include "pandabase.h"
#include "DNAProp.h"

class EXPCL_PANDASKEL DNAAnimProp : public DNAProp
{
	PUBLISHED:
		DNAAnimProp(string name);
		~DNAAnimProp(void);
};

#endif