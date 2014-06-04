#ifndef DNADOOR_H
#define DNADOOR_H

#include "pandabase.h"
#include "DNAGroup.h"

class EXPCL_PANDASKEL DNADoor : public DNAGroup
{
	PUBLISHED:
		DNADoor(string name);
		~DNADoor(void);
};

#endif
