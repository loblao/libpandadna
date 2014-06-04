#ifndef DNAWINDOWS_H
#define DNAWINDOWS_H

#include "pandabase.h"
#include "DNAGroup.h"

class EXPCL_PANDASKEL DNAWindows : public DNAGroup
{
	PUBLISHED:
		DNAWindows(string name);
		~DNAWindows(void);
};

#endif
