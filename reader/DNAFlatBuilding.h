#ifndef DNAFLATBUILDING_H
#define DNAFLATBUILDING_H

#include "pandabase.h"
#include "DNANode.h"

class EXPCL_PANDASKEL DNAFlatBuilding : public DNANode
{
	PUBLISHED:
		DNAFlatBuilding(string name);
		~DNAFlatBuilding(void);

	public:
		void make_from_dgi(DatagramIterator& dgi, DNAStorage* store);
		virtual void traverse(NodePath np, DNAStorage* store);
		static int current_wall_height;
	
	private:
		unsigned char m_width;
        bool m_has_door;
};

#endif
