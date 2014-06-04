#ifndef DNALANDMARKBUILDING_H
#define DNALANDMARKBUILDING_H

#include "pandabase.h"
#include "DNANode.h"

class EXPCL_PANDASKEL DNALandmarkBuilding : public DNANode
{
	PUBLISHED:
		DNALandmarkBuilding(string name);
		~DNALandmarkBuilding(void);
};

#endif
