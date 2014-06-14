#ifndef DNAANIMBUILDING_H
#define DNAANIMBUILDING_H

#include "pandabase.h"
#include "DNALandmarkBuilding.h"

class EXPCL_PANDASKEL DNAAnimBuilding : public DNALandmarkBuilding
{
	PUBLISHED:
		DNAAnimBuilding(string name);
		~DNAAnimBuilding(void);

		void set_anim(const string& anim_name);
		string get_anim();

	public:
		virtual void traverse(NodePath& np, DNAStorage* store);

	protected:
		string m_anim_name;
};

#endif
